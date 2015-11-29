include <servo_lib.scad>
outer_radius=10;
inner_radius=8;
offset=3;
handle_height=9;
handle_length=110;
handle_width=8;
module spoon(){
    
difference(){
    union(){
    translate([0,0,offset])scale([1.5,1.5,1.5])scale([1.2,1.8,1])sphere(r=outer_radius);
    translate([0,(handle_length/2)+5,-handle_height/2])cube([handle_width,handle_length,handle_height],center=true); // the arm
    }
    
    translate([0,0,offset])scale([1.5,1.5,1.5])scale([1.2,1.8,1])sphere(r=inner_radius);
    scale([1.5,1.5,1.5])translate([0,0,10])cube([40,40,20],center=true);
    
}

}
module makeSpoon(){
union(){

difference(){

 spoon();
    
 scale([1.0,1.0,1.0])translate([-5,handle_length-10,-4])rotate([0,90,0])cylinder(r=4, h=5);
}
}
scale([1.0,1.0,1.0])translate([-4,handle_length-10,-4])rotate([0,90,0]) servo_standard();
}
module makeSpoonPrint(){
rotate([0,180,0])makeSpoon();
}
makeSpoon();