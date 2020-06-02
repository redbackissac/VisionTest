#include "stdboard.h"

void StdBoard::get_stdPoint()
{
	//Img_stdboard = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����	
	//createROI(Img_stdboard, vec_rois);//����roi
	//vec_stdLines.clear();//���ֱ�߲�������

	openImg(srcImg);//��ͼ��
	createROI(srcImg, vec_strrois);//����roi

	//ֻ����ʽ����roi
	//��¼��׼��ı�Ե��
	for (auto &it_roi : vec_strrois)
	{	
		///*ֱ����ȡ�����ر�Ե�����ڶԱ�*/
		//vector<Vec4d> vecPara_1;
		//vector<Point2d> VecSubPixelEdgePoint_1;
		//getSubPixEdge(it_roi.roi, vecPara_1, VecSubPixelEdgePoint_1);



		/*��ôֱ�Եλ��vecEdgePoint*/
		vector<Point2i> vecEdgePoint;//�ֱ�Ե����		
		getRoughEdge_All(it_roi.roi, vecEdgePoint);//��ȡ���Ա�Ե����

		

		/*�����ֱ�Ե�����չ7*7��ROI*/
		int neiborNum;//���������������Ե�������
		Mat AllNeibor;//�ֱ�Ե���7*7����		

		//����Ҫ���࣡������
		Point2d CornerPoint;//roi���Ͻ�����
		getNeiborROI(it_roi.linetype, vecEdgePoint, it_roi.roi, AllNeibor, CornerPoint);

		/*��ROI�е������ؾ�ȷ��Եλ��*/
		vector<Vec4d> vecPara;
		vector<Point2d> VecSubPixelEdgePoint;
		//getSubPixEdge(AllNeibor, vecPara, VecSubPixelEdgePoint);
		getSubPixEdge(AllNeibor, vecPara, it_roi.VecSubPixelEdgePoint);
		//ת��Ϊ�ڴ�ROI�е�����
		if (it_roi.linetype == HORIZONTAL)
			for (auto &it_subPixelRela : it_roi.VecSubPixelEdgePoint)
			{
				it_subPixelRela.x += CornerPoint.x;
				it_subPixelRela.y += CornerPoint.y - 3;
			}
		else
			for (auto &it_subPixelRela : it_roi.VecSubPixelEdgePoint)
			{
				it_subPixelRela.x += CornerPoint.x - 3;
				it_subPixelRela.y += CornerPoint.y;
			}
		
	}
}
