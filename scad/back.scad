include <constant.scad>;

module back(){         
    module screwHole(position) {
        translate(position + [2, 2, border + 0.5]) color("green", 1.0)
            cylinder(d=screw_diameter + 2.5, h=screw_depth);
        translate(position + [2, 2, border]) color("green", 1.0)
            cylinder(d=screw_diameter, h=screw_depth);
    }
    
    difference() {
        union() {
            // plat part
            translate([border / 2, border / 2, depth + border])
                cube([width + border, height + border, border / 2]);
            // grid part
            color("blue", 1.0)
                intersection() {
                    union() {
                        for (a =[0:1:45]) {
                            translate([0, 10 * a - height * 4, depth + border + border / 2])
                                rotate([0, 0, 45])
                                    cube([width * 2, border, border / 2]);
                            translate([0, height * 5 - (10 * a), depth + border + border / 2])
                                rotate([0, 0, -45])
                                    cube([width * 2, border, border / 2]);
                        }
                    }
                    translate([border / 2, border / 2, depth + border])
                        cube([width + border, height + border, border * 2]);
                }
            // add text in center
            translate([border / 2 + width / 2, border / 2 + height / 2, depth + border + border / 2])
                color("red", 1.0)
                linear_extrude(height = border) {
                    text(text = back_center_text, size = back_center_size, halign = "center", valign = "center");
                }
            // add text in bottom
            translate([border / 2 + width, border / 2 + height / 8, depth + border + border / 2])
                color("red", 1.0)
                linear_extrude(height = border) {
                    text(text = back_bottom_text, size = back_bottom_size, halign = "right", valign = "center");
                }
        }
        // add screw hole in each angle 
        screwHole([border, border, depth]);
        screwHole([width + border - 4, border, depth]);
        screwHole([border, height + border - 4, depth]);
        screwHole([width + border - 4, height + border - 4, depth]);
    }
}

back();