$fn=100;
ent_fixation();
module ent_fixation() {
difference() {
color([206/255,206/255,206/255]) linear_extrude(height = 10, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/ent-fixation.dxf", layer = "contour-dessous");};
//translate([0,0,-5])linear_extrude(height = 2*1.2, center = true, convexity = 10, scale = 1.0) {import(file = "/home/airel/SCAO/Ping/LibreCAD/ent-fixation.dxf", layer = "lamage-5");};
//translate([0,0,5])linear_extrude(height = 2*1.5, center = true, convexity = 10, scale = 1.0) {import(file = "/home/airel/SCAO/Ping/LibreCAD/ent-fixation.dxf", layer = "lamage-3");};
translate([-9.5,2,0]) rotate([0,90,0]) cylinder(6.1,2.5,2.5,center=true);
translate([-9.5,-3.4,0]) rotate([0,90,0]) cylinder(6.1,0.9,0.9,center=true);
}
}