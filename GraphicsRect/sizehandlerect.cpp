#include "sizehandlerect.h"
#include <QPainter>

/*
�˹��ܶ���Ϊһ���ࣺSizeHandleRect���̳���QGraphicsRectItem
��Ҫ����Ϊ��Ӧλ�õļ�¼�����λ�õ��жϡ������ƶ����Ƿ�ѡ��ʱ����������ʾ
*/

/*
���캯��
*/
SizeHandleRect::SizeHandleRect(QGraphicsItem *parent, QRectF rect, Direction dir) :
	QGraphicsRectItem(rect, parent),
	m_dir(dir),
	m_state(SelectionHandleOff)
{
	setParentItem(parent);
	hide();//��ʼ״̬Ϊ����
}

/*
���ص�ǰС���ε�λ��
*/
SizeHandleRect::Direction SizeHandleRect::dir() const
{
	return m_dir;
}

/*
�����жϵ�ǰ���λ���Ƿ���С����������
*/
bool SizeHandleRect::hitTest(const QPointF &point)
{
	QPointF pt = mapFromScene(point);
	return rect().contains(pt);
}

/*
�ƶ���(x,y)��
*/
void SizeHandleRect::move(qreal x, qreal y)
{
	setPos(x, y);
}

/*
��������С����ѡ��״̬ʱ�����غ���ʾ
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
����С����
*/
void SizeHandleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QColor c = QColor("limegreen");
	painter->setPen(Qt::NoPen);
	painter->setBrush(QBrush(c));

	painter->drawRect(rect());
}
