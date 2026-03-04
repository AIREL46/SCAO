//Cet assemblage 3D est réalisé à partir d'une phoro d'une oeuvre de Jean Gorin exposé au musée d'arts de Nantes
$fn=50;
translate([100,0,80]){
scale([1.1,1.1,1.1])
{
union()
{
//[1]
color([0,0,0])translate([-16,9,88])cube([2,2,73], center=true);
//[2]
color([254/255,254/255,254/255])translate([6.5,-10,-8])cube([13,5,203], center=true);
//[3]
color([254/255,254/255,254/255])translate([-16,10,-28])cube([13,5,164], center=true);
//[4]
color([254/255,254/255,254/255])translate([25,0,33])cube([16,5,33], center=true);
//[5]
color([254/255,254/255,254/255])translate([-8,0,40])cube([58,10,3], center=true);
//[6]
color([255/255,255/255,0/255])translate([-23,8,-18])cube([12,3,46], center=true);
//[7]
color([254/255,254/255,254/255])translate([-28,3,-70])cube([48,3,8], center=true);
//[8]
color([254/255,254/255,254/255])translate([0,0,-72])cube([77,9,2], center=true);
//[8a]
color([255/255,0/255,0/255])translate([0,-4.7,-72])cube([77,0.1,2], center=true);
//[9]
color([254/255,254/255,254/255])translate([7,-16,-85])cube([30,7,4], center=true);
//[10]
color([254/255,254/255,254/255])translate([-8,0,-112])cube([42,30,7], center=true);
//[11]
color([254/255,254/255,254/255])translate([-8.5,0,-120])cube([55,90,10], center=true);
//[Fond]
//rotate([0,0,0])color([175/255,175/255,175/255])translate([-37,60,-55])cube([110,1,300], center=true);
}
}
}