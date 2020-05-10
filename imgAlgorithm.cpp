#include "imgAlgorithm.h"



//��ӡmat�����е�����ֵ��������
void print_px_value(Mat& im)
{
	int rowNumber = im.rows;  //����
	int colNumber = im.cols * im.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���

											  //˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i++)  //��ѭ��
	{
		uchar* data = im.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		for (int j = 0; j < colNumber; j++)   //��ѭ��
		{
			//data[j] = data[j] / div * div + div / 2;
			cout << (int)data[j] << " ";
		}  //�д������
		cout << endl;
	}
	cout << "" << endl;
}

void ImgAlgorithm::test()//���ڲ���
{
	openImg(srcImg);//��ͼ��
	createROI(srcImg, vec_rois);//����roi
	for (auto it_roi : vec_rois)
	{
		///*��ôֱ�Եλ��vecEdgePoint*/
		//vector<Point2i> vecEdgePoint;//�ֱ�Ե����		
		//getRoughEdge_All(it_roi, vecEdgePoint);//��ȡ���Ա�Ե����

		///*Ϊÿ���ֱ�Ե����ȡ������7*7����*/
		//vector<Mat> AllNeibors;
		//getNeiborOfPoints(vecEdgePoint,it_roi, AllNeibors);



	 //   /*�����ֱ�Ե���7*7����*/
		//int neiborNum;//���������������Ե�������
		//Mat AllNeibor;//�ֱ�Ե���7*7����
		//neiborNum = vecEdgePoint.size();
	
		//getNeiborROI(vecEdgePoint, it_roi, AllNeibor);
		//


		///*�����ؾ�ȷ��Եλ��*/
		//vector<Vec4d> vecPara;
		//vector<Point2d> VecSubPixelEdgePoint;
		//getSubPixEdge(AllNeibor, vecPara, VecSubPixelEdgePoint);
		//int i = 1;
	}
	
	
}


/*
�򿪴�����ͼ��
srcImg:�򿪵�ͼ�񣬺�������Ķ�������ͼ
*/
void ImgAlgorithm::openImg(Mat &srcImg)
{
	srcImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(sb).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
}


/*
���������߳��н��յĲ����б���ROI
���ı�ԭͼ��
srcImg:����ͼ��
vec_rois��������roi����
*/
void ImgAlgorithm::createROI(const Mat srcImg, vector<Mat> &vec_rois)
{	
	vec_rois.clear();//���roi�б�Ϊ����roi��׼��
	//���������б�
	for (auto it_roipar : vec_roipars)
	{
		Mat RoiImgs = srcImg(Rect(it_roipar[0], it_roipar[1], it_roipar[2], it_roipar[3]));//����roi		
		vec_rois.push_back(RoiImgs);//���´�����roi����roi�б�	
	}	
}

void ImgAlgorithm::createROI(const Mat srcImg, vector<struct_roi>& vec_strrois)
{	
	//���������б�
	for (auto &it_roi : vec_strrois)
	{
		it_roi.roi = srcImg(Rect(it_roi.roipar[0], it_roi.roipar[1], it_roi.roipar[2], it_roi.roipar[3]));//����roi		
		//vec_rois.push_back(RoiImgs);//���´�����roi����roi�б�	
	}
}

/*
�Ľ���̬ѧ�ݶȱ�Ե��ȡ
IGrad(f) = (f open g)	dilate g - (f close g) erode g
input:����ͼ��
output:���ͼ��
element:ģ��
*/
void  ImgAlgorithm::getIGrad(const Mat input, Mat& output, Mat &element)
{
	Mat erode_ouput, dilate_output, open_output, close_output;

	morphologyEx(input, open_output, MORPH_OPEN, element);//������
	morphologyEx(input, close_output, MORPH_CLOSE, element);//�ղ���

	dilate(open_output, dilate_output, element); //���Ϳ��������ͼ��
	erode(close_output, erode_ouput, element); //��ʴ�ղ������ͼ��

	absdiff(dilate_output, erode_ouput, output);
}



/*
��ȡ���еĴֱ�Ե������
����̬ѧ�ķ������Դ��˲���ţ��ţ��
input:����ͼ��
vecEdgePoint:��¼�ı�Ե��
*/
void ImgAlgorithm::getRoughEdge_All(const Mat input, vector<Point2i>& vecEdgePoint)
{
	// �����Զ���ṹԪ��
	Mat element_1 = (Mat_<uchar>(3, 3) <<   //ʮ�ֽṹԪ��
		0, 1, 0,
		1, 1, 1,
		0, 1, 0);

	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x�νṹԪ��
		1, 0, 1,
		0, -1, 0,
		1, 0, 1);

	Mat output_1, output_2;

	getIGrad(input, output_1, element_1);//��̬ѧ��Ե��ȡ->ʮ�ֽṹԪ��
	getIGrad(input, output_2, element_2);//��̬ѧ��Ե��ȡ->x�νṹԪ��

	Mat output;
	addWeighted(output_1, 0.5, output_2, 0.5, 0, output);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��

	//��ǿͼ��ʹ��Ե��������
	convertScaleAbs(output, output, 3.0, 10);	//ͼ����ǿ
	threshold(output, output, 130, 255, THRESH_BINARY); //��ֵ��

    //��¼���дֱ�Ե�������
	Point2i  pointTemp;
	for (int i = 0; i < output.rows; i++)
		for (int j = 0; j < output.cols; j++)
			if (output.at<uchar>(i, j) == 255)
			{
				//image.at<>(x,y)������õĵ�x��y�Ƿ�������
				pointTemp.x = i;
				pointTemp.y = j;
				vecEdgePoint.push_back(pointTemp);
			}
}

///*
//������Ե��������ȽϹ���
//*/
//bool cmp(const Rect& a, const Rect& b)
//{
//	if (a.x < b.x)
//		return true;
//	else
//		return false;
//}

/*
��ȡ�����ֱ�Ե������
Input:����ͼ��
Output�����ͼ��
vecEdgeOutline:�����ֱ�Ե��ľ�������
*/
void ImgAlgorithm::getRoughEdge_Normal(const Mat Input, Mat &Output, vector<Rect> &vecEdgeOutline)
{
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
	Mat Edge_X, Edge_Y, Edge_XY;//ֻ����X����ı�Ե��ֻ����Y����ı�Ե��ֻ����X��Y����ı�Ե

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
		vecEdgeOutline.push_back(boundingRect(Mat(contours_out[i])));// ת��Ϊ��������
	}
	//sort(vecEdgeOutline.begin(), vecEdgeOutline.end(), cmp); // ����������Ϣ	
}


/*
��ȡ�Դֱ�ԵΪ���ĵ�������Ϊroi
��ñ�Ե7 * 7����
EdgePoint:Ҫ����ı�Ե��(y,x)
matIn:�������
matNeibor:������������
nbsize:�����С
*/
void ImgAlgorithm::getNeiborROI(const Line_Type type, const vector<Point2i> EdgePoint, const Mat matIn, Mat& matNeibor, Point2d &point,int nbsize)
{
	Mat matInRoi, matNewRoi;
	int halfN = (nbsize - 1) / 2;
	int x_MAX = 0;
	int x_MIN = INT_MAX;
	int y_MAX = 0;
	int y_MIN = INT_MAX;

	//�������д���ı�Ե��
	for (auto it_EdgePoint : EdgePoint)
	{
		if (x_MAX < it_EdgePoint.x) x_MAX = it_EdgePoint.x;
		if (x_MIN > it_EdgePoint.x) x_MIN = it_EdgePoint.x;
		if (y_MAX < it_EdgePoint.y) y_MAX = it_EdgePoint.y;
		if (y_MIN > it_EdgePoint.y) y_MIN = it_EdgePoint.y;
	}
	point.y = x_MIN;
	point.x = y_MIN;
	matInRoi = matIn(Range(x_MIN, x_MAX), Range(y_MIN, y_MAX));//������ͼ����ѡȡroi
	/*imshow("sex", matInRoi);
	waitKey(0);*/
	if (type == HORIZONTAL)//ˮƽ��
		matInRoi.adjustROI(halfN, halfN, 0, 0);//��roi����Ϊ7*7
	else
		matInRoi.adjustROI(0, 0, halfN, halfN);//��roi����Ϊ7*7
	
	matNeibor = matInRoi;
}


/*
����ϵ�ֱ��ת��Ϊax + by + c = 0�ı�׼��ʽ
y0=(m/n)x0+b  -> mx-ny+(-mx0+ny0)=0
m=InputLine[1]
n=InputLine[0]
x0=InputLine[2]
y0=InputLine[3]
*/
void ImgAlgorithm::changeLine2std(const Vec4f InputLine, Vec3f &OutputLine)
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
��ñ�Ե7 * 7����
EdgePoint:Ҫ����ı�Ե��(y,x)
matIn:Ҫȡ�����ͼ��
matNeibor:���,�õ�������
nbsize:�����С
*/
void ImgAlgorithm::getNeiborOfPoints(const vector<Point2i> EdgePoint, const Mat matIn, vector<Mat> &matNeibor, int nbsize)
{
	Mat matInRoi, matNewRoi;
	int halfN = (nbsize - 1) / 2;
	//�������д���ı�Ե��
	for (auto it_edgepoint : EdgePoint)
	{
		matInRoi = matIn(Rect(it_edgepoint.y, it_edgepoint.x, 1, 1));//������ͼ����ѡȡroi
		matInRoi.adjustROI(halfN, halfN, halfN, halfN);//��roi����Ϊ7*7
		matNeibor.push_back(matInRoi);
		//matNeibor[i] = matInRoi;
	}
	//for (auto it_roi : matNeibor)
		//print_px_value(it_roi);
}




/*
��ȡ�����ر�Ե
InputNeibor:����ͼ��,����ȡ�����ر�Ե������
vecPara:�����ر�Ե�Ĳ���,L,��,H,K
nbsize:�����С
*/
void ImgAlgorithm::getSubPixEdge(const Mat InputNeibor, vector<Vec4d>& vecPara, vector<Point2d>& VecSubPixelEdgePoint, int nbsize, int ZerBgrL, int ZerBgrH)
{

	Vec4d  para;
	Point2d point;

	Mat mZerImageM00;
	Mat mZerImageM11R;
	Mat mZerImageM11I;
	Mat mZerImageM20;
	Mat mZerImageM31R;
	Mat mZerImageM31I;
	Mat mZerImageM40;

	//���
	filter2D(InputNeibor, mZerImageM00, CV_64F, ZERPOLY00);
	filter2D(InputNeibor, mZerImageM11R, CV_64F, ZERPOLY11R);
	filter2D(InputNeibor, mZerImageM11I, CV_64F, ZERPOLY11I);
	filter2D(InputNeibor, mZerImageM20, CV_64F, ZERPOLY20);
	filter2D(InputNeibor, mZerImageM31R, CV_64F, ZERPOLY31R);
	filter2D(InputNeibor, mZerImageM31I, CV_64F, ZERPOLY31I);
	filter2D(InputNeibor, mZerImageM40, CV_64F, ZERPOLY40);

	double rotated_z11 = 0.0;
	double rotated_z31 = 0.0;
	double l_method1 = 0.0;
	double l_method2 = 0.0;

	double l_t1 = sqrt(2) / (2.00 * nbsize);
	double l_t2 = sqrt(2) / 2.00;

	int row_number = InputNeibor.rows;
	int col_number = InputNeibor.cols;
	//ʹ��7����7*7��Zernikeģ�壨�䱾���Ǹ�����M00��M11R��M11I��M20��M31R��M31I��M40���ֱ���ͼ����о�����õ�ÿ�����ص���߸�Zernike��Z00��Z11R��Z11I��Z20��Z31R��Z31I��Z40

	//����ÿ���㣬���������߸�Zernike�أ���þ������l�ͻҶȲ����k����l��k�������趨������ʱ�����ж��õ�Ϊ��Ե�㣬����һ����������7��Zernike������õ�������ؼ�����

	//���l��k�������趨����������õ㲻�Ǳ�Ե�㣬ת����һ�������������l�ͻҶȲ����k
	for (int i = 0; i < row_number; i++)
		for (int j = 0; j < col_number; j++)
		{
			if (mZerImageM00.at<double>(i, j) == 0)
				continue;

			para[THETA] = atan2(mZerImageM31I.at<double>(i, j), mZerImageM31R.at<double>(i, j));

			//����Z11'��Z31'Ϊ����L1,L2��׼��,rotated_z11=Z11',rotated_z31=Z31'

			rotated_z11 = sin(para[THETA])*(mZerImageM11I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM11R.at<double>(i, j));
			rotated_z31 = sin(para[THETA])*(mZerImageM31I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM31R.at<double>(i, j));

			//����L1��L2,
			/*	cout << "mZerImageM40.at<double>(i, j)" << mZerImageM40.at<double>(i, j) << endl;
			cout << "mZerImageM20.at<double>(i, j)" << mZerImageM20.at<double>(i, j) << endl;
			cout << " " << endl;*/
			l_method1 = sqrt((5 * mZerImageM40.at<double>(i, j) + 3 * mZerImageM20.at<double>(i, j)) / (8 * mZerImageM20.at<double>(i, j)));
			l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
			para[L] = (l_method1 + l_method2) / 2;
			//l = l - 0.207107;//��ȥ����ֵk

			//����k��h 
			para[K] = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
			para[H] = (mZerImageM00.at<double>(i, j) - para[K] * PI / 2 + para[K] * asin(l_method2) + para[K] * l_method2*sqrt(1 - l_method2*l_method2)) / PI;

			vecPara.push_back(para);
			/*��ֵ����*/
			//if (para[L]>l_t1 &&  para[L]<l_t2 &&  para[K]>ZerBgrL && para[H]>ZerBgrH) 
			if (abs(l_method1 - l_method2) <= (sqrt(2) / (2.00*7.00)) && para[L]<l_t2 && para[K]>ZerBgrL && para[H] <50)			
			{
				/*��Ե�߶Ȼָ�*/
				point.x = (j + para[L] * nbsize*cos(para[THETA]) / 2.00);
				point.y = (i + para[L] * nbsize*sin(para[THETA]) / 2.00);
				VecSubPixelEdgePoint.push_back(point);
			}
			else
				continue;

		}

	//��ʾ����⵽�������ر�Ե

	//	for (size_t i = 0; i < subPixelRela.size(); i++)

	//{

	//	Point center_forshow(cvRound(subPixelRela[i].x), cvRound(subPixelRela[i].y));

	//	circle(matSingleResizeNeibor, center_forshow, 1, 255, 1, 8, 0);

	//}
	//int i = 0;
	//imshow("�����ر�Ե", matSingleResizeNeibor);
	////imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\�����ر�Ե.jpg", matSingleResizeNeibor);//������ƽ���˲����ͼ��	

	//waitKey(0);
}



//
///*
//���ƽ���˲�
//�������:int imgNumͼ������
//���:Mat����ƽ����ͼ��
//*/
//Mat SingleBattery::ImageAverage(int imgNum)
//{
//	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".png", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
//	cvtColor(temp, temp, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", temp);//������ƽ���˲����ͼ��
//	cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
//	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC1);                                       //��ʼ��ƽ��ͼ��Mat����ʽΪCV_32FC
//	for (int i = 1; i <= imgNum; i++)                                                                 //���δ�3��ͼƬ
//	{
//		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg", IMREAD_UNCHANGED);//�����i��ͼƬ		                                                       
//		accumulate(temp, AverageImage);                                                         //����ʱͼ����ƽ��ͼ�����
//	}
//	AverageImage /= imgNum;                                                                     //ȡƽ��	
//	AverageImage.convertTo(AverageImage, CV_8UC1);                                              //Ϊ��ʾ��Ҫ������ת��Ϊ8UC1
//																								//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//������ƽ���˲����ͼ��
//	return AverageImage;
//}
//
//
//Mat SingleBattery::getEdgeVal(Mat srcImg)
//{
//	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;
//
//	//cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ
//
//	Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);    //��x����ʹ��Sobel()����
//	convertScaleAbs(grad_x, abs_grad_x);   //��Ե���ݶȷ���ֱ��������������Ļ��أ���Ե�Ǻ������������ĳһ������ݶ��Ǵ�ֱ��
//
//
//	Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
//	convertScaleAbs(grad_y, abs_grad_y);
//
//	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, srcImg);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
//																 //imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//������ƽ���˲����ͼ��		
//	return dstimage;
//}
//
