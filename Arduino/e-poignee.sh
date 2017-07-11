#!/bin/bash


while true  
do 
 gatttool -b 98:4F:EE:0D:03:32 --char-read -a 0x000b ; gatttool -b 98:4F:EE:0D:03:32 --char-read -a 0x000b
 
sleep 5 
done
