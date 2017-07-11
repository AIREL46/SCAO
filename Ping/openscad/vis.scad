$fn=100;
include <dim1.scad>
translate([L2/2,l2/2,0])union(){
cylinder(h = 4, r1 = 1.25, r2 = 1.25, center = true);
translate([0,0,3])cylinder(h = 2, r1 = 3, r2 = 3, center = true);
translate([0,0,-2.5])cylinder(h = 1, r1 = 0.75, r2 = 1.25, center = true);
}
translate([-L2/2,l2/2,0])union(){
cylinder(h = 4, r1 = 1.25, r2 = 1.25, center = true);
translate([0,0,3])cylinder(h = 2, r1 = 3, r2 = 3, center = true);
translate([0,0,-2.5])cylinder(h = 1, r1 = 0.75, r2 = 1.25, center = true);
}translate([-L2/2,-l2/2,0])union(){
cylinder(h = 4, r1 = 1.25, r2 = 1.25, center = true);
translate([0,0,3])cylinder(h = 2, r1 = 3, r2 = 3, center = true);
translate([0,0,-2.5])cylinder(h = 1, r1 = 0.75, r2 = 1.25, center = true);
}translate([L2/2,-l2/2,0])union(){
cylinder(h = 4, r1 = 1.25, r2 = 1.25, center = true);
translate([0,0,3])cylinder(h = 2, r1 = 3, r2 = 3, center = true);
translate([0,0,-2.5])cylinder(h = 1, r1 = 0.75, r2 = 1.25, center = true);
}