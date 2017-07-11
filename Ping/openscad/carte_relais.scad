$fn=120;
include <dim_plt_arduino.scad>
difference(){
cube([2.2*C,1.9*C,1], center=true); //Carte relais
    translate([0.95*C,0.8*C,0]) cylinder(1.2,r1,r1, center=true);
    translate([0.95*C,-0.8*C,0]) cylinder(1.2,r1,r1, center=true);
    translate([-0.95*C,0.8*C,0]) cylinder(1.2,r1,r1, center=true);
    translate([-0.95*C,-0.8*C,0]) cylinder(1.2,r1,r1, center=true);
    }
     