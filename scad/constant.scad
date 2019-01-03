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
diffuser_corner = 10;
diffuser_nb_vertical_square = 8;
diffuser_nb_horizontal_square = diffuser_nb_vertical_square * 4;

 function calculSquareSize(size, nb_square) = (( size - (diffuser_border * 2 )) - (nb_square - 1 * diffuser_border) - (matrice_border * 2)) / nb_square;
 
diffuser_square_height = calculSquareSize(height, diffuser_nb_vertical_square);
diffuser_square_width = calculSquareSize(width, diffuser_nb_horizontal_square);

back_center_text = "center text";
back_center_size = 20;
back_bottom_text = "bottom text";
back_bottom_size = 8;