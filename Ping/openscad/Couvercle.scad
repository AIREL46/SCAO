include <dim1.scad>
$fn=100;
cylinder(h = e, r = 1.2*R, center = true);
translate([0,0,(e/2)+3])cylinder(h = 6, r = 2.5, center = true);