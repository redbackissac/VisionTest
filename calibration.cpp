#include "calibration.h"

/*����ȽϹ���*/
bool cmp(const Rect& a, const Rect& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}


/*
����궨ֵk
*/
void Calibration::getK()
{
	calImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
	//cvtColor(calImg, calImg, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(ttt).jpg", calImg);//������ƽ���˲����ͼ��
	cout << "channels:" << calImg.channels() << endl;	//��ӡͼ��ͨ����//cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
	createROI(calImg);//����roi						 
	//��������roi����
	for (int i = 0; i != m_rois.size(); ++i)
	{
		/*��ôֱ�Եλ��vecEdgePoint*/
		vector<Point2i> vecEdgePoint;//�ֱ�Ե����	
		getSmallEdgePoint(*m_rois[i], *m_rois[i], vecEdgePoint);//ֻ����ˮƽ����ֱ����ı�Ե��
	

	    /*�����ֱ�Ե���7*7����*/
		int neiborNum;//���������������Ե�������
		Mat AllNeibor;//�ֱ�Ե���7*7����
		neiborNum = vecEdgePoint.size();
	

		


		//AllNeibor = new Mat[neiborNum];		
		//getNeibor(vecEdgePoint, *m_rois[i], AllNeibor);

		/*��ԭͼ����ʾ����ȡ���ı�Ե�����ڲ���*/
		Mat test;
		test = m_rois[i]->clone();
		cvtColor(test, test, COLOR_GRAY2RGB);   //ת��Ϊrgbͼ
		cout << "channels:" << test.channels() << endl;
		Point center_forshow;
		for (int j = 0; j < vecEdgePoint.size(); j++)
		{
				center_forshow.x = cvRound(vecEdgePoint[j].y);
				center_forshow.y = cvRound(vecEdgePoint[j].x);
				circle(test, center_forshow, 1, Scalar(0,0,255), -1);//����(x, y)��
			
		}

		imshow("test",test);
		waitKey(0);
		getNewROI(vecEdgePoint, *m_rois[i], AllNeibor);

		///*��������в�ֵ���Ҽ����Ե����*/
		//Mat* matResizeNeibor;//��ֵ��õ�������
		//matResizeNeibor = new Mat[neiborNum];
		//resizeNeibor(matAllNeibor, matResizeNeibor, vecResizeXY, neiborNum);


		/*�����ؾ�ȷ��Եλ��*/
		vector<Vec4d> vecPara;
		vector<Point2d> subPixelRela;
		m_calEdgePara(AllNeibor, vecPara, subPixelRela);
		//subpixeltest(AllNeibor);


		/*ֱ�����*/
		Vec4f line_para;//��ϳ�ֱ�ߵĲ���
		fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
		int j = INT_MAX;
	}
}






/*
Input:����ͼ��
Output:���ͼ��
EdgePoint:��ȡ�ľ��״ģ���ˮƽ����ֱ�ߵı�Ե��
*/
void Calibration::getSmallEdgePoint(Mat &Input,Mat Output, vector<Point2i> EdgePoint)
{
	///*��ôֱ�Եλ��vecEdgePoint*/
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
	//convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//ͼ����ǿ
	threshold(Edge_XY, Edge_XY, 100, 255, THRESH_BINARY); //��ֵ��
	imshow("Edge_X", Edge_X);
	imshow("Edge_Y", Edge_Y);
	imshow("Edge_XY", Edge_XY);
	waitKey(0);



	vector<vector<Point> > contours_out;
	vector<Vec4i> hierarchy;
	findContours(Edge_XY, contours_out, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	// re-arrange location according to the real position in the original image 
	const size_t size = contours_out.size();
	vector<Rect> num_location;
	for (int i = 0; i < contours_out.size(); i++)
	{
		num_location.push_back(boundingRect(Mat(contours_out[i])));// ת��Ϊ��������
	}
	sort(num_location.begin(), num_location.end(), cmp); // ����������Ϣ

	Point2i  pointTemp;
	for (int i = 0; i < AllEdge.rows; i++)
	{
		for (int j = 0; j < AllEdge.cols; j++)
		{
			if (AllEdge.at<uchar>(i, j) == 255)
			{
				//image.at<>(x,y)������õĵ�x��y�Ƿ�������
				pointTemp.x = i;
				pointTemp.y = j;
				EdgePoint.push_back(pointTemp);
			}
		}
	}
}



