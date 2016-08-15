#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: AlertMiBand.py
#      Author: Zhao Yanbai
#              2016-08-07 19:15:05 Sunday CST
# Description: none
# ------------------------------------------------------------------------

import os
import re
import sys
import time
import thread
import random
import logging
import binascii
import subprocess
import datetime
from bluepy.btle import Scanner, DefaultDelegate
import bluepy.btle as btle
import mibanda



SELF_MI_MAC = "C8:0F:10:6A:B1:F0"

def stdoutencode(data):
    retVal = None

    try:
        data = data or ""

        # Reference: http://bugs.python.org/issue1602
        if IS_WIN:
            output = data.encode(sys.stdout.encoding, "replace")

            if '?' in output and '?' not in data:
                warnMsg = "cannot properly display Unicode characters "
                warnMsg += "inside Windows OS command prompt "
                warnMsg += "(http://bugs.python.org/issue1602). All "
                warnMsg += "unhandled occurances will result in "
                warnMsg += "replacement with '?' character. Please, find "
                warnMsg += "proper character representation inside "
                warnMsg += "corresponding output files. "
                singleTimeWarnMessage(warnMsg)

            retVal = output
        else:
            retVal = data.encode(sys.stdout.encoding)
    except:
        retVal = data.encode(UNICODE_ENCODING) if isinstance(data, unicode) else data

    return retVal

class ColorizingStreamHandler(logging.StreamHandler):
    # color names to indices
    color_map = {
        'black': 0,
        'red': 1,
        'green': 2,
        'yellow': 3,
        'blue': 4,
        'magenta': 5,
        'cyan': 6,
        'white': 7,
    }

    # levels to (background, foreground, bold/intense)
    level_map = {
        logging.DEBUG: (None, 'blue', False),
        logging.INFO: (None, 'green', False),
        logging.WARNING: (None, 'yellow', False),
        logging.ERROR: (None, 'red', False),
        logging.CRITICAL: ('red', 'white', False)
    }
    csi = '\x1b['
    reset = '\x1b[0m'
    disable_coloring = False

    @property
    def is_tty(self):
        isatty = getattr(self.stream, 'isatty', None)
        return isatty and isatty() and not self.disable_coloring

    def emit(self, record):
        try:
            message = stdoutencode(self.format(record))
            stream = self.stream

            if not self.is_tty:
                if message and message[0] == "\r":
                    message = message[1:]
                stream.write(message)
            else:
                self.output_colorized(message)
            stream.write(getattr(self, 'terminator', '\n'))

            self.flush()
        except (KeyboardInterrupt, SystemExit):
            raise
        except IOError:
            pass
        except:
            self.handleError(record)

    if not subprocess.mswindows:
        def output_colorized(self, message):
            self.stream.write(message)
    else:
        ansi_esc = re.compile(r'\x1b\[((?:\d+)(?:;(?:\d+))*)m')

        nt_color_map = {
            0: 0x00,    # black
            1: 0x04,    # red
            2: 0x02,    # green
            3: 0x06,    # yellow
            4: 0x01,    # blue
            5: 0x05,    # magenta
            6: 0x03,    # cyan
            7: 0x07,    # white
        }

        def output_colorized(self, message):
            parts = self.ansi_esc.split(message)
            write = self.stream.write
            h = None
            fd = getattr(self.stream, 'fileno', None)

            if fd is not None:
                fd = fd()

                if fd in (1, 2): # stdout or stderr
                    h = ctypes.windll.kernel32.GetStdHandle(-10 - fd)

            while parts:
                text = parts.pop(0)

                if text:
                    write(text)

                if parts:
                    params = parts.pop(0)

                    if h is not None:
                        params = [int(p) for p in params.split(';')]
                        color = 0

                        for p in params:
                            if 40 <= p <= 47:
                                color |= self.nt_color_map[p - 40] << 4
                            elif 30 <= p <= 37:
                                color |= self.nt_color_map[p - 30]
                            elif p == 1:
                                color |= 0x08 # foreground intensity on
                            elif p == 0: # reset to default color
                                color = 0x07
                            else:
                                pass # error condition ignored

                        ctypes.windll.kernel32.SetConsoleTextAttribute(h, color)

    def colorize(self, message, record):
        if record.levelno in self.level_map and self.is_tty:
            bg, fg, bold = self.level_map[record.levelno]
            params = []

            if bg in self.color_map:
                params.append(str(self.color_map[bg] + 40))

            if fg in self.color_map:
                params.append(str(self.color_map[fg] + 30))

            if bold:
                params.append('1')

            if params and message:
                if message.lstrip() != message:
                    prefix = re.search(r"\s+", message).group(0)
                    message = message[len(prefix):]
                else:
                    prefix = ""

                message = "%s%s" % (prefix, ''.join((self.csi, ';'.join(params),
                                   'm', message, self.reset)))

        return message

    def format(self, record):
        message = logging.StreamHandler.format(self, record)
        return self.colorize(message, record)


class CUSTOM_LOGGING :
    IMPT    = 2
    INFO    = 3
    ERR     = 1


logging.addLevelName(CUSTOM_LOGGING.IMPT, "IMPT")
logging.addLevelName(CUSTOM_LOGGING.INFO, "INFO")
logging.addLevelName(CUSTOM_LOGGING.ERR,  "ERR")

LOGGER = logging.getLogger("AlertMiBandLog")
LOGGER_HANDLER = None
try:
    disableColor = False

    for argument in sys.argv:
        if "disable-col" in argument:
            disableColor = True
            break

    if disableColor:
        LOGGER_HANDLER = logging.StreamHandler(sys.stdout)
    else:
        LOGGER_HANDLER = ColorizingStreamHandler(sys.stdout)
        LOGGER_HANDLER.level_map[logging.getLevelName("IMPT")] = (None, "cyan", False)
        LOGGER_HANDLER.level_map[logging.getLevelName("INFO")] = (None, "magenta", False)
        LOGGER_HANDLER.level_map[logging.getLevelName("ERR")] = ("magenta", None, False)
except ImportError:
    LOGGER_HANDLER = logging.StreamHandler(sys.stdout)


LOGGER_HANDLER = logging.StreamHandler(sys.stdout)
#LOGGER_HANDLER = logging.FileHandler('/root/AlertMiBand.{0}.log'.format(datetime.date.today().strftime('%Y%m%d')))
FORMATTER = logging.Formatter("\r[%(asctime)s] [%(levelname)s] %(message)s", "%H:%M:%S")

LOGGER_HANDLER.setFormatter(FORMATTER)
LOGGER.addHandler(LOGGER_HANDLER)
LOGGER.setLevel(logging.INFO)

logger = LOGGER

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self, dev, isNewDev, isNewData):
        if isNewDev:
            logger.info("Discovered device {0}".format(dev.addr))
        elif isNewData:
            logger.info("Received new data from {0} ".format(dev.addr))


alert_lock = thread.allocate_lock()


def GetNewDevInfo(addr) :
    addr = str(addr)
    alert_lock.acquire()
    try :
        device = mibanda.BandDevice(addr, "MI")
        device.connect()
        logger.info("Name: {0} Address:{1} Steps: {2}".format(device.getName(), device.getAddress(), device.getSteps()))
        bi = device.getBatteryInfo()
        di = device.getDeviceInfo()
        logger.info("BatteryInfo. Status:{0} Level:{1} Charge Counter:{2} Last Charge:{3} DeviceInfo {4}".format(bi.status, bi.level, bi.charge_counter, bi.last_charged, di.firmware_version))
        device.setUserInfo(27182818+random.randint(0, 100), True, 25, 123, 45, 0, "Ace")
        t= datetime.datetime.now() + datetime.timedelta(seconds=100)
        device.setAlarm(enable=1, number=0, when=t, smart=0, repeat=0)

        alert_lock.release()
    except Exception, e:
        logger.info("Failed to Get New Device Info {0} Error {1}".format(addr, e))
        alert_lock.release()
        return False


    return True

def AlertDevice(addr, level, msg) :
    if level < 0 :
        level = 0
    if level > 2 :
        level = 2

    alert_lock.acquire()
    logger.info("To Alert Device {0} level {1} [ {2} ]".format(addr, level, msg))
    try :
        p = btle.Peripheral(addr, btle.ADDR_TYPE_PUBLIC, 0)
        Characteristics = p.getCharacteristics()
        for c in Characteristics :
            if c.uuid.getCommonName() == 'Alert Level' :
                c.write(binascii.a2b_hex("{0:02}".format(level)))

        p.disconnect()
        logger.info("Alerted Device {0} [ {1} ]".format(addr, msg))
        alert_lock.release()
    except Exception, e:
        logger.info("Failed to Alert Device {0} Error {1} [ {2} ]".format(addr, e, msg))
        alert_lock.release()
        return False


    return True

def NotifySelf(level, msg="") :
    AlertDevice(SELF_MI_MAC, level, msg)

lock = thread.allocate_lock()
num = 0
mi_macs = set()

def ThreadFunc(name) :
    global num
    global logger
    global mi_macs
    while True :
        time.sleep(1)

        lock.acquire()
        alert_macs = list(mi_macs)
        lock.release()

        if len(alert_macs) == 0 :
            logger.info("{0}".format(str(mi_macs)))
            logger.info("Device Set Empty")
            continue

        logger.info(">ALERT THREAD TODO LIST {0}".format(str(alert_macs)))

        for m in alert_macs :
            if not AlertDevice(m, 2, "Hack") :
                lock.acquire()
                #mi_macs.remove(m)
                lock.release()


    print "AlertThread Exit"
    sys.exit(0)


def ScanMiBandThread(d) :
    global mi_macs
    global lock
    while True :
        try :
            scanner = Scanner().withDelegate(ScanDelegate())
            devices = scanner.scan(3.0)
        except Exception, e :
            logger.info("Scan Failed {0}".format(e))
            time.sleep(1)
            continue

        for dev in devices:
            devAddr = dev.addr.upper();

            if devAddr == SELF_MI_MAC :
                print ">>>>>>>>>>>>>>>>>>> {0} ".format(devAddr)
                continue

            if devAddr != '88:0F:10:50:BE:3E' :
                #continue
                pass

            if devAddr not in mi_macs :
                logger.info("Discoveryed New Device {0} ({1}), RSSI={2} dB".format(devAddr, dev.addrType, dev.rssi))

                bIsMiBand = False
                for (adtype, desc, value) in dev.getScanData():
                    logger.info("  {0} = {1} ".format(desc, value))
                    if 'Complete Local Name' == desc and 'MI' in value :
                        bIsMiBand = True

                if not bIsMiBand :
                    logger.info("Not MiBand Device")
                    continue

                NotifySelf(1, "Notify New Device {0}".format(devAddr))

                lock.acquire()
                print("------------------------- Add New Device {0}".format(devAddr))
                mi_macs.add(devAddr)
                lock.release()
                time.sleep(5)


            else :
                logger.info("Skip Old Device {0} ({1}), RSSI={2} dB".format(devAddr, dev.addrType, dev.rssi))

        time.sleep(1)

def main() :
    global logger
    global mi_macs

    logger.info("Alert Tool is Running")
    thread.start_new_thread(ScanMiBandThread, ('ThreadA', ))
    thread.start_new_thread(ThreadFunc, ('ThreadB', ))


    mi_infos = { }

    i = 0
    while True :
        i += 1
        if i == 1 :
            NotifySelf(2, "Program Started")

        time.sleep(1)
        lock.acquire()
        macs = list(mi_macs)
        lock.release()

        print("MI INFO THREAD {0}".format(str(mi_infos)))   
        for m in macs :
            if mi_infos.get(m, None) == None :
                #if GetNewDevInfo('88:0F:10:50:BE:3E') :
                if GetNewDevInfo(m) :
                    mi_infos[m] = 'Handled'

if __name__ == "__main__" :
    main()
