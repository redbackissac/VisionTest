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
	GraphicsScene();//���캯��
	void creatRect();//�����¾���    

	GraphicsRectItem *m_RectItem = NULL;//��ǰitem
	typedef QList<GraphicsRectItem*> rectItems;//�������л��Ƶľ��ε�QList
	rectItems m_rectItems;//�洢���еľ��ο���б�
private:
	QPointF m_lastMousePos;  // �������µ�λ��	
	void setCursor(const QCursor & cursor);//���ù��
										   //�������¼�
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
};

#endif // GRAPHICSSCENE_H
