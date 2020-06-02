#include "stdboard.h"

void StdBoard::get_stdPoint()
{
	//Img_stdboard = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数	
	//createROI(Img_stdboard, vec_rois);//创建roi
	//vec_stdLines.clear();//清空直线参数向量

	openImg(srcImg);//打开图像
	createROI(srcImg, vec_strrois);//创建roi

	//只读方式遍历roi
	//记录标准板的边缘点
	for (auto &it_roi : vec_strrois)
	{	
		///*直接提取亚像素边缘，用于对比*/
		//vector<Vec4d> vecPara_1;
		//vector<Point2d> VecSubPixelEdgePoint_1;
		//getSubPixEdge(it_roi.roi, vecPara_1, VecSubPixelEdgePoint_1);



		/*获得粗边缘位置vecEdgePoint*/
		vector<Point2i> vecEdgePoint;//粗边缘坐标		
		getRoughEdge_All(it_roi.roi, vecEdgePoint);//提取粗略边缘坐标

		

		/*创建粗边缘点的扩展7*7子ROI*/
		int neiborNum;//邻域的数量，即边缘点的数量
		Mat AllNeibor;//粗边缘点的7*7邻域		

		//这里要分类！！！！
		Point2d CornerPoint;//roi左上角坐标
		getNeiborROI(it_roi.linetype, vecEdgePoint, it_roi.roi, AllNeibor, CornerPoint);

		/*子ROI中的亚像素精确边缘位置*/
		vector<Vec4d> vecPara;
		vector<Point2d> VecSubPixelEdgePoint;
		//getSubPixEdge(AllNeibor, vecPara, VecSubPixelEdgePoint);
		getSubPixEdge(AllNeibor, vecPara, it_roi.VecSubPixelEdgePoint);
		//转换为在大ROI中的坐标
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
