//
//  main.cpp
//  opencv_test5
//
//  Created by ZHHJemotion on 2016/10/10.
//  Copyright © 2016年 Lukas_Zhang. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

#define PATH string("/Users/zhangxingjian/Desktop/Programming/C++/OpenCV/opencv_test5/opencv_test5/opencv_test5/")

// ================================ global function declaration Section ===================
//    Describe: Global Function Declaration
// ======================================================================================
static void ContrastAndBright(int, void *);

// ================================ global varibales declaration Section =======================
//    Describe: Global Variable Declaration
// =====================================================================================
int g_nContrastValue; // the value of the Contrast 对比度值
int g_nBrightValue; // the value of the Brightness 亮度值
Mat g_srcImage,g_dstImage;

// ================================ ComtrastAndBright() Function =========================
//    Describe: Changing the callback function of the image's values of contrast and brightness
// ===============================================================================================
static void ContrastAndBright(int, void *)
{
    
    // Create a window
    for (int y=0; y < g_srcImage.rows; y++)
    {
        for (int x=0; x < g_srcImage.cols; x++)
        {
            for (int c=0; c<3; c++)
            {
                g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c] + g_nBrightValue));
            }
        }
    }
    
    // show the image
    imshow("original image", g_srcImage);
    imshow("destination image", g_dstImage);
    
}


// ================================= main() function ==========================
// Describe: main function
// ============================================================================
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //VideoCapture cap(0);
    //if(!cap.isOpened()){
    //    return -1;
    //}
    //Mat frame;
    
    //while(true){
    //    cap>>frame;
    //    imshow("the current Video", frame);
    //    if(waitKey(30) >= 0) break;
    //}
    
    
    
    // change the color of the console's foreground and background
    system("color 5F");
    
    // read the original images
    g_srcImage = imread(PATH+String("pic1.jpg"));
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
    
    // exception handling
    if (!g_srcImage.data) {
        printf("Error: we can't read the pic1.jpg! \n");
        return false;
    }
    
    // set the initial values of the contrast and brightness
    g_nContrastValue = 80;
    g_nBrightValue = 80;
    
    // create a new window
    namedWindow("destination image",1);
    
    // create the Track Bar
    createTrackbar("Contrast", "destination image", &g_nContrastValue, 300, ContrastAndBright);
    createTrackbar("Brightness", "destination image", &g_nBrightValue, 200, ContrastAndBright);  // &g_nContrastValue 这是一个指向 g_nContrastValue（这是全局的整型变量）整型指针（int* Value ） &&&& ContrastValue 是回调函数，即指向函数地址的指针
    
    // call the callback function
    ContrastAndBright(g_nContrastValue, 0); // here: 0 means the initialization of the values for the Contrast and Brightness
    ContrastAndBright(g_nBrightValue, 0);
    
    // output some helpful infoamtion
    cout<<endl<<"\t ok! please adjust the track bar to observe the result! \n\n"
                <<"\t when you type 'q', the program quit! \n"
                <<"\n\n\t\t\t\t by ZHHJemotion ";
    
    // when you type the "q", the program quit
    while (char(waitKey(1)) != 'q') {}
    
    
    return 0;
}
