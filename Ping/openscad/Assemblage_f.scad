//Ce programme permet la représentation de l'assemblage des différentes pièces de la e-p-433-v2.
//La représentation est réalisable selon un mode statique ou animé.
//En mode statique la représentation est réelle.
//En mode animé la représentation évolue progressivement entre une représentation réelle et une représentation éclatée qui permet d'apercevoir le détail des différentes pièces.
//The $t variable is used for animation. If you enable the animation frame with view->animate and give a value for "FPS" and "Steps", the "Time" field shows the current value of $t.
//Pour obtenir le mode statique Temps=t FPS=0 Etapes=0 avec t=0 (sans éclaté) t=1 (éclaté)
include <dim1.scad>
include <z_f.scad>//Ce fichier contient pour zn deux séries de valeurs, celles dédiées à une représentation réelle (non éclatée) et celles dédiées à une représentation éclatée. La variable $t évoquée ci-dessus permet l'évolution progressive entre les 2 valeurs en créant ainsi une animation.
$fn=100;//nombre de facettes
use <visserie.scad> //Modules écrou, entretoise hexagonale, rondelle et vis
//Définition des couleurs
orange=[233/255, 93/255, 15/255];
vert=[151/255, 191/255, 13/255];
gris=[112/255, 113/255, 115/255];
noir=[0/255, 0/255, 0/255];
bleu=[51/255, 51/255, 255/255];
//Pour mettre en rotation rotate([0,0,$t*90])
translate([-10,0,0])rotate([0,0,0]){
//Assemblage des pièces de la e-p-433-v2
//vis M3 (1)
color( gris)vishexa(3,5,1.5,5.5,true,L2/2,l2/2,z1+$t*(z1_e-z1));
color( gris)vishexa(3,5,1.5,5.5,true,L2/2,-l2/2,z1+$t*(z1_e-z1));
color( gris)vishexa(3,5,1.5,5.5,true,-L2/2,l2/2,z1+$t*(z1_e-z1));
color( gris)vishexa(3,5,1.5,5.5,true,-L2/2,-l2/2,z1+$t*(z1_e-z1));
//Rondelles (2) supprimées
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
//Plateforme d'essais équipée (3) - version essais
union()translate([22,0,z3+$t*(z3_e-z3)]){
x=-49.53; y=-19.48; //Coordonnées du CI chargeur
//Vis M2.5 (3a)
color( gris)vis_M(2.5, 6.7, 1.5, true, x, y, z3a+$t*(z3a_e-z3a));
//Platine breadboard (3b)
color(bleu)translate([0,0,z3b+$t*(z3b_e-z3b)]) linear_extrude(height = 10, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/plateforme-essais.dxf", layer = "breadboard");};
//Rondelle isolante 2.5 ep=1.3 (3c)
rond_M(2.5, 1.3, x, y, z3c+$t*(z3c_e-z3c));
//Chargeur (3d)
color(orange)translate([0,0,z3d+$t*(z3d_e-z3d)])scale([1,1,1]) linear_extrude(height = 1, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/plateforme-essais.dxf", layer = "chargeur");}; //CI chargeur
//Rondelle isolante 2.5 ep=1.3 (3e)
rond_M(2.5, 1.3, x, y, z3e+$t*(z3e_e-z3e));
//Entretoise M2.5 (3f)
color( gris)ent_M(2.5,4.8,6,5,true, x, y, z3f+$t*(z3f_e-z3f)); 
//Plateforme d'essais (3g)
include <plateforme-essais.scad>
//Rondelle M2.5 (3h)
rond_M(2.5, 0.5, x, y, z3h+$t*(z3h_e-z3h));
//Ecrou M2.5 (3i)
color( gris)Ecrou(2.5,1.7, 4.8, x, y, z3i+$t*(z3i_e-z3i));
}
//Batterie (4)
color([255/255, 0/255, 0/255]) translate([0,0,z4+$t*(z4_e-z4)]) linear_extrude(height = 6, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/batterie.dxf", layer = "contour");};
//Entretoises hexagonales M3 femelles (5)
color( gris) Ecrou(3,10, 5.5, L2/2, l2/2,z5+$t*(z5_e-z5));
color( gris) Ecrou(3,10, 5.5, -L2/2, l2/2,z5+$t*(z5_e-z5));
color( gris) Ecrou(3,10, 5.5, L2/2, -l2/2,z5+$t*(z5_e-z5));
color( gris) Ecrou(3,10, 5.5, -L2/2, -l2/2,z5+$t*(z5_e-z5));
//Rondelles (6) supprimées
//Capteur de température (7)
translate([0,0,z7+$t*(z7_e-z7)])rotate([0,-90,180]){import("capteur.stl");}
//Jupe (8)
translate([0,0,z8+$t*(z8_e-z8)])color( vert){import("jupe.stl");}
//entretoises M3 (9)
color( gris)ent_M(2.5,4.9,8,5,false,L2/2,l2/2,z9+$t*(z9_e-z9));
color( gris)ent_M(2.5,4.9,8,5,false,-L2/2,-l2/2,z9+$t*(z9_e-z9));
color( gris)ent_M(2.5,4.9,8,5,false,L2/2,-l2/2,z9+$t*(z9_e-z9));
color( gris)ent_M(2.5,4.9,8,5,false,-L2/2,l2/2,z9+$t*(z9_e-z9));
//Vis M3 (10)
color( gris)vis_M(3, 6, 1.5, true, 8.5, 8.5, z10+$t*(z10_e-z10));
color( gris)vis_M(3, 6, 1.5, true, -8.5, 8.5, z10+$t*(z10_e-z10));
color( gris)vis_M(3, 6, 1.5, true, 8.5, -8.5, z10+$t*(z10_e-z10));
color( gris)vis_M(3, 6, 1.5, true, -8.5, -8.5, z10+$t*(z10_e-z10));
//Rondelle M3 (11)
rond_M(3, 0.5, 8.5, 8.5, z11+$t*(z11_e-z11));
rond_M(3, 0.5, -8.5, 8.5, z11+$t*(z11_e-z11));
rond_M(3, 0.5, 8.5, -8.5, z11+$t*(z11_e-z11));
rond_M(3, 0.5, -8.5, -8.5, z11+$t*(z11_e-z11));
//isolateur (12)
translate([0,0,z12+$t*(z12_e-z12)])color(orange)linear_extrude(height = 2, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/isolateur-433-v2.dxf", layer = "contour");};
//rondelles (13) supprimées
//vis M3 (14)
color( gris)vis_M(3, 6, 1.5, false, L2/2, l2/2, z14+$t*(z14_e-z14));
color( gris)vis_M(3, 6, 1.5, false, -L2/2, l2/2, z14+$t*(z14_e-z14));
color( gris)vis_M(3, 6, 1.5, false, L2/2, -l2/2, z14+$t*(z14_e-z14));
color( gris)vis_M(3, 6, 1.5, false, -L2/2, -l2/2, z14+$t*(z14_e-z14));
//Entretoise M3 (15)
color( gris)ent_M(3,4.9,8,4.8,true,8.5,8.5,z15+$t*(z15_e-z15));
color( gris)ent_M(3,4.9,8,4.8,true,-8.5,8.5,z15+$t*(z15_e-z15));
color( gris)ent_M(3,4.9,8,4.8,true,8.5,-8.5,z15+$t*(z15_e-z15));
color( gris)ent_M(3,4.9,8,4.8,true,-8.5,-8.5,z15+$t*(z15_e-z15));
//Entretoise en aluminium (16)
translate([0,0,z16+$t*(z16_e-z16)])rotate([0,0,0])color( [255/255, 0/255, 0/255]){import("ent-fixation.stl");}
//Capteur de température (17)
translate([x17+$t*(x17_e-x17),2,z17+$t*(z17_e-z17)])rotate([0,90,0]){import("capteur.stl");}
//Vis de serrage du capteur (18)
translate([-8.5,2,z18+$t*(z18_e-z18)])color( noir)cylinder(4,1.75,1.75,center=true);
//Connexion masse mécanique (19)
translate([x19-5+$t*(x19_e-x19),-3.4,z19+$t*(z19_e-z19)])rotate([0,90,0])color( noir)cylinder(14,0.9,0.9,center=true);
//Vis de serrage de la masse métallique (20)
translate([-8.5,-3.4,z20+$t*(z20_e-z20)])color( noir)cylinder(4,1.75,1.75,center=true);
//couvercle (21)
translate([0,0,z21+$t*(z21_e-z21)])color( [190/255, 190/255, 190/255]){import("Couvercle.stl");}

}