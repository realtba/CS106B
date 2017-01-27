/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
#include "random.h"
using namespace std;
const double SQRT3 = 1.73205080757;

int gcd(int a, int b) {
    if(b==0) {
        cout << "gcd(" << a << ",0)="<< a << endl;
        return a;
    }
    cout << "gcd(" << a << "," << b <<")"" = gcd(" << b << "," << a%b << ")" << endl;
    return gcd(b, a%b);
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {

    // the height of the current triangle
    double height = 0.5*SQRT3*size;

    if(order == 0) return ;

    else if(order < 0) error("serpinskii: the order was negative");

    //if the order is bigger then one, we call serpinskii for the three substringles in the current triangle
    else if(order > 1){
        serpinskii( w,  leftX,  leftY,  size/2,  order-1);
        serpinskii( w,  leftX+size/2,  leftY,  size/2,  order-1);
        serpinskii( w,  leftX+size/4,  leftY+height/2,  size/2,  order-1);
    }
    // if the order is 1 we are ready to draw a triangle
    else if(order == 1){
        w.drawLine(leftX, leftY, leftX+size, leftY);
        w.drawLine(leftX, leftY, leftX+size/2, leftY+height);
        w.drawLine( leftX+size, leftY,leftX+size/2, leftY+height);
    }
}


int floodFill(GBufferedImage& image, int x, int y, int newColor) {

    // check if the current pxiel is inside the bounds of the image
    // Note: The +40 offset is neceassary since the toolbar at the bottom is also calculated to the height
    // The +1 and -1 offsets are out of laziness, otherwise we would need to adjust the
    // return value for all the corner cases. Hence the right, left and top corner pixels are nor colored.
    if( !image.inBounds(x+1, y+40) || !image.inBounds(x-1, y-1)  ) return 0;

    // if the the color at (x,y) matches the newColor we are done and do not need to explore further
    if(image.getRGB(x,y) == newColor) return 0;

    // save the current color of the pixel
    int currentColor = image.getRGB(x,y);
    //  set the new color
    image.setRGB(x,y,newColor);

    // return 1 and explore all other directions
    // For all adjacent Pixel: pass newColor to floodFill if the color that pixel is the same as the currentColor
    // If not we are crossing a bonudary, pass the color of that pixel to floodFill
    // This will not color the pixel and there is no further exploration from that pixel.
    return 1+floodFill(image, x+1,y, image.getRGB(x+1,y)==currentColor ? newColor : image.getRGB(x+1,y))
           + floodFill(image, x,y+1, image.getRGB(x,y+1)==currentColor ? newColor : image.getRGB(x,y+1))
           + floodFill(image, x+1,y+1, image.getRGB(x+1,y+1)==currentColor ? newColor : image.getRGB(x+1,y+1))
           + floodFill(image, x-1,y+1, image.getRGB(x-1,y+1)==currentColor ? newColor : image.getRGB(x-1,y+1))
           + floodFill(image, x+1,y-1, image.getRGB(x+1,y-1)==currentColor ? newColor : image.getRGB(x+1,y-1))
           + floodFill(image, x-1,y-1, image.getRGB(x-1,y-1)==currentColor ? newColor : image.getRGB(x-1,y-1))
           + floodFill(image, x+1,y, image.getRGB(x+1,y)==currentColor ? newColor : image.getRGB(x+1,y))
           + floodFill(image, x,y+1, image.getRGB(x,y+1)==currentColor ? newColor : image.getRGB(x,y+1));

}



void personalCurriculum(Map<string, Vector<string>> & prereqMap, string goal) {

    // static variable to keep track of the concept that have allready been printed
    static Set<string> printedConcept ;

    // static variable to keep track of the order of the concepts.
    // We use order.get(0) to deduce when we are at the orginal call of personalCurriculum
    static Vector<string> order;

    // add the current goal to the order
    order.add(goal);

    // Call personalCurriculum on all conecpts needed for goal
    for( string concept : prereqMap.get(goal)){
        personalCurriculum(prereqMap, concept);
    }
    // if the current goal has not been printed, print it and add it to printedConcept
    if(!printedConcept.contains(goal)){
        cout << goal << endl;
        printedConcept.add(goal);
    }
    // If we are at the first call of personalCurriculum clear the static variabels
    if(order.get(0) == goal){
       printedConcept.clear();
        order.clear();
    }
}



string generate(Map<string, Vector<string> > & grammar, string symbol) {

    // check if symbol is terminal, if so return it
    if(!grammar.containsKey(symbol)){
        return symbol;
    }

    // randomly choose a rule from the rules of the current symbol
    string rule = grammar.get(symbol).get(randomInteger(0, grammar.get(symbol).size()-1));

    string nonTerminal;

    // for each token in rule call generate on it and add the result to nonTerminal
    TokenScanner scanner(rule);
    while (scanner.hasMoreTokens()) {
        nonTerminal += generate(grammar,scanner.nextToken());
    }

    //return nonTerminal
    return nonTerminal;
}
