include <dim1.scad>
include <z_ecl_f.scad>//ecl=éclaté secl=normal
$fn=100;//nombre de facettes
use <visserie.scad> //Modules écrou, entretoise hexagonale, rondelle et vis
//Définition des couleurs
orange=[233/255, 93/255, 15/255];
vert=[151/255, 191/255, 13/255];
gris=[112/255, 113/255, 115/255];
noir=[0/255, 0/255, 0/255];
bleu=[51/255, 51/255, 255/255];
//Assemblage des pièces de la e-p-433-v2
//vis M3 (1)
color( gris)vis_M(3, 4, 1.5, true, L2/2, l2/2, z1);
color( gris)vis_M(3, 4, 1.5, true, -L2/2, l2/2, z1);
color( gris)vis_M(3, 4, 1.5, true, L2/2, -l2/2, z1);
color( gris)vis_M(3, 4, 1.5, true, -L2/2, -l2/2, z1);
//Rondelles (2)
rond_M(3, 1, L2/2, l2/2, z2);
rond_M(3, 1, L2/2, -l2/2, z2);
rond_M(3, 1, -L2/2, l2/2, z2);
rond_M(3, 1, -L2/2, -l2/2, z2);
//CI e-p-433 (3) - version proto
//translate([0,0,z3]) color(orange) difference(){
//minkowski() {cube([(3.2*CC)-3,(3.2*CC)-3,0.7], center=true); cylinder(0.7,3,3,center=true);}
//translate([L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
//translate([-L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
//translate([L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
//translate([-L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
//translate([-1.05*CC,0,-e/4])minkowski()
//{
  //cube([2.5,20,e/2], center=true);
  //cylinder(r=2,h=e/2);
//}//Trou pour les câbles des capteurs de température (prévoir de l'agrandir)
//}
//Plateforme d'essais (3) - version essais
union()translate([0,0,z3]){
include <plateforme-essais.scad>
//Chargeur
color(orange)translate([0,0,+8*e])scale([CC,CC,CC]) linear_extrude(height = 0.02, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/plateforme-essais.dxf", layer = "chargeur");}; //CI chargeur
x=-1.95*CC; y=-0.6*CC; //Coordonnées du CI chargeur
color( gris)ent_M(2.5,4.8,6,5,true, x, y, 5.5*e); //Entretoise M2.5
rond_M(3, 1, x, y, -2*e);
color( gris)Ecrou(2.5,1.7, 4.8, x, y,-3*e); //Ecrou M2.5
//Platine
color(bleu)translate([0,0,+10*e])scale([CC,CC,CC]) linear_extrude(height = 0.36, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/plateforme-essais.dxf", layer = "platine");};
}
//Batterie (4)
color( [255/255, 0/255, 0/255]) translate([0,0,z4]) cube([23.6,35.2,5.7], center=true);
//Entretoises M3 femelle (5)
color( gris) translate([0,0,z5]) union() {difference(){
    translate([L2/2,l2/2,0]) cylinder(8,3,3,center=true);
    translate([L2/2,l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
    difference(){
    translate([L2/2,-l2/2,0]) cylinder(8,3,3,center=true);
    translate([L2/2,-l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
    difference(){
    translate([-L2/2,-l2/2,0]) cylinder(8,3,3,center=true);
    translate([-L2/2,-l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
    difference(){
    translate([-L2/2,l2/2,0]) cylinder(8,3,3,center=true);
    translate([-L2/2,l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
}
//Rondelles (6)
rond_M(3, 1, L2/2, l2/2, z6);
rond_M(3, 1, -L2/2, l2/2, z6);
rond_M(3, 1, L2/2, -l2/2, z6);
rond_M(3, 1, -L2/2, -l2/2, z6);
//Capteur de température (7)
translate([0,0,z7])rotate([0,-90,180])color( noir){import("capteur.stl");}
//Jupe (8)
translate([0,0,z8])color( vert){import("jupe.stl");}
//entretoises M3 (9)
color( gris)ent_M(2.5,5,8,5,false,L2/2,l2/2,z9);
color( gris)ent_M(2.5,5,8,5,false,-L2/2,-l2/2,z9);
color( gris)ent_M(2.5,5,8,5,false,L2/2,-l2/2,z9);
color( gris)ent_M(2.5,5,8,5,false,-L2/2,l2/2,z9);
//Vis M3 (10)
color( gris)vis_M(3, 4, 1.5, true, 8.5, 8.5, z10);
color( gris)vis_M(3, 4, 1.5, true, -8.5, 8.5, z10);
color( gris)vis_M(3, 4, 1.5, true, 8.5, -8.5, z10);
color( gris)vis_M(3, 4, 1.5, true, -8.5, -8.5, z10);
//Rondelle M3 (11)
rond_M(3, 1, 8.5, 8.5, z11);
rond_M(3, 1, -8.5, 8.5, z11);
rond_M(3, 1, 8.5, -8.5, z11);
rond_M(3, 1, -8.5, -8.5, z11);
//isolateur (12)
translate([0,0,z12])color(orange){import("isolateur-bruno.stl");}
//rondelles (13)
rond_M(3, 1, L2/2, l2/2, z13);
rond_M(3, 1, -L2/2, l2/2, z13);
rond_M(3, 1, L2/2, -l2/2, z13);
rond_M(3, 1, -L2/2, -l2/2, z13);
//vis M3 (14)
color( gris)vis_M(3, 4, 1.5, false, L2/2, l2/2, z14);
color( gris)vis_M(3, 4, 1.5, false, -L2/2, l2/2, z14);
color( gris)vis_M(3, 4, 1.5, false, L2/2, -l2/2, z14);
color( gris)vis_M(3, 4, 1.5, false, -L2/2, -l2/2, z14);
//Entretoise M3 (15)
color( gris)ent_M(3,4.7,8.1,4.8,true,8.5,8.5,z15);
color( gris)ent_M(3,4.7,8.1,4.8,true,-8.5,8.5,z15);
color( gris)ent_M(3,4.7,8.1,4.8,true,8.5,-8.5,z15);
color( gris)ent_M(3,4.7,8.1,4.8,true,-8.5,-8.5,z15);
//Entretoise en aluminium (16)
translate([0,0,z16])rotate([0,0,0])color( [255/255, 0/255, 0/255]){import("ent-fixation.stl");}
//Capteur de température (17)
translate([x17,0,z17])rotate([0,90,0])color( noir){import("capteur.stl");}
//Vis de serrage du capteur (18)
translate([-8.5,0,z18])color( noir)cylinder(4,1.75,1.75,center=true);
//couvercle (19)
translate([0,0,z19])color( [190/255, 190/255, 190/255]){import("Couvercle.stl");}
