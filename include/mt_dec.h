#ifndef _MT_DEC_H
#define _MT_DEC_H
#include "mtcnn_detect.h"


class MT_dec
{
public:
	MT_dec();
	virtual ~MT_dec();

	virtual int dec(unsigned char* imagedata, int width, int height, int channels, const char* modelname, int* face_rec,
			unsigned char* resultdata, int crop_size = 160) = 0;
};

class Dec : public MT_dec
{
public:
	Dec();
	~Dec();

	int dec(unsigned char* imagedata, int width, int height, int channels, const char* modelname, int* face_rec,
			unsigned char* resultdata, int crop_size = 160);
private:
	Mtcnn_detect *m_decface;
};

#endif