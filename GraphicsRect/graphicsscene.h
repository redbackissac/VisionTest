#pragma once
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "GraphicsRect/graphicsrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

typedef QList<GraphicsRectItem*> rectItems;//�������л��Ƶľ��ε�QList

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene();//���캯��
	void creatRect();//�����¾���    
	int getSelectedNum();//��ȡ��ѡ��ľ��ο����

	GraphicsRectItem *m_RectItem = NULL;//��ǰitem
	
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
