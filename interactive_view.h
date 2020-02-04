#pragma once
#ifndef INTERACTIVE_VIEW_H
#define INTERACTIVE_VIEW_H

#include <QGraphicsView>

class QWheelEvent;
class QKeyEvent;

class InteractiveView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit InteractiveView(QWidget *parent = 0);

	// ƽ���ٶ�
	void setTranslateSpeed(qreal speed);
	qreal translateSpeed() const;

	// ���ŵ�����
	void setZoomDelta(qreal delta);
	qreal zoomDelta() const;

protected:	
	// �Ŵ�/��С
	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

	public Q_SLOTS:
	void zoomIn();  // �Ŵ�
	void zoomOut();  // ��С
	void zoom(float scaleFactor); // ���� - scaleFactor�����ŵı�������
	void translate(QPointF delta);  // ƽ��

private:
	Qt::MouseButton m_translateButton;  // ƽ�ư�ť
	qreal m_translateSpeed;  // ƽ���ٶ�
	qreal m_zoomDelta;  // ���ŵ�����
	bool m_bMouseTranslate;  // ƽ�Ʊ�ʶ
	QPoint m_lastMousePos;  // �������µ�λ��
	qreal m_scale;  // ����ֵ
};

#endif // INTERACTIVE_VIEW_H
