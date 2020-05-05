//Ce programme permet la représentation de l'assemblage des différentes pièces de la e-p-433-WIFI
include <dim1.scad>
include <z_f.scad>//Ce fichier contient pour zn deux séries de valeurs, celles dédiées à une représentation réelle (non éclatée) et celles dédiées à une représentation éclatée. La variable $t évoquée ci-dessus permet l'évolution progressive entre les 2 valeurs en créant ainsi une animation. Pour activer l'animation -> menu Vue - animation, saisir les paramètres (FPS et étapes), l'animation se met en place, en fonction du nombre d'étapes sélectionnées, le temps s'incrémente. Pour l'arrêter sur la vue éclatée, retourner dans Vue et cliquer à nouveau sur animer.
$fn=100;//nombre de facettes
use <visserie.scad> //Modules écrou, entretoise hexagonale, rondelle et vis
use <MKR1010.scad>
use <MKR1010-shield.scad>
use <ent-fixation.scad>
use <jupe_wifi.scad>
use <Cable T.scad>
use <Sangle.scad>
//Définition des couleurs
orange=[233/255, 93/255, 15/255];
vert=[151/255, 191/255, 13/255];
gris=[112/255, 113/255, 115/255];
noir=[0/255, 0/255, 0/255];
bleu=[51/255, 51/255, 255/255];
blanc=[255/255, 255/255, 255/255];
rouge=[255/255, 0/255, 0/255];
//couvercle (20) sous l'entretoise en alu
translate([0,0,z21+$t*(z21_e-z21)])color( [190/255, 190/255, 190/255]){import("Couvercle.stl");}
//Jupe (8)
//#translate([0,0,z8+$t*(z8_e-z8)])color(vert){import("jupe_wifi.stl");}
//entretoises M3 (13+15) 4 entretoises sur l'isolateur (2 avec tige)
color( gris)ent_M(2.5,5,6,5,false,L2/2,l2/2,z9+$t*(z9_e-z9));
color( gris)ent_M(2.5,5,0,5,false,-L2/2,-l2/2,z9+$t*(z9_e-z9));
color( gris)ent_M(2.5,5,6,5,false,L2/2,-l2/2,z9+$t*(z9_e-z9));
color( gris)ent_M(2.5,5,0,5,false,-L2/2,l2/2,z9+$t*(z9_e-z9));
//Vis M3 (14) 4 vis sur l'isolateur
color( gris)vis_M(3, 6, 1.5, true, 8.5, 8.5, z10+$t*(z10_e-z10));
color( gris)vis_M(3, 6, 1.5, true, -8.5, 8.5, z10+$t*(z10_e-z10));
color( gris)vis_M(3, 6, 1.5, true, 8.5, -8.5, z10+$t*(z10_e-z10));
color( gris)vis_M(3, 6, 1.5, true, -8.5, -8.5, z10+$t*(z10_e-z10));
//Rondelle M3 (11) 4 rondelles sur l'isolateur
rond_M(3, 0.5, 8.5, 8.5, z11+$t*(z11_e-z11));
rond_M(3, 0.5, -8.5, 8.5, z11+$t*(z11_e-z11));
rond_M(3, 0.5, 8.5, -8.5, z11+$t*(z11_e-z11));
rond_M(3, 0.5, -8.5, -8.5, z11+$t*(z11_e-z11));
//isolateur (12)
translate([0,0,z12+$t*(z12_e-z12)])color(orange)linear_extrude(height = 2, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/isolateur-433-v2.dxf", layer = "contour");};
//vis M3 (14) 4 vis tête en bas sous l'isolateur
color( gris)vis_M(3, 6, 1.5, false, L2/2, l2/2, z14+$t*(z14_e-z14));
color( gris)vis_M(3, 6, 1.5, false, -L2/2, l2/2, z14+$t*(z14_e-z14));
color( gris)vis_M(3, 6, 1.5, false, L2/2, -l2/2, z14+$t*(z14_e-z14));
color( gris)vis_M(3, 6, 1.5, false, -L2/2, -l2/2, z14+$t*(z14_e-z14));
//vis M3 (14) 1 vis tête en bas sous la JUPE
color( gris)vis_M(3, 6, 1.5, false, -L2/2,0, 12);
//Vis M3 (14) 2 vis sur la JUPE
color( gris)vis_M(3, 5, 1.5, true, -L2/2, l2/2, 9);
color( gris)vis_M(3, 5, 1.5, true, -L2/2, -l2/2, 9);
//Entretoise M3 (15) 4 entretoises sous l'isolateur (avec tige)
color( gris)ent_M(3,4.9,8,4.8,true,8.5,8.5,z15+$t*(z15_e-z15));
color( gris)ent_M(3,4.9,8,4.8,true,-8.5,8.5,z15+$t*(z15_e-z15));
color( gris)ent_M(3,4.9,8,4.8,true,8.5,-8.5,z15+$t*(z15_e-z15));
color( gris)ent_M(3,4.9,8,4.8,true,-8.5,-8.5,z15+$t*(z15_e-z15));
//Entretoise en aluminium (16)
translate([0,0,z16+$t*(z16_e-z16)])rotate([0,0,0])color( [206/255,206/255,206/255]){ent_fixation();}
//Capteur de température (17) dans l'entretoise en alu
translate([x17+$t*(x17_e-x17),2,z17+$t*(z17_e-z17)])rotate([0,90,0]){import("capteur.stl");}
//Vis de serrage du capteur (18) dans l'entretoise en alu
translate([-8.5,2,z18+$t*(z18_e-z18)])color( noir)cylinder(4,1.75,1.75,center=true);
//Connexion masse mécanique (19) dans l'entretoise en alu
translate([x19-5+$t*(x19_e-x19),-3.4,z19+$t*(z19_e-z19)])rotate([0,90,0])color( noir)cylinder(14,0.9,0.9,center=true);
//Vis de serrage de la masse métallique (18) dans l'entretoise en alu
translate([-8.5,-3.4,z20+$t*(z20_e-z20)])color( noir)cylinder(4,1.75,1.75,center=true);
//vis M3 (14) 3 vis sur le circuit imp
color( gris)vis_M(3,5,1.5,true,L2/2,l2/2,hauteur-28.4);
color( gris)vis_M(3,5,1.5,true,L2/2,-l2/2,hauteur-28.4);
color( gris)vis_M(3,5,1.5,true,-L2/2,0,hauteur-28.4);
//color( gris)vishexa(3,5,1.5,5.5,true,-L2/2,-l2/2,20.8);
//Rondelle M3 (11) 3 rondelles sous + 3 dessus circuit imp
rond_M(3, 0.5, L2/2,l2/2, hauteur-28);
rond_M(3, 0.5, L2/2,-l2/2,  hauteur-28);
rond_M(3, 0.5, -L2/2,0,  hauteur-28);
rond_M(3, 0.5, L2/2,l2/2, hauteur-26.1);
rond_M(3, 0.5, L2/2,-l2/2, hauteur-26.1);
rond_M(3, 0.5, -L2/2,0, hauteur-26.1);
//Entretoises hexagonales M3 femelles (5) 3 entretoises sous le circuit imp
color( gris) Ecrou(3,8, 5.5, L2/2, l2/2,15.8);
color( gris) Ecrou(3,8, 5.5, L2/2, -l2/2,15.8);
color( gris) Ecrou(3,8, 5.5, -L2/2, 0,15.8);
//Vis M2 (9) 4 vis sur le TOP
color( gris)vis_M(2, 30, 1.5, true, x1/2,y1/2, hauteur-18);
color( gris)vis_M(2, 30, 1.5, true, x1/2,-y1/2, hauteur-18);
color( gris)vis_M(2, 30, 1.5, true, -x1/2,y1/2, hauteur-18);
color( gris)vis_M(2, 30, 1.5, true, -x1/2,-y1/2, hauteur-18);
//Entretoise M2 ronde (21) 4 entre le circuit imp et le MKR WIFI
color( blanc)ent_R(2.2,4,10,x1/2,y1/2,hauteur-21.3);
color( blanc)ent_R(2.2,4,10,-x1/2,y1/2,hauteur-21.3);
color( blanc)ent_R(2.2,4,10,x1/2,-y1/2,hauteur-21.3);
color( blanc)ent_R(2.2,4,10,-x1/2,-y1/2,hauteur-21.3);
//Entretoise M2 ronde (22) 4 entre le MKR WIFI et le TOP
color( blanc)ent_R(2.2,4,10,x1/2,y1/2,hauteur-9.9);
color( blanc)ent_R(2.2,4,10,-x1/2,y1/2,hauteur-9.9);
color( blanc)ent_R(2.2,4,10,x1/2,-y1/2,hauteur-9.9);
color( blanc)ent_R(2.2,4,10,-x1/2,-y1/2,hauteur-9.9);
//Ecrou M2 (10) 4 écrous sous circuit imp
Ecrou(2, 1.6, 4,x1/2,y1/2, hauteur-28.7);
Ecrou(2, 1.6, 4,-x1/2,y1/2, hauteur-28.7);
Ecrou(2, 1.6, 4,x1/2,-y1/2, hauteur-28.7);
Ecrou(2, 1.6, 4,-x1/2,-y1/2,hauteur-28.7);
//Rondelle M2 (10) 4 rondelles sous circuit imp
rond_M(2, 0.3, x1/2,y1/2, hauteur-27.8);
rond_M(2, 0.3, -x1/2,y1/2, hauteur-27.8);
rond_M(2, 0.3, x1/2,-y1/2, hauteur-27.8);
rond_M(2, 0.3, -x1/2,-y1/2, hauteur-27.8);
//Vis M2 (9) 2 vis sur l'équerre
color( gris)vis_M(2, 6, 1.5, true, 6,decalage-2, hauteur-27.4);
color( gris)vis_M(2, 6, 1.5, true, -6,decalage-2, hauteur-27.4);
//Ecrou M2 (10) 2 écrous sous équerre
Ecrou(2, 1.6, 4,6,decalage-2, hauteur-28.4);
Ecrou(2, 1.6, 4,-6,decalage-2, hauteur-28.4);
//TOP (6) entraxe du MKR WIFI
hauteur=48;
#translate([0,0,hauteur])rotate([0,0,-90])color(orange){import("top.stl");}
//LOGO (7) monté sur le TOP
translate([0,0,hauteur+7])rotate([0,0,-90])color(vert){import("Logo.stl");}
//SHIELD (Batterie(4) + circuit imp(2)) + MKR (3)
translate([0,0,hauteur-27])rotate([0,0,-180])scale([25.4,25.4,25.4])
{
shield(); 
translate([0,0,0.45])MKR();
}
//Cable USB ()
#translate([43,0,hauteur-14])rotate([0,0,0])color(gris){import("Cable USB.stl");}
//Cable du thermometre
//translate([0,0,hauteur-22])rotate([0,0,90])
{
//color(vert)CableT1();
//color(bleu)translate([0,2,0])CableT1();
//color(rouge)translate([0,-2,0])CableT1();
//color(vert)translate([0,0,2])CableT2(); 
//color(bleu)translate([0,2,2])CableT2(); 
//color(rouge)translate([0,-2,2])CableT2(); 
}
//Sangle batterie
translate([0,32.5,hauteur-23])rotate([90,0,90])
{
color(vert)Sangle();
translate([0,0,-20])color(vert)Sangle();
}