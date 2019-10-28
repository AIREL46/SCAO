//Unité : pouce
$fn=100;//nombre de facettes
//Définition des couleurs
orange=[233/255, 93/255, 15/255];
vert=[151/255, 191/255, 13/255];
gris=[112/255, 113/255, 115/255];
noir=[0/255, 0/255, 0/255];
bleu=[51/255, 51/255, 255/255];
blanc=[255/255, 255/255, 255/255];
rouge=[255/255, 0/255, 0/255];
translate([0,0,1.5])shield();
module shield() {
difference() {
color(vert)linear_extrude(height = 0.05, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "shield");}
linear_extrude(height = 0.06, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "trous-fixation");}
}
translate([0,0,0.215])color(noir)linear_extrude(height = 0.37, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "connecteur");}
translate([0,0,0.185])linear_extrude(height = 0.44, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "trous");}
color(rouge)translate([0,0,0.165])linear_extrude(height = 0.28, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "bat");}
}

