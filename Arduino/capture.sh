#Dans le cadre du concept culinaire Quiet cook http://quiet-cook.com/ et de son Système de Cuisson Assistée par Ordinateur (SCAO) http://fablabo.net/wiki/SCAO. Le prototypage (prototype N°3) de la e-poignée (433MHZ en version 2) est réalisé par Régis LERUSTE http://fablabo.net/wiki/Utilisateur:LERUSTE_REGIS et Olivier MARAIS http://fablabo.net/wiki/Cahier_de_recettes#Les_recettes_d.27Olivier . Ce programme est dévelloppé sous licence creative commons CC-BY-SA. Il est complémentaire au programme e-p-433-v2.ino. Il a pour objet la capture périodique des données transmises par le microcontrôleur. Ces données son stockées au fur et à mesure dans un fichier "journal". Ce programme est exécuté sur l'ordinateur tandis que l'e-p-433-v2.ino est téléversé dans le microcontrôleur.
#Il demande à l'utilisateur de fixer la durée de la capture.
#En option, il permet de lancer la plateforme Arduino IDE.
#Il s'arrête quand la durée de capture est écoulée.
#Il met à la disposition de l'utilisateur le fichier journal.txt.
#!/bin/bash
if [ -e journal.txt ] ; then #test l'existence du fichier journal
rm journal.txt #détruit le précédent fichier journal
fi
#Entrer la Durée de Capture
echo "Entrer la Durée de Capture (mm)"
read DC
#Lancer la plateforme Arduino IDE
echo "Lancer la plateforme Arduino IDE ? o/n"
read ide
#test du caractère entré par l'utilisateur oui/non (o/n)
until ([ "$ide" == o ] || [ "$ide" == n ]) 
#la boucle est exécutée tant que le résultat du test est "false"
do
	echo "Lancer la plateforme Arduino IDE ? o/n"
	read ide
	sleep 1
done
#Si ide="oui"
if ([ "$ide" == "o" ]) ; then
#Ouvrir un terminal dans une autre fenêtre et lancer ard.sh (lancement de l'Arduino IDE)
gnome-terminal --tab -e "./ard.sh"	
fi
#Mettre sous tension le Teensy 3.2 et attendre l'établissement de la liaison série en testant le port série USB /dev/ttyACM0 utilisé par le Teensy 3.2 pour envoyé les message à la console.
ls -l /dev/ttyACM0
er1=$? # $? est la variable d'environnement accessible après l'exécution d'une commande (ls), si elle est égale à 0, le résultat est correct, si elle est égale à 2, le résultat est incorrect.
er2=2
echo $?
#Attente de l'établissement de la liaison série
while ([ "$er1" -eq "$er2" ]) 
do
	echo "Mettre sous tension le Teensy 3.2 et attendre l'établissement de liaison série"	
	ls -l /dev/ttyACM0
	er1=$?
	sleep 1
done
#Boucle de capture
fin=`date +"%s"` #délaration de la variable "fin" de capture
let fin=$fin+$DC*60 #calcul de l'heure de fin
#exécuter la boucle tant que l'heure de fin n'est pas atteinte
while [ `date +"%s"` -lt $fin ]
do
#Edition du fichier journal par ajout successif des enregistrements dans le fichier journal.
cat /dev/ttyACM0 >> journal.txt
sleep 0.2
done
#Visualisation du fichier journal.
cat journal.txt

