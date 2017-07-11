include <dim1.scad>
$fn=100;//nombre de facettes
x=0; y=0; z=0;
module sup_bat(x,y,z) {
//Support de batterie
translate([x,y,z]) difference(){
    union() {cube([L1,l1,2.4], center=true); translate([0,0,2]) cube([26,l1,2], center=true);}
    translate([L2/2,0,0]) cylinder(e,1,1,center=true); //Trou pour sangler la batterie
    translate([-L2/2,0,0]) cylinder(e,1,1,center=true); //Trou pour sangler la batterie
    translate([L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true); //Trou de fixation 1
    translate([L2/2,l2/2,1]) cylinder(e,3.1,3.1,center=true); //Chanfrein 1
    translate([-L2/2,l2/2,0]) cylinder(e,1.6,1.6,center=true); //Trou de fixation 2
    translate([-L2/2,l2/2,1]) cylinder(e,3.1,3.1,center=true); //Chanfrein 2
    translate([L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true); //Trou de fixation 3
    translate([L2/2,-l2/2,1]) cylinder(e,3.1,3.1,center=true); //Chanfrein 3
    translate([-L2/2,-l2/2,0]) cylinder(e,1.6,1.6,center=true); //Trou de fixation 4
    translate([-L2/2,-l2/2,1]) cylinder(e,3.1,3.1,center=true); //Chanfrein 4
    //translate([0,0,0]) scale([1.3,1,1]) cylinder(e,6,6,center=true);
    translate([0,0,2.2]) cube(size = [24,L1,4], center = true);
    }
}
sup_bat();