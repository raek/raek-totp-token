EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "TOTP Token"
Date ""
Rev ""
Comp "Rasmus Bondesson"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega32U4-AU U1
U 1 1 603E7D30
P 4400 5450
F 0 "U1" H 4400 3561 50  0000 C CNN
F 1 "ATmega32U4-AU" H 4400 3470 50  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 4400 5450 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf" H 4400 5450 50  0001 C CNN
	1    4400 5450
	1    0    0    -1  
$EndComp
$Comp
L Timer_RTC:DS3231M U4
U 1 1 604BB822
P 6500 3000
F 0 "U4" H 6500 2511 50  0000 C CNN
F 1 "DS3231M" H 6500 2420 50  0000 C CNN
F 2 "Package_SO:SOIC-16W_7.5x10.3mm_P1.27mm" H 6500 2400 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231.pdf" H 6770 3050 50  0001 C CNN
	1    6500 3000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 604CAA52
P 3200 2900
F 0 "#PWR0102" H 3200 2750 50  0001 C CNN
F 1 "+3.3V" H 3215 3073 50  0000 C CNN
F 2 "" H 3200 2900 50  0001 C CNN
F 3 "" H 3200 2900 50  0001 C CNN
	1    3200 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3000 2900 3000
Wire Wire Line
	3200 3000 3200 2900
$Comp
L power:+3.3V #PWR0103
U 1 1 604CC1DF
P 4400 3450
F 0 "#PWR0103" H 4400 3300 50  0001 C CNN
F 1 "+3.3V" H 4415 3623 50  0000 C CNN
F 2 "" H 4400 3450 50  0001 C CNN
F 3 "" H 4400 3450 50  0001 C CNN
	1    4400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3450 4400 3550
Wire Wire Line
	4500 3650 4500 3550
Wire Wire Line
	4500 3550 4400 3550
Connection ~ 4400 3550
Wire Wire Line
	4400 3550 4400 3650
$Comp
L power:GND #PWR0104
U 1 1 604CD4F2
P 2200 1600
F 0 "#PWR0104" H 2200 1350 50  0001 C CNN
F 1 "GND" H 2205 1427 50  0000 C CNN
F 2 "" H 2200 1600 50  0001 C CNN
F 3 "" H 2200 1600 50  0001 C CNN
	1    2200 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1600 2200 1500
$Comp
L power:GND #PWR0105
U 1 1 604CFC40
P 4700 1300
F 0 "#PWR0105" H 4700 1050 50  0001 C CNN
F 1 "GND" H 4705 1127 50  0000 C CNN
F 2 "" H 4700 1300 50  0001 C CNN
F 3 "" H 4700 1300 50  0001 C CNN
	1    4700 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1200 4700 1200
Wire Wire Line
	4700 1200 4700 1300
Wire Wire Line
	4700 1000 4700 1100
Wire Wire Line
	4700 1100 4600 1100
$Comp
L totp:VBAT #PWR0106
U 1 1 604D537D
P 4700 1000
F 0 "#PWR0106" H 4700 850 50  0001 C CNN
F 1 "VBAT" H 4715 1173 50  0000 C CNN
F 2 "" H 4700 1000 50  0001 C CNN
F 3 "" H 4700 1000 50  0001 C CNN
	1    4700 1000
	1    0    0    -1  
$EndComp
$Comp
L totp:VBAT #PWR0107
U 1 1 604D5A34
P 3700 1050
F 0 "#PWR0107" H 3700 900 50  0001 C CNN
F 1 "VBAT" H 3715 1223 50  0000 C CNN
F 2 "" H 3700 1050 50  0001 C CNN
F 3 "" H 3700 1050 50  0001 C CNN
	1    3700 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 604D7F91
P 4400 7450
F 0 "#PWR0109" H 4400 7200 50  0001 C CNN
F 1 "GND" H 4405 7277 50  0000 C CNN
F 2 "" H 4400 7450 50  0001 C CNN
F 3 "" H 4400 7450 50  0001 C CNN
	1    4400 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 7450 4400 7350
Wire Wire Line
	4300 7250 4300 7350
Wire Wire Line
	4300 7350 4400 7350
Connection ~ 4400 7350
Wire Wire Line
	4400 7350 4400 7250
$Comp
L power:GND #PWR0110
U 1 1 604E7A33
P 3050 5850
F 0 "#PWR0110" H 3050 5600 50  0001 C CNN
F 1 "GND" H 3055 5677 50  0000 C CNN
F 2 "" H 3050 5850 50  0001 C CNN
F 3 "" H 3050 5850 50  0001 C CNN
	1    3050 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 5800 3050 5800
Wire Wire Line
	3050 5800 3050 5850
Wire Wire Line
	3150 5800 3050 5800
Connection ~ 3050 5800
Wire Wire Line
	2600 1300 2700 1300
Wire Wire Line
	1650 1300 1800 1300
$Comp
L power:GND #PWR0112
U 1 1 6052453E
P 1650 1800
F 0 "#PWR0112" H 1650 1550 50  0001 C CNN
F 1 "GND" H 1655 1627 50  0000 C CNN
F 2 "" H 1650 1800 50  0001 C CNN
F 3 "" H 1650 1800 50  0001 C CNN
	1    1650 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 604BFE60
P 4400 1200
F 0 "J1" H 4450 850 50  0000 R CNN
F 1 "Conn_01x02" H 4650 950 50  0000 R CNN
F 2 "Connector_JST:JST_PH_B2B-PH-SM4-TB_1x02-1MP_P2.00mm_Vertical" H 4400 1200 50  0001 C CNN
F 3 "~" H 4400 1200 50  0001 C CNN
	1    4400 1200
	-1   0    0    1   
$EndComp
$Comp
L totp:VBUS #PWR0114
U 1 1 60529812
P 1150 2600
F 0 "#PWR0114" H 1150 2450 50  0001 C CNN
F 1 "VBUS" H 1165 2773 50  0000 C CNN
F 2 "" H 1150 2600 50  0001 C CNN
F 3 "" H 1150 2600 50  0001 C CNN
	1    1150 2600
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS84 Q1
U 1 1 6053D288
P 1550 2700
F 0 "Q1" H 1754 2746 50  0000 L CNN
F 1 "BSS84" H 1754 2655 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1750 2625 50  0001 L CIN
F 3 "http://assets.nexperia.com/documents/data-sheet/BSS84.pdf" H 1550 2700 50  0001 L CNN
	1    1550 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3000 1650 2900
Wire Wire Line
	1150 2600 1150 2700
Wire Wire Line
	1150 2700 1350 2700
Connection ~ 1150 2700
Wire Wire Line
	1150 2700 1150 3000
Connection ~ 1150 3000
$Comp
L power:GND #PWR0115
U 1 1 6054847B
P 1150 3500
F 0 "#PWR0115" H 1150 3250 50  0001 C CNN
F 1 "GND" H 1155 3327 50  0000 C CNN
F 2 "" H 1150 3500 50  0001 C CNN
F 3 "" H 1150 3500 50  0001 C CNN
	1    1150 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 60549816
P 2500 3500
F 0 "#PWR0116" H 2500 3250 50  0001 C CNN
F 1 "GND" H 2505 3327 50  0000 C CNN
F 2 "" H 2500 3500 50  0001 C CNN
F 3 "" H 2500 3500 50  0001 C CNN
	1    2500 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3500 2500 3400
Wire Wire Line
	1650 3000 1900 3000
Connection ~ 1650 3000
Wire Wire Line
	2100 3500 2100 3100
Wire Wire Line
	2100 3100 2200 3100
$Comp
L power:GND #PWR0117
U 1 1 6055B51F
P 1650 3500
F 0 "#PWR0117" H 1650 3250 50  0001 C CNN
F 1 "GND" H 1655 3327 50  0000 C CNN
F 2 "" H 1650 3500 50  0001 C CNN
F 3 "" H 1650 3500 50  0001 C CNN
	1    1650 3500
	1    0    0    -1  
$EndComp
$Comp
L totp:VBAT #PWR0118
U 1 1 6055EAC1
P 1650 2400
F 0 "#PWR0118" H 1650 2250 50  0001 C CNN
F 1 "VBAT" H 1665 2573 50  0000 C CNN
F 2 "" H 1650 2400 50  0001 C CNN
F 3 "" H 1650 2400 50  0001 C CNN
	1    1650 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2400 1650 2500
$Comp
L power:GND #PWR0119
U 1 1 60580FDF
P 1250 1450
F 0 "#PWR0119" H 1250 1200 50  0001 C CNN
F 1 "GND" H 1255 1277 50  0000 C CNN
F 2 "" H 1250 1450 50  0001 C CNN
F 3 "" H 1250 1450 50  0001 C CNN
	1    1250 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 60581400
P 2900 3500
F 0 "#PWR0120" H 2900 3250 50  0001 C CNN
F 1 "GND" H 2905 3327 50  0000 C CNN
F 2 "" H 2900 3500 50  0001 C CNN
F 3 "" H 2900 3500 50  0001 C CNN
	1    2900 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 605815D6
P 3200 3500
F 0 "#PWR0121" H 3200 3250 50  0001 C CNN
F 1 "GND" H 3205 3327 50  0000 C CNN
F 2 "" H 3200 3500 50  0001 C CNN
F 3 "" H 3200 3500 50  0001 C CNN
	1    3200 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:Resonator Y1
U 1 1 6058DBB9
P 3650 4250
F 0 "Y1" V 3604 4360 50  0000 L CNN
F 1 "8MHz" V 3695 4360 50  0000 L CNN
F 2 "" H 3625 4250 50  0001 C CNN
F 3 "~" H 3625 4250 50  0001 C CNN
	1    3650 4250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 60591DD5
P 3350 4350
F 0 "#PWR0122" H 3350 4100 50  0001 C CNN
F 1 "GND" H 3355 4177 50  0000 C CNN
F 2 "" H 3350 4350 50  0001 C CNN
F 3 "" H 3350 4350 50  0001 C CNN
	1    3350 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4400 3650 4450
Wire Wire Line
	3650 4450 3750 4450
Wire Wire Line
	3750 4450 3750 4350
Wire Wire Line
	3750 4350 3800 4350
Wire Wire Line
	3650 4100 3650 4050
Wire Wire Line
	3650 4050 3750 4050
Wire Wire Line
	3750 4050 3750 4150
Wire Wire Line
	3750 4150 3800 4150
Wire Wire Line
	3450 4250 3350 4250
Wire Wire Line
	3350 4250 3350 4350
$Comp
L power:GND #PWR0123
U 1 1 6059B137
P 3550 5850
F 0 "#PWR0123" H 3550 5600 50  0001 C CNN
F 1 "GND" H 3555 5677 50  0000 C CNN
F 2 "" H 3550 5850 50  0001 C CNN
F 3 "" H 3550 5850 50  0001 C CNN
	1    3550 5850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0124
U 1 1 6059D76B
P 3400 5350
F 0 "#PWR0124" H 3400 5200 50  0001 C CNN
F 1 "+3.3V" H 3415 5523 50  0000 C CNN
F 2 "" H 3400 5350 50  0001 C CNN
F 3 "" H 3400 5350 50  0001 C CNN
	1    3400 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5350 3400 5400
Wire Wire Line
	3400 5400 3550 5400
Wire Wire Line
	3800 5250 3700 5250
Wire Wire Line
	3700 5250 3700 5400
Wire Wire Line
	3700 5400 3550 5400
Connection ~ 3550 5400
Connection ~ 3200 3000
Connection ~ 2900 3000
Wire Wire Line
	2900 3000 3200 3000
Wire Wire Line
	3700 1100 3700 1050
Connection ~ 3700 1100
$Comp
L power:GND #PWR0125
U 1 1 605F3176
P 3700 1450
F 0 "#PWR0125" H 3700 1200 50  0001 C CNN
F 1 "GND" H 3705 1277 50  0000 C CNN
F 2 "" H 3700 1450 50  0001 C CNN
F 3 "" H 3700 1450 50  0001 C CNN
	1    3700 1450
	1    0    0    -1  
$EndComp
Connection ~ 1250 1100
NoConn ~ 4300 3650
$Comp
L power:GND #PWR0126
U 1 1 606518F9
P 6500 3500
F 0 "#PWR0126" H 6500 3250 50  0001 C CNN
F 1 "GND" H 6505 3327 50  0000 C CNN
F 2 "" H 6500 3500 50  0001 C CNN
F 3 "" H 6500 3500 50  0001 C CNN
	1    6500 3500
	1    0    0    -1  
$EndComp
$Comp
L totp:QDSP-6064 DS1
U 1 1 6066AE75
P 9150 4250
F 0 "DS1" H 9150 4917 50  0000 C CNN
F 1 "QDSP-6064" H 9150 4826 50  0000 C CNN
F 2 "Package_DIP:DIP-12_W7.62mm_Socket_LongPads" H 9150 3650 50  0001 C CNN
F 3 "https://cdn.sparkfun.com/datasheets/Components/LED/BB_QDSP_DS.pdf" H 8720 4280 50  0001 C CNN
	1    9150 4250
	1    0    0    -1  
$EndComp
$Comp
L totp:QDSP-6064 DS2
U 1 1 60672A86
P 9150 5700
F 0 "DS2" H 9150 6367 50  0000 C CNN
F 1 "QDSP-6064" H 9150 6276 50  0000 C CNN
F 2 "Package_DIP:DIP-12_W7.62mm_Socket_LongPads" H 9150 5100 50  0001 C CNN
F 3 "https://cdn.sparkfun.com/datasheets/Components/LED/BB_QDSP_DS.pdf" H 8720 5730 50  0001 C CNN
	1    9150 5700
	1    0    0    -1  
$EndComp
Text Label 5100 5150 0    50   ~ 0
SCL
Text Label 5100 5250 0    50   ~ 0
SDA
$Comp
L totp:MCP73831-2-OT U2
U 1 1 604D1BFE
P 2200 1200
F 0 "U2" H 2200 1567 50  0000 C CNN
F 1 "MCP73831-2-OT" H 2200 1476 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 2250 950 50  0001 L CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001984g.pdf" H 2050 1150 50  0001 C CNN
	1    2200 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1100 1800 1100
Text Label 7050 5350 0    50   ~ 0
SEGA
Text Label 7050 5450 0    50   ~ 0
SEGB
Text Label 7050 5550 0    50   ~ 0
SEGC
Text Label 7050 5650 0    50   ~ 0
SEGD
Text Label 7050 5750 0    50   ~ 0
SEGE
Text Label 7050 5850 0    50   ~ 0
SEGF
Text Label 7050 5950 0    50   ~ 0
SEGG
Text Label 7050 6050 0    50   ~ 0
SEGDP
Text Label 8050 5350 2    50   ~ 0
SEGA
Text Label 8050 5450 2    50   ~ 0
SEGB
Text Label 8050 5550 2    50   ~ 0
SEGC
Text Label 8050 5650 2    50   ~ 0
SEGD
Text Label 8050 5750 2    50   ~ 0
SEGE
Text Label 8050 5850 2    50   ~ 0
SEGF
Text Label 8050 5950 2    50   ~ 0
SEGG
Text Label 8050 6050 2    50   ~ 0
SEGDP
Wire Wire Line
	7300 6050 7050 6050
Wire Wire Line
	7050 5950 7300 5950
Wire Wire Line
	7300 5850 7050 5850
Wire Wire Line
	7050 5750 7300 5750
Wire Wire Line
	7300 5650 7050 5650
Wire Wire Line
	7050 5550 7300 5550
Wire Wire Line
	7300 5450 7050 5450
Wire Wire Line
	7050 5350 7300 5350
Wire Wire Line
	8050 6050 7800 6050
Wire Wire Line
	7800 5950 8050 5950
Wire Wire Line
	8050 5850 7800 5850
Wire Wire Line
	8050 5750 7800 5750
Wire Wire Line
	8050 5650 7800 5650
Wire Wire Line
	8050 5550 7800 5550
Wire Wire Line
	8050 5450 7800 5450
Wire Wire Line
	8050 5350 7800 5350
Text Label 8050 3900 2    50   ~ 0
SEGA
Text Label 8050 4000 2    50   ~ 0
SEGB
Text Label 8050 4100 2    50   ~ 0
SEGC
Text Label 8050 4200 2    50   ~ 0
SEGD
Text Label 8050 4300 2    50   ~ 0
SEGE
Text Label 8050 4400 2    50   ~ 0
SEGF
Text Label 8050 4500 2    50   ~ 0
SEGG
Text Label 8050 4600 2    50   ~ 0
SEGDP
Wire Wire Line
	7800 3900 8050 3900
Wire Wire Line
	7800 4600 8050 4600
Wire Wire Line
	8050 4500 7800 4500
Wire Wire Line
	8050 4400 7800 4400
Wire Wire Line
	8050 4300 7800 4300
Wire Wire Line
	8050 4200 7800 4200
Wire Wire Line
	8050 4100 7800 4100
Wire Wire Line
	8050 4000 7800 4000
Entry Wire Line
	7800 3900 7700 4000
Entry Wire Line
	7800 4000 7700 4100
Entry Wire Line
	7800 4100 7700 4200
Entry Wire Line
	7800 4200 7700 4300
Entry Wire Line
	7800 4300 7700 4400
Entry Wire Line
	7800 4400 7700 4500
Entry Wire Line
	7800 4500 7700 4600
Entry Wire Line
	7800 4600 7700 4700
Entry Wire Line
	7800 5350 7700 5450
Entry Wire Line
	7800 5450 7700 5550
Entry Wire Line
	7800 5550 7700 5650
Entry Wire Line
	7800 5650 7700 5750
Entry Wire Line
	7800 5750 7700 5850
Entry Wire Line
	7800 5850 7700 5950
Entry Wire Line
	7800 5950 7700 6050
Entry Wire Line
	7800 6050 7700 6150
Entry Wire Line
	7300 5350 7400 5450
Entry Wire Line
	7300 5450 7400 5550
Entry Wire Line
	7300 5550 7400 5650
Entry Wire Line
	7300 5650 7400 5750
Entry Wire Line
	7300 5750 7400 5850
Entry Wire Line
	7300 5850 7400 5950
Entry Wire Line
	7300 5950 7400 6050
Entry Wire Line
	7300 6050 7400 6150
Text Label 7050 4450 0    50   ~ 0
DIG0
Text Label 7050 4550 0    50   ~ 0
DIG1
Text Label 7050 4650 0    50   ~ 0
DIG2
Text Label 7050 4750 0    50   ~ 0
DIG3
Text Label 7050 4850 0    50   ~ 0
DIG4
Text Label 7050 4950 0    50   ~ 0
DIG5
Text Label 7050 5050 0    50   ~ 0
DIG6
Text Label 7050 5150 0    50   ~ 0
DIG7
Wire Wire Line
	7050 5150 7300 5150
Wire Wire Line
	7300 5050 7050 5050
Wire Wire Line
	7050 4950 7300 4950
Wire Wire Line
	7300 4850 7050 4850
Wire Wire Line
	7050 4750 7300 4750
Wire Wire Line
	7300 4650 7050 4650
Wire Wire Line
	7050 4550 7300 4550
Wire Wire Line
	7300 4450 7050 4450
Entry Wire Line
	7300 5150 7400 5050
Entry Wire Line
	7300 5050 7400 4950
Entry Wire Line
	7300 4950 7400 4850
Entry Wire Line
	7300 4850 7400 4750
Entry Wire Line
	7300 4750 7400 4650
Entry Wire Line
	7300 4650 7400 4550
Entry Wire Line
	7300 4550 7400 4450
Entry Wire Line
	7300 4450 7400 4350
Text Label 10250 4300 0    50   ~ 0
DIG0
Text Label 10250 4400 0    50   ~ 0
DIG1
Text Label 10250 4500 0    50   ~ 0
DIG2
Text Label 10250 4600 0    50   ~ 0
DIG3
Text Label 10250 5750 0    50   ~ 0
DIG4
Text Label 10250 5850 0    50   ~ 0
DIG5
Text Label 10250 5950 0    50   ~ 0
DIG6
Text Label 10250 6050 0    50   ~ 0
DIG7
Wire Wire Line
	10250 4300 10450 4300
Wire Wire Line
	10450 4400 10250 4400
Wire Wire Line
	10250 4500 10450 4500
Wire Wire Line
	10250 4600 10450 4600
Wire Wire Line
	10250 5750 10450 5750
Wire Wire Line
	10450 5850 10250 5850
Wire Wire Line
	10250 5950 10450 5950
Wire Wire Line
	10250 6050 10450 6050
Entry Wire Line
	10450 6050 10550 5950
Entry Wire Line
	10450 5950 10550 5850
Entry Wire Line
	10450 5850 10550 5750
Entry Wire Line
	10450 5750 10550 5650
Entry Wire Line
	10450 4600 10550 4500
Entry Wire Line
	10450 4500 10550 4400
Entry Wire Line
	10450 4400 10550 4300
Entry Wire Line
	10450 4300 10550 4200
Wire Bus Line
	10550 3350 7400 3350
NoConn ~ 7050 6250
$Comp
L power:GND #PWR?
U 1 1 60628E1A
P 6500 6650
F 0 "#PWR?" H 6500 6400 50  0001 C CNN
F 1 "GND" H 6505 6477 50  0000 C CNN
F 2 "" H 6500 6650 50  0001 C CNN
F 3 "" H 6500 6650 50  0001 C CNN
	1    6500 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 6450 6450 6550
Wire Wire Line
	6450 6550 6500 6550
Wire Wire Line
	6550 6550 6550 6450
Wire Wire Line
	6500 6550 6500 6650
Connection ~ 6500 6550
Wire Wire Line
	6500 6550 6550 6550
Wire Wire Line
	1250 1050 1250 1100
$Comp
L totp:VBUS #PWR0113
U 1 1 60525A44
P 1250 1050
F 0 "#PWR0113" H 1250 900 50  0001 C CNN
F 1 "VBUS" H 1265 1223 50  0000 C CNN
F 2 "" H 1250 1050 50  0001 C CNN
F 3 "" H 1250 1050 50  0001 C CNN
	1    1250 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C1
U 1 1 60653B50
P 1250 1300
F 0 "C1" H 1338 1346 50  0000 L CNN
F 1 "10uF" H 1338 1255 50  0000 L CNN
F 2 "" H 1250 1300 50  0001 C CNN
F 3 "~" H 1250 1300 50  0001 C CNN
	1    1250 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1100 1250 1200
Wire Wire Line
	1250 1400 1250 1450
$Comp
L Device:R_Small R1
U 1 1 60660A60
P 1650 1550
F 0 "R1" H 1709 1596 50  0000 L CNN
F 1 "10k" H 1709 1505 50  0000 L CNN
F 2 "" H 1650 1550 50  0001 C CNN
F 3 "~" H 1650 1550 50  0001 C CNN
	1    1650 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1300 1650 1450
Wire Wire Line
	1650 1650 1650 1800
$Comp
L Device:CP_Small C2
U 1 1 6066C405
P 3700 1300
F 0 "C2" H 3788 1346 50  0000 L CNN
F 1 "10uF" H 3788 1255 50  0000 L CNN
F 2 "" H 3700 1300 50  0001 C CNN
F 3 "~" H 3700 1300 50  0001 C CNN
	1    3700 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1400 3700 1450
Wire Wire Line
	3700 1100 3700 1200
$Comp
L Device:R_Small R?
U 1 1 606782D0
P 1150 3250
F 0 "R?" H 1209 3296 50  0000 L CNN
F 1 "100k" H 1209 3205 50  0000 L CNN
F 2 "" H 1150 3250 50  0001 C CNN
F 3 "~" H 1150 3250 50  0001 C CNN
	1    1150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3000 1150 3150
Wire Wire Line
	1150 3350 1150 3500
$Comp
L Device:CP_Small C?
U 1 1 6068ED48
P 1650 3250
F 0 "C?" H 1738 3296 50  0000 L CNN
F 1 "10uF" H 1738 3205 50  0000 L CNN
F 2 "" H 1650 3250 50  0001 C CNN
F 3 "~" H 1650 3250 50  0001 C CNN
	1    1650 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C?
U 1 1 6068F4BB
P 2900 3250
F 0 "C?" H 2988 3296 50  0000 L CNN
F 1 "10uF" H 2988 3205 50  0000 L CNN
F 2 "" H 2900 3250 50  0001 C CNN
F 3 "~" H 2900 3250 50  0001 C CNN
	1    2900 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3000 1650 3150
Wire Wire Line
	1650 3350 1650 3500
Wire Wire Line
	2900 3000 2900 3150
Wire Wire Line
	2900 3350 2900 3500
$Comp
L Device:CP_Small C?
U 1 1 606AC173
P 3200 3250
F 0 "C?" H 3288 3296 50  0000 L CNN
F 1 "1uF" H 3288 3205 50  0000 L CNN
F 2 "" H 3200 3250 50  0001 C CNN
F 3 "~" H 3200 3250 50  0001 C CNN
	1    3200 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3000 3200 3150
Wire Wire Line
	3200 3350 3200 3500
$Comp
L Device:R_Small R?
U 1 1 606B7D2E
P 1900 3250
F 0 "R?" H 1959 3296 50  0000 L CNN
F 1 "100k" H 1959 3205 50  0000 L CNN
F 2 "" H 1900 3250 50  0001 C CNN
F 3 "~" H 1900 3250 50  0001 C CNN
	1    1900 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 3000 1900 3150
Wire Wire Line
	1900 3350 1900 3500
$Comp
L Device:D_Schottky_Small D?
U 1 1 606CBE1E
P 1400 3000
F 0 "D?" H 1400 2793 50  0000 C CNN
F 1 "D_Schottky_Small" H 1400 2884 50  0000 C CNN
F 2 "" V 1400 3000 50  0001 C CNN
F 3 "~" V 1400 3000 50  0001 C CNN
	1    1400 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 3000 1300 3000
Wire Wire Line
	1500 3000 1650 3000
$Comp
L Device:R_Small R?
U 1 1 606D7C80
P 2950 5650
F 0 "R?" H 3009 5696 50  0000 L CNN
F 1 "5.1k" H 3009 5605 50  0000 L CNN
F 2 "" H 2950 5650 50  0001 C CNN
F 3 "~" H 2950 5650 50  0001 C CNN
	1    2950 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 606D7FA2
P 3150 5650
F 0 "R?" H 3209 5696 50  0000 L CNN
F 1 "5.1k" H 3209 5605 50  0000 L CNN
F 2 "" H 3150 5650 50  0001 C CNN
F 3 "~" H 3150 5650 50  0001 C CNN
	1    3150 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 5750 3150 5800
Wire Wire Line
	2950 5750 2950 5800
Wire Wire Line
	3400 4950 3800 4950
Wire Wire Line
	3400 5050 3800 5050
$Comp
L Device:CP_Small C?
U 1 1 60711328
P 3550 5700
F 0 "C?" H 3638 5746 50  0000 L CNN
F 1 "1uF" H 3638 5655 50  0000 L CNN
F 2 "" H 3550 5700 50  0001 C CNN
F 3 "~" H 3550 5700 50  0001 C CNN
	1    3550 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 5400 3550 5600
Wire Wire Line
	3550 5800 3550 5850
NoConn ~ 7000 3100
NoConn ~ 7000 2800
$Comp
L Transistor_FET:BSS84 Q2
U 1 1 607497CD
P 4450 2600
F 0 "Q2" H 4654 2646 50  0000 L CNN
F 1 "BSS84" H 4654 2555 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4650 2525 50  0001 L CIN
F 3 "http://assets.nexperia.com/documents/data-sheet/BSS84.pdf" H 4450 2600 50  0001 L CNN
	1    4450 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6074A6E0
P 4550 2100
F 0 "#PWR?" H 4550 1950 50  0001 C CNN
F 1 "+3.3V" H 4565 2273 50  0000 C CNN
F 2 "" H 4550 2100 50  0001 C CNN
F 3 "" H 4550 2100 50  0001 C CNN
	1    4550 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60768FEE
P 4250 2400
F 0 "R?" H 4309 2446 50  0000 L CNN
F 1 "100k" H 4309 2355 50  0000 L CNN
F 2 "" H 4250 2400 50  0001 C CNN
F 3 "~" H 4250 2400 50  0001 C CNN
	1    4250 2400
	1    0    0    -1  
$EndComp
Text Label 3900 2600 0    50   ~ 0
~PERI_EN
$Comp
L totp:VPERI #PWR?
U 1 1 6078A0D7
P 4750 2100
F 0 "#PWR?" H 4750 1950 50  0001 C CNN
F 1 "VPERI" H 4765 2273 50  0000 C CNN
F 2 "" H 4750 2100 50  0001 C CNN
F 3 "" H 4750 2100 50  0001 C CNN
	1    4750 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2600 4250 2600
Wire Wire Line
	4250 2600 4250 2500
Connection ~ 4250 2600
Wire Wire Line
	4250 2200 4250 2300
Wire Wire Line
	4550 2200 4550 2400
Wire Wire Line
	4250 2200 4550 2200
Wire Wire Line
	4550 2100 4550 2200
Connection ~ 4550 2200
Wire Wire Line
	4550 2800 4550 2900
Wire Wire Line
	4550 2900 4750 2900
Wire Wire Line
	1900 3500 2100 3500
Wire Wire Line
	1900 3000 2200 3000
Connection ~ 1900 3000
$Comp
L power:+3.3V #PWR?
U 1 1 60743670
P 6500 2500
F 0 "#PWR?" H 6500 2350 50  0001 C CNN
F 1 "+3.3V" H 6515 2673 50  0000 C CNN
F 2 "" H 6500 2500 50  0001 C CNN
F 3 "" H 6500 2500 50  0001 C CNN
	1    6500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 2500 6500 2600
Wire Wire Line
	6400 2500 6400 2600
$Comp
L Device:R_Small R?
U 1 1 608D36CB
P 5850 4300
F 0 "R?" H 5909 4346 50  0000 L CNN
F 1 "10k" H 5909 4255 50  0000 L CNN
F 2 "" H 5850 4300 50  0001 C CNN
F 3 "~" H 5850 4300 50  0001 C CNN
	1    5850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4250 6500 4150
Wire Wire Line
	6500 4150 5850 4150
Wire Wire Line
	5850 4150 5850 4200
Wire Wire Line
	6500 4050 6500 4150
Connection ~ 6500 4150
$Comp
L totp:VPERI #PWR?
U 1 1 608E8A46
P 6500 4050
F 0 "#PWR?" H 6500 3900 50  0001 C CNN
F 1 "VPERI" H 6515 4223 50  0000 C CNN
F 2 "" H 6500 4050 50  0001 C CNN
F 3 "" H 6500 4050 50  0001 C CNN
	1    6500 4050
	1    0    0    -1  
$EndComp
$Comp
L totp:VPERI #PWR?
U 1 1 608E94C4
P 6400 2500
F 0 "#PWR?" H 6400 2350 50  0001 C CNN
F 1 "VPERI" H 6415 2673 50  0000 C CNN
F 2 "" H 6400 2500 50  0001 C CNN
F 3 "" H 6400 2500 50  0001 C CNN
	1    6400 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 4400 5850 4450
Wire Wire Line
	5850 4450 5950 4450
Wire Wire Line
	4750 2100 4750 2900
Text Label 5850 6250 2    50   ~ 0
SCK
Text Label 5100 4050 0    50   ~ 0
SCK
Text Label 5100 4150 0    50   ~ 0
MOSI
Text Label 5850 6050 2    50   ~ 0
MOSI
$Comp
L totp:AS1107WL-T U?
U 1 1 6094A5B2
P 6500 5350
F 0 "U?" H 6500 6631 50  0000 C CNN
F 1 "AS1107WL-T" H 6500 6540 50  0000 C CNN
F 2 "Package_SO:SOIC-24W_7.5x15.4mm_P1.27mm" H 6500 6900 50  0001 C CNN
F 3 "https://ams.com/documents/20143/36005/AS1106-07_DS000171_1-00.pdf" H 6500 6900 50  0001 C CNN
	1    6500 5350
	1    0    0    -1  
$EndComp
Text Label 5850 6150 2    50   ~ 0
SS
Text Label 5100 3950 0    50   ~ 0
SS
Entry Wire Line
	5500 5150 5600 5050
Entry Wire Line
	5500 5250 5600 5150
Entry Wire Line
	5700 2800 5600 2900
Entry Wire Line
	5700 2900 5600 3000
Text Label 5900 2900 2    50   ~ 0
SDA
Text Label 5900 2800 2    50   ~ 0
SCL
Wire Wire Line
	5000 5150 5500 5150
Wire Wire Line
	5000 5250 5500 5250
Wire Wire Line
	5700 2800 6000 2800
Wire Wire Line
	6000 2900 5700 2900
Wire Wire Line
	5000 4150 5300 4150
Wire Wire Line
	5000 4050 5300 4050
Wire Wire Line
	5000 3950 5300 3950
Entry Wire Line
	5300 3950 5400 4050
Entry Wire Line
	5300 4050 5400 4150
Entry Wire Line
	5300 4150 5400 4250
Wire Wire Line
	5500 6050 5950 6050
Wire Wire Line
	5500 6150 5950 6150
Wire Wire Line
	5500 6250 5950 6250
Entry Wire Line
	5500 6050 5400 5950
Entry Wire Line
	5500 6150 5400 6050
Entry Wire Line
	5500 6250 5400 6150
Wire Bus Line
	7400 6350 7700 6350
NoConn ~ 6000 3200
Wire Wire Line
	3700 4750 3800 4750
Text Notes 5600 3250 1    50   ~ 0
I2C
Text Notes 5400 5850 1    50   ~ 0
SPI\n
Text Notes 7500 5000 1    50   ~ 0
DIGITS/CATHODES
Text Notes 7500 6200 1    50   ~ 0
SEGMENTS/ANODES
Wire Wire Line
	6500 3500 6500 3400
Wire Wire Line
	2600 1100 3700 1100
$Comp
L Device:R_Small R?
U 1 1 60BC8555
P 5750 6750
F 0 "R?" H 5809 6796 50  0000 L CNN
F 1 "100k" H 5809 6705 50  0000 L CNN
F 2 "" H 5750 6750 50  0001 C CNN
F 3 "~" H 5750 6750 50  0001 C CNN
	1    5750 6750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60BC88BF
P 5750 7050
F 0 "R?" H 5809 7096 50  0000 L CNN
F 1 "100k" H 5809 7005 50  0000 L CNN
F 2 "" H 5750 7050 50  0001 C CNN
F 3 "~" H 5750 7050 50  0001 C CNN
	1    5750 7050
	1    0    0    -1  
$EndComp
$Comp
L totp:VBAT #PWR?
U 1 1 60BCA18E
P 5750 6600
F 0 "#PWR?" H 5750 6450 50  0001 C CNN
F 1 "VBAT" H 5765 6773 50  0000 C CNN
F 2 "" H 5750 6600 50  0001 C CNN
F 3 "" H 5750 6600 50  0001 C CNN
	1    5750 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 6600 5750 6650
Wire Wire Line
	5750 6850 5750 6900
Wire Wire Line
	5400 6350 5000 6350
Connection ~ 5750 6900
Wire Wire Line
	5750 6900 5750 6950
Wire Wire Line
	5750 7150 5750 7200
Wire Wire Line
	5350 6450 5000 6450
Wire Wire Line
	5400 6900 5750 6900
Wire Wire Line
	5400 6350 5400 6900
Wire Wire Line
	5350 7200 5750 7200
Wire Wire Line
	5350 6450 5350 7200
$Comp
L totp:VBUS #PWR?
U 1 1 6059C5F9
P 2150 4500
F 0 "#PWR?" H 2150 4350 50  0001 C CNN
F 1 "VBUS" H 2165 4673 50  0000 C CNN
F 2 "" H 2150 4500 50  0001 C CNN
F 3 "" H 2150 4500 50  0001 C CNN
	1    2150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 5550 2950 5450
Wire Wire Line
	3150 5350 3150 5550
NoConn ~ 2750 5750
Connection ~ 2750 4950
Wire Wire Line
	2500 4950 2750 4950
Wire Wire Line
	2950 5450 2750 5450
NoConn ~ 2750 5650
Connection ~ 2750 5050
Wire Wire Line
	2750 5150 2750 5050
Wire Wire Line
	3200 5050 2750 5050
Wire Wire Line
	2750 4850 2750 4950
Wire Wire Line
	2750 5350 3150 5350
$Comp
L power:GND #PWR0101
U 1 1 604C71E8
P 2150 6050
F 0 "#PWR0101" H 2150 5800 50  0001 C CNN
F 1 "GND" H 2155 5877 50  0000 C CNN
F 2 "" H 2150 6050 50  0001 C CNN
F 3 "" H 2150 6050 50  0001 C CNN
	1    2150 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4550 3700 4750
$Comp
L totp:USB_C_Receptacle_USB2.0 J?
U 1 1 60601BFE
P 2150 5300
F 0 "J?" H 1721 5346 50  0000 R CNN
F 1 "USB_C_Receptacle_USB2.0" H 1721 5255 50  0000 R CNN
F 2 "totp:USB_C_Receptacle_JAE_DX07S016JA1" H 2300 5800 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 2300 5800 50  0001 C CNN
	1    2150 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4500 2150 4550
Wire Wire Line
	3700 4550 2150 4550
Connection ~ 2150 4550
$Comp
L Device:R_Small R?
U 1 1 606F9B6C
P 3300 5050
F 0 "R?" V 3104 5050 50  0000 C CNN
F 1 "22" V 3195 5050 50  0000 C CNN
F 2 "" H 3300 5050 50  0001 C CNN
F 3 "~" H 3300 5050 50  0001 C CNN
	1    3300 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 606F99A8
P 3300 4950
F 0 "R?" V 3104 4950 50  0000 C CNN
F 1 "22" V 3195 4950 50  0000 C CNN
F 2 "" H 3300 4950 50  0001 C CNN
F 3 "~" H 3300 4950 50  0001 C CNN
	1    3300 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 4950 3200 4950
Wire Wire Line
	2750 5050 2500 5050
Wire Bus Line
	5600 2900 5600 5150
Wire Bus Line
	5400 4050 5400 6150
Wire Bus Line
	10550 3350 10550 5950
Wire Bus Line
	7400 3350 7400 5050
Wire Bus Line
	7400 5450 7400 6350
Wire Bus Line
	7700 4000 7700 6350
$Comp
L Regulator_Linear:AP2112K-3.3 U3
U 1 1 6057B166
P 2500 3100
F 0 "U3" H 2500 3442 50  0000 C CNN
F 1 "AP2112K-3.3" H 2500 3351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 2500 3425 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/AP2112.pdf" H 2500 3200 50  0001 C CNN
	1    2500 3100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
