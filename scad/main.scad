$fn = 20;

screw_depth = 17;
screw_diameter = 3.2;

width = 330;
height = 90;
depth = 40;

border = 2;
matrice_border = 5;

difference() {
	cube([width, depth, height]);
	// empty cube inside
	translate([border, border, border])
		cube([width - border * 2, depth - border, height - border * 2]);
	// border for the matrice
	translate([matrice_border, 0, matrice_border])
		cube([width - matrice_border * 2, depth, height - matrice_border * 2]);
	// gap at the back plate
	translate([border / 2, depth - border, border / 2])
		cube([width - border, depth, height - border]);
}

module supportAndScrewHole(){ 
    difference() {
        // suport for screw hole
        intersection() {
            rotate([-90, 0, 0])
                cylinder(d=8, h=depth - border * 2);
            cube([4, depth - border, 4]);
        }
        // screw hole
        translate([1.6, depth - border, 1.6])
            rotate([90,0,0])
                cylinder(d1=screw_diameter, d2=screw_diameter / 1.5, h=screw_depth);
    }
}

translate([border, border, border]) 
    supportAndScrewHole();
translate([width - border, border, border]) 
    rotate([0, -90, 0])
        supportAndScrewHole();
translate([border, border, height - border]) 
    rotate([0, 90, 0])
        supportAndScrewHole();
translate([width - border, border, height - border])
    rotate([0, 180, 0])
        supportAndScrewHole();