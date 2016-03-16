# ImageFormatConversion
A Demo of converting the single channel 16-bit images to 8-bit images.

昨天一个朋友，向我求助，帮忙去除掉一组遥感影像数据中，因为裁剪时产生的全黑图像，实现起来也很简单，就将工程代码提供给大家：

GitHub链接：[yhlleo/ImageFormatConversion](https://github.com/yhlleo/ImageFormatConversion)

图像格式为单通道16-bit的`tif`，可以使用OpenCV库读取：

```c
cv::Mat curImage = cv::imread(fileName, IMREAD_UNCHANGED);
```

因为图像是16-bit的，所指使用图片查看器，浏览的话，肯定是全黑的。但是可以在Photoshop中，调整灰度曲线，显示图片内容（将曲线调成近似直角折线）：

![image_ps](http://img.blog.csdn.net/20160316134513618)

那些黑色图像（真的是全黑，像素值为0），判断方法比较简单，获取图像灰度最大最小值，区间范围是0，必然是全黑图像：

```c
double pMax = 0, pMin = 0;
cv::minMaxIdx(curImage, &pMin, &pMax);
int pRange = pMax - pMin;

if ( pRange > 0 )
{
    // ...
}
else
{
    // Black image 
    // ...
}
```

如果想把16-bit图像转为常见的8-bit图像，我使用的方法是这样的：

```c
if( pRange > 0 )
{
	for ( int i=0; i<rows*cols; ++i )
	{
		int pValue = ( static_cast<int>(*++data_cur & 0xffff) - ipMin ) * 255 / pRange;
		data_trans[i] = static_cast<uchar>(pValue);
	}
}
```

即，使用简单的线性拉伸方法：

![linear](http://img.blog.csdn.net/20160316144309396)

另外，为了操作简单，将代码写成批处理的形式：

```c
std::vector<std::string> file_list = getFileList(input_folder);
```

指定图片所在文件夹后，自动加载当前文件夹子目录下的所有`tif`图片，以`vector`的形式返回文件名。

由于每张图片的操作是独立的，所以还可以把OpenMP开启：

```c
#pragma omp parallel for
```

工程编译环境，如下：
   
   - `CMake ( version >= 2.8.3)`
   - `Visual Studio 2010`
   - `OpenCV`

测试程序：

 - `BlackImageFilterTest`：滤除全黑图像，其余文件自动另存至当前图像文件下的空子目录下
 - `ImageConversionTest`：将原16-bit图像转为8-bit，可选择地保留或去除全黑图像

编译结果如图：

![compile](http://img.blog.csdn.net/20160316143130017)

测试结果：
 
 - 转为8-bit图像，保留全黑图
![compile2](http://img.blog.csdn.net/20160316143333416)

 - 转为8-bit图像，删除全黑图
![compile3](http://img.blog.csdn.net/20160316143437612)
