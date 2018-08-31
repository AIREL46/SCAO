#!/bin/bash
if [ -e bonjour.txt ] ; then
rm bonjour.txt
fi
#echo "Début du programme de capture" >> bonjour.txt
#Entrer la Durée de Cuisson
echo "Entrer la Durée de Cuisson (DC)"
read DC
#Lancer Arduino IDE
echo "Lancer Arduino IDE ? o/n"
read ide
until ([ "$ide" == o ] || [ "$ide" == n ]) #test du caractère entré par l'utilisateur oui/non (o/n)
#la boucle est exécutée tant que le résultat du test est "false"
do
	echo "Lancer Arduino IDE ? o/n"
	read ide
	sleep 1
done
if ([ "$ide" == "o" ]) ; then
#Ouvrir un terminal dans une autre fenêtre et lancer ard.sh (lancement de l'Arduino IDE)
gnome-terminal --tab -e "./ard.sh"	
fi
#Mettre sous tension le Teensy 3.2 et attendre l'établissement de la liaison série
ls -l /dev/ttyACM0
er1=$?
er2=2
echo $?
while ([ "$er1" -eq "$er2" ])
do
	echo "Mettre sous tension le Teensy 3.2 et attendre l'établissement de liaison série"	
	ls -l /dev/ttyACM0
	er1=$?
	sleep 1
done
#Afficher le contenu du port série /dev/ttyACM0
#cat /dev/ttyACM0
#Copier périodiquement le contenu  dans le fichier bonjour.txt
it=0
while ([ "$it" -le "$DC" ])
do
	it=$(($it + 1))
	echo "N° de l'itération : $it" >> bonjour.txt
	cat /dev/ttyACM0 >> bonjour.txt
	sleep 0.1
done
#Afficher à l'écran le contenu du fichier bonjour.txt
cat bonjour.txt
echo "Fin de cuisson"
