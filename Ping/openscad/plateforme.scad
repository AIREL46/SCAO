//Plateforme Arduino
$fn=120;
include <dim_plt_arduino.scad>
ouverture=false;
plt_arduino(true);
module plt_arduino(ouverture){
union()rotate([0,0,0]){
difference() {
minkowski()
{
 cube([L1-4*r1, l1-4*r1, e/2], center = true);
 cylinder(r=2*r1,h=e/2, center = true);
}
if (ouverture){scale([1,1.8,1])cylinder(30,r=9,center = true);} //Ouverture
translate([xt2,yt2,0]) cylinder(r=r1,h=1.1*e, center = true); //Passage de la vis 2
translate([xt2,yt2,-0.5]) cylinder(r=2*r1,h=1.1*e, center = true); //Logement de l'écrou 2
translate([xt3,yt3,0]) cylinder(r=r1,h=1.1*e, center = true); //Passage de la vis 3
translate([xt3,yt3,-0.5]) cylinder(r=2*r1,h=1.1*e, center = true); //Logement de l'écrou 3
}
//T1 -> Plot 1
translate([xt1,yt1,4]) cylinder(r=2.6,h=6, center = true);
translate([xt1,yt1,8]) cylinder(r=1.55,h=4, center = true);
//T2 -> Entretoise 2
difference() {
translate([xt2,yt2,1.5]) cylinder(r=4.5,h=2, center = true);
translate([xt2,yt2,1.5]) cylinder(r=1.6,h=2.1, center = true);
}
difference() {
translate([xt2,yt2,4.5]) cylinder(r=2.6,h=5, center = true);
translate([xt2,yt2,4.5]) cylinder(r=1.6,h=6, center = true);
}
//T3 -> Entretoise 3
difference() {
translate([xt3,yt3,1.5]) cylinder(r=4.5,h=2, center = true);
translate([xt3,yt3,1.5]) cylinder(r=1.6,h=2.1, center = true);
}
difference() {
translate([xt3,yt3,4.5]) cylinder(r=2.6,h=5, center = true);
translate([xt3,yt3,4.5]) cylinder(r=1.6,h=6, center = true);
}
//T4 -> Plot 4
translate([xt4,yt4,4]) cylinder(r=2.6,h=6, center = true);
translate([xt4,yt4,8]) cylinder(r=1.55,h=4, center = true);
}
}