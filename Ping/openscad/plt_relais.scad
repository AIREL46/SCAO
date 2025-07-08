//Plateforme Relais
$fn=120;
include <dim_plt_arduino.scad>
//La carte relais utilise comme premier trou de fixation T3
xt5=xt3; xt6=xt3-1.9*C; xt7=xt3-1.9*C;//xt des 3 autres trous de percage de la carte relais
yt5=yt3+1.6*C; yt6=yt3; yt7=yt3+1.6*C;//yt des 3 autres trous de percage de la carte relais
xl=-1.2*C;//xl des 3 leds
yl2=0; yl1=0.5*C; yl3=-yl1;//yl des 3 leds
delta=-0.375*C;
use <entretoise.scad>
include <entretoise.scad>
//he=37;//hauteur de l'entretoise
ouverture=false;//pas d'ouverture
rotate([180,0,0]) {
plt_arduino(ouverture); //Appel du module plt_arduino
he=44.5;
translate([-((L1/2)-1.6),-0.2*C,-((he/2)-e/2)]) entretoise(he, false, true, false, false);//Entretoise avec raccord a la plateforme
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
translate([xl,yl1,0]) cylinder(r=2.5,h=1.1*e, center = true);//trou de percage de la led1
translate([xl,yl2,0]) cylinder(r=2.5,h=1.1*e, center = true);//trou de percage de la led2
translate([xl,yl3,0]) cylinder(r=2.5,h=1.1*e, center = true);//trou de percage de la led3
//Aération de la carte relais
translate([10,0,0])hull() {
   translate([-12,0,0]) cylinder(10, 13, 13, center=true);
   cylinder(10, 13, 13, center=true);
 }
translate([xt2,yt2,0]) cylinder(r=2*r1,h=1.1*e, center = true); //Passage de la vis 2
//translate([xt2,yt2,-0.5]) cylinder(r=2*r1,h=1.1*e, center = true); //Logement de l'écrou 2
translate([xt3,yt3,0]) cylinder(r=r1,h=1.1*e, center = true); //Passage de la vis 3
//translate([xt3,yt3,-0.5]) cylinder(r=2*r1,h=1.1*e, center = true); //Logement de l'écrou 3
translate([xt5,yt5,0]) cylinder(r=r1,h=1.1*e, center = true);//trou de percage de la carte relais
translate([xt6,yt6,0]) cylinder(r=r1,h=1.1*e, center = true);//trou de percage de la carte relais
translate([xt7,yt7,0]) cylinder(r=r1,h=1.1*e, center = true);//trou de percage de la carte relais
}
//T1 -> Plot 1
//translate([xt7,yt7,(he/2-5)]) entretoise(he-10, false, true);
//translate([xt1,yt1,he/2]) cylinder(r=2.6,h=he, center = true);
//translate([xt1,yt1,(he-10)+5]) cylinder(r=1.55,h=10, center = true);
he=25;
translate([xt2,yt2,-he/2]) entretoise(he, true, true, false, false);//T2 -> Entretoise 2
translate([xt3,yt3,-he/2]) entretoise(he, true, true, false, false);//T3 -> Entretoise 3 + trou de fixation de la carte relais
//T4 -> Plot 4
//translate([xt4,yt4,he/2]) cylinder(r=2.6,h=he, center = true);
//translate([xt4,yt4,he+2]) cylinder(r=1.55,h=4, center = true);
}//difference
//translate([-10,15,e/3]) scale([0.6,0.6,1.3])linear_extrude( height=e/2, center = true) {text ("plt_relais");}//Gravure du nom de la plateforme
}//union
