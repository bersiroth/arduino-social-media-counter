$fn = 60;

screw_depth = 20;
screw_diameter = 2.8;

border = 2;
border_radius = 1;
matrice_border = 5;

width = 330;
height = 90;
depth = 40;

diffuser_depth = 10;
diffuser_border = 1;

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


