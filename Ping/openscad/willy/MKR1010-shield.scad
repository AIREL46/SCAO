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
module shield() 
{

//PCB
#color(orange)translate([54.28/25.4,-63.175/25.4,-0.7/25.4])scale([1/25.4,1/25.4,1/25.4])rotate([0,0,180]){import("PCB.stl");}
difference() 
{
color(orange)linear_extrude(height = 0.05, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "shield");}
linear_extrude(height = 0.06, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "trous-fixation");}//trous vis M2
linear_extrude(height = 0.06, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "trous-vis");}//trous vis M3
translate([25.86/25.4,0,0])cube([0.4,0.1,1],center=true);//trou fil
}//difference


//Connecteurs
translate([0,0,0.215])color(noir)linear_extrude(height = 0.37, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "connecteur");}
translate([0,0,0.185])linear_extrude(height = 0.44, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "trous");}

//Batterie 
//color(rouge)translate([0,-0.1,0.165])linear_extrude(height = 0.28, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/MKR1010-shield.dxf", layer = "bat");}//
color(blanc)minkowski() 
{
translate([10/25.4,-34/25.4,5/25.4])rotate([0,0,0])scale([1/25.4,1/25.4,1/25.4])cube([50-6,29-6,8-6],center=true);//position verticale
sphere(3/25.4);
}

//Capteur de température (7)
translate([11/25.4,-32/25.4,10.5/25.4])scale([1/25.4,1/25.4,1/25.4])rotate([-90,90,180]){import("capteur.stl");}

//Boutons ()
/*color(bleu)translate([10/25.4,-40/25.4,0.05])scale([1/25.4,1/25.4,1/25.4])cube([8,4,2],center=true);
color(vert)translate([0/25.4,-40/25.4,0.05])scale([1/25.4,1/25.4,1/25.4])cube([8,4,2],center=true);
color(blanc)translate([-10/25.4,-40/25.4,0.05])scale([1/25.4,1/25.4,1/25.4])cube([8,4,2],center=true);*/

} //module