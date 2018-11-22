#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace std;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 *
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;
  

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal *trav, const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  image = png;
  tol = tolerance;
  current = trav->peek();
  traversal = trav;
  startPoint = start;

  

  // dVector.resize(image.width());
  // for(int i = 0; i < image.width(); i++){
  //   dVector[i].resize(image.height());
  // }
  // for(auto i; dVector){
  //   fill(dVector[i].begin(),dVector[i].end(),false)
  // }
  
  for(unsigned int i = 0; i < image.width(); i++){
    vector<bool>status;
    for(unsigned int i = 0; i < image.height(); i++){
      status.push_back(false);
    }
    dVector.push_back(status);
  }
}
ImageTraversal::Iterator::Iterator(){
  traversal = NULL;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
if(!traversal->empty()){

  current = traversal->pop();
  unsigned int x = current.x; 
  unsigned int y = current.y;
  HSLAPixel startPix = image.getPixel(startPoint.x,startPoint.y);
  dVector[x][y] = true;

if(x+1 < image.width() && y < image.height()){
  if(dVector[x+1][y] == false){
    HSLAPixel compPix = image.getPixel(x+1,y);
    double delta = calculateDelta(startPix, compPix);
    if(delta < tol){
      traversal->add(Point(x+1, y));
    }
  } 
}
if( x < image.width() && y+1 < image.height()){
  if(dVector[x][y+1] == false){
    HSLAPixel compPix = image.getPixel(x,y+1);
    double delta = calculateDelta(startPix, compPix);
    if(delta < tol){
      traversal->add(Point(x, y+1));
    }
  } 
}
if(x >= 1 && x-1 < image.width() && y < image.height()){
  if(dVector[x-1][y] == false){
    HSLAPixel compPix = image.getPixel(x-1,y);
     double delta = calculateDelta(startPix, compPix);
    if(delta < tol){
      traversal->add(Point(x-1, y));
    }
  }
}
if(y >= 1 && x < image.width() && y-1 < image.height()){
  if(dVector[x][y-1] == false){
    HSLAPixel compPix = image.getPixel(x,y-1);
    double delta = calculateDelta(startPix, compPix);
    if(delta < tol){
      traversal->add(Point(x, y-1));
    }
  }  
}
if(!traversal->empty()){
  current = traversal->peek();
  while(dVector[current.x][current.y]){
    traversal->pop();
  if(!traversal->empty()){
    current = traversal->peek();
  }else{
    break;
  }
}

}

}

// =if(traversal->empty()){
//   tol = 69;
// }else{

return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
    bool thisEmpty = false; 
    bool otherEmpty = false;

    if (this->traversal == NULL) { thisEmpty = true; }
    if (other.traversal == NULL) { otherEmpty = true; }

    if (!thisEmpty)  { 
      thisEmpty = this->traversal->empty();
     }
    if (!otherEmpty) { 
      otherEmpty = other.traversal->empty(); 
    }

    if (thisEmpty && otherEmpty){
      return false;
     } // both empty then the traversals are equal, return true
    else if ((!thisEmpty)&&(!otherEmpty)){
     return (this->traversal != other.traversal);
     } //both not empty then compare the traversals
    else {
      return true;
    } // one is empty while the other is not, return true
    

 //return!(current == other.current);
}

