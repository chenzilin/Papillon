#ifndef TAGLISTWIDGET_H
#define TAGLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QTableWidget>

class TaglistWidget : public QDockWidget
{
	Q_OBJECT

public:
	TaglistWidget(QWidget *parent = 0);
	~TaglistWidget(){}
};

#endif
