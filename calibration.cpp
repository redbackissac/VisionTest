#include "calibration.h"
#define HIGH 0
#define MIDDLE 1
#define LOW 2

/*����ȽϹ���*/
bool cmp(const Rect& a, const Rect& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}

bool cmpLines(const Vec2f& a, const Vec2f& b)
{
	if (a[0] < b[0])
		return true;
	else
		return false;
}

bool cmpDecisions(const Vec2i& a, const Vec2i& b)
{
	if (a[0] < b[0])
		return true;
	else
		return false;
}

/*
����ֱ�Ե���������׼
Input:����ͼ��
Sequence:�����׼
*/
void Calibration::getStdPixel(const Mat Input, Vec3i &Sequence)
{
	//����任���ֱ��
	vector<Vec2f> lines;//��⵽��ֱ��(����������ԭ��((0,0)��Ҳ����ͼ������Ͻǣ��ľ���;���ǻ���������ת�Ƕȣ�0~��ֱ�ߣ���/2~ˮƽ�ߣ���)	
	//'1'���ɼ�����ʱ�������ɨ�貽����'CV_PI/180'���ɼ�����ʱ��ĽǶȲ�����'10'��Сֱ�߳��ȣ�'0'��������ܹ���һ��ֱ�ߣ� 	
	HoughLines(Input, lines, 1, CV_PI / 180, 100, 0, 0);

	sort(lines.begin(), lines.end(), cmpLines); // �Ե�ԭ���������ֱ����Ϣ
	
	Sequence[HIGH] = lines[0][0];//��
	Sequence[MIDDLE] = lines[1][0];//��
	Sequence[LOW] = lines[2][0];//��
}


/*
�ֱ�Ե����������
num_location:�����Ե����
Sequence[3]:�б��׼
Classification:�����������
*/
int Calibration::Classify(const Rect num_location, const Vec3i Sequence)
{
	vector<Vec2i> decisions; //�����жϸ��е͵��б���,(�б���ֵ,����ǩ)
	for (int i = HIGH; i <= LOW; i++)//�ֱ����ÿһ����б���ֵ
	{
		Vec2i decision;		
		decision[0] = abs(num_location.y - Sequence[i]);
		decision[1] = i;
		decisions.push_back(decision);
	}

	//���������С���б���
	sort(decisions.begin(), decisions.end(), cmpDecisions); // �����б���ֵ�����б���Ϣ
	return decisions[0][1];//���ط�����
}

/*
У׼ROI��ȥ�������޷�����궨ֵ�Ĳ���
InputROI:����roi
num_location:���е�����
Sequence:�б��׼
*/
void Calibration::resetROI(Mat &InputROI, vector<Rect> num_location, const Vec3i Sequence)
{
	const int max = num_location.size();
	if(Classify(num_location[0], Sequence) == 1)//��ͷ
		InputROI.adjustROI(0, 0, -num_location[1].x, 0);
	if(Classify(num_location[max - 1], Sequence) == 1)//ȥβ
		InputROI.adjustROI(0, 0, 0, -num_location[max - 1].x);
}


/*
����궨ֵk
*/
void Calibration::getK()
{
	calImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
	//cvtColor(calImg, calImg, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(ttt).jpg", calImg);//������ƽ���˲����ͼ��
	//cout << "channels:" << calImg.channels() << endl;	//��ӡͼ��ͨ����//cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
	createROI(calImg);//����roi						 
	//��������roi����
	for (int i = 0; i != m_rois.size(); ++i)
	{
		/*��ôֱ�Եλ��vecEdgePoint*/
		//vector<Point2i> vecEdgePoint;//�ֱ�Ե����
		vector<Rect> num_location;//�ֱ�Ե����
		Mat BinImg = m_rois[i]->clone();//��¡һ��roi���ڴ�Ŵ����Ķ�ֵͼ
		getSmallEdgePoint(*m_rois[i], BinImg, num_location);//ֻ����ˮƽ����ֱ����ı�Ե��
		imshow("BinImg", BinImg);
		waitKey(0);

		/*�����ֱ�Ե���������׼*/
		Vec3i Sequence;//�ֱ�Ե���������׼
		getStdPixel(BinImg, Sequence);
		
		/*У��ROI,ȥ�������޷�����궨ֵ�Ĳ���*/		
		if (Classify(num_location[0], Sequence) == MIDDLE)//��ͷ
		{
			m_rois[i]->adjustROI(0, 0, - num_location[1].x, 0);
			//BinImg.adjustROI(0, 0, - num_location[1].x, 0);
			//num_location.erase(num_location.begin());//����һ���ֱ�Ե����ɾ��
		}
		const int max = num_location.size();
		if (Classify(num_location[max - 1], Sequence) == MIDDLE)//ȥβ
		{			
			m_rois[i]->adjustROI(0, 0, 0, - num_location[max - 2].x);
			//BinImg.adjustROI(0, 0, 0, - num_location[max - 2].x);
			//num_location.erase(num_location.end());
		}	

		//������ȡ�ֱ�Ե����
		num_location.clear();
		BinImg = m_rois[i]->clone();//��¡һ��roi���ڴ�Ŵ����Ķ�ֵͼ
		getSmallEdgePoint(*m_rois[i], BinImg, num_location);//ֻ����ˮƽ����ֱ����ı�Ե��
		imshow("BinImg", BinImg);
		waitKey(0);


		/*imshow("NewBinImg", BinImg);	
		imshow("NewROI", *m_rois[i]);
		waitKey(0);*/
		vector<vector<double> > Ks(m_rois[i]->rows, vector<double>(m_rois[i]->cols));;//�������Kֵ,> >�м�ո���ʡ��
		for (int m = 0; m < m_rois[i]->rows; m++) //��ʼ��Ϊ0
			for (int n = 0; n < m_rois[i]->cols; n++)
				Ks[m][n] = 0.0;		
		//�������дֱ�Ե����
		for (int m = 0; m < num_location.size(); m++)
		{
			if (Classify(num_location[m], Sequence) != MIDDLE)//�м�Ĳ���
			{

				Mat* smallROI;//Ϊһ���ݴ���3��ROI
				smallROI = new Mat[3];
				for (int n = 0; n < 3; n++)
				{
					Mat matNewRoi;
					matNewRoi = (*m_rois[i])(Rect(num_location[m + n].x, num_location[m + n].y, num_location[m + n].width, num_location[m + n].height));//������ͼ����ѡȡroi
					//cout << num_location[i].x << " " << num_location[i].y << endl;
					matNewRoi.adjustROI(3, 3, 0, 0);//��roi����Ϊ7*7	
					smallROI[n] = matNewRoi;		
				}		
				
				/*���ֱ��*/
				vector<Vec4f> line_paras;//��ϳ�ֱ�ߵĲ���	           
				for (int n = 0; n < 3; n++)
				{
					/*�����ؾ�ȷ��Եλ��*/
					vector<Vec4d> vecPara;
					vector<Point2d> subPixelRela;
					m_calEdgePara(smallROI[n], vecPara, subPixelRela);//�����ر�Ե����
					for (int k = 0; k < subPixelRela.size(); k++)//ת��Ϊ�ڴ�ROI�е�����
					{
						subPixelRela[k].x += num_location[m + n ].x;
						subPixelRela[k].y += num_location[m + n ].y;
					}

					/*ֱ�����*/
					Vec4f line_para;//��ϳ�ֱ�ߵĲ���
					fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
					line_paras.push_back(line_para);
				}	


											   //vector<Vec4f> line_paras;
											   ////��ÿ��Сroi������ȡ
											   //for (int i = 0; i < num_location.size(); i++)
											   //{		
											   //	/*�����ؾ�ȷ��Եλ��*/
											   //	vector<Vec4d> vecPara;
											   //	vector<Point2d> subPixelRela;
											   //	m_calEdgePara(smallROI[i], vecPara, subPixelRela);
											   //	for (int j = 0; j < subPixelRela.size(); j++)
											   //	{
											   //		subPixelRela[j].x += num_location[i].x;
											   //		subPixelRela[j].y += num_location[i].y;
											   //	}
											   //	
											   //	/*ֱ�����*/
											   //	Vec4f line_para;//��ϳ�ֱ�ߵĲ���
											   //	fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
											   //	line_paras.push_back(line_para);		
											   //}	
				//print_px_value(smallROI);
				//imshow("SmallROI", smallROI);				
				//waitKey(0); 


				//Mat* smallROI;//ΪÿһС���߶δ���ROI
				//smallROI = new Mat[num_location.size()];
				//for (int i = 0; i < num_location.size(); i++)
				//{
				//	Mat matNewRoi;
				//	matNewRoi = Input(Rect(num_location[i].x, num_location[i].y, num_location[i].width, num_location[i].height));//������ͼ����ѡȡroi
				//	//cout << num_location[i].x << " " << num_location[i].y << endl;
				//	matNewRoi.adjustROI(3, 3, 0, 0);//��roi����Ϊ7*7	
				//	smallROI[i] = matNewRoi;		
				//}

			}
		}
	}
}






/*
Input:����ͼ��
Output:���ͼ��
EdgePoint:��ȡ�ľ��״ģ���ˮƽ����ֱ�ߵı�Ե��
*/
void Calibration::getSmallEdgePoint(const Mat Input,Mat &Output, vector<Rect> &num_location)
{
	//*��ôֱ�Եλ��vecEdgePoint*/
	//vector<Point2i> vecEdgePoint;//�ֱ�Ե����	

	/* ��̬ѧ��Ե��ȡ*/
	//�����Զ���ṹԪ��
	Mat element_1 = (Mat_<uchar>(3, 3) <<   //ʮ�ֽṹԪ��
		0, 1, 0,
		1, 1, 1,
		0, 1, 0);

	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x�νṹԪ��
		1, 0, 1,
		0, -1, 0,
		1, 0, 1);

	Mat IGrad_1, IGrad_2;

	getIGrad(Input, IGrad_1, element_1);
	getIGrad(Input, IGrad_2, element_2);

	Mat AllEdge;//�������б�Ե���ͼ��
	addWeighted(IGrad_1, 0.5, IGrad_2, 0.5, 0, AllEdge);   //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
	convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//ͼ����ǿ
	threshold(AllEdge, AllEdge, 130, 255, THRESH_BINARY); //��ֵ��

	/*ȥ��ģ���б�ߣ��ȸ�ʴ��������*/
	Mat kernel;//���͸�ʴģ��
	Mat Edge_X,Edge_Y,Edge_XY;//ֻ����X����ı�Ե��ֻ����Y����ı�Ե��ֻ����X��Y����ı�Ե
	
    //ˮƽ��
	kernel = getStructuringElement(MORPH_RECT, Size(12, 1), Point(-1, -1));//��ʴģ��
	erode(AllEdge, Edge_X, kernel);//��ʴ
    kernel = getStructuringElement(MORPH_RECT, Size(9, 1), Point(-1, -1));//����ģ�壬�ȸ�ʴģ��Сһ�㣬Ϊ���洴��������׼��		
	dilate(Edge_X, Edge_X, kernel);//����

	//��ֱ��
	kernel = getStructuringElement(MORPH_RECT, Size(1, 12), Point(-1, -1));//��ʴģ��
	erode(AllEdge, Edge_Y, kernel);//��ʴ	
	kernel = getStructuringElement(MORPH_RECT, Size(1, 9), Point(-1, -1));//����ģ�壬�ȸ�ʴģ��Сһ�㣬Ϊ���洴��������׼��
	dilate(Edge_Y, Edge_Y, kernel);//����

	addWeighted(Edge_X, 0.5, Edge_Y, 0.5, 0, Edge_XY);   //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
	convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//ͼ����ǿ
	threshold(Edge_XY, Output, 100, 255, THRESH_BINARY); //��ֵ��	

	//�ֱ�Ե������ȡ
	vector<vector<Point> > contours_out;
	vector<Vec4i> hierarchy;
	findContours(Edge_XY, contours_out, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	// re-arrange location according to the real position in the original image 
	const size_t size = contours_out.size();
	//vector<Rect> num_location;//�ֱ�Ե������
	for (int i = 0; i < contours_out.size(); i++)
	{
		num_location.push_back(boundingRect(Mat(contours_out[i])));// ת��Ϊ��������
	}
	sort(num_location.begin(), num_location.end(), cmp); // ����������Ϣ
	

	
	
	
	
	
	
	
}





