// Testing device
$fn=100;
difference(){
    cube([80,30,10],center=true);
    translate([0,0,-10])cylinder(r=6.35/2,h=20);
}