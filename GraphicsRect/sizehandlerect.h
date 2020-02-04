#pragma once
#ifndef SIZEHANDLERECT_H
#define SIZEHANDLERECT_H

#include <QGraphicsRectItem>

enum SelectionHandleState { SelectionHandleOff, SelectionHandleInactive, SelectionHandleActive };//选中状态

class SizeHandleRect :public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	enum Direction { LeftTop, Top, RightTop, Right, RightBottom, Bottom, LeftBottom, Left, Center, None }; //Direction为一个枚举类型，用于表示小矩形所代表的位置，边缘特殊点共8个。
	SizeHandleRect(QGraphicsItem* parent, QRectF rect, Direction dir);//构造函数
	Direction dir() const;//返回小矩形方向
	bool hitTest(const QPointF & point);//用于判断当前鼠标位置是否在小矩形区域中
	void move(qreal x, qreal y);//移动
	void setState(SelectionHandleState st);//用于设置小矩形选中状态时的隐藏和显示
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//绘制事件
private:
	const Direction m_dir;
	SelectionHandleState m_state;//当前选中状态
};

#endif // SIZEHANDLERECT_H
