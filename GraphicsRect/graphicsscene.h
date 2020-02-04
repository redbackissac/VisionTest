#pragma once
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "GraphicsRect/graphicsrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene();//构造函数
	void creatRect();//创建新矩形    

	GraphicsRectItem *m_RectItem = NULL;//当前item
	typedef QList<GraphicsRectItem*> rectItems;//存贮所有绘制的矩形的QList
	rectItems m_rectItems;//存储所有的矩形框的列表
private:
	QPointF m_lastMousePos;  // 鼠标最后按下的位置	
	void setCursor(const QCursor & cursor);//设置光标
										   //鼠标键盘事件
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
};

#endif // GRAPHICSSCENE_H
