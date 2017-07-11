$fn=100;
include <dim1.scad>
difference(){
cube(size = [L1,l1,e], center = true);
translate([L2/2,l2/2,0])cylinder(h = 2*e, r = r, center = true);
translate([L2/2,-l2/2,0])cylinder(h = 2*e, r = r, center = true);
translate([-L2/2,l2/2,0])cylinder(h = 2*e, r = r, center = true);
translate([-L2/2,-l2/2,0])cylinder(h = 2*e, r = r, center = true);
}
difference(){
translate([(L1/2)-(0.34*25.4)/2,0,(e+(0.1*25.4))/2])cube(size = [0.34*25.4,0.32*25.4,0.1*25.4], center = true);
translate([L1/2,0,(e+(0.1*25.4))/2])cube(size = [0.1*25.4,0.25*25.4,0.08*25.4], center = true);
}
difference(){
translate([-(L1/2)+(0.3*25.4)/2,0,(e+(0.339*25.4))/2])cube(size = [0.3*25.4,0.32*25.4,0.339*25.4], center = true);
translate([-(L1/2),e,(e+(0.25*25.4))/2])cube(size = [0.07*25.4,0.07*25.4,0.07*25.4], center = true);
translate([-(L1/2),-e,(e+(0.25*25.4))/2])cube(size = [0.07*25.4,0.07*25.4,0.07*25.4], center = true);
}
