//Unité : pouce
$fn=100;//nombre de facettes
//Définition des couleurs
orange=[233/255, 93/255, 15/255];
vert=[151/255, 191/255, 13/255];
gris=[112/255, 113/255, 115/255];
noir=[0/255, 0/255, 0/255];
bleu=[51/255, 51/255, 255/255];
blanc=[255/255, 255/255, 255/255];
MKR();

module MKR() {
color(vert)linear_extrude(height = 0.05, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010.dxf", layer = "0");}
translate([0,0,0])linear_extrude(height = 0.81, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010.dxf", layer = "trous");}
translate([0,0,0.065])color( gris)linear_extrude(height = 0.08, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010.dxf", layer = "usb");}
translate([0,0,0.12])color(blanc)linear_extrude(height = 0.20, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010.dxf", layer = "bat");}
translate([0,0,0.215])color(noir)linear_extrude(height = 0.37, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010.dxf", layer = "connecteur");}
}