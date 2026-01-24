rotate([0,0,-90])logo();
module logo() 
{
//Parmi les 3 pieces de la e-poignee, cette piece a pour objet de recevoir le logo, soit colle, soit incruste.
//Il est compose d'une plateforme cylindrique equipee :
//d'une fenetre qui permet la visibilite de l'embase USB du CI
//de 4 plots prevus pour assurer l'assemblage par emboitement du logo sur le top.
//L'emboitement est realise grace a la forme conique des 4 plots qui s'introduisent dans les 4 lamages des cylindres verticaux du top.
//Chaque plot est evide par une sphere pour accueillir la tete bonbee de la vis de fixation du top. 
module plot (x,y)
{
r1=4.9;//Rayon du cone inferieur
r2=4.95;//Rayon du cone superieur
rs=3.5;//Rayon de la sphere
color(rouge_groseille)difference()
	{
		translate([x,y,-3*e/2])cylinder(2*e,r1=r1,r2=r2,center=true);
		translate([x,y,-3*e/2])cylinder(2.1*e,r1=0.6*r1,r2=0.6*r2,center=true);
	}
}//module plot

//Initialisation des parametres
include <dim1.scad>
//Rl=R-12;//Rayon du logo
Rl=50-12;
$fn=100;
rouge_groseille=([207/255, 10/255, 29/255]);
//Construction du logo
//Construction de la plateforme
color(rouge_groseille)translate([5,-16,1.5])rotate([0,0,90])linear_extrude(height=1, scale=[1,1], center=true)text("S C I");
color(rouge_groseille)difference()
{
	//Construction du cylindre plateforme
	translate([0,0,0])cylinder(e,r=Rl,center=true);
	//Decoupe de la fenêtre USB
	//translate([3+L2/2,0,0])minkowski(){cube(size = [8,6,1.1*e], center = true);
	//cylinder(r=3,h=e);
	//}
	difference()
	{
		translate([25,0,0])cube([50,80,10],center=true);
		translate([-75,0,0])cylinder(r=100,h=12,center=true);
	}
	difference()
	{
		translate([-25,0,0])cube([50,80,10],center=true);
		translate([75,0,0])cylinder(r=100,h=12,center=true);
	}
	difference()
	{
		translate([0,55,0])rotate([90,0,0])polyhedron(
			points=[ [13,13,0],[13,-13,0],[-13,-13,0],[-13,13,0],[0,0,40]  ], 
			faces=[ [0,1,4],[1,2,4],[2,3,4],[3,0,4],[1,0,3],[2,1,3] ]
			);//fenetre USB
		translate([0,20,0])cube([30,20,15],center=true);
	}
	rotate([0,0,180])difference()
	{
		translate([0,55,0])rotate([90,0,0])polyhedron(
			points=[ [13,13,0],[13,-13,0],[-13,-13,0],[-13,13,0],[0,0,40]  ], 
			faces=[ [0,1,4],[1,2,4],[2,3,4],[3,0,4],[1,0,3],[2,1,3] ]
			);//fenetre USB
		translate([0,20,0])cube([30,20,15],center=true);
	}
	//translate([0,0,e])rotate([0,0,90])scale([0.06,0.06,1])linear_extrude(height = 5, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/cuisinier.dxf", layer = "0");};
	translate([10,-18,e])rotate([0,0,90])scale([1,1,1])linear_extrude(height = 4, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/a3c.dxf", layer = "0");};
	*translate([10,-18,1.2*e])rotate([0,0,90])scale([1,1,1])linear_extrude(height = 4, center = true, convexity = 10, scale = 1.0) {import(file = "../LibreCAD/a3c.dxf", layer = "Etiquette");};
}

L=y1;
l=x1;
//Construction des 4 plots
plot(L/2,l/2);//Plot 1
plot(-L/2,l/2);//Plot 2
plot(-L/2,-l/2);//Plot 3
plot(L/2,-l/2);//Plot 4
}//module logo
//Marquage SCI
