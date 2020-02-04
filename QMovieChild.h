#pragma once
#ifndef QMOVIECHILD_H
#define QMOVIECHILD_H

#include <QMovie>

class QMovieChild : public QMovie
{
	Q_OBJECT
public:
	QMovieChild(QObject * parent = 0) :QMovie(parent) {
		connect(this, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
	}
	~QMovieChild();

signals:
	void newSignal();
	private slots:
	void onFrameChanged(int frameNumber) {
		if (frameNumber == frameCount()-1) {
			emit newSignal();			
		}
	}

};

#endif // QMOVIECHILD_H