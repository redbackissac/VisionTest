#include "graphicsscene.h"
#include <QGraphicsView>
/*
1、完成鼠标三事件，mousePressEvent、mouseMoveEvent、mouseReleaseEvent
2、创建矩形
3、添加图像
*/

/*
鼠标事件
*/
enum SelectMode
{
	none,
	move, //移动
	size, //改变大小  
};

SelectMode selectMode = none; //鼠标事件

SizeHandleRect::Direction nDragHandle = SizeHandleRect::None;//检测鼠标位置在矩形的哪个位置句柄

															 /*
															 构造函数
															 */
GraphicsScene::GraphicsScene()
{
	m_rectItems.reserve(0); //初始化绘制的矩形数为0
}

/*
创建新的矩形框
*/
void GraphicsScene::creatRect()
{
	this->clearSelection();//清空选择状态
	m_RectItem = new GraphicsRectItem(QRect(0, 0, 200, 100), NULL);//实例化一个矩形框的item
	this->addItem(m_RectItem);//向场景中添加item
	m_RectItem->setSelected(true);//设置新添加的item状态为选中
	this->update();//更新
	m_rectItems.push_back(m_RectItem);//存贮新绘制的矩形
}

/*
设置光标
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
判断鼠标位置，确定操作类型：缩放-size，移动-move，无操作-none
鼠标点击
*/
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QList<QGraphicsItem *> items = this->selectedItems();//所有选中的item的列表
	GraphicsRectItem *item = nullptr;
	if (items.count() == 1)//若选中的item只有1个
	{
		item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());//类型转换

		nDragHandle = item->hitTest(event->scenePos());//检测鼠标位置在矩形的哪个位置
		if (nDragHandle != SizeHandleRect::None)//若鼠标位置在控制小矩形上，则选择模式为调整大矩形的大小，否则为移动
			selectMode = size;
		else
			selectMode = move;
	}
	if (selectMode == move || selectMode == none) //若选择模式为移动或无操作，等待鼠标点击事件
	{
		QGraphicsScene::mousePressEvent(event);
	}
}

/*
鼠标移动
*/
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QList<QGraphicsItem *> items = this->selectedItems();//所有选中的item的列表
	if (items.count() == 1)//若选中的item只有1个
	{
		GraphicsRectItem *item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());//类型转换
																					  //调整大小
		if (nDragHandle != SizeHandleRect::None && selectMode == size)
		{
			item->resizeTo(nDragHandle, event->scenePos());

		}
		//无操作时设置光标
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
		//移动
		else if (nDragHandle == SizeHandleRect::None && selectMode == move)
		{
			QGraphicsScene::mouseMoveEvent(event);	//默认的鼠标移动事件重设item的位置		
		}
	}
}

/*
鼠标释放
*/
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::ArrowCursor);
	selectMode = none;
	nDragHandle = SizeHandleRect::None;
	QGraphicsScene::mouseReleaseEvent(event);
}

/*
键盘事件，键盘按下Backspace执行删除操作
*/
void GraphicsScene::keyPressEvent(QKeyEvent *event)
{
	QList<QGraphicsItem *> items = this->selectedItems();//所有选中的item的列表
	if (items.count() == 1)//若选中的item为1个
	{
		GraphicsRectItem *item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());//类型转换
																					  //删除矩形框
		if (event->key() == Qt::Key_Backspace)
		{
			m_rectItems.removeOne(item);//从存储列表中移除Item
			removeItem(item);//从场景中移除Item

		}
		else {
			QGraphicsScene::keyPressEvent(event);
		}

	}
}
