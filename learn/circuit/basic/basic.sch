EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R?
U 1 1 5CF46E84
P 2350 1650
F 0 "R?" V 2143 1650 50  0000 C CNN
F 1 "4.7K" V 2234 1650 50  0000 C CNN
F 2 "" V 2280 1650 50  0001 C CNN
F 3 "~" H 2350 1650 50  0001 C CNN
	1    2350 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5CF47D6C
P 2350 2300
F 0 "R?" V 2143 2300 50  0000 C CNN
F 1 "1K" V 2234 2300 50  0000 C CNN
F 2 "" V 2280 2300 50  0001 C CNN
F 3 "~" H 2350 2300 50  0001 C CNN
	1    2350 2300
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5CF4820F
P 3500 1650
F 0 "C?" V 3248 1650 50  0000 C CNN
F 1 "104pF" V 3339 1650 50  0000 C CNN
F 2 "" H 3538 1500 50  0001 C CNN
F 3 "~" H 3500 1650 50  0001 C CNN
	1    3500 1650
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5CF48B55
P 4450 2300
F 0 "#PWR?" H 4450 2150 50  0001 C CNN
F 1 "+3V3" V 4465 2428 50  0000 L CNN
F 2 "" H 4450 2300 50  0001 C CNN
F 3 "" H 4450 2300 50  0001 C CNN
	1    4450 2300
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5CF49CDA
P 1150 1650
F 0 "#PWR?" H 1150 1400 50  0001 C CNN
F 1 "Earth" H 1150 1500 50  0001 C CNN
F 2 "" H 1150 1650 50  0001 C CNN
F 3 "~" H 1150 1650 50  0001 C CNN
	1    1150 1650
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5CF4C6BB
P 3500 2300
F 0 "SW?" H 3500 2585 50  0000 C CNN
F 1 "SW_Push" H 3500 2494 50  0000 C CNN
F 2 "" H 3500 2500 50  0001 C CNN
F 3 "~" H 3500 2500 50  0001 C CNN
	1    3500 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2300 2850 2300
Wire Wire Line
	3700 2300 4100 2300
Wire Wire Line
	2500 1650 2850 1650
Wire Wire Line
	3650 1650 4100 1650
Wire Wire Line
	4100 1650 4100 2300
Connection ~ 4100 2300
Wire Wire Line
	4100 2300 4450 2300
Wire Wire Line
	2850 1650 2850 2300
Connection ~ 2850 1650
Wire Wire Line
	2850 1650 3350 1650
Connection ~ 2850 2300
Wire Wire Line
	2850 2300 3300 2300
Wire Wire Line
	1150 1650 2200 1650
Text Label 1050 2300 0    50   ~ 0
INPUT
Wire Wire Line
	1050 2300 2200 2300
Wire Notes Line
	700  1100 4950 1100
Wire Notes Line
	4950 1100 4950 2500
Wire Notes Line
	4950 2500 700  2500
Wire Notes Line
	700  2500 700  1100
Text Notes 1050 1250 0    50   ~ 0
Hardware debounce circuit
$EndSCHEMATC