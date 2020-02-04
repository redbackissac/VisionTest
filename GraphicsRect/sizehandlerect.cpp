#include "sizehandlerect.h"
#include <QPainter>

/*
此功能定义为一个类：SizeHandleRect，继承自QGraphicsRectItem
主要内容为对应位置的记录、鼠标位置的判断、坐标移动、是否选择时的隐藏与显示
*/

/*
构造函数
*/
SizeHandleRect::SizeHandleRect(QGraphicsItem *parent, QRectF rect, Direction dir) :
	QGraphicsRectItem(rect, parent),
	m_dir(dir),
	m_state(SelectionHandleOff)
{
	setParentItem(parent);
	hide();//初始状态为隐藏
}

/*
返回当前小矩形的位置
*/
SizeHandleRect::Direction SizeHandleRect::dir() const
{
	return m_dir;
}

/*
用于判断当前鼠标位置是否在小矩形区域中
*/
bool SizeHandleRect::hitTest(const QPointF &point)
{
	QPointF pt = mapFromScene(point);
	return rect().contains(pt);
}

/*
移动到(x,y)处
*/
void SizeHandleRect::move(qreal x, qreal y)
{
	setPos(x, y);
}

/*
用于设置小矩形选中状态时的隐藏和显示
*/
void SizeHandleRect::setState(SelectionHandleState st)
{
	if (st == m_state)
		return;
	switch (st) {
	case SelectionHandleOff:
		hide();
		break;
	case SelectionHandleInactive:
	case SelectionHandleActive:
		show();
		break;
	}
	m_state = st;
}

/*
绘制小矩形
*/
void SizeHandleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QColor c = QColor("limegreen");
	painter->setPen(Qt::NoPen);
	painter->setBrush(QBrush(c));

	painter->drawRect(rect());
}
