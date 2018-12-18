include <constant.scad>;

module grid() {
    // grid border
    difference() {
        translate([border, border, border]) 
            cube([width, height, diffuser_depth]);
        translate([border + diffuser_border, border + diffuser_border, border]) 
            cube([width - diffuser_border * 2, height - diffuser_border * 2, diffuser_depth]);
        translate([border, border, border]) 
            cylinder(d=10, h=diffuser_depth);
    }
    // WIP : make this for each angle
    difference() {
        translate([border, border, border]) 
        intersection() {
            // WIP : add constant 
            cylinder(d=12, h=diffuser_depth);
            cube([7, 7, diffuser_depth]);
        }
        translate([border, border, border]) 
            cylinder(d=10, h=diffuser_depth);
    }
    
    // horizontal row
    for (a =[0:1:6])
        translate([border, border + matrice_border + a + 9.125 * (a + 1), border]) 
            cube([width, diffuser_border, diffuser_depth]);
    // vertical row
    for (a =[0:1:30])
        translate([border + matrice_border + a + 9.125 * (a + 1), border, border]) 
            cube([diffuser_border, height, diffuser_depth]);
}

grid();