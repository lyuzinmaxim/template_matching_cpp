#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

bool use_mask;
Mat img; Mat templ; Mat mask; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";
int match_method;
int max_Trackbar = 5;
void MatchingMethod( int, void* );

string path_template = "C:/Users/SaSha/Documents/Samples/Check_photos/160920_174818_6388_1min47sec.jpg";
string path_image = "C:/Users/SaSha/Documents/Samples/Check_photos/160920_174818_6388_1min47sec.jpg";

int main( int argc, char** argv )

{
  img = imread( path_image, IMREAD_GRAYSCALE );
  templ = imread( path_template, IMREAD_GRAYSCALE );

  if(img.empty() || templ.empty())
  {
    cout << "Can't read one of the images" << endl;
    return EXIT_FAILURE;
  }
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );
  MatchingMethod( 0, 0 );
  waitKey(0);
  return EXIT_SUCCESS;
}
void MatchingMethod( int, void* )
{
  Mat img_display;
  img.copyTo( img_display );
  int result_cols = img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;
  result.create( result_rows, result_cols, CV_32FC1 );
  bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
  matchTemplate( img, templ, result, TM_SQDIFF_NORMED, mask);
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;
  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
  matchLoc = minLoc;

  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  imshow( image_window, img_display );
  imshow( result_window, result );
  return;
}