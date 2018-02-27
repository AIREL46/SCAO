$fn=100;
difference() {
color([206/255,206/255,206/255]) linear_extrude(height = 10, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/ent-fixation.dxf", layer = "contour");};
translate([0,0,-5])linear_extrude(height = 2*1.2, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/ent-fixation.dxf", layer = "lamage-5");};
translate([0,0,5])linear_extrude(height = 2*1.5, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/ent-fixation.dxf", layer = "lamage-3");};
translate([-9.5,0,0]) rotate([0,90,0]) cylinder(6.1,2.5,2.5,center=true);
}