$fn=100;
C1=32; //Longueur
C2=10;//Largeur
C3=4;//Hauteur

module Sangle()
{
difference()
{
minkowski()
	{
		cube([C1,C2,C3], center = true);
		sphere(1);
	}//minkowski
	cube([C1,C2,10*C3], center = true);
}

}
Sangle();
