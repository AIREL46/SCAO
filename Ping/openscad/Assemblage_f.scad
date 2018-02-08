include <dim1.scad>
include <z_ecl_f.scad>//ecl=éclaté secl=normal
$fn=100;//nombre de facettes
//Orange color([233/255, 93/255, 15/255])
//Vert color( [151/255, 191/255, 13/255])
//Gris color( [112/255, 113/255, 115/255])
//Module vis
haut=true;
module vis_M(M,l,k,haut,xt,yt,zt)
{
translate([xt,yt,zt])union(){
cylinder(h = l,r1 = M/2,r2 = M/2,center = true);
if (haut) {translate([0,0,((l/2)+(k/2))])cylinder(h = k,r1 = M,r2 = M,center = true);}
else {translate([0,0,-((l/2)+(k/2))])cylinder(h = k,r1 = M,r2 = M,center = true);}
}
}
//Module rondelle
module rond_M(M,ep,xt,yt,zt)
{
translate([xt,yt,zt])difference(){
cylinder(h = ep,r1 = M,r2 = M,center = true);
cylinder(h = 1.1*ep,r1 = M/2,r2 = M/2,center = true);
}
}
//Module Entretoise
haut=true; //Pour la partie hexagonale
module ent_M(M,l1_e,l2_e, x, haut, xt, yt,zt)
{r=x/tan(60);
translate([xt,yt,zt]){
difference(){
union(){
rotate([0,0,0])cube(size = [r,x,l1_e], center = true);
rotate([0,0,-60])cube(size = [r,x,l1_e], center = true);
rotate([0,0,-120])cube(size = [r,x,l1_e], center = true);
}
if (haut) translate([0,0,l2_e/4])cylinder(h = l2_e, r1 = M/2, r2 = M/2, center = true);
else translate([0,0,-l2_e/4])cylinder(h = l2_e, r1 = M/2, r2 = M/2, center = true);
}
if (haut) translate([0,0,-((l1_e/2)+(l2_e/2))])cylinder(h = l2_e, r1 = M/2, r2 = M/2, center = true);
else translate([0,0,((l1_e/2)+(l2_e/2))])cylinder(h = l2_e, r1 = M/2, r2 = M/2, center = true);
}
}
//vis M3 (1)
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, L2/2, l2/2, z1);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, -L2/2, l2/2, z1);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, L2/2, -l2/2, z1);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, -L2/2, -l2/2, z1);
//Rondelles (2)
rond_M(3, 1, L2/2, l2/2, z2);
rond_M(3, 1, L2/2, -l2/2, z2);
rond_M(3, 1, -L2/2, l2/2, z2);
rond_M(3, 1, -L2/2, -l2/2, z2);
//CI e-p-433 (3)
translate([0,0,z3]) color([233/255, 93/255, 15/255]) difference(){
minkowski() {cube([(3.2*25.4)-3,(3.2*25.4)-3,0.7], center=true); cylinder(0.7,3,3,center=true);}
translate([L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([-L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([-L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true);//Trou de fixation
translate([-1.05*25.4,0,-e/4])minkowski()
{
  cube([2.5,20,e/2], center=true);
  cylinder(r=2,h=e/2);
}//Trou pour les câbles des capteurs de température (prévoir de l'agrandir)
}
//Batterie (4)
color( [255/255, 0/255, 0/255]) translate([0,0,z4]) cube([23.6,35.2,5.7], center=true);
//Entretoises M3 femelle (5)
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
//Rondelles (6)
rond_M(3, 1, L2/2, l2/2, z6);
rond_M(3, 1, -L2/2, l2/2, z6);
rond_M(3, 1, L2/2, -l2/2, z6);
rond_M(3, 1, -L2/2, -l2/2, z6);
//Capteur de température (7)
translate([0,0,z7])rotate([0,-90,180])color( [0/255, 0/255, 0/255]){import("capteur.stl");}
//Jupe (8)
translate([0,0,z8])color( [151/255, 191/255, 13/255]){import("jupe.stl");}
//entretoises M3 (9)
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,false,L2/2,l2/2,z9);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,false,-L2/2,-l2/2,z9);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,false,L2/2,-l2/2,z9);
color( [112/255, 113/255, 115/255])ent_M(2.5,5,8,5,false,-L2/2,l2/2,z9);
//Vis M3 (10)
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, 8.5, 8.5, z10);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, -8.5, 8.5, z10);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, 8.5, -8.5, z10);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, true, -8.5, -8.5, z10);
//Rondelle M3 (11)
rond_M(3, 1, 8.5, 8.5, z11);
rond_M(3, 1, -8.5, 8.5, z11);
rond_M(3, 1, 8.5, -8.5, z11);
rond_M(3, 1, -8.5, -8.5, z11);
//isolateur (12)
translate([0,0,z12])color([233/255, 93/255, 15/255]){import("isolateur-bruno.stl");}
//rondelles (13)
rond_M(3, 1, L2/2, l2/2, z13);
rond_M(3, 1, -L2/2, l2/2, z13);
rond_M(3, 1, L2/2, -l2/2, z13);
rond_M(3, 1, -L2/2, -l2/2, z13);
//vis M3 (14)
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, false, L2/2, l2/2, z14);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, false, -L2/2, l2/2, z14);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, false, L2/2, -l2/2, z14);
color( [112/255, 113/255, 115/255])vis_M(3, 4, 1.5, false, -L2/2, -l2/2, z14);
//Entretoise M3 (15)
color( [112/255, 113/255, 115/255])ent_M(3,4.7,8.1,4.8,true,8.5,8.5,z15);
color( [112/255, 113/255, 115/255])ent_M(3,4.7,8.1,4.8,true,-8.5,8.5,z15);
color( [112/255, 113/255, 115/255])ent_M(3,4.7,8.1,4.8,true,8.5,-8.5,z15);
color( [112/255, 113/255, 115/255])ent_M(3,4.7,8.1,4.8,true,-8.5,-8.5,z15);
echo(z15);
//Entretoise en aluminium (16)
translate([0,0,z16])rotate([0,0,0])color( [255/255, 0/255, 0/255]){import("ent-alu.stl");}
//Capteur de température (17)
translate([x17,0,z17])rotate([0,90,0])color( [0/255, 0/255, 0/255]){import("capteur.stl");}
//Vis de serrage du capteur (18)
translate([-8.5,0,z18])color( [0/255, 0/255, 0/255])cylinder(4,1.75,1.75,center=true);
//couvercle (19)
translate([0,0,z19])color( [190/255, 190/255, 190/255]){import("Couvercle.stl");}

