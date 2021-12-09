EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Liaison filaire entre e-p-wifi et e-r-wifi"
Date "2021-11-04"
Rev "A"
Comp "A3C Presqu'île"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Transistor_BJT:2N2219 Q1
U 1 1 61867581
P 1400 3100
F 0 "Q1" H 1591 3054 50  0000 L CNN
F 1 "2N2222A" H 1150 2950 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-18-3" H 1600 3025 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 1400 3100 50  0001 L CNN
	1    1400 3100
	1    0    0    1   
$EndComp
Wire Wire Line
	1500 3300 1500 3450
$Comp
L power:GND #PWR01
U 1 1 6186C193
P 1500 3650
F 0 "#PWR01" H 1500 3400 50  0001 C CNN
F 1 "GND" H 1505 3477 50  0000 C CNN
F 2 "" H 1500 3650 50  0001 C CNN
F 3 "" H 1500 3650 50  0001 C CNN
	1    1500 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6186CABE
P 1050 3100
F 0 "R1" V 950 3100 50  0000 C CNN
F 1 "470" V 1050 3100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 980 3100 50  0001 C CNN
F 3 "~" H 1050 3100 50  0001 C CNN
	1    1050 3100
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 6186FCF3
P 700 3100
F 0 "J1" H 618 2875 50  0000 C CNN
F 1 "Speaker" H 618 2966 50  0000 C CNN
F 2 "e-p-wifi-lf:pastille" H 700 3100 50  0001 C CNN
F 3 "~" H 700 3100 50  0001 C CNN
	1    700  3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	1500 3650 1500 3550
$Comp
L power:GND #PWR02
U 1 1 618F15D5
P 3450 2950
F 0 "#PWR02" H 3450 2700 50  0001 C CNN
F 1 "GND" V 3455 2822 50  0000 R CNN
F 2 "" H 3450 2950 50  0001 C CNN
F 3 "" H 3450 2950 50  0001 C CNN
	1    3450 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 61941CBE
P 1500 2750
F 0 "R2" V 1400 2750 50  0000 C CNN
F 1 "0" V 1500 2750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1430 2750 50  0001 C CNN
F 3 "~" H 1500 2750 50  0001 C CNN
	1    1500 2750
	-1   0    0    1   
$EndComp
$Comp
L New_Library:liaison_filaire J2
U 1 1 619CEFF3
P 1800 2150
F 0 "J2" V 1804 2530 50  0000 L CNN
F 1 "liaison_filaire" V 1895 2530 50  0000 L CNN
F 2 "e-p-wifi-lf:PinHeader_1x08" H 1800 2150 50  0001 C CNN
F 3 "~" H 1800 2150 50  0001 C CNN
	1    1800 2150
	0    1    1    0   
$EndComp
NoConn ~ 2100 1950
NoConn ~ 2000 1950
NoConn ~ 1900 1950
NoConn ~ 1800 1950
NoConn ~ 1600 1950
NoConn ~ 2000 2450
NoConn ~ 1600 2450
NoConn ~ 1500 2450
NoConn ~ 1400 2450
Wire Wire Line
	1400 1950 1400 1750
Wire Wire Line
	1500 1800 1500 1950
Wire Wire Line
	1700 1950 1700 1850
Wire Wire Line
	1800 2450 1800 2550
Wire Wire Line
	1700 2700 1700 2450
$Comp
L e-p-wifi-cache:Device_Speaker LS1
U 1 1 619E030B
P 1700 3450
F 0 "LS1" H 1870 3446 50  0000 L CNN
F 1 "Device_Speaker" H 1870 3355 50  0000 L CNN
F 2 "e-p-wifi:mini_speaker" H 1700 3250 50  0001 C CNN
F 3 "" H 1690 3400 50  0001 C CNN
	1    1700 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2600 1900 2600
Wire Wire Line
	3450 1750 3800 1750
Wire Wire Line
	3800 1750 3800 2850
Wire Wire Line
	3450 2850 3800 2850
Connection ~ 3450 2850
$Comp
L e-p-wifi-lf-rescue:RJ45-e-p-wifi-cache-e-p-wifi-lf-rescue J3
U 1 1 619D99D4
P 3450 2250
F 0 "J3" H 3120 2254 50  0000 R CNN
F 1 "RJ45" H 3120 2345 50  0000 R CNN
F 2 "e-p-wifi-lf:RJ45" V 3450 2275 50  0001 C CNN
F 3 "" V 3450 2275 50  0001 C CNN
	1    3450 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3450 2950 3450 2850
Wire Wire Line
	1900 2450 1900 2600
Wire Wire Line
	3050 2450 2800 2450
Wire Wire Line
	2800 2450 2800 1750
Wire Wire Line
	2800 1750 1400 1750
Wire Wire Line
	1500 1800 2750 1800
Wire Wire Line
	2750 1800 2750 2650
Wire Wire Line
	2750 2650 3050 2650
Wire Wire Line
	1700 1850 2700 1850
Wire Wire Line
	2700 1850 2700 2550
Wire Wire Line
	2700 2550 3050 2550
Wire Wire Line
	2100 2450 2650 2450
Wire Wire Line
	2650 2450 2650 2350
Wire Wire Line
	2650 2350 3050 2350
Wire Wire Line
	2550 2600 1900 2600
Connection ~ 1900 2600
Wire Wire Line
	3050 2150 3000 2150
Wire Wire Line
	3000 2150 3000 2000
Wire Wire Line
	3000 1950 3050 1950
Wire Wire Line
	1800 2550 2500 2550
Wire Wire Line
	2500 2550 2500 2000
Wire Wire Line
	2500 2000 3000 2000
Connection ~ 3000 2000
Wire Wire Line
	3000 2000 3000 1950
Wire Wire Line
	2600 2700 1700 2700
Wire Wire Line
	2500 2850 2500 2550
Wire Wire Line
	2500 2850 3450 2850
Connection ~ 2500 2550
Wire Wire Line
	3050 2250 2600 2250
Wire Wire Line
	2600 2250 2600 2700
Wire Wire Line
	3050 2050 2550 2050
Wire Wire Line
	2550 2050 2550 2600
$EndSCHEMATC
