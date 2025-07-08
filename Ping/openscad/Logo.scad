logo();
module logo() {
//Parmi les 3 pieces de la e-poignee, cette piece a pour objet de recevoir le logo, soit colle, soit incruste.
//Il est compose d'une plateforme cylindrique equipee :
//d'une fenetre qui permet la visibilite de l'embase USB du CI
//de 4 plots prevus pour assurer l'assemblage par emboitement du logo sur le top.
//L'emboitement est realise grace a la forme conique des 4 plots qui s'introduisent dans les 4 lamages des cylindres verticaux du top.
//Chaque plot est evide par une sphere pour accueillir la tete bonbee de la vis de fixation du top. 

module plot (x,y){
r1=4.9;//Rayon du cone inferieur
r2=4.95;//Rayon du cone superieur
rs=3.5;//Rayon de la sphere
difference(){
		translate([x,y,-3*e/2])cylinder(2*e,r1=r1,r2=r2,center=true);
		translate([x,y,-3*e/2])cylinder(2.1*e,r1=0.6*r1,r2=0.6*r2,center=true);
}
}

//Initialisation des parametres
include <dim1.scad>
Rl=R-12;//Rayon du logo
$fn=100;

//Construction du logo
rotate([0,0,0]){

//Construction de la plateforme
difference(){
	//Construction du cylindre plateforme
	translate([0,0,0])cylinder(e,r=Rl,center=true);
	//Decoupe de la fenêtre USB
	translate([3+L2/2,0,0])minkowski(){cube(size = [8,6,1.1*e], center = true);
	cylinder(r=3,h=e);
	}
}

//Construction des 4 plots
plot(L2/2,l2/2);//Plot 1
plot(-L2/2,l2/2);//Plot 2
plot(-L2/2,-l2/2);//Plot 3
plot(L2/2,-l2/2);//Plot 4

}//rotate
}//module logo