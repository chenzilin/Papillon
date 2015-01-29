#include <QLabel>
#include <QHeaderView>
#include <QRadioButton>

#include <taglistwidget.h>

TaglistWidget::TaglistWidget(QWidget *parent)
	:QDockWidget(parent)
{
	setFeatures(QDockWidget::NoDockWidgetFeatures);
}
