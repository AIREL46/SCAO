$fn=100;
cube(size = [20,10,6], center = true);
translate([-13.5,0,0])cube(size = [7,7,2], center = true);
translate([13.5,0,0])rotate([0,90,0])cylinder(h = 50, r = 1, center = true);