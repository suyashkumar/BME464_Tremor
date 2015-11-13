include <servo_lib.scad>
module spoon(){
difference(){
    union(){
    scale([1.5,1.5,1.5])scale([1,1.5,1])sphere(r=10);
    translate([0,40,-4])cube([8,67,8],center=true);
    }
    
    scale([1.5,1.5,1.5])scale([1,1.5,1])sphere(r=8);
    scale([1.5,1.5,1.5])translate([0,0,5])cube([25,30,10],center=true);
    
}

}
module makeSpoon(){
union(){

difference(){
spoon();
 scale([0.92,0.92,0.92])translate([-5,65,-4])rotate([0,90,0])cylinder(r=4, h=5);
}
}
scale([0.92,0.92,0.92])translate([-4,65,-4])rotate([0,90,0]) servo_standard();
}
module makeSpoonPrint(){
rotate([0,180,0])makeSpoon();
}
makeSpoon();