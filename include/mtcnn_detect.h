#ifndef _MTCNN_DETECT_H
#define _MTCNN_DETECT_H
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "tensorflow/c/c_api.h"
#include "tensorflow_mtcnn.hpp"
#include "mtcnn.hpp"
#include "comm_lib.hpp"
#include "utils.hpp"


class Mtcnn_detect
{
public:
	Mtcnn_detect();
	~Mtcnn_detect();

	int Load_graph(const char *modelname);
	int infotrans(face_box & box, int *face_rec);
	int detect(unsigned char* imagedata, int width, int height, int channels, int* face_rec, unsigned char* resziedata, int crop_size = 160); 
private:
	TF_Session *m_sess;
	TF_Graph *m_graph;
};

#endif
