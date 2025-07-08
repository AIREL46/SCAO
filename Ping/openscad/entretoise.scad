//Entretoise
//Modelisation 3D d'une entretoise avec les options, hauteur, logements pour un ecrou (haut et bas), raccord (haut et bas)
$fn=120;//nombre de facettes
include <dim_plt_arduino.scad>
he=25;
r=5;
ec_h=false; //Logement ecrou haut
ec_b=true; //Logement ecrou bas
rac_h=false; //Raccord haut
rac_b=false; //Raccord bas
deg_h=true; //Dégagement haut
//entretoise(he, ec_h, ec_b, rac_h, rac_b, deg_h);
module entretoise(he, ec_h, ec_b, rac_h, rac_b, deg_h){
difference(){
union() {
cylinder(he, r, r, center=true);
if (rac_h) {z=he/2; raccord (z);}
if (rac_b) {z=-he/2; raccord (z);}
    }
cylinder(1.2*he,1.6,1.6,center=true);
if (ec_h) {translate([0,0,(he/2)-5])rotate([90,0,0])cube([5.6,2.8,12], center=true);}
if (ec_b) {translate([0,0,-((he/2)-5)])rotate([90,0,0])cube([5.6,2.8,12], center=true);}
if (deg_h) {difference(){
    translate([0,0,he/2]) cylinder(he/2, 1.1*r, 1.1*r, center=true);
    translate([0,0,he/2]) cylinder(he/2, r/2, r/2, center=true);
    } //difference
    } //if
}
}
module raccord (z) {
difference() {
translate([0,0,z])hull() {
   translate([15,0,0]) cylinder(e, r, r, center=true);
   cylinder(e, r, r, center=true);
 }
 translate([15,0,z]) cube([2.7*r,3*r,1.1*e], center=true);
 }
 }
