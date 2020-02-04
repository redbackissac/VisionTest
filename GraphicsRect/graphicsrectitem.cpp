#include "graphicsrectitem.h"
#include <QPen>
#include <QPainter>
#pragma execution_character_set("utf-8")
/*
实现所要绘制的矩形类
1、在构造函数中作为父类实例化8个小矩形SizeHandleRect，并将其放在对应的位置。
2、当大小变化时，重新绘制。
3、根据不同位置设置鼠标的形状。
4、管理鼠标位置引起的标志变化。
5、选择项目变化时的事件处理。
*/

/*
在构造函数中作为父类实例化8个小矩形SizeHandleRect，将其放在对应的位置，并设置一些标志属性
*/
GraphicsRectItem::GraphicsRectItem(const QRect &rect, QGraphicsItem *parent) :
	QGraphicsItem(parent)
{
	m_rect = rect;
	m_handles.reserve(SizeHandleRect::None);
	//依次初始化各个小矩形
	for (int i = SizeHandleRect::LeftTop; i <= SizeHandleRect::Left; ++i) {
		SizeHandleRect *shr = new SizeHandleRect(this, QRectF(0, 0, 4, 4), static_cast<SizeHandleRect::Direction>(i));
		m_handles.push_back(shr);
	}
	updateGeometry();
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	this->setAcceptHoverEvents(true);
}
/*
调整大小
*/
void GraphicsRectItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{
	QPointF local = mapFromScene(point);

	QRect delta = m_rect.toRect();
	switch (dir) {
	case SizeHandleRect::LeftTop:
		delta.setTopLeft(local.toPoint());
		break;

	case SizeHandleRect::Top:
		delta.setTop(local.y());
		break;

	case SizeHandleRect::RightTop:
		delta.setTopRight(local.toPoint());
		break;

	case SizeHandleRect::Left:
		delta.setLeft(local.x());
		break;
	case SizeHandleRect::Right:
		delta.setRight(local.x());
		break;

	case SizeHandleRect::LeftBottom:
		delta.setBottomLeft(local.toPoint());
		break;

	case SizeHandleRect::Bottom:
		delta.setBottom(local.y());
		break;

	case SizeHandleRect::RightBottom:
		delta.setBottomRight(local.toPoint());
		break;

	default:
		break;
	}
	prepareGeometryChange();
	m_rect = delta;
	updateGeometry();
}

void GraphicsRectItem::move(const QPointF &point)
{
	QPointF local = mapFromScene(point);

	QRectF delta = QRectF(local, m_rect.size());

	prepareGeometryChange();
	m_rect = delta;
	updateGeometry();
}

/*
获取光标
*/
Qt::CursorShape GraphicsRectItem::getCursor(SizeHandleRect::Direction dir)
{
	switch (dir) {
	case SizeHandleRect::Right:
		return Qt::SizeHorCursor;
	case SizeHandleRect::RightTop:
		return Qt::SizeBDiagCursor;
	case SizeHandleRect::RightBottom:
		return Qt::SizeFDiagCursor;
	case SizeHandleRect::LeftBottom:
		return Qt::SizeBDiagCursor;
	case SizeHandleRect::Bottom:
		return Qt::SizeVerCursor;
	case SizeHandleRect::LeftTop:
		return Qt::SizeFDiagCursor;
	case SizeHandleRect::Left:
		return Qt::SizeHorCursor;
	case SizeHandleRect::Top:
		return Qt::SizeVerCursor;
	default:
		break;
	}
	return Qt::ArrowCursor;
}

/*
用于判断当前鼠标位置在矩形框中的位置
*/
SizeHandleRect::Direction GraphicsRectItem::hitTest(const QPointF &point) const
{
	const Handles::const_iterator hend = m_handles.end();
	for (Handles::const_iterator it = m_handles.begin(); it != hend; ++it)
	{
		if ((*it)->hitTest(point)) {
			return (*it)->dir();
		}
	}
	return SizeHandleRect::None;
}

/*
画大矩形
*/
void GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = painter->pen();
	pen.setWidth(1);
	pen.setColor(QColor(0, 0, 150));
	painter->setPen(pen);
	painter->drawRect(rect());
}

/*
更新形状
*/
void GraphicsRectItem::updateGeometry()
{
	const QRectF &rect = this->boundingRect();

	//遍历控制小矩形，并更新其位置
	const Handles::iterator hend = m_handles.end();
	for (Handles::iterator it = m_handles.begin(); it != hend; ++it) {
		SizeHandleRect *hndl = *it;
		switch (hndl->dir()) {
		case SizeHandleRect::LeftTop:
			hndl->move(rect.x() - selection_handle_size / 2, rect.y() - selection_handle_size / 2);
			break;
		case SizeHandleRect::Top:
			hndl->move(rect.x() + rect.width() / 2 - selection_handle_size / 2, rect.y() - selection_handle_size / 2);
			break;
		case SizeHandleRect::RightTop:
			hndl->move(rect.x() + rect.width() - selection_handle_size / 2, rect.y() - selection_handle_size / 2);
			break;
		case SizeHandleRect::Right:
			hndl->move(rect.x() + rect.width() - selection_handle_size / 2, rect.y() + rect.height() / 2 - selection_handle_size / 2);
			break;
		case SizeHandleRect::RightBottom:
			hndl->move(rect.x() + rect.width() - selection_handle_size / 2, rect.y() + rect.height() - selection_handle_size / 2);
			break;
		case SizeHandleRect::Bottom:
			hndl->move(rect.x() + rect.width() / 2 - selection_handle_size / 2, rect.y() + rect.height() - selection_handle_size / 2);
			break;
		case SizeHandleRect::LeftBottom:
			hndl->move(rect.x() - selection_handle_size / 2, rect.y() + rect.height() - selection_handle_size / 2);
			break;
		case SizeHandleRect::Left:
			hndl->move(rect.x() - selection_handle_size / 2, rect.y() + rect.height() / 2 - selection_handle_size / 2);
			break;
		case SizeHandleRect::Center:
			hndl->move(rect.center().x() - selection_handle_size / 2, rect.center().y() - selection_handle_size / 2);
			break;
		default:
			break;
		}
	}
}

QRectF GraphicsRectItem::rect() const
{
	return QRectF(QPointF(m_rect.left(), m_rect.top()),
		QPointF(m_rect.right(), m_rect.bottom()));
}

void GraphicsRectItem::setState(SelectionHandleState st)
{
	const Handles::iterator hend = m_handles.end();
	for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
		(*it)->setState(st);
}

QVariant GraphicsRectItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemSelectedHasChanged) {

		setState(value.toBool() ? SelectionHandleActive : SelectionHandleOff);
	}
	else if (change == QGraphicsItem::ItemRotationHasChanged) {

	}
	else if (change == QGraphicsItem::ItemTransformOriginPointHasChanged) {

	}
	return value;
}

QRectF GraphicsRectItem::boundingRect() const
{
	return rect();
}
