#include "Animation.h"
#include <opencv2/opencv.hpp>
#include<Windows.h>

#include <chrono>
#include <thread>
//topLeft.x += ((1 / 10) * (canvas.size().width));

//varible
//int screen_width = GetSystemMetrics(SM_CXSCREEN);
//int screen_height = GetSystemMetrics(SM_CYSCREEN);
//cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
bool isToExit;
int key;

//function
cv::Point moveWalkRight(cv::Point topLeft);
cv::Point moveJampRight(cv::Point topLeft);
void duck();
void moveRightBackground();
void jumpRight();
void stop();
void walkRight();
void path();
//main
//int main()
//{
//	cv::resize(background, background, cv::Size(screen_width, screen_height));
//
//	// Animation is a class we wrote for saving you the handling with the 
//	// details of image processing and focusing on code design. iyH we'll get 
//	// to it in the image processing course.
//	Animation animationRun = Animation(R"(../Animations/Hero/runRight)");
//
//	// OpenCV is a popular image processing and computer vision library.
//	// it is not part of the C++ language, but it's written in C++.
//	// in this project we integrated it for you.
//	// The class that represents an image in OpenCV is Mat (i.e. Matrix),
//	// and it's defined inside namespace cv. So the full name is cv::Mat.
//	
//	
//	// player
//	isToExit = false;
//	while (false == isToExit)
//	{
//		walkRight();
//		path();
//	}	
//	return 0;
//}
// 1.
// draws an animation of our hero that ducks in place, and stays down till you 
// press the 'w' key. (if (key == 'w'))
//void duck() {
//    key = GetAsyncKeyState(VK_DOWN) & 0x8000;
//	Animation animationDuckDown = Animation(R"(../Animations/Hero/duckDown)");
//	for (int i = 0; i < animationDuckDown.numFrames(); i++)
//	{
//		Frame const& frame = animationDuckDown.getFrame(i);
//		// create a copy of the original backgrount - not to "dirty" it.
//		cv::Mat canvas = background.clone();
//		// the point of the canvas where we would like to place the top left corner 
//		// of our frame. NOTE: the y axis on the screen goes from top to bottom.
//		cv::Point topLeft(canvas.size().width / 3, canvas.size().height * 0.67);
//		topLeft = moveWalkRight(topLeft);
//		drawFrame(frame, canvas, topLeft);
//		// show what we've got (use BOTH of the following two commands):
//		cv::imshow("test", canvas);
//		// wait 100 milliseconds for a key to be pressed. if not pressed, returns -1:
//		// (you MUST call it after cv::imshow. will discuss why in image processing).
//		int key = cv::waitKey(100);
//		
//		if (key == 27) // if you pressed ESC key
//		{
//			isToExit = true;
//		}
//	}
//	Animation animationDuckStay = Animation(R"(../Animations/Hero/duckStay)");
//
//	while (key!= (GetAsyncKeyState(VK_UP) & 0x8000)) {
//		Frame const& frame = animationDuckStay.getFrame(0);
//		// create a copy of the original backgrount - not to "dirty" it.
//		cv::Mat canvas = background.clone();
//		// the point of the canvas where we would like to place the top left corner 
//		// of our frame. NOTE: the y axis on the screen goes from top to bottom.
//		cv::Point topLeft(canvas.size().width / 3, canvas.size().height * 0.67);
//		topLeft = moveWalkRight(topLeft);
//		drawFrame(frame, canvas, topLeft);
//		// show what we've got (use BOTH of the following two commands):
//		cv::imshow("test", canvas);
//		int key = cv::waitKey(100);
//		if (key != (GetAsyncKeyState(VK_UP) & 0x8000))
//			return;
//		if (key == 27) // if you pressed ESC key
//		{
//			isToExit = true;
//		}
//	}
//}
//
//// 2.
//// draws an animation of our hero that walks to the right, and ACTUALLLY MOVES RIGHT
//// with a constant speed, of (1/10)*(image width) per 100 milliseconds (=0.1 second).
//void moveRightBackground() {
//	std::this_thread::sleep_for(std::chrono::seconds(10));
//}
//
//
//// 3.
//// draw our hero jumps up and right, and stays standing after jump finishes.
//void jumpRight() {
//	key = GetAsyncKeyState(VK_UP) & 0x8000;
//	Animation animationDuckJamp = Animation(R"(../Animations/Hero/standAfterDuck/jump)");
//	for (int i = 0; i < animationDuckJamp.numFrames(); i++)
//	{
//		Frame const& frame = animationDuckJamp.getFrame(i);
//		// create a copy of the original backgrount - not to "dirty" it.
//		cv::Mat canvas = background.clone();
//		// the point of the canvas where we would like to place the top left corner 
//		// of our frame. NOTE: the y axis on the screen goes from top to bottom.
//		cv::Point topLeft(canvas.size().width / 3, canvas.size().height * (0.67));
//		topLeft.y -= 70*i;
//
//		topLeft = moveWalkRight(topLeft);
//		drawFrame(frame, canvas, topLeft);
//		// show what we've got (use BOTH of the following two commands):
//		cv::imshow("test", canvas);
//		// wait 100 milliseconds for a key to be pressed. if not pressed, returns -1:
//		// (you MUST call it after cv::imshow. will discuss why in image processing).
//	    key = cv::waitKey(1000);
//		if (key != ( GetAsyncKeyState(VK_UP) & 0x8000))
//			return;
//		if (key == 27) // if you pressed ESC key
//		{
//			isToExit = true;
//		}
//	}
//}
//
//void stop()
//{
//	key = GetAsyncKeyState(VK_LEFT) & 0x8000;
//	Animation animationIdle = Animation(R"(../Animations/Hero/idle)");
//	for (int i = 0; i < animationIdle.numFrames(); i++)
//	{
//		Frame const& frame = animationIdle.getFrame(i);
//		// create a copy of the original backgrount - not to "dirty" it.
//		cv::Mat canvas = background.clone();
//		// the point of the canvas where we would like to place the top left corner 
//		// of our frame. NOTE: the y axis on the screen goes from top to bottom.
//		cv::Point topLeft(canvas.size().width / 3, canvas.size().height * 0.67);
//		topLeft = moveWalkRight(topLeft);
//		drawFrame(frame, canvas, topLeft);
//		// show what we've got (use BOTH of the following two commands):
//		cv::imshow("test", canvas);
//		// wait 100 milliseconds for a key to be pressed. if not pressed, returns -1:
//		// (you MUST call it after cv::imshow. will discuss why in image processing).
//		int key = cv::waitKey(100);
//		if (key != (GetAsyncKeyState(VK_LEFT) & 0x8000))
//			return;
//		if (key == 27) // if you pressed ESC key
//		{
//			isToExit = true;
//		}
//	}
//}
//
//void walkRight()
//{
//	Animation animationRunRight = Animation(R"(../Animations/Hero/runRight)");
//	key = GetAsyncKeyState(VK_RIGHT) & 0x8000;
//	for (int i = 0; i < animationRunRight.numFrames(); i++)
//	{
//		Frame const& frame = animationRunRight.getFrame(i);
//		// create a copy of the original backgrount - not to "dirty" it.
//		cv::Mat canvas = background.clone();
//		// the point of the canvas where we would like to place the top left corner 
//		// of our frame. NOTE: the y axis on the screen goes from top to bottom.
//		cv::Point topLeft(canvas.size().width / 3, canvas.size().height * 0.67);
//		topLeft = moveWalkRight(topLeft);
//		drawFrame(frame, canvas, topLeft);
//		// show what we've got (use BOTH of the following two commands):
//		cv::imshow("test", canvas);
//		// wait 100 milliseconds for a key to be pressed. if not pressed, returns -1:
//		// (you MUST call it after cv::imshow. will discuss why in image processing).
//		int key = cv::waitKey(100);
//		if (key != (GetAsyncKeyState(VK_UP) & 0x8000))
//			return;
//		if (key == 27) // if you pressed ESC key
//		{
//			isToExit = true;
//		}
//	}
//}
//
//
//// 4.
//void path() {
//	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
//		walkRight();
//	}
//	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
//		duck();
//	}
//	else if (GetAsyncKeyState(VK_UP) & 0x8000) {
//		jumpRight();
//	}	
//	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
//		stop();
//	}
//}
//// write a main() that:
//// when user presses 'd' - hero walks right
//// when user presses 's' - hero ducks
//// when user presses 'w - hero jumps
//// when user presses 'a' - hero stops (if it was walking right before)
//
//// 5.
//// in walkRight - when hero reaches the canvas boundery - don't let it go outside of image.
//// force the hero x coordinate to be such that we'll see her.
//// hint: you can get hero image cv::Mat with frame.image
//
//// 6.
//// do the same with jumpRight
//
//cv::Point moveWalkRight(cv::Point topLeft)
//{
//	topLeft.x += 10;
//	return topLeft;
//}
//cv::Point moveJampRight(cv::Point topLeft)
//{
//	topLeft.x += 10;
//	return topLeft;
//}
//
