//Initialisation des parametres
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

Cv(0,0);

module plot (x,y)
{
r1=4.9;//Rayon du cone inferieur
r2=4.95;//Rayon du cone superieur
rs=3.5;//Rayon de la sphere
difference()
	{
		translate([x,y,-3*e/2])cylinder(2*e,r1=r1,r2=r2,center=true);
		translate([x,y,-3*e/2])cylinder(2.1*e,r1=0.6*r1,r2=0.6*r2,center=true);
	}
}//module plot

translate([0,0,15])plot(0,0);
echo(r=1.008*(rc-e));
echo(r=1*(rc-e));