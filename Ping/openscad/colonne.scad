//$fn=100;
include <dim1.scad>
translate([L2/2,l2/2,0])difference(){
cylinder(h2,2.5,2.5,center=true);
cylinder(1.1*h2,1.25,1.25,center=true);
}
translate([L2/2,-l2/2,0])difference(){
cylinder(h2,2.5,2.5,center=true);
cylinder(1.1*h2,1.25,1.25,center=true);
}
translate([-L2/2,-l2/2,0])difference(){
cylinder(h2,2.5,2.5,center=true);
cylinder(1.1*h2,1.25,1.25,center=true);
}
translate([-L2/2,l2/2,0])difference(){
cylinder(h2,2.5,2.5,center=true);
cylinder(1.1*h2,1.25,1.25,center=true);
}