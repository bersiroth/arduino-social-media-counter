module box(){ 
    difference() {
        // box with round corner
        hull(){
            translate([border_radius, border_radius, 0])
                cylinder(h=depth + border * 2, r=border_radius);
            translate([width + border + border_radius, border_radius, 0])
                cylinder(h=depth + border * 2, r=border_radius);
            translate([border_radius, height + border + border_radius, 0])
                cylinder(h=depth + border * 2, r=border_radius);
            translate([width + border + border_radius, height + border + border_radius, 0])
                cylinder(h=depth + border * 2, r=border_radius);
        }
        // empty cube inside
        translate([border, border, border])
            cube([width, height, depth + border]);
        // border for the matrice
        translate([matrice_border + border, matrice_border + border, 0])
            cube([width - matrice_border * 2, height - matrice_border * 2, border]);
        // gap at the back plate
        translate([border / 2, border / 2, depth + border])
            cube([width + border, height + border, border]);
    }

    module supportAndScrewHole(){ 
        difference() {
            // suport for screw hole
            intersection() {
                cylinder(d=10, h=depth);
                cube([5, 5, depth]);
            }
            // screw hole
            translate([2, 2, depth])
                cylinder(d=screw_diameter, h=screw_depth);
        }
    }

    // add support and screw hole in each angle 
    translate([border, border, border]) 
        supportAndScrewHole();
    translate([width + border, border, border]) 
        rotate([0, 0, 90])
            supportAndScrewHole();
    translate([border, height + border, border]) 
        rotate([0, 0, -90])
            supportAndScrewHole();
    translate([width + border, height + border, border])
        rotate([0, 0, 180])
            supportAndScrewHole();
}