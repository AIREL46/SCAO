EESchema Schematic File Version 5
EELAYER 36 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "e-rupteur wifi - Carte cde relais"
Date "2020-11-12"
Rev "A"
Comp "A3C presqu'île"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Wire Wire Line
	2800 2200 2800 2100
Wire Wire Line
	2800 2600 4300 2600
Wire Wire Line
	2800 2700 4500 2700
Wire Wire Line
	2800 2800 4500 2800
Wire Wire Line
	3100 2200 2800 2200
Wire Wire Line
	3700 1350 2800 1350
Wire Wire Line
	3700 1350 3700 1800
Wire Wire Line
	4300 2600 4300 2000
Wire Wire Line
	4450 1800 4300 1800
Wire Wire Line
	4450 2600 4450 1800
Wire Wire Line
	4500 2600 4450 2600
Wire Wire Line
	5855 2000 5855 2002
Text Notes 2100 2000 0    25   ~ 0
D8 (MKR wifi 1010)
Text Notes 2100 2100 0    25   ~ 0
GND (MKR wifi 1010)
Text Notes 3400 2600 0    50   ~ 0
Phase
Text Notes 3400 2700 0    50   ~ 0
Neutre
Text Notes 3400 2800 0    50   ~ 0
Terre
Text Notes 3850 2000 1    25   ~ 0
440 Ohms
$Comp
L e-r-wifi-rescue:GND-power #PWR01
U 1 1 5FAEC963
P 2800 1450
F 0 "#PWR01" H 2800 1200 50  0001 C CNN
F 1 "GND" H 2805 1277 50  0000 C CNN
F 2 "" H 2800 1450 50  0001 C CNN
F 3 "" H 2800 1450 50  0001 C CNN
	1    2800 1450
	1    0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:GND-power #PWR02
U 1 1 5FAECE51
P 3700 2200
F 0 "#PWR02" H 3700 1950 50  0001 C CNN
F 1 "GND" H 3705 2027 50  0000 C CNN
F 2 "" H 3700 2200 50  0001 C CNN
F 3 "" H 3700 2200 50  0001 C CNN
	1    3700 2200
	1    0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:LED-Device D1
U 1 1 5FAED66A
P 2950 2000
F 0 "D1" H 2943 2217 50  0000 C CNN
F 1 "LED " H 2943 2126 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P2.54mm_Vertical_AnodeUp" H 2950 2000 50  0001 C CNN
F 3 "https://asset.conrad.com/media10/add/160267/c1/-/en/000180129DS01/fiche-technique-180129-led-3-mm-jaune-kingbright-l-7104yd-l-7104yd-rond-15-mcd-40-20-ma-21-v-1-pcs.pdf" H 2950 2000 50  0001 C CNN
	1    2950 2000
	-1   0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:Conn_01x02-Connector_Generic J4
U 1 1 5FAE6DEE
P 2600 1350
F 0 "J4" H 2600 1550 50  0000 C CNN
F 1 "5V" H 2600 1450 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2600 1350 50  0001 C CNN
F 3 "~" H 2600 1350 50  0001 C CNN
	1    2600 1350
	-1   0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:Conn_01x02-Connector_Generic J3
U 1 1 5FAE24A2
P 2600 2000
F 0 "J3" H 2600 2200 50  0000 C CNN
F 1 "cde relais Celduc" H 2750 2100 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2600 2000 50  0001 C CNN
F 3 "~" H 2600 2000 50  0001 C CNN
	1    2600 2000
	-1   0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:Conn_01x03-Connector_Generic J1
U 1 1 5FACCECA
P 2600 2700
F 0 "J1" H 2518 3017 50  0000 C CNN
F 1 "Entrée 230V" H 2518 2926 50  0000 C CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_3-G-5.08_1x03_P5.08mm_Horizontal" H 2600 2700 50  0001 C CNN
F 3 "https://fr.farnell.com/phoenix-contact/smkds-2-5-3-5-08/terminal-block-wire-to-brd-3pos/dp/1793041" H 2600 2700 50  0001 C CNN
	1    2600 2700
	-1   0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:Conn_01x03-Connector_Generic J2
U 1 1 5FAD57E8
P 4700 2700
F 0 "J2" H 4618 3017 50  0000 C CNN
F 1 "Sortie 230V" H 4700 2900 50  0000 C CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_3-G-5.08_1x03_P5.08mm_Horizontal" H 3550 2500 40  0000 C CNN
F 3 "https://fr.farnell.com/phoenix-contact/smkds-2-5-3-5-08/terminal-block-wire-to-brd-3pos/dp/1793041" H 4700 2700 50  0001 C CNN
	1    4700 2700
	1    0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:PC817-Isolator U2
U 1 1 5FADB3A3
P 3400 2100
F 0 "U2" H 3400 2425 50  0000 C CNN
F 1 "PC817" H 3400 2334 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 3200 1900 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 3400 2100 50  0001 L CNN
	1    3400 2100
	1    0    0    -1  
$EndComp
$Comp
L e-r-wifi-rescue:S102S01-Relay_SolidState U1
U 1 1 5FACEE00
P 4000 1900
F 0 "U1" H 4000 2225 50  0000 C CNN
F 1 "SKL10120" H 4000 2134 50  0000 C CNN
F 2 "SKL10120:SKL10120" H 3800 1700 50  0001 L CIN
F 3 "https://www.e-catalogue.celduc-relais.com/fr/index.php?controller=attachment&id_attachment=42" H 4000 1900 50  0001 L CNN
	1    4000 1900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
