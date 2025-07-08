#!/bin/bash


while true  
do 
gatttool -b 98:4F:EE:0C:14:D5 --char-write -a 0x000b -n 0x01 ;  gatttool -b 98:4F:EE:0C:14:D5 --char-write -a 0x000b -n 01
sleep 1 
gatttool -b 98:4F:EE:0C:14:D5 --char-write -a 0x000b -n 0x01 ;  gatttool -b 98:4F:EE:0C:14:D5 --char-write -a 0x000b -n 00
sleep 1 
done
