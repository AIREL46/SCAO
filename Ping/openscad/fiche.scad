$fn=120; 
R1=18.35; R2=16.73; e1=R1-R2; ent_axe=12.185; hc=30;
translate([0,0,z1])rotate([180,0,270])union(){
difference() {
    cylinder(hc,r=R1,center = true); //Grand cylindre
    translate([0,0,e1]) cylinder(hc,r=R2,center = true); //Petit cylindre
    scale([1,1.8,1])cylinder(32,r=9,center = true); //Ouverture
}
//Plot droit
difference() {
translate([ent_axe,0,-8.5]) cylinder(13,r=3,center = true); //Colonne droite
translate([ent_axe,0,-8.5]) cylinder(13*1.1,r=1.35,center = true); //Percage du trou de fixation droit
}
difference() {
translate([-ent_axe,0,-6.5]) cylinder(13,r=3,center = true); //Colonne gauche
translate([-ent_axe,0,-6.5]) cylinder(13*1.1,r=1.35,center = true); //Percage du trou de fixation gauche
}
//rotate([0,0,-10]) translate([-34/2.05 ,0,0]) scale([1.2,1,1]) union() {cylinder(0.9*24,r=3/3,center = true); translate([0,0,10.9]) sphere(r=3/3);}
}