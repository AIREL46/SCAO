//e_poignee_ble
use <jupe.scad>
use <plateforme.scad>
difference (){
union (){
translate([0,0,11]) plt_arduino(ouverture=false);
jupe(percement=false);
}
per_jupe(percement=true);
}
