Matrice::Matrice(Adafruit_NeoPixel* matrix)
{
  this->matrix = matrix;
}

byte Matrice::zero[6][4] =
{
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1},
};

byte Matrice::one[6][4] =
{
  {0, 0, 1, 0},
  {0, 1, 1, 0},
  {1, 0, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 0},
  {1, 1, 1, 1},
};

byte Matrice::two[6][4] =
{
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {0, 0, 0, 1},
  {1, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 1, 1, 1},
};

byte Matrice::three[6][4] =
{
  {1, 1, 1, 1},
  {0, 0, 0, 1},
  {0, 0, 0, 1},
  {0, 1, 1, 1},
  {0, 0, 0, 1},
  {1, 1, 1, 1},
};

byte Matrice::four[6][4] =
{
  {1, 0, 0, 0},
  {1, 0, 0, 0},
  {1, 0, 1, 0},
  {1, 1, 1, 1},
  {0, 0, 1, 0},
  {0, 0, 1, 0},
};

byte Matrice::five[6][4] =
{
  {1, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 1, 1, 1},
  {0, 0, 0, 1},
  {0, 0, 0, 1},
  {1, 1, 1, 1},
};

byte Matrice::six[6][4] =
{
  {1, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 0},
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1},
};

byte Matrice::seven[6][4] =
{
  {1, 1, 1, 1},
  {0, 0, 0, 1},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 1, 0, 0},
  {1, 0, 0, 0},
};

byte Matrice::eight[6][4] =
{
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1},
};

byte Matrice::nine[6][4] =
{
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1},
  {0, 0, 0, 1},
  {0, 0, 0, 1},
  {1, 1, 1, 1},
};

void Matrice::setPixelColorCustom(int column, int row, int green, int blue, int red)
{
  if (column % 2 != 0) {
    row = pannelHeight - row;
    row++;
  }
  int nbPixel = (column * pannelHeight) - row;
  this->matrix->setPixelColor(nbPixel, green, blue, red);
}

void Matrice::displayLogo(Logo logo)
{
  switch (logo){
    case Logo::facebook:
      this->_displayLogo(this->FbLogo, this->FbLogoColors);
      break;
    case Logo::youtube:
      this->_displayLogo(this->YtLogo, this->YtLogoColors);
      break;
    case Logo::twitter:
      this->_displayLogo(this->TwitterLogo, this->TwitterLogoColors);
      break;
  }
}

void Matrice::_displayLogo(byte logo[][10], byte color[][3])
{
  for (int a = -10; a <= 0; a++) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 10; j++) {
        int row =  i + 1 + a;
        if (row >= 1) {
          this->setPixelColorCustom(j + 1, row, color[logo[i][j]][0], color[logo[i][j]][1], color[logo[i][j]][2]);
        }
      }
    }
    delay(35);
    this->matrix->show();
  }
}

void Matrice::displayNumber(byte number[][4], int emplacement)
{ 
  for (int a = -7; a <= 0; a++) {
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 5; j++) {        
        this->setPixelColorCustom(j + 10 + ((4 + 1) * (emplacement - 1)) + 2, 1, 0, 0, 0);
      }
    }
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 4; j++) {
        int color;
        if (number[i][j] == 1) {
          color = 255;
        } else {
          color = 0;
        }
        
        int row = i + 2 + a;
        if (row >= 1) {
          this->setPixelColorCustom(j + 10 + ((4 + 1) * (emplacement - 1)) + 2, row, color, color, color);
        }
      }
    }
    delay(35);
    this->matrix->show();
  }
}
