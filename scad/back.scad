include <constant.scad>;

module back(){ 
    translate([border / 2, border / 2, depth + border])
        cube([width + border, height + border, border / 2]);
    
    intersection() {
        union() {
            for (a =[0:1:45]) {
                translate([0, 10 * a - height * 4, depth + border + border / 2])
                    color("blue", 1.0)
                    rotate([0, 0, 45])
                        cube([width * 2, border, border / 2]);
                translate([0, height * 5 - (10 * a), depth + border + border / 2])
                    color("blue", 1.0)
                    rotate([0, 0, -45])
                        cube([width * 2, border, border / 2]);
            }
        }
        translate([border / 2, border / 2, depth + border])
            cube([width + border, height + border, border * 2]);
    }
    
    translate([border / 2 + width / 2, border / 2 + height / 2, depth + border + border / 2])
        color("red", 1.0)
        linear_extrude(height = border) {
            text(text = "LINKVALUE", size = 20, halign = "center", valign = "center");
        }
}

back();