#include <QWheelEvent>
#include <QKeyEvent>
#include "interactive_view.h"
/*
交互式界面，可实现滚轮缩放，按住shift上下移动，按住ctrl左右移动
*/
#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()


//构造函数
InteractiveView::InteractiveView(QWidget *parent)
	: QGraphicsView(parent),
	m_translateButton(Qt::LeftButton),
	m_scale(1.0),
	m_zoomDelta(0.1),
	m_translateSpeed(1.0),
	m_bMouseTranslate(false)
{
	// 去掉滚动条
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCursor(Qt::CrossCursor);
	setRenderHint(QPainter::Antialiasing);
	setStyleSheet("padding: 0px; border: 0px;");
	setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);	
	centerOn(0, 0);
	

}

// 平移速度
void InteractiveView::setTranslateSpeed(qreal speed)
{
	// 建议速度范围
	Q_ASSERT_X(speed >= 0.0 && speed <= 2.0,
		"InteractiveView::setTranslateSpeed", "Speed should be in range [0.0, 2.0].");
	m_translateSpeed = speed;
}

qreal InteractiveView::translateSpeed() const
{
	return m_translateSpeed;
}

// 缩放的增量
void InteractiveView::setZoomDelta(qreal delta)
{
	// 建议增量范围
	Q_ASSERT_X(delta >= 0.0 && delta <= 1.0,
		"InteractiveView::setZoomDelta", "Delta should be in range [0.0, 1.0].");
	m_zoomDelta = delta;
}

qreal InteractiveView::zoomDelta() const
{
	return m_zoomDelta;
}


// 放大/缩小
void InteractiveView::wheelEvent(QWheelEvent *event)
{
	// 滚轮的滚动量
	QPoint scrollAmount = event->angleDelta();

	//按住shift上下移动
	if (event->modifiers() == Qt::ShiftModifier)
	{
		scrollAmount.y() > 0 ? translate(QPointF(0, 8)) : translate(QPointF(0, -8));
		
	}
	else if (event->modifiers() == Qt::ControlModifier)
	{
		scrollAmount.y() > 0 ? translate(QPointF(-8, 0)) : translate(QPointF(8, 0));
	}
	else
	{
		// 正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
		scrollAmount.y() > 0 ? zoomIn() : zoomOut();
	}


	


}

// 放大
void InteractiveView::zoomIn()
{
	zoom(1 + m_zoomDelta);
}

// 缩小
void InteractiveView::zoomOut()
{
	zoom(1 - m_zoomDelta);
}

// 缩放 - scaleFactor：缩放的比例因子
void InteractiveView::zoom(float scaleFactor)
{
	// 防止过小或过大
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
	m_scale *= scaleFactor;
}

// 平移
void InteractiveView::translate(QPointF delta)
{
	// 根据当前 zoom 缩放平移数
	//delta *= m_scale;
	delta *= m_translateSpeed;

	// view 根据鼠标下的点作为锚点来定位 scene
	//setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	QPoint newCenter(VIEW_WIDTH / 2 - delta.x(), VIEW_HEIGHT / 2 - delta.y());
	centerOn(mapToScene(newCenter));

	// scene 在 view 的中心点作为锚点
	setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}
