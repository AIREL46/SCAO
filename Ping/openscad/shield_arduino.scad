include <dim_plt_arduino.scad>
$fn=120;
difference() {
cube([L2,l2,ep_sh], center=true);
    translate([xt1,yt1,0]) cylinder(1.1*ep_sh,r1,r1,center=true);
    translate([xt2,yt2,0]) cylinder(1.1*ep_sh,r1,r1,center=true);
    translate([xt3,yt3,0]) cylinder(1.1*ep_sh,r1,r1,center=true);
    translate([xt4,yt4,0]) cylinder(1.1*ep_sh,r1,r1,center=true);
}