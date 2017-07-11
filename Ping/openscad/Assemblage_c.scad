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
include <z_ecl_c.scad>//ecl=éclaté secl=normal
//Ecrous M3
translate([l1/2,l2/2,z2-36])color( [112/255, 113/255, 115/255]){import("ecrou_M3.stl");}
translate([l1/2,-l2/2,z2-36])color( [112/255, 113/255, 115/255]){import("ecrou_M3.stl");}
translate([-l1/2,l2/2,z2-36])color( [112/255, 113/255, 115/255]){import("ecrou_M3.stl");}
translate([-l1/2,-l2/2,z2-36])color( [112/255, 113/255, 115/255]){import("ecrou_M3.stl");}
//rondelle
translate([0,0,z3-35])color( [112/255, 113/255, 115/255]){import("rondelle.stl");}
//rondelles
//translate([0,0,z8])color( [112/255, 113/255, 115/255]){import("rondelle.stl");}
//Shield Arduino
translate([0,0,z6+8.5])color([233/255, 93/255, 15/255]){import("shield_arduino.stl");}
//Embase USB
translate([-2.7*CC/2,11,z7+4.5]) color([233/255, 93/255, 15/255]) cube([16,12.04,10.3], center=true); //Embase USB
//Carte Arduino
translate([0,0,z8+8])color([233/255, 93/255, 15/255]){import("carte_arduino.stl");}
//e-p ble
translate([0,0,z9])color( [151/255, 191/255, 13/255]){import("e_p_ble.stl");}
//ecrou M5
translate([0,0,z10])color( [112/255, 113/255, 115/255]){import("ecrou_M5.stl");}
//entretoises
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,L2/2,l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,-L2/2,-l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,L2/2,-l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,-L2/2,l2/2,z11);
//rondelle M5
translate([0,0,z12])color( [112/255, 113/255, 115/255]){import("rondelle_M5.stl");}
//isolateur
translate([0,0,z13])color([233/255, 93/255, 15/255]){import("isolateur.stl");}
//rondelles
translate([0,0,z14])color( [112/255, 113/255, 115/255]){import("rondelle.stl");}
//vis
translate([0,0,z15])rotate([180,0,0])color( [112/255, 113/255, 115/255]){import("vis.stl");}
//entretoise M5
color( [112/255, 113/255, 115/255])ent_M(5,16,8,8,0,0,z16);
//couvercle
//translate([0,0,z17])color( [190/255, 190/255, 190/255]){import("couvercle.stl");}

