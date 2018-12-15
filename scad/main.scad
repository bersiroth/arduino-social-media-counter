$fn = 20;

screw_size = 3.2;

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

//translate([border, border, border]) cube([4, depth - border, 4]);
difference() {
	intersection() {
		translate([border, depth - border, border])
			rotate([90, 90, 0])
				cylinder(d1=9, d2=7, h=30);
		translate([border, border, border])
			cube([4, depth - border, 4]);
	}
	translate([border + 1.6, depth - border, border + 1.6])
		rotate([90,90,0])
			cylinder(d=screw_size, h=10);
}