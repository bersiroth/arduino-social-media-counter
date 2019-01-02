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
        translate([border, border + height, border]) 
            cylinder(d=10, h=diffuser_depth);
        translate([border + width, border, border]) 
            cylinder(d=10, h=diffuser_depth);
        translate([border + width, border + height, border]) 
            cylinder(d=10, h=diffuser_depth);
    }
    
    module gridBorder() {
        difference() {
            intersection() {
                // WIP : add constant 
                cylinder(d=12, h=diffuser_depth);
                    cube([7, 7, diffuser_depth]);
            }
            cylinder(d=10, h=diffuser_depth);
        }
    }
    
    translate([border, border, border]) 
    rotate([0, 0, 0])
    gridBorder();
    
    translate([border, border + height, border]) 
    rotate([0, 0, -90])
    gridBorder();
    
    translate([border + width, border, border]) 
    rotate([0, 0, 90])
    gridBorder();    
    
    translate([border + width, border + height, border]) 
    rotate([0, 0, 180])
    gridBorder();
    
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