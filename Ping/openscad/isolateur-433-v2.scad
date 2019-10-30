$fn=100;
isolateur();
module isolateur() {
color([206/255,206/255,206/255]) linear_extrude(height = 2, center = true, convexity = 10, scale = 1) {import(file = "/home/airel/SCAO/Ping/LibreCAD/isolateur-433-v2.dxf", layer = "contour");};
}