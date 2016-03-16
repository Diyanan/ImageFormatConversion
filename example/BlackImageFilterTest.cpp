
#include <iostream>

#include "cv.h"
#include "highgui.h"

#include "ImageFormatConversion.h"

using namespace cv;
using namespace std;

void main()
{
	std::string imageFolder = "E:\\ImageFolder";
	ImageFormatConversion::blackImageFilter(imageFolder);
}
