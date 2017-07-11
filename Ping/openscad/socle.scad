//Socle
$fn=120;
//Dimensions de la carte de crédit
L1=85;
l1=54;
e2=1;
r1=3.2/2;//rayon des trous de fixation
rotate([0,0,315])translate([0,0,z2]){minkowski()
{
 cube([L1-4*r1, l1-4*r1, e2/2], center = true);
 cylinder(r=2*r1,h=e2/2, center = true);
}
}
