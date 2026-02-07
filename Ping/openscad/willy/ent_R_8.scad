//$fn=50;//nombre de facettes
use <visserie.scad> //Modules écrou, entretoise hexagonale, rondelle et vis

ent_R(2.2,4,10,0,0,0);

ent_R(2.2,4,10,10,0,0);

ent_R(2.2,4,10,-10,0,0);

ent_R(2.2,4,10,0,10,0);

ent_R(2.2,4,10,0,-10,0);

ent_R(2.2,4,10,-10,10,0);

ent_R(2.2,4,10,-10,-10,0);

ent_R(2.2,4,10,10,-10,0);

ent_R(2.2,4,10,10,10,0);

//translate([0,0,-5])cube([25,25,1], center=true);
