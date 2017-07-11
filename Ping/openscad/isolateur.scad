$fn=100;
include <dim1.scad>
difference(){
cube(size = [L1,l1,e1], center = true);
translate([0,0,0])cylinder(h = 2*e1, r1 = 2.5, r2 = 2.5, center = true);
translate([L2/2,l2/2,0])cylinder(h = 2*e1, r1 = d1/2, r2 = d1/2, center = true);
translate([L2/2,-l2/2,0])cylinder(h = 2*e1, r1 = d1/2, r2 = d1/2, center = true);
translate([-L2/2,l2/2,0])cylinder(h = 2*e1, r1 = d1/2, r2 = d1/2, center = true);
translate([-L2/2,-l2/2,0])cylinder(h = 2*e1, r1 = d1/2, r2 = d1/2, center = true);
}