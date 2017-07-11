//e_poignee_433
use <jupe.scad>
include <jupe.scad>
use <sup_bat.scad>
echo (hj);
difference() {
union() {jupe(percement=false); sup_bat(0,0,(e/2)+hj/2);}
//per_jupe(percement=true);

}