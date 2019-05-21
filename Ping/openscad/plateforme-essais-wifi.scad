//Plateforme d'essais de la e-p-433-wifi
include <dim1.scad>
$fn=120;//nombre de facettes
difference(){
translate([50,0,0])color([206/255,206/255,206/255]) scale([1,1,1])linear_extrude(height = 2*e, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/plateforme-essais-wifi.dxf", layer = "contour");}; //Plateforme
translate([50,0,e])scale([1,1,1]) linear_extrude(height = 2*e, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/plateforme-essais-wifi.dxf", layer = "lamage-dessus");}; //Lamage du dessus
}