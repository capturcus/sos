#ifndef UITHREAD_H
#define UITHREAD_H

#include <QThread>

class UIThread : public QThread
{
	Q_OBJECT

public:
	UIThread(QObject *parent);
	~UIThread();

	void run();
private:
	
};

#endif // UITHREAD_H
