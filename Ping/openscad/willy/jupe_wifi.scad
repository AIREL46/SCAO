usb=false; v433=true; ent=false; lamage=false;
//Ce fichier permet la modélisation de 2 versions de jupe, la version USB et la version 433MHZ. En option ajout : 4 entretoises pour sureleve le CI et 4 lamages.
//Parmi les 3 pieces de la e-poinee, la jupe a pour objet de constituer l'habillage de la partie inferieure.
//Elle a la forme d'un parallelepipede (cube) dont les angles sont arrondis,
//elle est constituee de 4 flancs lateraux et d'une partie superieure appellee plateforme.
//cette plateforme est percee de 4 trous qui permettent, au dessus, la fixation du CI, et au dessous, la fixation de l'isolateur,
//N.B. : l'isolateur a les memes dimensions que le CI,
//Pour tenir compte de la contrainte thermique liee a la proximite de la jupe et du couvercle,
//Il est necessaire d'eviter leur contact, mieux, menager un petit espace entre eux.
//En outre, cet espace constitue l'entree d'un flux d'air ambiant.
//Ce flux d'air sort par une ouverture prevue sur la plateforme.
//Cette aeration naturelle permet de maitriser la temperature sous la jupe et donc celle du CI.
//La hauteur de la jupe hj est ajustee en consequence.
//En complement, une autre ouverture permet le passage du cable du thermocouple.
//Les longueurs (interieure et exterieure) et les largeurs (interieure et exterieure) de la jupe
//correspondent a celles du CI (longueur L1, largeur l1) auxquelles viennent s'ajouter un multiple de e, soit :
//longueur exterieure = L1+4*e, longueur interieure = L1+2*e,
//largeur exterieure = l1+4*e, largeur interieure = l1+2*e.
//Ce programme utilise principalement les instructions rotate, difference, union et minkowski.
//L'instruction rotate realise une rotation de 180 degres necessaire a l'impression 3D.
//L'instruction difference va permettre de retirer de la matiere aux endroits adequats.
//L'instruction union va permettre de grouper le grand cube et la goulotte.
//L'instruction minkowski effectue la somme d'un parallelepipede (cube) et d'un cylindre,
//ce cylindre va permettre d'arrondir les angles du cube,
//la somme minkowski est calculee selon les 3 axes (x, y et z) et prend en compte les dimensions du cube et du cylindre,
//l'instruction minkowski permet les contructions successives d'un "grand cube" et d'un "petit cube".
//l'instruction difference entre le "grand cube" et le "petit cube" genere la jupe,
//attention : pour gerer correctement les dimensions, il convient :
//selon l'axe z, pour retrouver la hauteur hj, de dimensionner hauteur du cube et du cylindre à hj/2.
//selon les axes x et y, le "grand cube", dimensionne son cube aux dimensions du CI, et son cylindre, à 2*e,
//le "petit cube", dimensionne son cube aux dimensions du CI, et son cylindre, à e,
//Pour verifier les dimensions énoncees ci-dessus,
//il faut additionner a la dimension du CI (L1 ou l1)
//2 fois celle du rayon du cylindre (celui situe sur la partie gauche et celui situe sur la partie droite de la jupe).

//Initialisation des parametres
vert=([151/255, 191/255, 13/255]);
$fn=120;
include <dim1.scad>
hj=23.34;//hauteur de la jupe
//Coordonnées des entretoises composées chacune d'un cylindre, d'un lamage et d'un percage
xe=L2/2;//Coordonnée x du cylindre
ye=l2/2;//Coordonnée y du cylindre
ze1=(hj/2)-(3*e/4);//Coordonnée z1 du lamage
ze2=hj/2;//Coordonnée z2 du percage


//module aeration
x=0; y=0; z=0; y1=0; h1=0; r1=0; 
module air (x,y,z,y1,h1,r1)
{
	translate([x,y,z]) hull() 
	{
   	 	translate([0,y1,0]) cylinder(h = h1, r = r1, center = true);
    		translate([0,-y1,0]) cylinder(h = h1, r = r1, center = true);
    		cylinder(h = h1, r = r1, center = true);
	}
}//fin du module air

//Début module percement de la jupe
percement=true;
module per_jupe (percement)
{
	//Percage des trous de fixation :
	translate([L2/2,l2/2,hj/2])cylinder(h = hj/2, r = r, center = true);
	translate([-L2/2,-l2/2,hj/2])cylinder(h = hj/2, r = r, center = true);
	translate([-L2/2,l2/2,hj/2])cylinder(h = hj/2, r = r, center = true);
	translate([L2/2,-l2/2,hj/2])cylinder(h = hj/2, r = r, center = true);
	translate([-L2/2,0,hj/2])cylinder(h = hj/2, r = r, center = true);
	//Percage du trou central
	//translate([0,0,hj/2])cylinder(h = hj/2, r = 3.5*r, center = true);
	//coupe pour representation de l'assemblage :
  	//  translate([0,-l1/2,-e])cube(size = [L1,l1/2,hj], center = true);

	//Ouverture pour le passage du cable du thermocouple dans la goulotte :
	minkowski()
	{
		translate([-((L1/2)+(1.5*e)),0,0])cube(size = [2*r,r/2,1.1*hj], center = true);
		cylinder(h = hj/2, r = e, center = true);
	}

	//Ouverture pour ventilation de la version USB
	if (usb) 
	{
		translate([0,0,hj/2])cylinder(h = hj/2, r = L2/2, center = true);
	}
	if (v433) 
	{
		translate([0,0,hj/2])scale([1.3,1,1])cylinder(h = hj/2, r = 10, center = true);
		//air (-L2/2,0,(hj/2)-e/2,6,1.1*e,1.5);
		//air (-1+L2/2,0,(hj/2)-e/2,6,1.1*e,1.5);
		air (4+L2/2,0,(hj/2)-e/2,6,1.1*e,1.5);
		//trous pour sangler la batterie avec serre câble
		//translate([L2/2,0,(hj/2)-e/2])cube(size = [1.5,14,1.1*e], center = true);
		//translate([-L2/2,0,(hj/2)-e/2])cube(size = [1.5,14,1.1*e], center = true);
	}
	if (lamage)
	{
		//Lamage et percage des 4 entretoises :
		translate([xe,ye,(ze1*0.9)])cylinder(h = e, r = 1.9*r, center = true);//Lamage
		translate([xe,ye,(ze1*0.9)])rotate([0,0,45])cube(size = [3*e,e,e], center = true);//Dégagement
		translate([xe,ye,ze2])cylinder(h = 2*e, r = r, center = true);//Percage
		translate([-xe,ye,(ze1*0.9)])cylinder(h = e, r = 1.9*r, center = true);//Lamage
		translate([-xe,ye,(ze1*0.9)])rotate([0,0,-45])cube(size = [3*e,e,e], center = true);//Dégagement
		translate([-xe,ye,ze2])cylinder(h = 2*e, r = r, center = true);//Percage
		translate([xe,-ye,(ze1*0.9)])cylinder(h = e, r = 1.9*r, center = true);//Lamage
		translate([xe,-ye,(ze1*0.9)])rotate([0,0,-45])cube(size = [3*e,e,e], center = true);//Dégagement
		translate([xe,-ye,ze2])cylinder(h = 2*e, r = r, center = true);//Percage
		translate([-xe,-ye,(ze1*0.9)])cylinder(h = e, r = 1.9*r, center = true);//Lamage
		translate([-xe,-ye,(ze1*0.9)])rotate([0,0,45])cube(size = [3*e,e,e], center = true);//Dégagement
		translate([-xe,-ye,ze2])cylinder(h = 2*e, r = r, center = true);//Percage
	}//fin if
}//fin module percement de la jupe

//Début module jupe
jupe(percement);
module jupe(percement)
{
	color([151/255, 191/255, 13/255])rotate([0,0,0])
	{
		//Construction de la jupe
		difference()
		{
			//Contruction du grand cube et de sa goulotte :
			union()
			{
				minkowski()
				{
					cube(size = [L1,l1,hj/2], center = true);
					cylinder(h = hj/2, r = 2*e, center = true);
				}//minkowski
				translate([-((L1/2)+(3*e/2)),0,0])cylinder(h = hj, r = 5*r, center = true); //Goulotte
				//Ajouter les 4 cylindres des entretoises
				if (ent) 
				{
					translate([xe,ye,ze2])cylinder(h = e, r = 2*r, center = true);
					translate([-xe,ye,ze2])cylinder(h = e, r = 2*r, center = true);
					translate([xe,-ye,ze2])cylinder(h = e, r = 2*r, center = true);
					translate([-xe,-ye,ze2])cylinder(h = e, r = 2*r, center = true);
				}
			}//union
			//Construction du petit cube :
			difference()
			{
				translate([0,0,-e])minkowski()
				{
					cube(size = [L1,l1,hj/2], center = true);
					cylinder(h = hj/2, r = e, center = true);
				}//minkowski
			}//difference
			if (percement) 
			{
				per_jupe ();
			}//if
		}//difference
	}//rotate
	if (usb) 
	{
		translate([0.99*(2*e+L1/2), -13.5, -5])rotate([90, 0, 90])linear_extrude(height=1, scale=[1,1])text("USB");
	}
	if (v433) 
	{
		translate([0.99*(2*e+L1/2), -14, -5])rotate([90, 0, 90])linear_extrude(height=1, scale=[1,1])text("WIFI");
	}
}//module jupe
