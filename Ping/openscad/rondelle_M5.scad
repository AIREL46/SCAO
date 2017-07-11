$fn=100;
include <dim1.scad>
e1=2.2;
translate([0,0,0])difference(){
cylinder(e1/2,5,5,center=true);
cylinder(1.1*e1/2,2.5,2.5,center=true);
}