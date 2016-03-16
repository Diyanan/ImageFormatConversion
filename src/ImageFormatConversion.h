/**
 *   Image format conversion.
 *   
 *    Editor: Yahui Liu.
 *    Data:   2016-03-15
 *    Email:  yahui.cvrs@gmail.com
 *    Address: Computer Vision and Remote Sensing(CVRS) Lab£¬ Wuhan University.
 */

#ifndef IMAGE_FORMAT_CONVERSION_H
#define IMAGE_FORMAT_CONVERSION_H
#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <direct.h> 
#include <omp.h>

#include "cv.h"
#include "highgui.h"

#include "tiffio.h"

using namespace std;
using namespace cv;

enum FilterMode{
	SAVE_BLACK = 0,
	DELETE_BLACK = 1
};

class ImageFormatConversion
{
public:
	ImageFormatConversion(){}
	~ImageFormatConversion(){}

public:
	static std::vector<std::string> getFileList( std::string foldname );
	
 	static void blackImageFilter( std::string input_folder );

	static void imageU162U8( std::string input_folder, FilterMode mode = SAVE_BLACK );

//	static bool imageU16Read( std::string file_name, cv::Mat& trans_image );
};
#endif // IMAGE_FORMAT_CONVERSION_H