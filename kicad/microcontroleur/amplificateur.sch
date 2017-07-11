EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:amplificateur-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Module mesure de la température"
Date "31 aug 2015"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DIL14 U1
U 1 1 54D2005E
P 4950 3650
F 0 "U1" H 4950 4050 60  0000 C CNN
F 1 "DIL14" V 4950 3650 50  0000 C CNN
F 2 "" H 4950 3650 60  0000 C CNN
F 3 "http://www.farnell.com/datasheets/20524.pdf" H 4950 3650 60  0001 C CNN
F 4 "Analog Device" H 4950 3650 60  0001 C CNN "Constructeur"
F 5 "AD595" H 4950 3650 60  0001 C CNN "Ref_c"
F 6 "Farnell" H 4950 3650 60  0001 C CNN "Fournisseur"
F 7 "409194" H 4950 3650 60  0001 C CNN "Ref_f"
F 8 "Channel thermocouple amplifier" H 4950 3650 60  0001 C CNN "Désignation"
	1    4950 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 54D20500
P 4250 2450
F 0 "P1" V 4200 2450 40  0000 C CNN
F 1 "CONN_2" V 4300 2450 40  0000 C CNN
F 2 "Diamètre de perçage 1.3 mm" H 4250 2450 60  0001 C CNN
F 3 "https://www.gotronic.fr/art-bornier-sc02-2-54-15468.htm" H 4250 2450 60  0001 C CNN
F 4 "?" V 4250 2450 60  0001 C CNN "Constructeur"
F 5 "?" V 4250 2450 60  0001 C CNN "Ref_c"
F 6 "GOTRONIC" V 4250 2450 60  0001 C CNN "Fournisseur"
F 7 "48930" V 4250 2450 60  0001 C CNN "Ref_f"
F 8 "Bornier SC02/2.54 - 2 contacts - 2.54" V 4250 2450 60  0001 C CNN "Désignation"
	1    4250 2450
	-1   0    0    1   
$EndComp
Connection ~ 4600 3950
Connection ~ 4600 3650
Connection ~ 4600 3350
Connection ~ 5300 3350
Connection ~ 5300 3650
Connection ~ 5300 3450
Wire Wire Line
	5300 3450 5400 3450
Wire Wire Line
	5400 3450 5400 4500
Connection ~ 5400 4500
Connection ~ 5300 3950
Connection ~ 5300 3850
Connection ~ 5300 3550
$Comp
L R R1
U 1 1 54D352D8
P 5500 3050
F 0 "R1" V 5500 2950 40  0000 C CNN
F 1 "20K" V 5500 3100 40  0000 C CNN
F 2 "~" V 5430 3050 30  0000 C CNN
F 3 "http://www.farnell.com/datasheets/1497270.pdf" H 5500 3050 30  0001 C CNN
F 4 "Farnell" V 5500 3050 60  0001 C CNN "Fournisseur"
F 5 "1751583" V 5500 3050 60  0001 C CNN "Ref_f"
F 6 "http://fr.farnell.com/te-connectivity-holsworthy/h820kbya/resistance-0-25w-0-1-20k/dp/1751583?Ntt=1751583" V 5500 3050 60  0001 C CNN "Lien"
	1    5500 3050
	1    0    0    -1  
$EndComp
Connection ~ 5500 3300
Wire Wire Line
	5500 2800 5500 2750
Connection ~ 5500 2750
Connection ~ 5500 2800
Wire Wire Line
	6050 3400 6050 3950
Wire Wire Line
	6050 3950 5300 3950
Wire Wire Line
	5300 3950 5300 3850
Wire Wire Line
	5300 3650 5550 3650
Wire Wire Line
	5350 3650 5350 2750
Wire Wire Line
	5300 3550 5500 3550
Wire Wire Line
	5500 3550 5500 3300
Wire Wire Line
	4550 3350 4550 4500
Wire Wire Line
	4550 3950 4600 3950
Wire Wire Line
	4600 3650 4550 3650
Connection ~ 4550 4500
Connection ~ 4550 3950
Connection ~ 5300 3750
Connection ~ 4600 3450
Connection ~ 4600 3550
Connection ~ 4600 3750
Connection ~ 4600 3850
Wire Wire Line
	4550 4500 7600 4500
$Comp
L R R3
U 1 1 54ED9350
P 5300 2800
F 0 "R3" V 5200 2800 40  0000 C CNN
F 1 "10k" V 5307 2801 40  0000 C CNN
F 2 "~" V 5230 2800 30  0000 C CNN
F 3 "~" H 5300 2800 30  0000 C CNN
	1    5300 2800
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54ED93F6
P 4600 2800
F 0 "R2" V 4680 2800 40  0000 C CNN
F 1 "R 10k" V 4607 2801 40  0000 C CNN
F 2 "~" V 4530 2800 30  0000 C CNN
F 3 "~" H 4600 2800 30  0000 C CNN
	1    4600 2800
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 54EDA22C
P 4950 3050
F 0 "C2" H 4950 3150 40  0000 L CNN
F 1 "C" H 4956 2965 40  0000 L CNN
F 2 "~" H 4988 2900 30  0000 C CNN
F 3 "~" H 4950 3050 60  0000 C CNN
	1    4950 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 3350 4550 3350
Connection ~ 4550 3650
$Comp
L C C4
U 1 1 54EDA33E
P 5700 3550
F 0 "C4" H 5700 3650 40  0000 L CNN
F 1 "C 10 microF" V 5850 3350 40  0000 L CNN
F 2 "~" H 5738 3400 30  0000 C CNN
F 3 "~" H 5700 3550 60  0000 C CNN
	1    5700 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3750 5300 3750
Wire Wire Line
	5700 3350 5350 3350
Connection ~ 5350 3350
Connection ~ 5700 3350
Connection ~ 5700 3750
$Comp
L C C3
U 1 1 54EDA57A
P 5550 4200
F 0 "C3" H 5550 4300 40  0000 L CNN
F 1 "0,1 microF" H 5556 4115 40  0000 L CNN
F 2 "~" H 5588 4050 30  0000 C CNN
F 3 "~" H 5550 4200 60  0000 C CNN
	1    5550 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3650 5550 4000
Connection ~ 5350 3650
Wire Wire Line
	5550 4400 5550 4500
Connection ~ 5550 4500
Connection ~ 5550 4400
Connection ~ 5550 4000
Wire Wire Line
	5300 3050 5300 3350
Wire Wire Line
	5150 3050 5300 3050
Wire Wire Line
	4600 3050 4750 3050
Wire Wire Line
	4600 3050 4600 3350
Wire Wire Line
	4600 2350 5300 2350
Wire Wire Line
	5300 2350 5300 2550
Connection ~ 5300 2550
Connection ~ 4600 2550
Connection ~ 4600 2350
Connection ~ 4600 3050
Connection ~ 5300 3050
$Comp
L CONN_1 P2
U 1 1 54EDF5C6
P 5800 3100
F 0 "P2" H 5750 3200 40  0000 L CNN
F 1 "CONN_1" H 5800 3155 30  0001 C CNN
F 2 "" H 5800 3100 60  0000 C CNN
F 3 "" H 5800 3100 60  0000 C CNN
	1    5800 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3300 5650 3300
Wire Wire Line
	5650 3300 5650 3100
Connection ~ 5650 3100
$EndSCHEMATC
