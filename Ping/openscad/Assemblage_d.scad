include <dim1.scad>
$fn=100;//nombre de facettes
//Orange color([233/255, 93/255, 15/255])
//Vert color( [151/255, 191/255, 13/255])
//Gris color( [112/255, 113/255, 115/255])
//Module Entretoise
module ent_M(M,l1_e,l2_e, x, xt, yt,zt)
{r=x/tan(60);
translate([xt,yt,zt]){
difference(){
union(){
rotate([0,0,0])cube(size = [r,x,l1_e], center = true);
rotate([0,0,-60])cube(size = [r,x,l1_e], center = true);
rotate([0,0,-120])cube(size = [r,x,l1_e], center = true);
}
translate([0,0,-l2_e/4])cylinder(h = l2_e, r1 = M/2, r2 = M/2, center = true);
}
translate([0,0,(l1_e/2)+(l2_e/2)])cylinder(h = l2_e, r1 = M/2, r2 = M/2, center = true);
}
}
include <z_secl_d.scad>//ecl=éclaté secl=normal
//vis M3
translate([0,0,z1])rotate([0,0,0])color( [112/255, 113/255, 115/255]){import("vis.stl");}
//Rondelles
translate([0,0,z2]){import("rondelle.stl");}
//CI e-p-433
translate([0,0,z3]) color([233/255, 93/255, 15/255]) difference(){
minkowski() {cube([(3.2*25.4)-3,(3.2*25.4)-3,0.7], center=true); cylinder(0.7,3,3,center=true);}
translate([L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([-L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([-L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([-1.05*25.4,0,0]) cylinder(e,2.5,2.5,center=true);//Trou pour le câble du thermocouple

}
//Batterie
color( [255/255, 0/255, 0/255]) translate([0,0,z4]) cube([23.6,35.2,5.7], center=true);
//Entretoises M3 femelle
color( [112/255, 113/255, 115/255]) translate([0,0,z5]) union() {difference(){
    translate([L2/2,l2/2,0]) cylinder(8,3,3,center=true);
    translate([L2/2,l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
    difference(){
    translate([L2/2,-l2/2,0]) cylinder(8,3,3,center=true);
    translate([L2/2,-l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
    difference(){
    translate([-L2/2,-l2/2,0]) cylinder(8,3,3,center=true);
    translate([-L2/2,-l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
    difference(){
    translate([-L2/2,l2/2,0]) cylinder(8,3,3,center=true);
    translate([-L2/2,l2/2,0]) cylinder(1.1*8,1.6,1.6,center=true);
    }
}

//Rondelles
translate([0,0,z6]){import("rondelle.stl");}   
//Jupe
translate([0,0,z9])color( [151/255, 191/255, 13/255]){import("jupe.stl");}
//ecrou M5
translate([0,0,z10])color( [112/255, 113/255, 115/255]){import("ecrou_M5.stl");}
//entretoises M3
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,L2/2,l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,-L2/2,-l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,L2/2,-l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,-L2/2,l2/2,z11);
//rondelle M5
translate([0,0,z12]){import("rondelle_M5.stl");}
//isolateur
translate([0,0,z13])color([233/255, 93/255, 15/255]){import("isolateur.stl");}
//rondelles
translate([0,0,z14]){import("rondelle.stl");}
//vis M3
translate([0,0,z15])rotate([180,0,0])color( [112/255, 113/255, 115/255]){import("vis.stl");}
//entretoise M5
color( [112/255, 113/255, 115/255])ent_M(5,16,8,8,0,0,z16);
//couvercle
translate([0,0,z17])color( [190/255, 190/255, 190/255]){import("couvercle.stl");}

