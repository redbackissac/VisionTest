#pragma once
#pragma execution_character_set("utf-8")
#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include <QGraphicsItem>
#include "sizehandlerect.h"

class GraphicsRectItem :public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
public:
	GraphicsRectItem(const QRect & rect, QGraphicsItem * parent);

	QRectF boundingRect() const;
	virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point);
	void move(const QPointF & point);
	virtual Qt::CursorShape getCursor(SizeHandleRect::Direction dir);
	SizeHandleRect::Direction  hitTest(const QPointF & point) const;
	virtual QRectF  rect() const;
	virtual void updateGeometry();
	QRectF m_rect;

private:

	typedef QVector<SizeHandleRect*> Handles;//存贮控制小矩形的QVector
	Handles m_handles;
	int selection_handle_size = 4;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void setState(SelectionHandleState st);
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // GRAPHICSRECTITEM_H
