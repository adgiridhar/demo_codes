/*
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    int angole=10;
    FILE * arduino;
   
    do
    {
        arduino = fopen("/dev/cu.usbmodem1D1131","w");
       
        cout<<"\ngive me the angle\n\n";
        //cin>>angole;
       
        fprintf(arduino,"%d\n",angole);
        sleep(1);
       
    }while(angole>=0 && angole<=179);
   
}
*/
/*
//super code.. for communication
#include <iostream>
#include <unistd.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Math.h"
#include <stdio.h>

using namespace cv;
using namespace std;

#define PI 3.14159265
#define height 190//270
#define cam_dist 25
#define length 98//100//176
#define width 80//44//50//84
//800px = 2*tan(24.1 deg)*height
//800px = 241.5cm
//1 cm = 3.31px
//1px = 0.301875cm

#define cm_px 4.706//4.706//3.2//3.31
#define px_cm 0.212//0.212//0.3333//0.301875


int main()
{
    int angle;
    FILE * arduino;
    //arduino = fopen("/dev/cu.usbmodem1421","w");
    arduino = fopen("/dev/cu.usbmodem1D1131","w");
   
   
    VideoCapture cap0(0);//right camera
   
    VideoCapture cap1(1);//left camera
   
    int z_0_offset = 5, z_1_offset = 0;
    int x_0_offset = 8, x_1_offset = -6+2;
    //Point center_0 = Point(400-(x_0_offset*cm_px),300-(z_0_offset*cm_px));
    //Point center_1 = Point(400-(x_1_offset*cm_px),300-(z_1_offset*cm_px));
    //Rect rect_line_crop_0(400-(((length/2)+cam_dist)*cm_px), 300 - 3, length*cm_px,6);
    //Rect rect_line_crop_1(400-(((length/2)-cam_dist)*cm_px), 300 - 3, length*cm_px,6);
    Rect rect_line_crop_0(400-(x_0_offset*cm_px)-(((length/2)+cam_dist)*cm_px), 300 -(z_0_offset*cm_px)- (width/2)*cm_px, length*cm_px,width*cm_px);
    Rect rect_line_crop_1(400-(x_1_offset*cm_px)-(((length/2)-cam_dist)*cm_px), 300 -(z_1_offset*cm_px)- (width/2)*cm_px, length*cm_px,width*cm_px);
    Mat rot_mat_0( 2, 3, CV_32FC1 );
    rot_mat_0 = getRotationMatrix2D( Point(400,300), -3,1);
    Mat rot_mat_1( 2, 3, CV_32FC1 );
    rot_mat_1 = getRotationMatrix2D( Point(400,300), -1,1);//clk-ve//aclk+ve
    if ( !cap0.isOpened() )return -1;
    if ( !cap1.isOpened() )return -1;
   
    cap0.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    cap0.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    cap1.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    cap0.set(CV_CAP_PROP_CONVERT_RGB , false);
    cap0.set(CV_CAP_PROP_FPS , 120);
    cap1.set(CV_CAP_PROP_CONVERT_RGB , false);
    cap1.set(CV_CAP_PROP_FPS , 120);
    //namedWindow("Control", CV_WINDOW_AUTOSIZE);
    //    Mat values;
    int iLowH = 60;
    int iHighH = 94;
   
    int iLowS = 38;
    int iHighS = 255;
   
    int iLowV = 39;
    int iHighV = 255;
   
    //Create trackbars in "Control" window
    //createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    //createTrackbar("HighH", "Control", &iHighH, 179);
   
   
    //createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    //createTrackbar("HighS", "Control", &iHighS, 255);
   
    //createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
    //createTrackbar("HighV", "Control", &iHighV, 255);
   
   
    int iLastX_0 = -1;
    int iLastY_0 = -1;
    int iLastX_1 = -1;
    int iLastY_1 = -1;
    int x1 = 0, y1 = 0;
    int y2 = height, x2=(length/2)+cam_dist;
    int y3 = height, x3=(length/2)-cam_dist;
    int x4 = 0, y4 = 0;
    int z0=0,z1=0;
    int X=0, Y=0, Z=0;
    //int prev_X=0, prev_Y=0, prev_Z =0;
   
   
    Mat imgTmp0, imgTmp1;;
    cap0.read(imgTmp0);
    cap1.read(imgTmp1);
   
    //Create a black image with the size as the camera output
    imgTmp0 = imgTmp0(rect_line_crop_0);//300+(((length/2)-cam_dist)*2.4), 6));
    Mat imgLines0 = Mat::zeros( imgTmp0.size(), CV_8UC3 );
   
   
    //Create a black image with the size as the camera output
    imgTmp1 = imgTmp1(rect_line_crop_1);//300+(((length/2)+cam_dist)*2.4), 6));260
    Mat imgLines1 = Mat::zeros( imgTmp1.size(), CV_8UC3 );
   
    Mat plotXY = Mat::zeros(height,length, CV_8UC3 );
    Mat plotXZ = Mat::zeros(length,width, CV_8UC3 );
   
    while(true)
    {
        Mat imgOriginal0;
        Mat imgOriginal1;
       
        cap0.read(imgOriginal0); // read a new frame from video
        cap1.read(imgOriginal1);
       
        warpAffine( imgOriginal0, imgOriginal0, rot_mat_0, imgOriginal0.size() );
        warpAffine( imgOriginal1, imgOriginal1, rot_mat_1, imgOriginal1.size() );
       
        //Mat imgOriginal2 = imgOriginal0;
        imgOriginal0 = imgOriginal0(rect_line_crop_0);//300+(((length/2)-cam_dist)*2.4), 6));
        //imgOriginal0 = imgOriginal0(Rect(107,297,432,6));
       
       
        //Mat imgOriginal3 = imgOriginal1;
        imgOriginal1 = imgOriginal1(rect_line_crop_1);//300+(((length/2)+cam_dist)*2.4), 6));
       
        Mat imgHSV0;
        cvtColor(imgOriginal0, imgHSV0, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
       
        Mat imgThresholded0;
        Mat imgThresholded0_1;
        Mat imgThresholded0_2;
        inRange(imgHSV0, Scalar(0,iLowS, iLowV), Scalar(iLowH, iHighS, iHighV), imgThresholded0_1);
        inRange(imgHSV0, Scalar(iHighH, iLowS, iLowV), Scalar(255, iHighS, iHighV), imgThresholded0_2);
        imgThresholded0 = imgThresholded0_1 + imgThresholded0_2;
        erode(imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        dilate( imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        dilate( imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        erode(imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        Moments oMoments = moments(imgThresholded0);
        double dM0_01 = oMoments.m01;
        double dM0_10 = oMoments.m10;
        double dArea_0 = oMoments.m00;
       
        Mat imgHSV1;
        cvtColor(imgOriginal1, imgHSV1, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
       
        Mat imgThresholded1;
        Mat imgThresholded1_1;
        Mat imgThresholded1_2;
        inRange(imgHSV1, Scalar(0,iLowS, iLowV), Scalar(iLowH, iHighS, iHighV), imgThresholded1_1);
        inRange(imgHSV1, Scalar(iHighH, iLowS, iLowV), Scalar(255, iHighS, iHighV), imgThresholded1_2);
        imgThresholded1 = imgThresholded1_1 + imgThresholded1_2;
        erode(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        dilate( imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        dilate( imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        erode(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        Moments iMoments = moments(imgThresholded1);
        double dM1_01 = iMoments.m01;
        double dM1_10 = iMoments.m10;
        double dArea_1 = iMoments.m00;
       
        //        rectangle(imgOriginal2,rect_line_crop_0,Scalar(0,0,255));//(300-(((length/2)+cam_dist)*2.4),400-3),(300+(((length/2)-cam_dist)*2.4), 400+3));
        //
        //
        //        rectangle(imgOriginal3,rect_line_crop_1,Scalar(0,0,255));
        //
        //        line(imgOriginal2,Point(400,300),Point(400,300),Scalar(0,0,255),4);
        //        line(imgOriginal3,Point(400,300),Point(400,300),Scalar(0,0,255),4);
        //        line(imgOriginal2,Point(center_0),Point(center_0),Scalar(0,255,255),4);
        //        line(imgOriginal3,Point(center_1),Point(center_1),Scalar(0,255,255),4);
        //
        //        imshow("Original0", imgOriginal2);
        //        imshow("Original1", imgOriginal3);
        //imshow("Adjust", 0.5*imgOriginal0 + 0.5*imgOriginal1);
       
        if (dArea_0 > 10000)
        {
            //calculate the position of the ball
            int posX_0 = dM0_10 / dArea_0;
            int posY_0 = dM0_01 / dArea_0;
           
            if (iLastX_0 >= 0 && iLastY_0 >= 0 && posX_0 >= 0 && posY_0 >= 0)
            {
                //Draw a red line from the previous point to the current point
                //++line(imgLines0, Point(posX_0, posY_0), Point(iLastX_0, iLastY_0), Scalar(0,255,255), 2);
                //cout<<"X0:"<<atan(abs(90-(posX_0*0.305))/250)*180/PI<<"\t"; //"   Y:"<<posY<<endl;
                //cout<<"X0:"<<posX_0<<" Y0:"<<posY_0<<"\t";
                x1 = posX_0*px_cm;
                z0 = posY_0;
            }
            iLastX_0 = posX_0;
            iLastY_0 = posY_0;
        }
        if (dArea_1 > 10000)
        {
           
            int posX_1 = dM1_10 / dArea_1;
            int posY_1 = dM1_01 / dArea_1;
           
            if (iLastX_1 >= 0 && iLastY_1 >= 0 && posX_1 >= 0 && posY_1 >= 0)
            {
                //Draw a red line from the previous point to the current point
                //**line(imgLines1, Point(posX_1, posY_1), Point(iLastX_1, iLastY_1), Scalar(0,255,255), 2);
                //cout<<"X1:"<<atan(abs(90-(posX_1*0.305))/250)*180/PI<<endl; //"   Y:"<<posY<<endl;
                //cout<<"X1:"<<posX_1<<" Y1:"<<posY_1<<"\t";
                x4 = posX_1*px_cm;
                z1 = posY_1;
            }
            iLastX_1 = posX_1;
            iLastY_1 = posY_1;
        }
        //try{
        //cout<<"x1:"<<x1<<" x4:"<<x4<<"\t";
        if((((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)))!=0)
        {
            X = {((((x1*y2)-(y1*x2))*(x3-x4)) - ((x1-x2)*((x3*y4)-(y3*x4)))) / (((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)))};
            Y = {((((x1*y2)-(y1*x2))*(y3-y4)) - (y1-y2)*((x3*y4)-(y3*x4))) / (((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)))};
            Y = abs(Y);
        }
        Z = ((z0+z1)/2)*px_cm;
        if((length/2)-X != 0)
        {
            angle = (90 - atan((float)abs((float)Y)/abs((float)(length/2)-X))*180/PI) * (float)(((length/2)-X)>0?1:-1);
            //sleep(1);
        }
        //}
        //catch(Exception e)
        //{
        //    cout<<e.msg;
        //}
        if(dArea_0>10000 && dArea_1>10000)
        {
            cout<<"X: "<<X<<" Y:"<<Y<<" Z:"<<Z<<" Angle:"<<angle;
            //fprintf(arduino,"%d",angle);
            //usleep(1);
        }
        cout<<"sent";
       
        if(dArea_0>10000 && dArea_1>10000)cout<<endl;
        imshow("0",imgOriginal0);
        imshow("1",imgOriginal1);
 cout<<"enbter";
        //cin>>angle;
        fprintf(arduino,"%d",angle);
        usleep(10);
       
    }
   
}

*/



 ////MAINNnnnnnnnnnn
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Math.h"
#include <stdio.h>
#include <unistd.h>

using namespace cv;
using namespace std;

#define PI 3.14159265
#define height 190//270
#define cam_dist 25
#define length 98//100//176
#define width 80//44//50//84
//800px = 2*tan(24.1 deg)*height
//800px = 241.5cm
//1 cm = 3.31px
//1px = 0.301875cm

#define cm_px 4.706//4.706//3.2//3.31
#define px_cm 0.212//0.212//0.3333//0.301875



int main( int argc, char** argv )
{
    int angle = 0;
   
    VideoCapture cap0(0);//right camera

    VideoCapture cap1(1);//left camera
   
    FILE * arduino;
    //cout<<arduino;
    int z_0_offset = 5, z_1_offset = 0;
    int x_0_offset = 8, x_1_offset = -6+2;
    //Point center_0 = Point(400-(x_0_offset*cm_px),300-(z_0_offset*cm_px));
    //Point center_1 = Point(400-(x_1_offset*cm_px),300-(z_1_offset*cm_px));
    //Rect rect_line_crop_0(400-(((length/2)+cam_dist)*cm_px), 300 - 3, length*cm_px,6);
    //Rect rect_line_crop_1(400-(((length/2)-cam_dist)*cm_px), 300 - 3, length*cm_px,6);
    Rect rect_line_crop_0(400-(x_0_offset*cm_px)-(((length/2)+cam_dist)*cm_px), 300 -(z_0_offset*cm_px)- (width/2)*cm_px, length*cm_px,width*cm_px);
    Rect rect_line_crop_1(400-(x_1_offset*cm_px)-(((length/2)-cam_dist)*cm_px), 300 -(z_1_offset*cm_px)- (width/2)*cm_px, length*cm_px,width*cm_px);
    Mat rot_mat_0( 2, 3, CV_32FC1 );
    rot_mat_0 = getRotationMatrix2D( Point(400,300), -3,1);
    Mat rot_mat_1( 2, 3, CV_32FC1 );
    rot_mat_1 = getRotationMatrix2D( Point(400,300), -1,1);//clk-ve//aclk+ve
    if ( !cap0.isOpened() )return -1;
    if ( !cap1.isOpened() )return -1;
   
    cap0.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    cap0.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    cap1.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    cap0.set(CV_CAP_PROP_CONVERT_RGB , false);
    cap0.set(CV_CAP_PROP_FPS , 120);
    cap1.set(CV_CAP_PROP_CONVERT_RGB , false);
    cap1.set(CV_CAP_PROP_FPS , 120);
    //namedWindow("Control", CV_WINDOW_AUTOSIZE);
//    Mat values;
    int iLowH = 60;
    int iHighH = 94;
   
    int iLowS = 38;
    int iHighS = 255;
   
    int iLowV = 39;
    int iHighV = 255;
   
    //Create trackbars in "Control" window
    //createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    //createTrackbar("HighH", "Control", &iHighH, 179);
   
   
    //createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    //createTrackbar("HighS", "Control", &iHighS, 255);
   
    //createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
    //createTrackbar("HighV", "Control", &iHighV, 255);
   
   
    int iLastX_0 = -1;
    int iLastY_0 = -1;
    int iLastX_1 = -1;
    int iLastY_1 = -1;
    int x1 = 0, y1 = 0;
    int y2 = height, x2=(length/2)+cam_dist;
    int y3 = height, x3=(length/2)-cam_dist;
    int x4 = 0, y4 = 0;
    int z0=0,z1=0;
    int X=0, Y=0, Z=0;
    //int prev_X=0, prev_Y=0, prev_Z =0;
   
   
    Mat imgTmp0, imgTmp1;;
    cap0.read(imgTmp0);
    cap1.read(imgTmp1);
   
    //Create a black image with the size as the camera output
    imgTmp0 = imgTmp0(rect_line_crop_0);//300+(((length/2)-cam_dist)*2.4), 6));
    Mat imgLines0 = Mat::zeros( imgTmp0.size(), CV_8UC3 );

   
    //Create a black image with the size as the camera output
    imgTmp1 = imgTmp1(rect_line_crop_1);//300+(((length/2)+cam_dist)*2.4), 6));260
    Mat imgLines1 = Mat::zeros( imgTmp1.size(), CV_8UC3 );
   
    Mat plotXY = Mat::zeros(height,length, CV_8UC3 );
    Mat plotXZ = Mat::zeros(length,width, CV_8UC3 );
   
    while (true)
    {
        //int fps = cap0.get(5);
        //cout<<fps<<"\t";
       
        Mat imgOriginal0;
        Mat imgOriginal1;
       
        cap0.read(imgOriginal0); // read a new frame from video
        cap1.read(imgOriginal1);
       
        warpAffine( imgOriginal0, imgOriginal0, rot_mat_0, imgOriginal0.size() );
        warpAffine( imgOriginal1, imgOriginal1, rot_mat_1, imgOriginal1.size() );
       
        //Mat imgOriginal2 = imgOriginal0;
        imgOriginal0 = imgOriginal0(rect_line_crop_0);//300+(((length/2)-cam_dist)*2.4), 6));
        //imgOriginal0 = imgOriginal0(Rect(107,297,432,6));
       
       
        //Mat imgOriginal3 = imgOriginal1;
        imgOriginal1 = imgOriginal1(rect_line_crop_1);//300+(((length/2)+cam_dist)*2.4), 6));
       
        Mat imgHSV0;
        cvtColor(imgOriginal0, imgHSV0, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
       
        Mat imgThresholded0;
        Mat imgThresholded0_1;
        Mat imgThresholded0_2;
        inRange(imgHSV0, Scalar(0,iLowS, iLowV), Scalar(iLowH, iHighS, iHighV), imgThresholded0_1);
        inRange(imgHSV0, Scalar(iHighH, iLowS, iLowV), Scalar(255, iHighS, iHighV), imgThresholded0_2);
        imgThresholded0 = imgThresholded0_1 + imgThresholded0_2;
        erode(imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        dilate( imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        dilate( imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        erode(imgThresholded0, imgThresholded0, getStructuringElement(MORPH_ELLIPSE, Size(20, 20)) );
        Moments oMoments = moments(imgThresholded0);
        double dM0_01 = oMoments.m01;
        double dM0_10 = oMoments.m10;
        double dArea_0 = oMoments.m00;
       
        Mat imgHSV1;
        cvtColor(imgOriginal1, imgHSV1, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
       
        Mat imgThresholded1;
        Mat imgThresholded1_1;
        Mat imgThresholded1_2;
        inRange(imgHSV1, Scalar(0,iLowS, iLowV), Scalar(iLowH, iHighS, iHighV), imgThresholded1_1);
        inRange(imgHSV1, Scalar(iHighH, iLowS, iLowV), Scalar(255, iHighS, iHighV), imgThresholded1_2);
        imgThresholded1 = imgThresholded1_1 + imgThresholded1_2;
        erode(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        dilate( imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        dilate( imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        erode(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        Moments iMoments = moments(imgThresholded1);
        double dM1_01 = iMoments.m01;
        double dM1_10 = iMoments.m10;
        double dArea_1 = iMoments.m00;
       
//        rectangle(imgOriginal2,rect_line_crop_0,Scalar(0,0,255));//(300-(((length/2)+cam_dist)*2.4),400-3),(300+(((length/2)-cam_dist)*2.4), 400+3));
//   
//       
//        rectangle(imgOriginal3,rect_line_crop_1,Scalar(0,0,255));
//       
//        line(imgOriginal2,Point(400,300),Point(400,300),Scalar(0,0,255),4);
//        line(imgOriginal3,Point(400,300),Point(400,300),Scalar(0,0,255),4);
//        line(imgOriginal2,Point(center_0),Point(center_0),Scalar(0,255,255),4);
//        line(imgOriginal3,Point(center_1),Point(center_1),Scalar(0,255,255),4);
//       
//        imshow("Original0", imgOriginal2);
//        imshow("Original1", imgOriginal3);
        //imshow("Adjust", 0.5*imgOriginal0 + 0.5*imgOriginal1);
       
        if (dArea_0 > 10000)
        {
            //calculate the position of the ball
            int posX_0 = dM0_10 / dArea_0;
            int posY_0 = dM0_01 / dArea_0;
           
            if (iLastX_0 >= 0 && iLastY_0 >= 0 && posX_0 >= 0 && posY_0 >= 0)
            {
                //Draw a red line from the previous point to the current point
                //++line(imgLines0, Point(posX_0, posY_0), Point(iLastX_0, iLastY_0), Scalar(0,255,255), 2);
                //cout<<"X0:"<<atan(abs(90-(posX_0*0.305))/250)*180/PI<<"\t"; //"   Y:"<<posY<<endl;
                //cout<<"X0:"<<posX_0<<" Y0:"<<posY_0<<"\t";
                x1 = posX_0*px_cm;
                z0 = posY_0;
            }
            iLastX_0 = posX_0;
            iLastY_0 = posY_0;
        }
            if (dArea_1 > 10000)
            {
               
                int posX_1 = dM1_10 / dArea_1;
                int posY_1 = dM1_01 / dArea_1;
               
                if (iLastX_1 >= 0 && iLastY_1 >= 0 && posX_1 >= 0 && posY_1 >= 0)
                {
                    //Draw a red line from the previous point to the current point
                    //**line(imgLines1, Point(posX_1, posY_1), Point(iLastX_1, iLastY_1), Scalar(0,255,255), 2);
                    //cout<<"X1:"<<atan(abs(90-(posX_1*0.305))/250)*180/PI<<endl; //"   Y:"<<posY<<endl;
                    //cout<<"X1:"<<posX_1<<" Y1:"<<posY_1<<"\t";
                    x4 = posX_1*px_cm;
                    z1 = posY_1;
                }
                iLastX_1 = posX_1;
                iLastY_1 = posY_1;
            }
        //try{
            //cout<<"x1:"<<x1<<" x4:"<<x4<<"\t";
        if((((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)))!=0)
        {
        X = {((((x1*y2)-(y1*x2))*(x3-x4)) - ((x1-x2)*((x3*y4)-(y3*x4)))) / (((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)))};
        Y = {((((x1*y2)-(y1*x2))*(y3-y4)) - (y1-y2)*((x3*y4)-(y3*x4))) / (((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)))};
        Y = abs(Y);
        }
        Z = ((z0+z1)/2)*px_cm;
        if((length/2)-X != 0)
        {
        angle = (90 - atan((float)abs((float)Y)/abs((float)(length/2)-X))*180/PI) * (float)(((length/2)-X)>0?-1:1);
            //sleep(1);
        }
        //}
        //catch(Exception e)
        //{
        //    cout<<e.msg;
        //}
 ///////*********
        if(dArea_0>10000 && dArea_1>10000)
        {
            cout<<"X: "<<X<<" Y:"<<Y<<" Z:"<<Z<<" Angle:"<<angle;
            arduino = fopen("/dev/cu.usbmodem1D1131","w");
            fprintf(arduino,"%d\n",angle);
            usleep(1000000);
        }
            //cout<<"sent";
       
        if(dArea_0>10000 && dArea_1>10000)cout<<endl;
//        line(plotXY,Point(x1,y1),Point(x1,y1),Scalar(0,0,250),5);
//        line(plotXY,Point(x4,y4),Point(x4,y4),Scalar(0,0,250),5);
//        line(plotXY,Point(X,Y),Point(prev_X,prev_Y),Scalar(250,255,255),2);
//
//        line(plotXZ,Point(X,Z),Point(prev_X,prev_Z),Scalar(250,255,255),2);
//       
//        prev_X = X;
//        prev_Y = Y;
//        prev_Z = Z;
//       
        //..line(imgOriginal2,center_0,Point(400,300),Scalar(0,0,255),4);
        //..line(imgOriginal3,center_1,Point(400,300),Scalar(0,0,255),4);
//        imshow("Thresholded Image 0", imgThresholded0);
//        imshow("Thresholded Image 1", imgThresholded1);
//       
//        imgOriginal0 = imgOriginal0 + imgLines0;
//        imgOriginal1 = imgOriginal1 + imgLines1;
        //imshow("Original0", imgOriginal0);
        //imshow("Original1", imgOriginal1);
        //cout<<"loop"<<endl;
//        imshow("Plot Ball XY", plotXY);
//        imshow("Plot Ball XZ", plotXZ);
//       
        //imgLines0 = Mat::zeros( imgTmp0.size(), CV_8UC3 );
        //imgLines1 = Mat::zeros( imgTmp1.size(), CV_8UC3 );
       
        //plotXY = Mat::zeros(180,250, CV_8UC3 );
        //plotXY = Mat::zeros(height,length, CV_8UC3 );
        //plotZY = Mat::zeros(width,length, CV_8UC3 );
       
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            //cout << "esc key is pressed by user" << endl;
            imgLines0 = Mat::zeros( imgTmp0.size(), CV_8UC3 );
            imgLines1 = Mat::zeros( imgTmp0.size(), CV_8UC3 );
            plotXY = Mat::zeros(height,length, CV_8UC3 );
            plotXZ = Mat::zeros(width,length, CV_8UC3 );
           
            //break;
        }
    }
   
    return 0;
   
}




/*
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Math.h"
using namespace cv;
using namespace std;
#define PI 3.14159265

int main( int argc, char** argv )
{
    VideoCapture cap(0); //capture the video from webcam
  
   
    if ( !cap.isOpened() )  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
   
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
   
    int iLowH = 60;
    int iHighH = 94;
   
    int iLowS = 38;
    int iHighS = 255;
   
    int iLowV = 39;
    int iHighV = 255;
   
   
    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);
   
    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);
   
    createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);
   
    int iLastX = -1;
    int iLastY = -1;
   
    //Capture a temporary image from the camera
    Mat imgTmp;
    cap.read(imgTmp);
    //Mat imgTmp1 = imgTmp;
    //imgTmp = imgTmp(Rect(26, 237, 588, 6));
    //Create a black image with the size as the camera output
   
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
   
   
    while (true)
    {
        Mat imgOriginal;
       
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video
        Mat imgOriginal2 = imgOriginal;
        //imgOriginal = imgOriginal(Rect(26, 237, 588, 6));
       
       
        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }
       
        Mat imgHSV;
       
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
       
        Mat imgThresholded1;
        Mat imgThresholded2;
        Mat imgThresholded;
        inRange(imgHSV, Scalar(0,iLowS, iLowV), Scalar(iLowH, iHighS, iHighV), imgThresholded1);
        inRange(imgHSV, Scalar(iHighH, iLowS, iLowV), Scalar(255, iHighS, iHighV), imgThresholded2);//Threshold the image
       
        imgThresholded = imgThresholded1 + imgThresholded2;
       
        //inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
        //morphological opening (removes small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
       
        //morphological closing (removes small holes from the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
       
        //Calculate the moments of the thresholded image
        Moments oMoments = moments(imgThresholded);
       
        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;
        //cout<<dM01<<"\t"<<dM10<<"\t"<<dArea<<endl;
        //line(imgLines,Point(26,237),Point(614,237),Scalar(250,0,0),1);
        //line(imgLines,Point(614,237),Point(614,243),Scalar(250,0,0),1);
        //line(imgLines,Point(614,243),Point(26,243),Scalar(250,0,0),1);
        //line(imgLines,Point(26,243),Point(26,237),Scalar(250,0,0),1);
        // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
        if (dArea > 10000)
        {
            //calculate the position of the ball
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;
           
            if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
            {
                //Draw a red line from the previous point to the current point
                line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,255,255), 2);
                cout<<"X:"<<atan(abs(90-(posX*0.305))/250)*180/PI<<endl; //"   Y:"<<posY<<endl;
            }
           
            iLastX = posX;
            iLastY = posY;
        }
       
        //imshow("Thresholded Image 1", imgThresholded1); //show the thresholded image
        //imshow("Thresholded Image 2", imgThresholded2);
        imshow("Thresholded Image", imgThresholded);
        //imshow("Thresholded Image_invert", imgThresholded_invert);
        imgOriginal = imgOriginal + imgLines;
        imshow("Original", imgOriginal); //show the original image
        imshow("Original2", imgOriginal2);
        //imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            //cout << "esc key is pressed by user" << endl;
            imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
            //break;
        }
    }
   
    return 0;
}
*/
