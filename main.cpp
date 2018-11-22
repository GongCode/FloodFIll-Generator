
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  PNG png;      
  png.readFromFile("ino.png");
  PNG backPng;      
  backPng.readFromFile("hello.png");

 
  
  FloodFilledImage image(png);
  BFS bfs(png, Point(40, 40), 0.2);
  DFS dfs(png, Point(250, 375), 0.2);
  // BFS bfs2(png, Point(350, 320), 0.5);
  MyColorPicker flood(backPng);
  image.addFloodFill(bfs, flood);
  image.addFloodFill(dfs, flood);

  // image.addFloodFill(bfs2, flood);

  Animation animation = image.animate(1000);
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1 );

  secondFrame.writeToFile("myFloodFillFirst.png");
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */

  return 0;
}
