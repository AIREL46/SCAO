$fn=120;
C=25.4;
difference() {
union() {
difference() {
scale([C,C,1]) linear_extrude(height = 2, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "volant");
scale([C,C,1]) linear_extrude(height = 2.1, center = true, convexity = 10) import(file = "e_r_ble.dxf", layer = "volant-trou");
}
translate([0, 0,0]) rotate_extrude(convexity = 10)
		translate([C*2.75, 0, 0])
		circle(r = C*0.4); //rayon du cercle de la section du tore
}
translate([0, 50,0]) cube([200,100,22], center=true);// coupe pour représentation de l'assemblage
}