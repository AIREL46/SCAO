$fn=100;
difference() {
scale([25.4,25.4,25.4]) color([206/255,206/255,206/255]) linear_extrude(height = 0.1, center = true, convexity = 10, scale = 1) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/isolateur-433-v2.dxf", layer = "contour");};
}