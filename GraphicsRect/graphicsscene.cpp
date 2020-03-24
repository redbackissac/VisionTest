#include "graphicsscene.h"
#include <QGraphicsView>
/*
1�����������¼���mousePressEvent��mouseMoveEvent��mouseReleaseEvent
2����������
3�����ͼ��
*/

/*
����¼�
*/
enum SelectMode
{
	none,
	move, //�ƶ�
	size, //�ı��С  
};

SelectMode selectMode = none; //����¼�

SizeHandleRect::Direction nDragHandle = SizeHandleRect::None;//������λ���ھ��ε��ĸ�λ�þ��

															 /*
															 ���캯��
															 */
GraphicsScene::GraphicsScene()
{
	m_rectItems.reserve(0); //��ʼ�����Ƶľ�����Ϊ0
}

/*
�����µľ��ο�
*/
void GraphicsScene::creatRect()
{
	this->clearSelection();//���ѡ��״̬
	m_RectItem = new GraphicsRectItem(QRect(0, 0, 200, 100), NULL);//ʵ����һ�����ο��item
	this->addItem(m_RectItem);//�򳡾������item
	m_RectItem->setSelected(true);//��������ӵ�item״̬Ϊѡ��
	this->update();//����
	m_rectItems.push_back(m_RectItem);//�����»��Ƶľ���
}

/*
���ù��
*/
void GraphicsScene::setCursor(const QCursor &cursor)
{
	QList<QGraphicsView*> views = this->views();
	if (views.count() > 0) {
		QGraphicsView * view = views.first();
		view->setCursor(cursor);
	}
}

/*
�ж����λ�ã�ȷ���������ͣ�����-size���ƶ�-move���޲���-none
�����
*/
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QList<QGraphicsItem *> items = this->selectedItems();//����ѡ�е�item���б�
	GraphicsRectItem *item = nullptr;
	if (items.count() == 1)//��ѡ�е�itemֻ��1��
	{
		item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());//����ת��

		nDragHandle = item->hitTest(event->scenePos());//������λ���ھ��ε��ĸ�λ��
		if (nDragHandle != SizeHandleRect::None)//�����λ���ڿ���С�����ϣ���ѡ��ģʽΪ��������εĴ�С������Ϊ�ƶ�
			selectMode = size;
		else
			selectMode = move;
	}
	if (selectMode == move || selectMode == none) //��ѡ��ģʽΪ�ƶ����޲������ȴ�������¼�
	{
		QGraphicsScene::mousePressEvent(event);
	}
}

/*
����ƶ�
*/
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QList<QGraphicsItem *> items = this->selectedItems();//����ѡ�е�item���б�
	if (items.count() == 1)//��ѡ�е�itemֻ��1��
	{
		GraphicsRectItem *item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());//����ת��
																					  //������С
		if (nDragHandle != SizeHandleRect::None && selectMode == size)
		{
			item->resizeTo(nDragHandle, event->scenePos());

		}
		//�޲���ʱ���ù��
		else if (nDragHandle == SizeHandleRect::None && selectMode == none)
		{
			SizeHandleRect::Direction handle = item->hitTest(event->scenePos());
			if (handle != SizeHandleRect::None) {
				setCursor(item->getCursor(handle));
			}
			else {
				setCursor(Qt::ArrowCursor);
			}
		}
		//�ƶ�
		else if (nDragHandle == SizeHandleRect::None && selectMode == move)
		{
			QGraphicsScene::mouseMoveEvent(event);	//Ĭ�ϵ�����ƶ��¼�����item��λ��		
		}
	}
}

/*
����ͷ�
*/
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::ArrowCursor);
	selectMode = none;
	nDragHandle = SizeHandleRect::None;
	QGraphicsScene::mouseReleaseEvent(event);
}

/*
�����¼������̰���Backspaceִ��ɾ������
*/
void GraphicsScene::keyPressEvent(QKeyEvent *event)
{
	QList<QGraphicsItem *> items = this->selectedItems();//����ѡ�е�item���б�
	if (items.count() == 1)//��ѡ�е�itemΪ1��
	{
		GraphicsRectItem *item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());//����ת��
																					  //ɾ�����ο�
		if (event->key() == Qt::Key_Backspace)
		{
			m_rectItems.removeOne(item);//�Ӵ洢�б����Ƴ�Item
			removeItem(item);//�ӳ������Ƴ�Item

		}
		else {
			QGraphicsScene::keyPressEvent(event);
		}

	}
}
