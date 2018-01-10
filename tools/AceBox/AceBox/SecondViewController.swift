//
//  SecondViewController.swift
//  AceBox
//
//  Created by Ace on 4/30/15.
//  Copyright (c) 2015 Ace. All rights reserved.
//

import UIKit
import CoreLocation

class SecondViewController: UIViewController, CLLocationManagerDelegate {
    
    var locationMgr:CLLocationManager!
    var cnt:Int = 0
    var labelGPS:UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        //view.backgroundColor = UIColor.blueColor()
        view.backgroundColor = UIColor(red: 0, green: 0.47843137250000001, blue: 1, alpha: 1)
        
        locationMgr = CLLocationManager()
        locationMgr.desiredAccuracy = kCLLocationAccuracyBestForNavigation
        if #available(iOS 9.0, *) {
            locationMgr.allowsBackgroundLocationUpdates = true
        }
        locationMgr.pausesLocationUpdatesAutomatically = false
        
        //locationMgr.distanceFilter = 50
        
        locationMgr.requestAlwaysAuthorization()
        
        locationMgr.delegate = self
        
        if CLLocationManager.locationServicesEnabled() {
            locationMgr.startUpdatingLocation()
        } else {
            print("no location service")
        }
        
        labelGPS = UILabel(frame: CGRect(x: 10, y: 20, width: 300, height: 100))
        labelGPS.text = "searching"
        labelGPS.textColor = UIColor.white
        labelGPS.numberOfLines = 3
        self.view.addSubview(labelGPS)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print(error)
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        if locations.count > 0 {
            let locationInfo  = locations.last!
            
            let msg = "次数:\(cnt)\n经度:\(locationInfo.coordinate.longitude)\n纬度:\(locationInfo.coordinate.latitude)"
            
            cnt += 1
            
            //let alert:UIAlertView = UIAlertView(title:"Get Location", message:msg, delegate:nil, cancelButtonTitle:"Yes")
            //alert.show()
            
            print(msg)
            
            labelGPS.text = msg
            /*
            let fileManager = FileManager.default
            let filePath:String = NSHomeDirectory() + "/Documents/gps.data"
            let exist = fileManager.fileExists(atPath: filePath)
            if exist {
                print("exist \(filePath)")
                let data = "\(cnt) \(locationInfo.coordinate.longitude) \(locationInfo.coordinate.latitude)\n"
                //try! data.write(toFile: filePath, atomically: true, encoding: String.Encoding.utf8)
            
                let writeHandler = try? FileHandle(forWritingAtPath: filePath)
                writeHandler!?.seekToEndOfFile()
                writeHandler!?.write(data.data(using: String.Encoding.utf8, allowLossyConversion: true)!)
                
                let rd = fileManager.contents(atPath: filePath)
                print("content: \(String(data:rd!, encoding: String.Encoding.utf8))")
            } else {
                print(NSHomeDirectory())
                try! fileManager.createDirectory(atPath: NSHomeDirectory()+"/Documents/",
                                                 withIntermediateDirectories: true, attributes: nil)
                let createSuccess = fileManager.createFile(atPath: filePath, contents: nil, attributes: nil)
                print("create file \(filePath) return \(createSuccess)")
            }*/
        }
    }


}

