#ifndef Matrice_h
#define Matrice_h

#include <Adafruit_NeoPixel.h>

enum Logo {
  facebook,
  twitter,
  youtube
};

class Matrice
{
  public:
  Matrice(Adafruit_NeoPixel* matrix);
  Adafruit_NeoPixel* matrix;
  byte YtLogoColors[3][3] = {{0, 0, 0}, {255, 0, 0}, {255, 255, 255}};
  byte YtLogo[8][10] =
  {
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 2, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 2, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}
  };

  byte TwitterLogoColors[3][3] = {{0, 0, 0}, {0, 172, 237}, {255, 255, 255}};
  byte TwitterLogo[8][10] =
  {
    {0, 1, 1, 2, 1, 1, 1, 1, 1, 0},
    {1, 1, 2, 2, 1, 1, 1, 1, 1, 1},
    {1, 1, 2, 2, 2, 2, 2, 1, 1, 1},
    {1, 1, 2, 2, 2, 2, 2, 1, 1, 1},
    {1, 1, 2, 2, 1, 1, 1, 1, 1, 1},
    {1, 1, 2, 2, 1, 1, 1, 1, 1, 1},
    {1, 1, 2, 2, 2, 2, 2, 1, 1, 1},
    {0, 1, 1, 2, 2, 2, 2, 1, 1, 0}
  };

  byte FbLogoColors[3][3] = {{0, 0, 0}, {40, 40, 125}, {255, 255, 255}};
  byte FbLogo[8][10] =
  {
    {0, 1, 1, 1, 1, 2, 2, 2, 1, 0},
    {1, 1, 1, 1, 2, 2, 2, 2, 1, 1},
    {1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
    {1, 1, 1, 2, 2, 2, 2, 2, 1, 1},
    {1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
    {0, 1, 1, 1, 2, 2, 1, 1, 1, 0}
  };

  static byte zero[6][4];
  static byte one[6][4];
  static byte two[6][4];
  static byte three[6][4];
  static byte four[6][4];
  static byte five[6][4];
  static byte six[6][4];
  static byte seven[6][4];
  static byte eight[6][4];
  static byte nine[6][4];
  std::array<byte(*)[4], 10> allNumbers {{
    Matrice::zero,
    Matrice::one,
    Matrice::two,
    Matrice::three,
    Matrice::four,
    Matrice::five,
    Matrice::six,
    Matrice::seven,
    Matrice::eight,
    Matrice::nine,
  }};

  void setPixelColorCustom(int column, int row, int green, int blue, int red);
  void displayLogo(Logo logo);
  void displayNumber(byte number[][4], int emplacement);
  void displayLetter(byte letter[][5], int emplacement);

  private:
  void _displayLogo(byte logo[][10], byte color[][3]);
};

#endif
