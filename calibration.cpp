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

bool cmpSubPix(const Point2d& a, const Point2d& b)
{
	if (a.x < b.x)
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
����ϵ�ֱ��ת��Ϊax + by + c = 0�ı�׼��ʽ
y0=(m/n)x0+b  -> mx-ny+(-mx0+ny0)=0
m=InputLine[1]
n=InputLine[0]
x0=InputLine[2]
y0=InputLine[3]
*/
void Calibration::changeLine2std(const Vec4f InputLine, Vec3f &OutputLine)
{
	float a, b, c;
	a = InputLine[1];
	b = -InputLine[0];
	c = -InputLine[1] * InputLine[2] + InputLine[0] * InputLine[3];
	OutputLine[0] = a;
	OutputLine[1] = b;
	OutputLine[2] = c;
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

	   /* imshow("BinImg", BinImg);
		waitKey(0);*/

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

	/*	imshow("newmrois[i]", *m_rois[i]);
		waitKey(0);*/

		const int max_s = num_location.size();
		if (Classify(num_location[max_s - 1], Sequence) == MIDDLE)//ȥβ
		{			
			m_rois[i]->adjustROI(0, 0, 0, - (m_rois[i]->cols - 1 - num_location[max_s - 1].x));			
		}	

	/*	imshow("newmrois[i]", *m_rois[i]);
		waitKey(0);*/

		//������ȡ�ֱ�Ե����
		num_location.clear();
		BinImg = m_rois[i]->clone();//��¡һ��roi���ڴ�Ŵ����Ķ�ֵͼ
		getSmallEdgePoint(*m_rois[i], BinImg, num_location);//ֻ����ˮƽ����ֱ����ı�Ե��
	/*	imshow("BinImg", BinImg);
		waitKey(0);*/


		vector<vector<double> > Ks(m_rois[i]->cols, vector<double>(m_rois[i]->rows));//�������Kֵ,> >�м�ո���ʡ��
		for (int m = 0; m < m_rois[i]->cols; m++) //��ʼ��Ϊ0
			for (int n = 0; n < m_rois[i]->rows; n++)
				Ks[m][n] = 0.0;

		//�������дֱ�Ե����
		for (int m = 0; m < num_location.size() - 2; m++)
		{
			if (Classify(num_location[m], Sequence) != MIDDLE)//�м�Ĳ���
			{

				Mat* smallROI;//Ϊһ���ݴ���3��ROI
				smallROI = new Mat[3];
				for (int n = 0; n < 3; n++)
				{
					Mat matNewRoi;
					matNewRoi = (*m_rois[i])(Rect(num_location[m + n].x, num_location[m + n].y, num_location[m + n].width, num_location[m + n].height));//������ͼ����ѡȡroi
					matNewRoi.adjustROI(3, 3, 0, 0);//��roi����Ϊ7*7	
					smallROI[n] = matNewRoi;
				/*	print_px_value(smallROI[n]);
					cout << " " << endl;*/
				}		
				
				/*���ֱ��*/			
				vector<Vec3f> line_stds;//��ϳ���׼��ʽֱ�ߵĲ���
				vector<Vec2d> endpoints;//�߶ζ˵�			
				for (int n = 0; n < 3; n++)
				{
					/*�����ؾ�ȷ��Եλ��*/
					vector<Vec4d> vecPara;
					vector<Point2d> subPixelRela;
					m_calEdgePara(smallROI[n], vecPara, subPixelRela);//�����ر�Ե����
					sort(subPixelRela.begin(), subPixelRela.end(), cmpSubPix); // ���������ر�Ե				
					for (int k = 0; k < subPixelRela.size(); k++)//ת��Ϊ�ڴ�ROI�е�����
					{
						subPixelRela[k].x += num_location[m + n ].x;
						subPixelRela[k].y += num_location[m + n ].y;
					}

					//��¼�߶ζ˵�
					Vec2d Endpoint;//[��˵�.x,�Ҷ˵�.x]
					const size_t size = subPixelRela.size();
					Endpoint[0] = subPixelRela[0].x;					
					Endpoint[1] = subPixelRela[size - 1].x;
					endpoints.push_back(Endpoint);

					/*ֱ�����*/
					Vec4f line_para;//��ϳ�ֱ�ߵĲ���
					Vec3f line_std;//��ϳ���׼��ʽֱ�ߵĲ���	 
					fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
					changeLine2std(line_para, line_std);//ת��Ϊ��׼��ʽ				
					line_stds.push_back(line_std);

					cout << num_location[m + n].x << " " << num_location[m + n].y << " " << num_location[m + n].width << " " << num_location[m + n].height << endl;
					cout << " " << endl;
				}

				double distance_1 = calDist(line_stds[0], endpoints[0], line_stds[1], endpoints[1]);//�������1
				double distance_2 = calDist(line_stds[1], endpoints[1], line_stds[2], endpoints[2]);//�������2
				
				/*�����������浽K������*/	
				//�м䲿��
				for (int n = num_location[m].x; n < num_location[m + 2].x; n++)
				{
					//��(��)�벿��
					const int part_1 = min(num_location[m].y, num_location[m + 1].y);
					const int part_1_end = max(num_location[m].y, num_location[m + 1].y);
					/*for (int k = part_1; k <= part_1 + abs(num_location[m].y - num_location[m + 1].y); k++)
						Ks[n][k] = REALSIZE / distance_1;*/
					for (int k = part_1; k < part_1_end; k++)
						Ks[n][k] = REALSIZE / distance_1; 
					//��(��)�벿��
					const int part_2 = min(num_location[m + 1].y, num_location[m + 2].y);
					const int part_2_end = max(num_location[m + 1].y, num_location[m + 2].y);
					for (int k = part_2; k < part_2_end; k++)
						Ks[n][k] = REALSIZE / distance_2;
				}
			}
		}

		//���˲���
		if (num_location[0].x != 0)//��ͷ
		{
			for (int n = 0; n < num_location[0].x; n++)
			{
				//��(��)�벿��
				const int part_1 = min(num_location[0].y, num_location[1].y);
				for (int k = part_1; k < part_1 + abs(num_location[0].y - num_location[1].y); k++)
					Ks[n][k] = Ks[num_location[0].x][part_1];
				//��(��)�벿��
				const int part_2 = min(num_location[1].y, num_location[2].y);
				for (int k = part_2; k < part_2 + abs(num_location[1].y - num_location[2].y); k++)
					Ks[n][k] = Ks[num_location[0].x][part_2];
			}
		}

		//��β��
		const size_t size_of_num = num_location.size();
		for (int n = num_location[size_of_num - 1].x; n < m_rois[i]->cols; n++)//�����һ�ε�x��ʼһֱ������
		{
			//��(��)�벿��
			const int part_1 = min(num_location[size_of_num - 1 - 2].y, num_location[size_of_num - 1 - 1].y);
			for (int k = part_1; k < part_1 + abs(num_location[size_of_num - 1 - 2].y - num_location[size_of_num - 1 - 1].y); k++)
				Ks[n][k] = Ks[num_location[size_of_num - 1 - 2].x][part_1];
				//Ks[n][k] = 100.0;
			   
			//��(��)�벿��
			const int part_2 = min(num_location[size_of_num - 1 - 1].y, num_location[size_of_num - 1].y);
			for (int k = part_2; k < part_2 + abs(num_location[size_of_num - 1 - 1].y - num_location[size_of_num - 1].y); k++)
				Ks[n][k] = Ks[num_location[size_of_num - 1 - 2].x][part_2];
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

	for (int i = 0; i < size; i++)
	{
		num_location.push_back(boundingRect(Mat(contours_out[i])));// ת��Ϊ��������
	}
	sort(num_location.begin(), num_location.end(), cmp); // ����������Ϣ	
}





