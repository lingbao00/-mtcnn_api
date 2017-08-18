#include "mt_dec.h"

MT_dec::MT_dec()
{
	
}

MT_dec::~MT_dec()
{
	
}

Dec::Dec()
{
	m_decface = new Mtcnn_detect();
}

Dec::~Dec()
{
	if(m_decface!=NULL)
	{
		delete m_decface;
		m_decface = NULL;
	}
}

int Dec::dec(unsigned char* imagedata, int width, int height, int channels, const char* modelname, int* face_rec,
			unsigned char* resultdata, int crop_size)
			 {
			 	if(m_decface->Load_graph(modelname)!=0)
			 	{
			 		printf("load detect modle error..\n");
			 		return -1;
			 	}

			 	if(m_decface->detect(imagedata, width, height, channels, face_rec, resultdata, crop_size)!=0)
			 		return -1;
			 	return 0;
			 }