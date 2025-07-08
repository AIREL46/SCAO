$fn=120;
include <dim_plt_arduino.scad>
//Orange color([233/255, 93/255, 15/255])
//Vert color( [151/255, 191/255, 13/255])
//Gris color( [112/255, 113/255, 115/255])
//Noir color( [0/255, 0/255, 0/255])
translate([-4,10,0]) rotate([0,0,90]) {
translate([0,0,-35.2]) rotate([0,0,0]) color( [151/255, 191/255, 13/255]) import ("e_r_ble.stl"); //Plateforme fiche mâle
//Arduino UNO
difference() {
translate([0,0,-27]) scale([C,C,1]) color([233/255, 93/255, 15/255]) linear_extrude(height = 2, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-contour");
translate([0,0,-27]) scale([C,C,1]) linear_extrude(height = 2.1, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-trou");
    }
translate([0,0,-24]) scale([C,C,1]) linear_extrude(height = 9, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-con");
translate([0,0,-22]) color( [0/255, 0/255, 0/255]) scale([C,C,1]) linear_extrude(height = 9, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-con-iso");
translate([-L2/2,10,-21]) color([233/255, 93/255, 15/255]) cube([16,12.04,10.3], center=true); //Embase USB
//Shield Arduino
difference() {
translate([0,0,-15]) scale([C,C,1]) color([233/255, 93/255, 15/255]) linear_extrude(height = 2, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-contour");
translate([0,0,-15]) scale([C,C,1]) linear_extrude(height = 2.1, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-trou");
     }
translate([0,0,-14]) scale([C,C,1]) linear_extrude(height = 9, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-con");
translate([0,0,-11]) color( [0/255, 0/255, 0/255]) scale([C,C,1]) linear_extrude(height = 9, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "c-a101-con-iso");
     
translate([0,0,-7]) color([233/255, 93/255, 15/255]) cube([23,24,18], center=true); //Bloc alim
translate([0,0,11.5]) rotate([180,0,180]) color( [151/255, 191/255, 13/255]) import ("plt_relais_a.stl"); // Plateforme relais
translate([0,0,-70]) linear_extrude(height = 19, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "fm-broche-m"); // Broches mâles de la fiche 230V
difference() {
translate([0,0,-62]) color( [112/255, 113/255, 115/255]) linear_extrude(height = 2, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "fm-socle"); // Socle de la fiche 230V
translate([0,0,-62]) color( [112/255, 113/255, 115/255]) linear_extrude(height = 2.1, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "fm-trou"); // 2 trous de fixation de la fiche 230V
translate([0,0,-62]) color( [112/255, 113/255, 115/255]) linear_extrude(height = 2.1, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "fm-broche-f"); // Broche femelle de la fiche 230V
    }
translate([-1.7*C,-1.1*C,18]) color([233/255, 93/255, 15/255]) import("3051.stl"); //Carte relais
rotate([0,0,-90]) translate([-0.9*C,0.3*C,18]) color([233/255, 93/255, 15/255]) import("1122.stl"); //Carte mesure de courant
translate([0,0,85]) rotate([0,0,0]) color( [151/255, 191/255, 13/255]) import ("plt_ff.stl"); //Plateforme fiche femelle
translate([0,0,85]) color([250/255, 240/255, 230/255]) scale([C,C,1]) linear_extrude(height = 3, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "fav-dec-laser");//Face avant
//3 leds
translate([0,0,85]) color( [0/255, 255/255, 0/255]) scale([C,C,1]) linear_extrude(height = 6, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "fav-led-v");
translate([0,0,85]) color( [255/255, 255/255, 0/255]) scale([C,C,1]) linear_extrude(height = 6, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "fav-led-j");
translate([0,0,85]) color( [255/255, 0/255, 0/255]) scale([C,C,1]) linear_extrude(height = 6, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "fav-led-r");
//Texte
translate([0,0,85]) color( [151/255, 191/255, 13/255]) scale([0.5,0.5,1]) rotate([0,0,-90]) translate([-35,20,2]) text("Quiet", font = "Liberation Sans:style=Bold");
translate([0,-19,85]) color([233/255, 93/255, 15/255]) scale([0.5,0.5,1]) rotate([0,0,-90]) translate([-35,20,2]) text("cook", font = "Liberation Sans:style=Bold");
//translate([0,0,15]) rotate([0,0,0]) color( [151/255, 191/255, 13/255]) import ("volant.stl"); //Volant
translate([0,0,57.5]) rotate([0,0,0]) color( [112/255, 113/255, 115/255]) import ("fiche-f.stl"); //Fiche femelle
translate([0,0,79.5]) linear_extrude(height = 14.3, center = true, convexity = 10) import(file = "e_r_ble_mm.dxf", layer = "ff-broche-m");//Fiche male
translate([-9.55,0,86.8]) sphere(d=4.8);

}//Rotate