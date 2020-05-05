//Unité : pouce
$fn=100;//nombre de facettes
//Définition des couleurs
orange=[233/255, 93/255, 15/255];
vert=[151/255, 191/255, 13/255];
gris=[112/255, 113/255, 115/255];
noir=[0/255, 0/255, 0/255];
bleu=[51/255, 51/255, 255/255];
blanc=[255/255, 255/255, 255/255];
rouge=[255/255, 0/255, 0/255];

//taille de l'equerre :
lo=20;//longueur
la=10;//largeur
hj=10;//hauteur
ep=2;//epaisseur paroi
color(vert)difference()
{
	union()
	{
	cube([lo,la,ep], center = true);
	translate([0,la/2-ep/2,hj/2-ep/2])cube([lo,ep,hj], center = true);
	difference()
	{
	translate([0,0,hj/2-ep/2])rotate([0,0,0])cube([ep,la,hj], center = true);
	translate([0,-5,10])rotate([45,0,0])cube([4,14,14], center = true);
	translate([0,2,2])cube([4,2,3], center = true);
	}//difference
	}
	//Percage des trous de fixation :
	translate([6,-2,0])cylinder(h = hj/2, r = 1.15, center = true);
	translate([-6,-2,0])cylinder(h = hj/2, r = 1.15, center = true);
}//difference

//sangle
translate([0,9.5,2])difference()
{
minkowski()
	{
		cube([50,9,0.5], center = true);
		sphere(1);
	}//minkowski
	cube([50,9,10], center = true);
}
translate([0,9.5,2])difference()
{
minkowski()
	{
		cube([20,13,0.5], center = true);
		sphere(1);
	}//minkowski
	cube([20,13,10], center = true);
	translate([0,2,0])cube([50,13,10], center = true);
}