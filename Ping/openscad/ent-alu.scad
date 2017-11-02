$fn=100;
difference() {
color([206/255,206/255,206/255]) linear_extrude(height = 10, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/ent-alu.dxf", layer = "contour");};
translate([-12,0,0]) rotate([0,90,0]) cylinder(13.4,3,3,center=true);
}