$fn=120;
rotate([0,0,0]){
union(){
difference(){
cylinder(4.58,2.29,2.29,center=true);
translate([3.86,0,0])cube([4.58,4.58,5], center=true);
}
}
//translate([0,0,-4.79])cube([0.46,0.38,5], center=true);
//translate([0,1.27,-4.79])cube([0.46,0.38,5], center=true);
//translate([0,-1.27,-4.79])cube([0.46,0.38,5], center=true);
}