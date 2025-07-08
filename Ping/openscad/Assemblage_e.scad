include <dim1.scad>
$fn=100;//nombre de facettes

//cable USB
//translate([33,0,9.95])scale([0.65,0.65,0.65])color([0, 0, 0]){import("Cable USB.stl");}

//CI
//translate([0,0,7.55])color([151/255, 191/255, 13/255]){import("CI.stl");}
//isolateur
translate([0,0,0])scale([1,1,1])color([233/255, 93/255, 15/255]) {import("isolateur-bruno.stl");}
//Entretoise en aluminium
translate([0,0,-11.25])rotate([0,0,0])color( [255/255, 0/255, 0/255]){import("ent-alu.stl");}
//Capteur
translate([-20,0,-11.25])rotate([0,90,0])color( [0/255, 0/255, 0/255]){import("capteur.stl");}
//couvercle
//translate([0,0,-16.4])color( [190/255, 190/255, 190/255]){import("Couvercle.stl");}

