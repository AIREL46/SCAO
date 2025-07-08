//Plateforme Relais
$fn=120;
include <dim_plt_arduino.scad>
xt5=(L1/2)-0.15*C; xt6=xt5; xt8=(L1/2)-1.75*C; xt7=xt8;//xt des 4 trous de percage de la carte relais
yt5=0.95*C; yt6=-yt5; yt7=-yt5; yt8=-yt6;//yt des 4 trous de percage de la carte relais
use <entretoise.scad>
include <entretoise.scad>
ouverture=false;//pas d'ouverture
rotate([0,180,0]) {
plt_arduino(ouverture); //Appel du module plt_arduino
he=46.5;
translate([-((L1/2)-1.6),-0.2*C,-((he/2)-e/2)]) entretoise(he, false, true, false, false, false);//Entretoise avec raccord a la plateforme
}//Rotate
module plt_arduino(ouverture){
union() {
difference() {
minkowski()
{
 cube([L1-4*r1, l1-4*r1, e/2], center = true);
 cylinder(r=2*r1,h=e/2, center = true);
}
if (ouverture){scale([1,1.8,1])cylinder(30,r=9,center = true);} //Ouverture
//Aération de la carte relais
scale([25.4,25.4,1]) linear_extrude(height = 5, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-rel-air");
//rotate([0,0,0]) translate([12,6,0])hull() {
  //translate([0,-12,0]) cylinder(10, 13, 13, center=true);
  //cylinder(10, 13, 13, center=true);
 //}
translate([xt2,yt2,0]) cylinder(r=2*r1,h=1.1*e, center = true); //Passage de la vis 2
//translate([xt2,yt2,-0.5]) cylinder(r=2*r1,h=1.1*e, center = true); //Logement de l'écrou 2
translate([xt3,yt3,0]) cylinder(r=r1,h=1.1*e, center = true); //Passage de la vis 3
//translate([xt3,yt3,-0.5]) cylinder(r=2*r1,h=1.1*e, center = true); //Logement de l'écrou 3
scale([25.4,25.4,1]) linear_extrude(height = 1.1*e, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-rel-trou");
scale([25.4,25.4,1]) linear_extrude(height = 1.1*e, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-mesi-cable");
//translate([xt5,yt5,0]) cylinder(r=r1,h=1.1*e, center = true);//trou de percage de la carte relais
//translate([xt6,yt6,0]) cylinder(r=r1,h=1.1*e, center = true);//trou de percage de la carte relais
//translate([xt7,yt7,0]) cylinder(r=r1,h=1.1*e, center = true);//trou de percage de la carte relais
//translate([xt8,yt8,0]) cylinder(r=r1,h=1.1*e, center = true);//trou de percage de la carte relais
rotate([0,0,0]) scale([25.4,25.4,1]) linear_extrude(height = 1.1*e, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-mesi-trou");
}
//T1 -> Plot 1
//translate([xt7,yt7,(he/2-5)]) entretoise(he-10, false, true);
//translate([xt1,yt1,he/2]) cylinder(r=2.6,h=he, center = true);
//translate([xt1,yt1,(he-10)+5]) cylinder(r=1.55,h=10, center = true);
he=25;
translate([xt2,yt2,-he/2]) entretoise(he, true, true, false, false, false);//T2 -> Entretoise 2
translate([xt3,yt3,-he/2]) entretoise(he, false, true, false, false, true);//T3 -> Entretoise 3 + trou de fixation de la carte relais
//T4 -> Plot 4
//translate([xt4,yt4,he/2]) cylinder(r=2.6,h=he, center = true);
//translate([xt4,yt4,he+2]) cylinder(r=1.55,h=4, center = true);
}//difference
//translate([-10,15,e/3]) scale([0.6,0.6,1.3])linear_extrude( height=e/2, center = true) {text ("plt_relais");}//Gravure du nom de la plateforme
}//union
