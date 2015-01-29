#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QDockWidget>


class ResultWidget : public QDockWidget
{
	Q_OBJECT

public:
	ResultWidget(QWidget *parent = 0);
	~ResultWidget(){}
};

#endif
