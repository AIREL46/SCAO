
include <dim1.scad>
include <jupe.scad>
$fn=100;//nombre de facettes
//Définition des couleurs
orange=[233/255, 93/255, 15/255];
vert=[151/255, 191/255, 13/255];
gris=[112/255, 113/255, 115/255];
noir=[0/255, 0/255, 0/255];
bleu=[51/255, 51/255, 255/255];
//Capteur de température (7)
translate([-12,0,(hj/2)-1.25])rotate([0,-90,180])color( noir){import("capteur.stl");}
//Jupe (8)
//translate([0,0,0])color( vert){import("jupe.stl");}