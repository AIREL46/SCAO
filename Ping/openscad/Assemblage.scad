include <dim1.scad>
$fn=100;//nombre de facettes
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
include <z_ecl.scad>
//Thermocouple
translate([-24,0,zth1])rotate([0,90,0])color( [255/255, 0,0])cylinder(h = 7, r = 1, center = true);
translate([-27,0,zth2])color( [255/255, 0,0])cylinder(h = h, r = 1, center = true);
translate([-16,0,zth3])rotate([0,90,0])color( [255/255, 0,0])cylinder(h = 24, r = 1, center = true);
translate([-5,0,zth4])color( [255/255, 0,0])cylinder(h = 15, r = 1, center = true);
translate([0,0,z1])color( [151/255, 191/255, 13/255]){import("logo.stl");}
translate([0,0,z2])color( [112/255, 113/255, 115/255]){import("vis.stl");}
translate([0,0,z3])color( [112/255, 113/255, 115/255]){import("rondelle.stl");}
translate([0,0,z4])color( [151/255, 191/255, 13/255]){import("top.stl");}
translate([0,0,z5])color( [112/255, 113/255, 115/255]){import("colonne.stl");}
translate([33,0,z6])scale([0.65,0.65,0.65])color([0, 0, 0]){import("Cable USB.stl");}
translate([0,0,z7])color([233/255, 93/255, 15/255]){import("CI.stl");}
translate([0,0,z8])color( [112/255, 113/255, 115/255]){import("rondelle.stl");}
translate([0,0,z9])color( [151/255, 191/255, 13/255]){import("jupe.stl");}
translate([0,0,z10])color( [112/255, 113/255, 115/255]){import("ecrou_M5.stl");}
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,L2/2,l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,-L2/2,-l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,L2/2,-l2/2,z11);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,-L2/2,l2/2,z11);
translate([0,0,z12])color( [112/255, 113/255, 115/255]){import("rondelle_M5.stl");}
translate([0,0,z13])color([233/255, 93/255, 15/255]){import("isolateur.stl");}
translate([0,0,z14])color( [112/255, 113/255, 115/255]){import("rondelle.stl");}
translate([0,0,z15])rotate([180,0,0])color( [112/255, 113/255, 115/255]){import("vis.stl");}
color( [112/255, 113/255, 115/255])ent_M(5,16,8,8,0,0,z16);
translate([0,0,z17])color( [190/255, 190/255, 190/255]){import("couvercle.stl");}

