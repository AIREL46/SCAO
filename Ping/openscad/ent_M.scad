//$fn=100;
include<dim1.scad>
//Module Entretoise
module ent_M(M,l1_e,l2_e, x, xt, yt)
//M comme métrique (diamètre de la partie filetée)
//l1_e est la longueur de la partie hexagonale femelle
//l2_e est la longueur de la partie male
//x est le quotient du rayon r par la tangente 60°
{r=x/tan(60);
translate([xt,yt,0]){
difference(){
union(){
rotate([0,0,0])cube(size = [r,x,l1_e], center = true);
rotate([0,0,-60])cube(size = [r,x,l1_e], center = true);
rotate([0,0,-120])cube(size = [r,x,l1_e], center = true);
}//union
translate([0,0,-l2_e/4])cylinder(h = l2_e, r1 = M/2, r2 = M/2, center = true);//filetage femelle
}//difference
translate([0,0,((l1_e/2)+(l2_e/2))-0.5])cylinder(h = l2_e-1, r1 = M/2, r2 = M/2, center = true);
translate([0,0,((l1_e/2)+(l2_e))-0.5])cylinder(h = 1, r1 = M/2, r2 = (M/2)-0.5, center = true);
}//translate
}//module
ent_M(2.5,5,8,5,L2/2,l2/2);
ent_M(2.5,5,8,5,-L2/2,-l2/2);
ent_M(2.5,5,8,5,L2/2,-l2/2);
ent_M(2.5,5,8,5,-L2/2,l2/2);