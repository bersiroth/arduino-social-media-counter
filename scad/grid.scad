include <constant.scad>;

module grid() {
    // grid border
    difference() {
        translate([border, border, border]) 
            cube([width, height, diffuser_depth]);
        translate([border + diffuser_border, border + diffuser_border, border]) 
            cube([width - diffuser_border * 2, height - diffuser_border * 2, diffuser_depth]);
        translate([border, border, border]) 
            cylinder(d=diffuser_corner, h=diffuser_depth);
        translate([border, border + height, border]) 
            cylinder(d=diffuser_corner, h=diffuser_depth);
        translate([border + width, border, border]) 
            cylinder(d=diffuser_corner, h=diffuser_depth);
        translate([border + width, border + height, border]) 
            cylinder(d=diffuser_corner, h=diffuser_depth);
    }
    
    // grid corner
    module corner() {
        difference() {
            intersection() {
                cylinder(d=diffuser_corner + diffuser_border, h=diffuser_depth);
                    cube([diffuser_corner + diffuser_border / 2, diffuser_corner + diffuser_border / 2, diffuser_depth]);
            }
            cylinder(d=diffuser_corner, h=diffuser_depth);
        }
    }
    
    // down left
    translate([border, border, border]) 
    rotate([0, 0, 0])
    corner();
    // up left
    translate([border, border + height, border]) 
    rotate([0, 0, -90])
    corner();
    // down right
    translate([border + width, border, border]) 
    rotate([0, 0, 90])
    corner();  
    // up right
    translate([border + width, border + height, border]) 
    rotate([0, 0, 180])
    corner();
    
    // horizontal row
    for (a =[0:1:diffuser_nb_vertical_square])
        translate([border, border + matrice_border + a + diffuser_square_height * a, border]) 
            cube([width, diffuser_border, diffuser_depth]);
    // vertical row
    for (a =[0:1:diffuser_nb_horizontal_square])
        translate([border + matrice_border + a + diffuser_square_width * a, border, border]) 
            cube([diffuser_border, height, diffuser_depth]);
}

grid();