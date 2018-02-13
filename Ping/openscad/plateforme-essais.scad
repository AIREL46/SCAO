//Plateforme d'essais de la e-p-433-v2
include <dim1.scad>
$fn=100;//nombre de facettes
difference(){
translate([0,0,0])color([206/255,206/255,206/255]) scale([CC,CC,CC])linear_extrude(height = 0.2, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/plateforme-essais.dxf", layer = "contour");}; //Plateforme
translate([0,0,e])scale([CC,CC,CC]) linear_extrude(height = 0.2, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/plateforme-essais.dxf", layer = "lamage-dessus");}; //Lamage du dessus
translate([0,0,-e])scale([CC,CC,CC]) linear_extrude(height = 0.2, center = true, convexity = 10, scale = 1.0) {import(file = "/home/leruste/SCAO/Ping/LibreCAD/plateforme-essais.dxf", layer = "lamage-dessous");}; //Lamage du dessous
}