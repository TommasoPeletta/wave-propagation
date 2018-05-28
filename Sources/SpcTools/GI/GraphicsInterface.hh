#ifndef GRAPHICSINTERFACE_HH
#define GRAPHICSINTERFACE_HH

//=======================================================
//
// = LIBRARY
//     GI
//
// = FILENAME
//     GraphicsInterface.hh
//
// = AUTHOR(S)
//     Alexandre Dupuis
//
// = VERSION
//     $Revision: 1.2 $
//
// = DATE RELEASED
//     $Date: 2000/06/15 09:13:44 $
//
// = COPYRIGHT
//     University of Geneva, Switzerland.
//
//=======================================================

//----------------------------------------
// Type definitions
//----------------------------------------

enum Palette {continuousColor, continuousGray, discreteColor};
enum Color {GI_white=0, GI_black=1, GI_red=2, GI_green=3, GI_blue=4, GI_yellow=5, GI_gray=6};
enum LineStyle {continuous, dot, dash, mix};
enum AreaPattern {none, filled};
enum CharSize {tiny=8, small=10, normal=12, large=14, Large=18, huge=24};
enum LineWidth {thin=1, thick=2, Thick=3};
enum ArrowStyle {noArrow, endArrow, startArrow, doubleArrow};
 
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/X.h>

#include "String.hh"
#include "Point.hh"
#include "Matrix.hh"
#include "Polygon.hh"

class GraphicsInterface 
//=======================================================
//
// = DESCRIPTION
//
//   The class <{GraphicsInterface}> provides basic necesary methods
//   to open, close, draw classical shapes and images manipulation.
//
// = SEE ALSO
//   <{String}>, <{Point}>, <{Matrix}>, <{Polygon}>.
//
//=======================================================
{
public:

  //=======================================================
  // = CONSTRUCTORS
  //=======================================================

  GraphicsInterface();
  // Default constructor.

  GraphicsInterface(const GraphicsInterface &aWindow);
  // Copy constructor.

  //=======================================================
  // = DESTRUCTOR
  //=======================================================

  ~GraphicsInterface();
  // Default constructor.

  //=======================================================
  // = ACCESSORS
  //=======================================================

  void setDrawingColor(const Color color);
  // Sets the drawing color.

  Color getDrawingColor() const;
  // Gets the current color.

  void setFillColor(const Color color);
  // Sets the fill color.

  Color getFillColor() const;
  // Sets the fill color.

  void setLineWidth(const LineWidth lineWidth);
  // Sets the line width.

  LineWidth getLineWidth() const;
  // Gets the line width.

  void setLineStyle(const LineStyle lineStyle);
  // Sets the line style.

  LineStyle getLineStyle() const;
  // Gets the line style.

/**
* Added by Mohamed Ben Belgacem
* date: 21/07/2014
* The font name in the method setCharSize(..) may exit only on ubuntu 10.10.
* This method getFont() serach for font that starts with "helvetica" and return it. Otherwise,
* it return the "fixed font"
*/
  XFontStruct * getFont (Display * display, int fontsize);


  void setCharSize(const CharSize charSize);
  // Sets the char size.

  CharSize getCharSize() const;
  // Gets the char size.

  bool isOpen() const;
  // Is the window open?

  //=======================================================
  // = OPERATORS
  //=======================================================

  void open(const int windowHeight, const int windowWidth, 
	    const Point<int> &leftTopCorner=Point<int>(0,0),
	    const Palette palette=continuousColor,
	    const String &windowTitle=String("GI window"));
  // Open a window of size <{windowHeight}>x<{windowWidth}> where the
  // left top corner is located on the point <{leftTopCorner}>, the
  // palette used is defined by <{palette}> and the title of the
  // window by <{windowTitle}>.

  void close();
  // Closes the window.

  void clearScreen();
  // Clears the screen.

  void drawPoint(const Point<int> &point);
  // Draws the point <{point}> on the window

  void drawLine(const Point<int> &startPoint, const Point<int> &endPoint, 
		const ArrowStyle style=noArrow);
  // Draws a line who begins with the point <{startPoint}> and stops
  // with the point <{endPoint}>. The arrow style is imposed by the
  // style <{style}>.

  void drawLine(const Point<float> &startPoint, const Point<float> &endPoint, 
		const ArrowStyle style=noArrow);
  // Draws a line who begins with the point <{startPoint}> and stops
  // with the point <{endPoint}>. Points are given in <{float}>. The
  // arrow style is imposed by the style <{style}>.
  
  void drawCircle(const Point<int> &center, const int radius, 
		  const AreaPattern pattern=none);
  // Draws a circle centered on the point <{center}> with a radius
  // <{radius}> and an area patern <{pattern}>.
 
  void drawArc(const Point<int> &center, const int radius, 
	       const float startAngle, const float endAngle, 
	       const AreaPattern pattern=none);
  // Draws an arc centered on the point <{center}> with a radius
  // <{radius}> and an area patern <{pattern}>. It begins at the angle
  // <{startAngle}> and stops at <{endAngle}> expressed in degrees.
  //
  // Internally, the two angles are expressed as a multiple of one
  // 64th of a degree.

  void drawEllipse(const Point<int> &center,
		   const int horizontalRadius, const int verticalRadius, 
		   const AreaPattern pattern=none);
  // Draws an ellipse centered on the point <{center}> with a
  // horizontal radius <{horizontalRadius}>, a vertical radius
  // <{verticalRadius}> and an area patern <{pattern}>. 

  void drawString(const Point<int> &startPoint, const String &string);
  // Draws a string <{string}> where the left top corner of the
  // bounding box is located on the point <{startPoint}>.

  int widthOf(const String &string);
  // Computes the width of the string <{string}> with the specified
  // size of character.

  void drawPolygon(Polygon &aPolygon, const AreaPattern pattern=none);
  // Draws a polygon describes by the polygon <{aPolygon}>. The area
  // pattern is defined with the pattern <{pattern}>.

  void drawBox(const Point<int> &leftTopCorner, 
	       const int height, const int width, 
	       const AreaPattern pattern=none);
  // Draws a box with a left top corner <{leftTopCorner}>, a height
  // <{height}>, a <{width}> width and a pattern <{pattern}>.

  void drawMatrix(const Matrix<unsigned char> &matrix);
  // Draws a matrix <{matrix}> with the specified palette.

  Matrix<unsigned char> getMatrix();
  // Grabs the window and returns it in a matrix.

  void printInto(const String &fileName, const int rightOffset=0, 
		 const int leftOffset=0, const int topOffset=0, 
		 const int bottomOffset=0);
  // Prints a viewport of the window in the file <{fileName}>. The
  // file format depends on the selected palette ('.ppm',
  // '.pgm'). <{xxxOffset}> specify the viewport geometry.

  void printInto(const String &fileName, 
		 const Matrix<unsigned char> image);
  // Prints the image <{image}> into the file <{fileName}> according
  // to current palette.

  //=======================================================
  // = PRIVATE METHODS AND ATTRIBUTES
  //=======================================================

private:

  void init();
  // Initializes the window.

  void createImage();
  // Creates an image.

  void destroyImage();
  // Destroys an image which has been created with the
  // <{createImage()}> method.

  int pixelToColor(const int pixel) const;
  // Returns the color associated to the pixel.

  int windowHeight_;
  // Stores the height of the window.

  int windowWidth_;
  // Stores the width of the window.

  Point<int> windowLeftTopCorner_;
  // Stores the left top corner of the window.

  bool isOpen_;
  // Flag indicates if the window is open or not.

  Color drawingColor_;
  // Stores the drawing color.

  Color fillColor_;
  // Stores the fill color.

  LineWidth lineWidth_;
  // Stores the line width.
  
  LineStyle lineStyle_;
  // Stores the line style.

  Palette palette_;
  // Stores the line style.

  int nbMaxColor_;
  // Stores the maximum number of color.

  CharSize charSize_;
  // Stores the size of characters 
  
  String windowTitle_;
  // Stores the title of the window.
  
  char *dotDefinition_;
  // definition of the dot style.

  char *dashDefinition_;
  // definition of the dash style.

  char *mixDefinition_;
  // definition of the mixte style.

  // X11 variables 
  Display *display_;
  Window  window_;
  GC      gc_;
  XColor  color_[256];
  XFontStruct *font_;
  XImage *image_;
  int depth_;
  Colormap cmap_;

};

// ============================================================
// = INLINE METHODS
// ============================================================

//=======================================================
// = ACCESSORS
//=======================================================

inline Color GraphicsInterface::getDrawingColor() const
{
  return drawingColor_;
}

//=======================================================
inline void GraphicsInterface::setFillColor(const Color color) 
{
  fillColor_=color;
}
  
//=======================================================
inline Color GraphicsInterface::getFillColor() const
{
  return fillColor_;
}

//=======================================================
inline LineWidth GraphicsInterface::getLineWidth() const
{
  return lineWidth_;
}

//=======================================================
inline LineStyle GraphicsInterface::getLineStyle() const
{
  return lineStyle_;
}

//=======================================================
inline CharSize GraphicsInterface::getCharSize() const
{
  return charSize_;
}

//=======================================================
inline bool GraphicsInterface::isOpen() const
{
  return isOpen_;
}

#endif
