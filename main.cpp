#include "mt_dec.h"
#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char** argv)
{
	if(argc < 2) 
		std::cout<<"parameter is not enough."<<std::endl;
	std::string model_path = "./models/mtcnn_frozen_model.pb";
	cv::Mat img = cv::imread(argv[1]);

	if(!img.data)
	{
		std::cout<<"img load failed."<<std::endl;
	}
	std::cout<<"-----"<<img.rows<<" "<< img.cols<<" "<< img.channels()<<std::endl;
	
	int *face_info = new int[4];
	std::cout<<"---00"<<std::endl;
	while(1){
		cv::Mat crop_resize_img(160,160,CV_8UC3);
		MT_dec *face_detect = new Dec();
		face_detect->dec(img.data, img.cols, img.rows, img.channels(), model_path.c_str(), face_info,
						crop_resize_img.data);
		//cv::Mat crop_img=img(cv::Rect(face_info[0],face_info[1], face_info[2], face_info[3]));
		cv::imwrite("result.jpg", crop_resize_img);
		delete face_detect;
	}

	return 0;
}
