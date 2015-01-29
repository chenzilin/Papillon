#include <QLabel>
#include <QHeaderView>
#include <QRadioButton>

#include <openedfilesviewwidget.h>

OpenedFilesViewWidget::OpenedFilesViewWidget(QWidget *parent)
	:QDockWidget(parent)
{
	m_openedFilesViewWidget = new QTableWidget(this);
	m_openedFilesViewWidget->setRowCount(0);
	m_openedFilesViewWidget->setColumnCount(2);
	m_openedFilesViewWidget->setShowGrid(true);
	m_openedFilesViewWidget->setFocusPolicy(Qt::NoFocus);
	m_openedFilesViewWidget->verticalHeader()->setVisible(false);
	m_openedFilesViewWidget->horizontalHeader()->setVisible(false);
	m_openedFilesViewWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	m_openedFilesViewWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

	setWidget(m_openedFilesViewWidget);
	setFeatures(QDockWidget::NoDockWidgetFeatures);

	QObject::connect(m_openedFilesViewWidget, SIGNAL(cellClicked(int,int)), this, SLOT(removeRow(int,int)));
}

void OpenedFilesViewWidget::insertRow(QString filePath)
{
	m_openedFilesViewWidget->insertRow(0);
	m_openedFilesViewWidget->setCellWidget(0, 0, new QLabel(filePath));
	m_openedFilesViewWidget->setCellWidget(0, 1, new QLabel("   x"));
	m_openedFilesViewWidget->resizeColumnsToContents();
}

void OpenedFilesViewWidget::removeRow(int row, int column)
{
	if (1 == column) {
		emit removeFileByFilePath(dynamic_cast<QLabel *>(m_openedFilesViewWidget->cellWidget(row, column))->text());
		m_openedFilesViewWidget->removeRow(row);
	}
	else {
		emit displayFileByFilePath(dynamic_cast<QLabel *>(m_openedFilesViewWidget->cellWidget(row, column))->text());
	}
}
