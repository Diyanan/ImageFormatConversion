#include "ImageFormatConversion.h"

std::vector<std::string> ImageFormatConversion::getFileList( std::string foldname )
{
	std::string filename = foldname + "/*.*";
	const char* mystr=filename.c_str();
	std::vector<std::string> flist;
	std::string lineStr;
	std::vector<std::string> extendName;
	extendName.push_back("tif");

	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	wchar_t fn[1000];
	mbstowcs( fn, mystr, 999 );
	file = FindFirstFile( fn, &fileData );
	FindNextFile( file, &fileData );
	while(FindNextFile( file, &fileData ))
       {
		wcstombs( line, (const wchar_t*)fileData.cFileName, 259);
		lineStr = line;
        // remove the files which are not images
		for (int i = 0; i < 4; i ++)
		{
			if (lineStr.find(extendName[i]) < 999)
			{
				flist.push_back(lineStr);
				break;
			}
		}	
	}
	return flist;
}

void ImageFormatConversion::imageU162U8( std::string input_folder, FilterMode mode/*= SAVE_BLACK*/ )
{
	std::vector<std::string> file_list = getFileList(input_folder);

	const int size_list = file_list.size();
	if ( !size_list )
	{
		std::cout << "No image loaded!" << std::endl;
		return;
	}

	std::string saveFolder = input_folder;
	saveFolder += "/trans_folder";
	_mkdir(saveFolder.c_str());

#pragma omp parallel for
	for ( int idx=0; idx<size_list; idx++ )
	{
		std::string curFile = input_folder;
		std::string curFileName = file_list[idx];
		curFile += "/" + curFileName;

		cv::Mat curImage = cv::imread(curFile, IMREAD_UNCHANGED);

		if (!curImage.data)
		{
			std::cout << idx << " Image " << curFileName << " read failed!" << std::endl;
		}
		else
		{

#if 0
			std::cout << idx << " Image " << curFileName << " read succeed!" << std::endl;
#endif

			const int cols = curImage.cols;
			const int rows = curImage.rows;

			cv::Mat transImage(rows, cols, CV_8UC1, cv::Scalar(0));
			uint16* data_cur = (uint16*)curImage.data;
			uchar* data_trans = (uchar*)transImage.data;

			double pMax = 0, pMin = 0;
			cv::minMaxIdx(curImage, &pMin, &pMax);
			int ipMin = pMin, pRange = pMax - pMin;

			if( pRange > 0 )
			{
				for ( int i=0; i<rows*cols; ++i )
				{
					int pValue = ( static_cast<int>(data_cur[i] & 0xffff) - ipMin ) * 255 / pRange;
					data_trans[i] = static_cast<uchar>(pValue);
				}

				std::string saveFileName = saveFolder;
				saveFileName += "/" + curFileName;
				saveFileName += ".jpg";

				cv::imwrite(saveFileName, transImage);
			}
			else
			{
				if ( mode == SAVE_BLACK )
				{
					for ( int i=0; i<rows*cols; ++i )
					{
						int pValue = static_cast<int>(data_cur[i] & 0xffff);
						data_trans[i] = static_cast<uchar>(pValue);
					}

					std::string saveFileName = saveFolder;
					saveFileName += "/" + curFileName;
					saveFileName += ".jpg";

					cv::imwrite(saveFileName, transImage);
				}
				else
				{
					std::cout << idx << " Black image!" << std::endl;
				}
			}
		}
	}
}

void ImageFormatConversion::blackImageFilter( std::string input_folder )
{
	std::vector<std::string> file_list = getFileList(input_folder);

	const int size_list = file_list.size();
	if ( !size_list )
	{
		std::cout << "No image loaded!" << std::endl;
		return;
	}

	std::string saveFolder = input_folder;
	saveFolder += "/trans_folder";
	_mkdir(saveFolder.c_str());

#pragma omp parallel for
	for ( int idx=0; idx<size_list; idx++ )
	{
		std::string curFile = input_folder;
		std::string curFileName = file_list[idx];
		curFile += "/" + curFileName;

		cv::Mat curImage = cv::imread(curFile, IMREAD_UNCHANGED);

		if (!curImage.data)
		{
			std::cout << idx << " Image " << curFileName << " read failed!" << std::endl;
		}
		else
		{

#if 0
			std::cout << idx << " Image " << curFileName << " read succeed!" << std::endl;
#endif

			const int cols = curImage.cols;
			const int rows = curImage.rows;

			double pMax = 0, pMin = 0;
			cv::minMaxIdx(curImage, &pMin, &pMax);
			int ipMin = pMin, pRange = pMax - pMin;

			if ( pRange > 0 )
			{
				std::string saveFileName = saveFolder;
				saveFileName += "/" + curFileName;
//				saveFileName += ".jpg";

				cv::imwrite(saveFileName, curImage);
			}
		}
	}
}
