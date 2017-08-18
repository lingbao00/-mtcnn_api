#include "mtcnn_detect.h"

Mtcnn_detect::Mtcnn_detect()
{

}

Mtcnn_detect::~Mtcnn_detect()
{
	TF_Status* s = TF_NewStatus();

	TF_CloseSession(m_sess,s);
	TF_DeleteSession(m_sess,s);
	TF_DeleteGraph(m_graph);
	TF_DeleteStatus(s);
}

int Mtcnn_detect::Load_graph(const char *modelname)
{
	m_sess = load_graph(modelname,&m_graph);

	if(m_sess==nullptr)
	{
		return -1;
	}
	else 
	{
		return 0;
	}
}

int Mtcnn_detect::infotrans(face_box &face_info, int *face_rec)
{
	assert((face_info.x1 > face_info.x0)||(face_info.y1 > face_info.y0));
	face_rec[0] = face_info.x0;
	face_rec[1] = face_info.y0;
	face_rec[2] = (face_info.x1 - face_info.x0);
	face_rec[3] = (face_info.y1 - face_info.y0);
	return 0;
}

int Mtcnn_detect::detect(unsigned char* imagedata, int width, int height, int channels, int* face_rec, unsigned char* resultdata, int crop_size)
{
	
	if(channels != 3)
	{
		std::cout<<"img is not RGB"<<std::endl;
	}
	cv::Mat frame(height, width, CV_8UC3, imagedata);

	if(!frame.data)
	{
		std::cerr<<"image failed."<<std::endl;
		return -1;
	}

	float max = 0.f;
	int flag = 0;
	std::vector<face_box> face_info;

	//detect face using mtcnn
	mtcnn_detect(m_sess,m_graph,frame,face_info);

	if(face_info.size() < 1)
	{
		std::cout<<"find no person"<<std::endl;
		return -1;
	}
	else
	{
		if(face_info.size() > 1)
		{
			//if detect faces more than one ,output the max face info as int*,include min x, min y, width, height 
			for(size_t i=0;i<face_info.size();i++)
			{
				face_box& box = face_info[i];

				float width = (box.x1 - box.x0);
				float height = (box.y1 - box.y0);
				float area = width * height;
				if(max < area)
				{
					max = area;
					flag = i;
				}
			}
		}
		//retyrn the face info as min x, min y, width, height
		infotrans(face_info[flag], face_rec);
		cv::Mat crop_img = frame(cv::Rect(face_rec[0],face_rec[1],face_rec[2],face_rec[3]));
		cv::Mat resize_img;
		cv::resize(crop_img,resize_img,cv::Size(crop_size,crop_size));
		memcpy(resultdata,resize_img.data,crop_size*crop_size*3*sizeof(unsigned char));
		if(resultdata==NULL)
		{
			printf("menmcpy error\n");
			return -1;
		}
	}
	return 0;
} 
