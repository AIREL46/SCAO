$fn=100;
C=5; //rayon rotation
Diam=1;//Diametre cable
Lg=39;//éloignement
A=8;//longueur partie prise
module CableT1()
{
translate([-A-2*C,Lg/2+C,0])rotate([0,0,0]) cylinder(r=Diam,h=2*C,center=true);//Raccordement prise 1
translate([-A-2*C,Lg/2+2*C,C])rotate([0,-90,180])rotate_extrude(angle = 90,convexity = 10)translate([C, 0, 0])circle(r = Diam);//coude 1
translate([-A-2*C,Lg/2+2*C,C])rotate([0,-90,0])rotate_extrude(angle = 90,convexity = 10)translate([C, 0, 0])circle(r = Diam);//coude 2
translate([-A-C,Lg/2+3*C,C])rotate([90,90,180])rotate_extrude(angle = 90,convexity = 10)translate([C, 0, 0])circle(r = Diam);//coude 3
translate([-A/2-C,Lg/2+3*C,0]) rotate([0,90,0]) cylinder(r=Diam,h=A,center=true);//Raccordement prise 2
translate([-C,Lg/2+2*C,0])rotate([0,0,0])rotate_extrude(angle = 90,convexity = 10)translate([C, 0, 0])circle(r = Diam);//coude 4
translate([0,Lg/2+2*C,-C])rotate([0,-90,180])rotate_extrude(angle = 90,convexity = 10)translate([C, 0, 0])circle(r = Diam);//coude 5
translate([0,Lg/2+C,-16])rotate([0,0,0]) cylinder(r=Diam,h=22,center=true);//Raccordement jupe 1
rotate([0,90,0])translate([22+C,Lg/2,0])rotate_extrude(angle = 90,convexity = 10)translate([C, 0, 0])circle(r = Diam);//coude 6
translate([0,Lg/2,-22-2*C])rotate([90,0,0]) cylinder(r=Diam,h=4,center=false);//Raccordement prise 5
}

D=5; //rayon rotation
Ld=23;//éloignement
B=8;//longueur partie prise
module CableT2()
{
translate([-B-2*C,Ld/2+D,0])rotate([0,0,0]) cylinder(r=Diam,h=2*D,center=true);//Raccordement prise 1
translate([-B-2*D,Ld/2+2*D,D])rotate([0,-90,180])rotate_extrude(angle = 90,convexity = 10)translate([D, 0, 0])circle(r = Diam);//coude 1
translate([-B-2*C,Ld/2+2*D+B,2*D])rotate([90,0,0]) cylinder(r=Diam,h=B,center=false);//Raccordement prise 2
translate([-B-D,Ld/2+2*D+B,2*D])rotate([0,0,90])rotate_extrude(angle = 90,convexity = 10)translate([D, 0, 0])circle(r = Diam);//coude 2
translate([-B-D,Ld/2+3*D+B,2*D]) rotate([0,90,0]) cylinder(r=Diam,h=(B+D)+2*D,center=false);//Raccordement prise 3
translate([2*D,Ld/2+2*D+B,2*D])rotate([0,0,0])rotate_extrude(angle = 90,convexity = 10)translate([D, 0, 0])circle(r = Diam);//coude 3
translate([3*D,Ld/2+B+2*D,2*D])rotate([90,0,0]) cylinder(r=Diam,h=B+D,center=false);//Raccordement prise 4
translate([4*D,Ld/2+D,2*D])rotate([0,0,180])rotate_extrude(angle = 90,convexity = 10)translate([D, 0, 0])circle(r = Diam);//coude 4
translate([4*D,Ld/2,4/3*D])rotate([90,0,0])rotate_extrude(angle = 90,convexity = 10)translate([D*2/3, 0, 0])circle(r = Diam);//coude 5
translate([4*D+D*4/3,Ld/2,4/3*D])rotate([90,90,180])rotate_extrude(angle = 90,convexity = 10)translate([D*2/3, 0, 0])circle(r = Diam);//coude 6
}
CableT1(); 
CableT2(); 
