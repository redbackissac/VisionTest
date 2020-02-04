#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "TurnTable.h"
#include "MyMovie.h"
int main(int argc, char *argv[])
{	
	QApplication a(argc, argv);
	MainWindow *w = new MainWindow;	
	w->showFullScreen();
	//w.show();		
	return a.exec();	
}
