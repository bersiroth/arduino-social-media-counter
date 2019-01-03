include <constant.scad>;

module back(){ 
    translate([border / 2, border / 2, depth + border])
        cube([width + border, height + border, border]);
}

back();