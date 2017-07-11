//Plate-forme fiche femelle
$fn=120;
C=25.4;
use <entretoise.scad>
include <entretoise.scad>
difference() {
linear_extrude(height = 3, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "cc-contour");
linear_extrude(height = 3.1, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-int");
scale([C,C,1]) linear_extrude(height = 3.1, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "plt-ff-trou");
scale([C,C,1]) linear_extrude(height = 3.1, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "fav-contour");
}
//color([220/255,220/255,220/255]) scale([C,C,1]) linear_extrude(height = 3, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "fav-dec-laser");
//color([0/255,0/255,0/255]) scale([0.5,0.5,1]) rotate([0,0,-90]) translate([-35,20,2]) text("Quiet cook");
difference() {
translate([0,0,-9.75]) linear_extrude(height = 16.5, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-ext");
translate([0,0,-9.75]) linear_extrude(height = 17, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-int");
}
difference() {
translate([0,0,-27.15]) linear_extrude(height = 34.8, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-int");
translate([0,0,-27.15]) linear_extrude(height = 35, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-epaule");
}
difference() {
translate([0,0,-35]) linear_extrude(height = 17.3, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-trou");
    translate([0,0,-35]) linear_extrude(height = 18.3, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-trou2"); 
}
translate([-3.5,0,-35]) linear_extrude(height = 17.3, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-trou");
//Entretoises
he=68;
translate([-1.55*C, 0.95*C, -(-1.5+he/2)]) entretoise(he,false, true, false, false, false);
translate([-1.55*C, -0.95*C, -(-1.5+he/2)]) entretoise(he,false, true, false, false, false);
translate([1.55*C, 0.75*C, -(-1.5+he/2)]) entretoise(he,false, true, false, false, false);
translate([1.55*C, -0.75*C, -(-1.5+he/2)]) entretoise(he,false, true, false, false, false);