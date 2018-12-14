$fn = 20;

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
	// gap at the bottom
	translate([border / 2, depth - border, border / 2])
		cube([width - border, depth, height - border]);
}