//Parmi les 3 pieces de la e-poignee, le top a pour objet de reconduire
//la fonctionnalite traditionnelle de la poignee du couvercle de la casserole, c'est a dire, de permettre sa manutention.
//Une fonctionnalite complementaire est attendue, c'est celle dite de "milieu de table", le couvercle equipee de la e-poignee,
//apres une rotation de 180 degres, sert au soutien de la casserole.
//N.B. : cette fonctionnalite est envisageable si la conception, de la casserole et de son couvercle, le prevoit.
//Le top est compose de 3 parties, le tore, 4 cylindres verticaux et 4 cylindres horizontaux de raccordement.
//Le tore est la partie fonctionnelle telle que décrite ci-dessus,
//ses dimensions doivent tenir compte de la morphologie de la main.
//le diametre exterieur du tore est d'environ 85 mm, par rapport a une main feminine, cette dimension est optimale.
//Les 4 cylindres verticaux sont conçu pour repondre a 2 fonctionnalites, la premiere, la fixation du top, au dessus du CI, à l'aide de
//4 entretoises filetees et de 4 vis equipees de rondelles, la deuxieme, le maintien par simple emboitement du logo.
//Les 4 cylindres horizontaux de raccordement relient le tore aux cylindres verticaux.

//Initialisation des parametres
rouge_groseille=([207/255, 10/255, 29/255]);
$fn=100;
include <dim1.scad>
Rt=5.5;//Rayon du cercle de la section du tore
coef=0.67;// Coef translation du cylindre de raccordement

//module Cylindre vertical (Cv)
rc=7.5;//rayon du cylindre
module Cv(x,y)
{
difference()
	{
	translate([x,y,0])cylinder(h=2*Rt,r=rc,center=true);
	translate([x,y,e/2])cylinder(h=1.01*(2*Rt-e),r=1.008*(rc-e),center=true);//lamage
	translate([x,y,0])cylinder(h=20,r=1.15,center=true);//trou
	}
}

//Module Cylindre horizontal de raccordement
module Ch(x,y,z)
	{
	translate([x*coef,y*coef,0])rotate([90,0,z])cylinder(h=10,r=Rt/1.1,center=true);
	}
//Construction du top
color(rouge_groseille)translate([0,0,0])rotate([0,0,-90])difference()
{
union()
{
//Construction du tore
//http://en.wikibooks.org/wiki/OpenSCAD_User_Manual/2D_to_3D_Extrusion#Rotate_Extrude
//Le principe est celui de l'extrusion qui permet la conversion d'un objet 2D en un objet 3D.
//Le tore est construit en utilisant une instruction composee de 3 parties,
//"rotate_extrude" "convexity" = 10, qui realise l'extrusion circulaire,
//"translate" qui exprime le rayon du cercle de revolution,
//"circle" qui exprime le rayon du cercle de la section du tore.
translate([0,10,0])rotate_extrude(angle = 180,convexity = 10)translate([R, 0, 0])circle(r = Rt); //demie-couronne droite
translate([0,10,Rt])rotate_extrude(angle = 180,convexity = 10)translate([R, 0, 0])circle(r = 0.45*Rt); //demie-couronne droite du milieu de table

translate([0, -10,0])rotate_extrude(angle =-180,convexity = 10)translate([R, 0, 0])circle(r = Rt); //demie-couronne gauche
translate([0, -10,Rt])rotate_extrude(angle =-180,convexity = 10)translate([R, 0, 0])circle(r = 0.45*Rt); //demie-couronne gauche du milieu de table

translate([R,0,0]) rotate([90,0,0]) cylinder(r=Rt,h=20,center=true);//Cylindre de raccordement 1
translate([R,0,Rt]) rotate([90,0,0]) cylinder(r=0.45*Rt,h=20,center=true);//Cylindre de raccordement du milieu de table 1

translate([-R,0,0]) rotate([90,0,0]) cylinder(r=Rt,h=20,center=true);//Cylindre de raccordement 2
translate([-R,0,Rt]) rotate([90,0,0]) cylinder(r=0.45*Rt,h=20,center=true);//Cylindre de raccordement du milieu de table 2

//Construction des 4 cylindres verticaux
L=y1;//y1=entre axes de fixation du CI
l=x1;//x1=entre axes de fixation du CI
Cv(L/2,l/2);
Cv(L/2,-l/2);
Cv(-L/2,-l/2);
Cv(-L/2,l/2);

//Construction des 4 cylindres horizontaux de raccordement
Ch(-L,l,atan (L/l));
Ch(L,l,-atan (L/l));
Ch(-L,-l,-atan (L/l));
Ch(L,-l,atan (L/l));
}//union
//creation du plat
translate([0,0,-2*Rt/2])cube(size = [4*R,4*R,e/2], center = true);
difference()
{
translate([0,55,0])rotate([90,0,0])polyhedron(
	points=[ [13,13,0],[13,-13,0],[-13,-13,0],[-13,13,0],[0,0,40]  ], 
	faces=[ [0,1,4],[1,2,4],[2,3,4],[3,0,4],[1,0,3],[2,1,3] ]
	);//fenetre USB
translate([0,25,0])cube([30,30,15],center=true);
}
}//difference

