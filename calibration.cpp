#include "calibration.h"
#define HIGH 0
#define LEFT 0
#define MIDDLE 1
#define LOW 2
#define RIGHT 2
///*����ȽϹ���*/
//bool cmp(const Rect& a, const Rect& b)
//{
//	if (a.x < b.x)
//		return true;
//	else
//		return false;
//}

bool cmpLines(const Vec3f& a, const Vec3f& b)
{
	if (a[0] < b[0])
		return true;
	else
		return false;
}


bool cmpLines_votes(const Vec3f& a, const Vec3f& b)
{
	if (a[2] > b[2])
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

bool cmpSubPix_x(const Point2d& a, const Point2d& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}

bool cmpSubPix_y(const Point2d& a, const Point2d& b)
{
	if (a.y < b.y)
		return true;
	else
		return false;
}


/*
������ά����
*/
void reverse_index(vector<vector<double>> vec)
{ 
	int i, j;  
	cout << "Use index : " << endl;   
	for (j = 0; j < vec[0].size(); j++)	
	{ 
		for (i = 0; i < vec.size(); i++)
			cout << vec[i][j] << " ";    
		cout << endl;
		cout << " " << endl;
	} 
}


/*
����ֱ�Ե���������׼
Input:����ͼ��
Sequence:�����׼
*/
Line_Type Calibration::getClassifyStd(const Mat Input, Vec3i &Sequence)
{
	//����任���ֱ��
	vector<Vec3f> lines;//��⵽��ֱ��(����������ԭ��((0,0)��Ҳ����ͼ������Ͻǣ��ľ���;���ǻ���������ת�Ƕȣ�0~��ֱ�ߣ���/2~ˮƽ�ߣ���)	
	//'1'���ɼ�����ʱ�������ɨ�貽����'CV_PI/180'���ɼ�����ʱ��ĽǶȲ�����'10'��Сֱ�߳��ȣ�'0'��������ܹ���һ��ֱ�ߣ� 	
	HoughLines(Input, lines, 5, CV_PI / 180, 50, 0, 0);
	sort(lines.begin(), lines.end(), cmpLines_votes); // ���ۼ�����Ŀ����ֱ����Ϣ
	lines.erase(lines.begin() + 3, lines.end());
	sort(lines.begin(), lines.end(), cmpLines); // �Ե�ԭ���������ֱ����Ϣ

	if (abs(lines[1][1] - PI / 2) < abs(lines[1][1] - 0))//����ˮƽ��
	{
		Sequence[HIGH] = lines[0][0];//��
		Sequence[MIDDLE] = lines[1][0];//��
		Sequence[LOW] = lines[2][0];//��
		return HORIZONTAL;
	}
	else //Ϊ��ֱ��
	{
		//sort(lines.begin(), lines.end(), cmpLines); // �Ե�ԭ���������ֱ����Ϣ

		Sequence[LEFT] = lines[0][0];//��
		Sequence[MIDDLE] = lines[1][0];//��
		Sequence[RIGHT] = lines[2][0];//��
		return VERTICAL;
	}	
}


/*
�ֱ�Ե����������
vecEdgeOutline:�����Ե����
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
vecEdgeOutline:���е�����
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
��������ֱ�߾���
��ֱ�� L �ķ���ΪAx+By+C=0���� P ������Ϊ��X0��Y0������� P ��ֱ�� L �ľ���Ϊ:|AX0+BY0+C|/sqrt(A^2+B^2)
*/
double Calibration::calDist(const Vec3f Line_1, const Vec2d EndPoint_1, const Vec3f Line_2, const Vec2d EndPoint_2)
{
	int a = 0, b = 1, c = 2;
	int left = 0, right = 1;
	double x1 = EndPoint_1[left], x2 = EndPoint_2[right];//Line_1ʹ����˵�,Line_2ʹ���Ҷ˵�
	double y1,y2,distance, distance_1, distance_2;
	//����y1,y2
	//y = -(ax+c)/b
	y1 = -(Line_1[a] * x1 + Line_1[c]) / Line_1[b];
	y2 = -(Line_2[a] * x2 + Line_2[c]) / Line_2[b];

	//����˵㵽��һ��ֱ�ߵľ���
	distance_1 = abs(Line_2[a] * x1 + Line_2[b] * y1 + Line_2[c]) / sqrtl(Line_2[a] * Line_2[a] + Line_2[b] * Line_2[b]);
	distance_2 = abs(Line_1[a] * x2 + Line_1[b] * y2 + Line_1[c]) / sqrtl(Line_1[a] * Line_1[a] + Line_1[b] * Line_1[b]);

	//ȡƽ��
	distance = (distance_1 + distance_2) / 2;
	return distance;
}


/*
������Ե��������ȽϹ���
*/
bool cmp_x(const Rect& a, const Rect& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}

/*
������Ե��������ȽϹ���
*/
bool cmp_y(const Rect& a, const Rect& b)
{
	if (a.y < b.y)
		return true;
	else
		return false;
}
/*
��ñ�׼���Ե��ֱ�߲���
*/
void Calibration::getStdLinePars(Mat &it_rois,const vector<Rect> vecEdgeOutline,const Line_Type type)
{
		/*�õ���׼��ر�Ե����*/
		vector<Point2d> subPixel;
		subPixel.clear();
		for (auto it_Edge : vecEdgeOutline)
			while(Classify(it_Edge, Sequence) == MIDDLE)//ֻ�����м��
			{
				Mat matNewRoi;
				
				matNewRoi = it_rois(Rect(it_Edge.x, it_Edge.y, it_Edge.width, it_Edge.height));//������ͼ����ѡȡroi
				if (type == HORIZONTAL)//ˮƽ��
				{
					//sort(vecEdgeOutline.begin(), vecEdgeOutline.end(), cmp_x); // ����������Ϣ
					matNewRoi.adjustROI(3, 3, 0, 0);//��roi����Ϊ7*7
					/*�����ؾ�ȷ��Եλ��*/
					vector<Vec4d> vecPara;
					vector<Point2d> subPixelRela;
					getSubPixEdge(matNewRoi, vecPara, subPixelRela);//�����ر�Ե����
					sort(subPixelRela.begin(), subPixelRela.end(), cmpSubPix_x); // ���������ر�Ե
					for (auto it_subPixelRela : subPixelRela)//ת��Ϊ�ڴ�ROI�е����겢�����׼��Ե������
					{
						//����������
						it_subPixelRela.x += it_Edge.x;
						it_subPixelRela.y += it_Edge.y - 3;
						subPixel.push_back(it_subPixelRela);
					}
				}
					
				else//��ֱ��
				{
					//sort(vecEdgeOutline.begin(), vecEdgeOutline.end(), cmp_y); // ����������Ϣ
					matNewRoi.adjustROI(0, 0, 3, 3);//��roi����Ϊ7*7
					/*�����ؾ�ȷ��Եλ��*/
					vector<Vec4d> vecPara;
					vector<Point2d> subPixelRela;
					getSubPixEdge(matNewRoi, vecPara, subPixelRela);//�����ر�Ե����
					sort(subPixelRela.begin(), subPixelRela.end(), cmpSubPix_y); // ���������ر�Ե
					for (auto it_subPixelRela : subPixelRela)//ת��Ϊ�ڴ�ROI�е����겢�����׼��Ե������
					{
						//����������
						it_subPixelRela.x += it_Edge.x - 3;
						it_subPixelRela.y += it_Edge.y;
						subPixel.push_back(it_subPixelRela);
					}
				}
					
				break;
			}
		/*ֱ�����*/
		Vec4f std_line_para;//��ϳ�ֱ�ߵĲ���
		Vec3f std_line_std;//��ϳ���׼��ʽֱ�ߵĲ���	 
		fitLine(subPixel, std_line_para, DIST_HUBER, 0, 0.000001, 0.000001);
		changeLine2std(std_line_para, std_line_std);//ת��Ϊ��׼��ʽ
		vec_stdLines.push_back(std_line_std);
}



/*
����궨ֵk
*/
void Calibration::getK()
{
	calImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����	
	createROI(calImg, vec_rois);//����roi
	vec_stdLines.clear();//���ֱ�߲�������
	//ʹ��auto&�ķ�ʽ��������roi���ǿ�д��
	for (auto &it_rois : vec_rois)
	{
		
		/*��ôֱ�Ե����*/		
		vector<Rect> vecEdgeOutline;//�ֱ�Ե����	
		Mat BinImg;
		getRoughEdge_Normal(it_rois, BinImg, vecEdgeOutline);//ֻ����ˮƽ����ֱ����Ĵֱ�Ե��

	/*	imshow("BinImg", BinImg);
		waitKey(0);*/

		/*�����ֱ�Ե���������׼����ñ�Ե����*/
		//Vec3i Sequence;//�ֱ�Ե���������׼
		Line_Type lineType = getClassifyStd(BinImg, Sequence);//��Ե����
		vec_linetype.push_back(lineType);

		if(lineType == HORIZONTAL)
			sort(vecEdgeOutline.begin(), vecEdgeOutline.end(), cmp_x); // ����������Ϣ
		else
			sort(vecEdgeOutline.begin(), vecEdgeOutline.end(), cmp_y); // ����������Ϣ
		
		getStdLinePars(it_rois, vecEdgeOutline, lineType);
		//int aaa = 0;

		///******************У��roi***********************/
		//if (lineType == HORIZONTAL)//ˮƽ��
		//{
		//	/*У��ROI,ȥ�������޷�����궨ֵ�Ĳ���*/
		//	if (Classify(vecEdgeOutline[0], Sequence) == MIDDLE)//��ͷ
		//	{
		//		it_rois.adjustROI(0, 0, -vecEdgeOutline[1].x, 0);
		//		//BinImg.adjustROI(0, 0, - vecEdgeOutline[1].x, 0);
		//		//vecEdgeOutline.erase(vecEdgeOutline.begin());//����һ���ֱ�Ե����ɾ��
		//	}

		//	imshow("newmrois[i]", it_rois);
		//	waitKey(0);

		//	const int max_s = vecEdgeOutline.size();
		//	if (Classify(vecEdgeOutline[max_s - 1], Sequence) == MIDDLE)//ȥβ
		//	{
		//		it_rois.adjustROI(0, 0, 0, -(it_rois.cols - 1 - vecEdgeOutline[max_s - 1].x));
		//	}

		//	imshow("newmrois[i]", it_rois);
		//	waitKey(0);

		//}
		//else
		//{
		//	/*У��ROI,ȥ�������޷�����궨ֵ�Ĳ���*/
		//	if (Classify(vecEdgeOutline[0], Sequence) == MIDDLE)//��ͷ
		//	{
		//		it_rois.adjustROI(-vecEdgeOutline[1].y, 0, 0, 0);
		//		//BinImg.adjustROI(0, 0, - vecEdgeOutline[1].x, 0);
		//		//vecEdgeOutline.erase(vecEdgeOutline.begin());//����һ���ֱ�Ե����ɾ��
		//	}

		//	imshow("newmrois[i]", it_rois);
		//	waitKey(0);

		//	const int max_s = vecEdgeOutline.size();
		//	if (Classify(vecEdgeOutline[max_s - 1], Sequence) == MIDDLE)//ȥβ
		//	{
		//		it_rois.adjustROI(0, -(it_rois.rows - 1 - vecEdgeOutline[max_s - 1].y), 0, 0);
		//	}

		//	imshow("newmrois[i]", it_rois);
		//	waitKey(0);
		//}
		//	/*������ȡ�ֱ�Ե����*/
		//	vecEdgeOutline.clear();
		//	BinImg = it_rois.clone();//��¡һ��roi���ڴ�Ŵ����Ķ�ֵͼ
		//	getRoughEdge_Normal(it_rois, BinImg, vecEdgeOutline);//ֻ����ˮƽ����ֱ����ı�Ե��
		//
		//	getStdLinePars(BinImg, vecEdgeOutline, lineType);
		//	int aaa;
		/****************************ˮƽ��*****************************/
		//if (lineType == HORIZONTAL)
		//{
		//	/*У��ROI,ȥ�������޷�����궨ֵ�Ĳ���*/
		//	if (Classify(vecEdgeOutline[0], Sequence) == MIDDLE)//��ͷ
		//	{
		//		it_rois.adjustROI(0, 0, -vecEdgeOutline[1].x, 0);
		//		//BinImg.adjustROI(0, 0, - vecEdgeOutline[1].x, 0);
		//		//vecEdgeOutline.erase(vecEdgeOutline.begin());//����һ���ֱ�Ե����ɾ��
		//	}

		//	imshow("newmrois[i]", it_rois);
		//	waitKey(0);

		//	const int max_s = vecEdgeOutline.size();
		//	if (Classify(vecEdgeOutline[max_s - 1], Sequence) == MIDDLE)//ȥβ
		//	{
		//		it_rois.adjustROI(0, 0, 0, -(it_rois.cols - 1 - vecEdgeOutline[max_s - 1].x));
		//	}

		//	imshow("newmrois[i]", it_rois);
		//	waitKey(0);

		//	/*������ȡ�ֱ�Ե����*/
		//	vecEdgeOutline.clear();
		//	BinImg = it_rois.clone();//��¡һ��roi���ڴ�Ŵ����Ķ�ֵͼ
		//	getRoughEdge_Normal(it_rois, BinImg, vecEdgeOutline);//ֻ����ˮƽ����ֱ����ı�Ե��
		//														 /*imshow("BinImg", BinImg);
		//														 waitKey(0);*/

		//	/*��ʼ��Kֵ����*/
		//	vector<vector<double> > Ks(it_rois.cols, vector<double>(it_rois.rows));//�������Kֵ,> >�м�ո���ʡ��
		//	for (int m = 0; m < it_rois.cols; m++) //��ʼ��Ϊ0
		//		for (int n = 0; n < it_rois.rows; n++)
		//			Ks[m][n] = 0.0;



	
		//	/*�������дֱ�Ե����*/
		//	for (int m = 0; m < vecEdgeOutline.size() - 2; m++)
		//	{
		//		if (Classify(vecEdgeOutline[m], Sequence) != MIDDLE)//�м�Ĳ���
		//		{

		//			Mat* smallROI;//Ϊһ���ݴ���3��ROI
		//			smallROI = new Mat[3];
		//			for (int n = 0; n < 3; n++)
		//			{
		//				Mat matNewRoi;
		//				matNewRoi = it_rois(Rect(vecEdgeOutline[m + n].x, vecEdgeOutline[m + n].y, vecEdgeOutline[m + n].width, vecEdgeOutline[m + n].height));//������ͼ����ѡȡroi
		//				matNewRoi.adjustROI(3, 3, 0, 0);//��roi����Ϊ7*7	
		//				smallROI[n] = matNewRoi;
		//				/*	print_px_value(smallROI[n]);
		//				cout << " " << endl;*/
		//			}

		//			/*���ֱ��*/
		//			vector<Vec3f> line_stds;//��ϳ���׼��ʽֱ�ߵĲ���
		//			vector<Vec2d> endpoints;//�߶ζ˵�			
		//			for (int n = 0; n < 3; n++)
		//			{
		//				/*�����ؾ�ȷ��Եλ��*/
		//				vector<Vec4d> vecPara;
		//				vector<Point2d> subPixelRela;
		//				getSubPixEdge(smallROI[n], vecPara, subPixelRela);//�����ر�Ե����
		//				sort(subPixelRela.begin(), subPixelRela.end(), cmpSubPix); // ���������ر�Ե				
		//				for (int k = 0; k < subPixelRela.size(); k++)//ת��Ϊ�ڴ�ROI�е�����
		//				{
		//					subPixelRela[k].x += vecEdgeOutline[m + n].x;
		//					subPixelRela[k].y += vecEdgeOutline[m + n].y;
		//				}

		//				/*��¼�߶ζ˵�*/
		//				Vec2d Endpoint;//[��˵�.x,�Ҷ˵�.x]
		//				const size_t size = subPixelRela.size();
		//				Endpoint[0] = subPixelRela[0].x;
		//				Endpoint[1] = subPixelRela[size - 1].x;
		//				endpoints.push_back(Endpoint);

		//				/*ֱ�����*/
		//				Vec4f line_para;//��ϳ�ֱ�ߵĲ���
		//				Vec3f line_std;//��ϳ���׼��ʽֱ�ߵĲ���	 
		//				fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
		//				changeLine2std(line_para, line_std);//ת��Ϊ��׼��ʽ				
		//				line_stds.push_back(line_std);

		//			/*	cout << vecEdgeOutline[m + n].x << " " << vecEdgeOutline[m + n].y << " " << vecEdgeOutline[m + n].width << " " << vecEdgeOutline[m + n].height << endl;
		//				cout << " " << endl;*/
		//			}

		//			double distance_1 = calDist(line_stds[0], endpoints[0], line_stds[1], endpoints[1]);//�������1
		//			double distance_2 = calDist(line_stds[1], endpoints[1], line_stds[2], endpoints[2]);//�������2

		//			/*�����������浽K������*/
		//			//�м䲿��
		//			for (int n = vecEdgeOutline[m].x; n < vecEdgeOutline[m + 2].x; n++)
		//			{
		//				//��(��)�벿��
		//				const int part_1 = min(vecEdgeOutline[m].y, vecEdgeOutline[m + 1].y);
		//				const int part_1_end = max(vecEdgeOutline[m].y, vecEdgeOutline[m + 1].y);
		//				/*for (int k = part_1; k <= part_1 + abs(vecEdgeOutline[m].y - vecEdgeOutline[m + 1].y); k++)
		//				Ks[n][k] = REALSIZE / distance_1;*/
		//				for (int k = part_1; k < part_1_end; k++)
		//					Ks[n][k] = REALSIZE / distance_1;
		//				//��(��)�벿��
		//				const int part_2 = min(vecEdgeOutline[m + 1].y, vecEdgeOutline[m + 2].y);
		//				const int part_2_end = max(vecEdgeOutline[m + 1].y, vecEdgeOutline[m + 2].y);
		//				for (int k = part_2; k < part_2_end; k++)
		//					Ks[n][k] = REALSIZE / distance_2;
		//			}
		//		}
		//	}

		//	//���˲���
		//	if (vecEdgeOutline[0].x != 0)//��ͷ
		//	{
		//		for (int n = 0; n < vecEdgeOutline[0].x; n++)
		//		{
		//			//��(��)�벿��
		//			const int part_1 = min(vecEdgeOutline[0].y, vecEdgeOutline[1].y);
		//			for (int k = part_1; k < part_1 + abs(vecEdgeOutline[0].y - vecEdgeOutline[1].y); k++)
		//				Ks[n][k] = Ks[vecEdgeOutline[0].x][part_1];
		//			//��(��)�벿��
		//			const int part_2 = min(vecEdgeOutline[1].y, vecEdgeOutline[2].y);
		//			for (int k = part_2; k < part_2 + abs(vecEdgeOutline[1].y - vecEdgeOutline[2].y); k++)
		//				Ks[n][k] = Ks[vecEdgeOutline[0].x][part_2];
		//		}
		//	}

		//	//��β��
		//	const size_t size_of_num = vecEdgeOutline.size();
		//	for (int n = vecEdgeOutline[size_of_num - 1].x; n < it_rois.cols; n++)//�����һ�ε�x��ʼһֱ������
		//	{
		//		//��(��)�벿��
		//		const int part_1 = min(vecEdgeOutline[size_of_num - 1 - 2].y, vecEdgeOutline[size_of_num - 1 - 1].y);
		//		for (int k = part_1; k < part_1 + abs(vecEdgeOutline[size_of_num - 1 - 2].y - vecEdgeOutline[size_of_num - 1 - 1].y); k++)
		//			Ks[n][k] = Ks[vecEdgeOutline[size_of_num - 1 - 2].x][part_1];
		//		//Ks[n][k] = 100.0;

		//		//��(��)�벿��
		//		const int part_2 = min(vecEdgeOutline[size_of_num - 1 - 1].y, vecEdgeOutline[size_of_num - 1].y);
		//		for (int k = part_2; k < part_2 + abs(vecEdgeOutline[size_of_num - 1 - 1].y - vecEdgeOutline[size_of_num - 1].y); k++)
		//			Ks[n][k] = Ks[vecEdgeOutline[size_of_num - 1 - 2].x][part_2];
		//	}
		//}

	}
}






///*
//Input:����ͼ��
//Output:���ͼ��
//EdgePoint:��ȡ�ľ��״ģ���ˮƽ����ֱ�ߵı�Ե��
//*/
//void Calibration::getSmallEdgePoint(const Mat Input,Mat &Output, vector<Rect> &num_location)
//{
//	//*��ôֱ�Եλ��vecEdgePoint*/
//	//vector<Point2i> vecEdgePoint;//�ֱ�Ե����	
//
//	/* ��̬ѧ��Ե��ȡ*/
//	//�����Զ���ṹԪ��
//	Mat element_1 = (Mat_<uchar>(3, 3) <<   //ʮ�ֽṹԪ��
//		0, 1, 0,
//		1, 1, 1,
//		0, 1, 0);
//
//	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x�νṹԪ��
//		1, 0, 1,
//		0, -1, 0,
//		1, 0, 1);
//
//	Mat IGrad_1, IGrad_2;
//
//	getIGrad(Input, IGrad_1, element_1);
//	getIGrad(Input, IGrad_2, element_2);
//
//	Mat AllEdge;//�������б�Ե���ͼ��
//	addWeighted(IGrad_1, 0.5, IGrad_2, 0.5, 0, AllEdge);   //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
//	convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//ͼ����ǿ
//	threshold(AllEdge, AllEdge, 130, 255, THRESH_BINARY); //��ֵ��
//
//	/*ȥ��ģ���б�ߣ��ȸ�ʴ��������*/
//	Mat kernel;//���͸�ʴģ��
//	Mat Edge_X,Edge_Y,Edge_XY;//ֻ����X����ı�Ե��ֻ����Y����ı�Ե��ֻ����X��Y����ı�Ե
//	
//    //ˮƽ��
//	kernel = getStructuringElement(MORPH_RECT, Size(12, 1), Point(-1, -1));//��ʴģ��
//	erode(AllEdge, Edge_X, kernel);//��ʴ
//    kernel = getStructuringElement(MORPH_RECT, Size(9, 1), Point(-1, -1));//����ģ�壬�ȸ�ʴģ��Сһ�㣬Ϊ���洴��������׼��		
//	dilate(Edge_X, Edge_X, kernel);//����
//
//	//��ֱ��
//	kernel = getStructuringElement(MORPH_RECT, Size(1, 12), Point(-1, -1));//��ʴģ��
//	erode(AllEdge, Edge_Y, kernel);//��ʴ	
//	kernel = getStructuringElement(MORPH_RECT, Size(1, 9), Point(-1, -1));//����ģ�壬�ȸ�ʴģ��Сһ�㣬Ϊ���洴��������׼��
//	dilate(Edge_Y, Edge_Y, kernel);//����
//
//	addWeighted(Edge_X, 0.5, Edge_Y, 0.5, 0, Edge_XY);   //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
//	convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//ͼ����ǿ
//	threshold(Edge_XY, Output, 100, 255, THRESH_BINARY); //��ֵ��	
//
//	//�ֱ�Ե������ȡ
//	vector<vector<Point> > contours_out;
//	vector<Vec4i> hierarchy;
//	findContours(Edge_XY, contours_out, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
//	// re-arrange location according to the real position in the original image 
//	const size_t size = contours_out.size();
//
//	for (int i = 0; i < size; i++)
//	{
//		num_location.push_back(boundingRect(Mat(contours_out[i])));// ת��Ϊ��������
//	}
//	sort(num_location.begin(), num_location.end(), cmp); // ����������Ϣ	
//}
//




