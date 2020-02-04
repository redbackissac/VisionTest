#include <QWheelEvent>
#include <QKeyEvent>
#include "interactive_view.h"
/*
����ʽ���棬��ʵ�ֹ������ţ���סshift�����ƶ�����סctrl�����ƶ�
*/
#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()


//���캯��
InteractiveView::InteractiveView(QWidget *parent)
	: QGraphicsView(parent),
	m_translateButton(Qt::LeftButton),
	m_scale(1.0),
	m_zoomDelta(0.1),
	m_translateSpeed(1.0),
	m_bMouseTranslate(false)
{
	// ȥ��������
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCursor(Qt::CrossCursor);
	setRenderHint(QPainter::Antialiasing);
	setStyleSheet("padding: 0px; border: 0px;");
	setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);	
	centerOn(0, 0);
	

}

// ƽ���ٶ�
void InteractiveView::setTranslateSpeed(qreal speed)
{
	// �����ٶȷ�Χ
	Q_ASSERT_X(speed >= 0.0 && speed <= 2.0,
		"InteractiveView::setTranslateSpeed", "Speed should be in range [0.0, 2.0].");
	m_translateSpeed = speed;
}

qreal InteractiveView::translateSpeed() const
{
	return m_translateSpeed;
}

// ���ŵ�����
void InteractiveView::setZoomDelta(qreal delta)
{
	// ����������Χ
	Q_ASSERT_X(delta >= 0.0 && delta <= 1.0,
		"InteractiveView::setZoomDelta", "Delta should be in range [0.0, 1.0].");
	m_zoomDelta = delta;
}

qreal InteractiveView::zoomDelta() const
{
	return m_zoomDelta;
}


// �Ŵ�/��С
void InteractiveView::wheelEvent(QWheelEvent *event)
{
	// ���ֵĹ�����
	QPoint scrollAmount = event->angleDelta();

	//��סshift�����ƶ�
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
		// ��ֵ��ʾ����Զ��ʹ���ߣ��Ŵ󣩣���ֵ��ʾ����ʹ���ߣ���С��
		scrollAmount.y() > 0 ? zoomIn() : zoomOut();
	}


	


}

// �Ŵ�
void InteractiveView::zoomIn()
{
	zoom(1 + m_zoomDelta);
}

// ��С
void InteractiveView::zoomOut()
{
	zoom(1 - m_zoomDelta);
}

// ���� - scaleFactor�����ŵı�������
void InteractiveView::zoom(float scaleFactor)
{
	// ��ֹ��С�����
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
	m_scale *= scaleFactor;
}

// ƽ��
void InteractiveView::translate(QPointF delta)
{
	// ���ݵ�ǰ zoom ����ƽ����
	//delta *= m_scale;
	delta *= m_translateSpeed;

	// view ��������µĵ���Ϊê������λ scene
	//setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	QPoint newCenter(VIEW_WIDTH / 2 - delta.x(), VIEW_HEIGHT / 2 - delta.y());
	centerOn(mapToScene(newCenter));

	// scene �� view �����ĵ���Ϊê��
	setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}
