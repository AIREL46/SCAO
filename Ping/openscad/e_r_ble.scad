//Le e-rupteur ble est contitué de 3 parties, la fiche équipée de 2 plots de fixation, la plateforme Arduino et la goulotte 230V
$fn=120;
ar=-45;//Angle de rotation des plots de fixation
//Dimensions de la fiche
R1=18.35; R2=16.73; e1=R1-R2; ent_axe=12.185; hc=30;
use <plateforme.scad> //Mise à disposition de la plateforme
include <dim_plt_arduino.scad>
union(){//union1
difference(){
union(){//union2
translate([0,0,-13.5])cylinder(hc,r=R1,center = true); //Grand cylindre de la fiche
plt_arduino(ouverture=false); //Construction de la plateforme Arduino
rotate([0,90,90])translate([0,0,20])scale([1,2,1])cylinder(r=5.5, h=14, center = true);//Contruction de la goulotte 230V
translate([-((L1/2)-1.6),-0.2*C,0]) cylinder(r=5.5, h=e, center = true);//raccord a la plateforme
}//union2
//Percement plateforme + fiche
translate([0,0,-13.5])cylinder(hc+8,r=R2,center = true); //Percement du cylindre de la fiche
rotate([0,90,90])translate([0,0,20])scale([1,2,1])cylinder(r=4, h=15, center = true);//Percement de la goulotte 230V
translate([-((L1/2)-1.6),-0.2*C,0]) cylinder(r=r1, h=1.1*e, center = true);//percement du raccord a la plateforme
}//difference
//Ajout des plots de fixation
//Plot droit
rotate([0,0,ar])translate([ent_axe,0,-5])difference() {
hull() {
   translate([3.25,0,0]) cylinder(13,4,4,center=true);
   cylinder(13,4,4,center=true);
 }
cylinder(13*1.1,r=1.35,center = true); //Percage du trou de fixation droit
}
//Plot gauche
rotate([0,0,ar])translate([-ent_axe,0,-5])difference() {
hull() {
   translate([-3.25,0,0]) cylinder(13,4,4,center=true);
   cylinder(13,4,4,center=true);
 }
cylinder(13*1.1,r=1.35,center = true); //Percage du trou de fixation gauche
}
}//union1
