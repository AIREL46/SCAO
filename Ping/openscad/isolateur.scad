$fn=100;
difference() {
color([206/255,206/255,206/255]) linear_extrude(height = 2.5, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/e-p-bruno.dxf", layer = "cont-iso");};
}