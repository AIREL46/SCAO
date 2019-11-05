//Unité : pouce
$fn=100;//nombre de facettes
use <Logo.scad>
use <top_a.scad>
use <MKR1010.scad>
use <MKR1010-shield.scad>
use <ent-fixation.scad>
use <jupe.scad>
use <isolateur-433-v2.scad>
translate([0,0,2.8])rotate([0,0,0])scale([1/25.4,1/25.4,1/25.4])logo();
translate([0,0,1.8])rotate([0,0,0])scale([1/25.4,1/25.4,1/25.4])top();
rotate([0,0,180]) {
shield();
translate([0,0,0.9])MKR();
}
translate([0,0,-0.8])rotate([0,0,0])scale([1/25.4,1/25.4,1/25.4])jup();
translate([0,0,-1.5])rotate([0,0,0])scale([1/25.4,1/25.4,1/25.4])isolateur();
translate([0,0,-1.9])rotate([0,0,0])scale([1/25.4,1/25.4,1/25.4])ent_fixation();