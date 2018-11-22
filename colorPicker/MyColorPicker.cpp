#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include <iostream>
#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <math.h>


using namespace cs225;

MyColorPicker::MyColorPicker(PNG img) { 
  // value = hue;
  customImg = img;
}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  // if(x > customImng.width()){
  //   x = 0;
  // }
  // if(y > customImng.height()){
  //   y = 0;
  // }
  
  return customImg.getPixel(x+300,y+300);
 
  
}
