//Visserie
//Ce progamme regroupe la visserie par ordre alphabétique : écrou, entretoise hexagonale, rondelle, vis. 
$fn=100;//nombre de facettes
module Ecrou(M,ep, x, xt, yt,zt)
//M est le métrique
//ep est l'épaisseur
//x est la valeur mesurée entre 2 pans opposés de l'hexagone
//xt, yt, zt sont les coordonnées
{r=x/tan(60);
translate([xt,yt,zt]){
difference(){
union(){
rotate([0,0,0])cube(size = [r,x,ep], center = true);
rotate([0,0,-60])cube(size = [r,x,ep], center = true);
rotate([0,0,-120])cube(size = [r,x,ep], center = true);
}
cylinder(h = 2*ep, r1 = M/2, r2 = M/2, center = true);
}
}
}
//ent_M(3,4.7,8.1,4.8,true,0,0,0); //Exemple
//Module Entretoise
//M est le métrique
//l1_e est la longueur de la partie hexagonale
//l2_e est la longueur de la tige filetée
//x est la valeur mesurée entre 2 pans opposés de l'hexagone
//haut : variable logique qui permet le positionnemt (haut ou bas) de la partie hexagonale
//xt, yt, zt sont les coordonnées
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
//Module rondelle
//M est le métrique
//ep est l'épaisseur de la rondelle
//xt, yt, zt sont les coordonnées
module rond_M(M,ep,xt,yt,zt)
{
translate([xt,yt,zt])difference(){
cylinder(h = ep,r1 = M,r2 = M,center = true);
cylinder(h = 1.1*ep,r1 = M/2,r2 = M/2,center = true);
}
}
//Module vis
//M est le métrique
//l longeur de la vis
//k épaisseur de la tête de vis
//haut : variable logique qui permet le positionnemt (haut ou bas) de la tête de vis
//xt, yt, zt sont les coordonnées
haut=true;
module vis_M(M,l,k,haut,xt,yt,zt)
{
translate([xt,yt,zt])union(){
cylinder(h = l,r1 = M/2,r2 = M/2,center = true);
if (haut) {translate([0,0,((l/2)+(k/2))])cylinder(h = k,r1 = M,r2 = M,center = true);}
else {translate([0,0,-((l/2)+(k/2))])cylinder(h = k,r1 = M,r2 = M,center = true);}
}
}
