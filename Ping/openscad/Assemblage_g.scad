//Unité : pouce
$fn=100;//nombre de facettes
use <MKR1010.scad>
use <MKR1010-shield.scad>
use <ent-fixation.scad>
rotate([0,0,180]) {
shield();
translate([0,0,0.9])MKR();
}
translate([0,0,-0.9])rotate([0,0,0])scale([1/25.4,1/25.4,1/25.4])ent_fixation();