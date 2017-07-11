$fn=100;
//include<dim1.scad>
x=8.69;//M5
//x=5.214;//M3
r=x/tan(60);
echo(r);
difference(){
union(){
rotate([0,0,0])cube(size = [r,x,2.5], center = true);
rotate([0,0,-60])cube(size = [r,x,2.5], center = true);
rotate([0,0,-120])cube(size = [r,x,2.5], center = true);
}
cylinder(h = 3, r1 = 2.5, r2 = 2.5, center = true);
}

