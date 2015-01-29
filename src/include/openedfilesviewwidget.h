#ifndef OPENEDFILESVIEWWIDGET_H
#define OPENEDFILESVIEWWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QTableWidget>

class OpenedFilesViewWidget : public QDockWidget
{
	Q_OBJECT

public:
	OpenedFilesViewWidget(QWidget *parent = 0);
	~OpenedFilesViewWidget(){}

signals:
	void displayFileByFilePath(QString filePath);
	void removeFileByFilePath(QString filePath);

private slots:
	void insertRow(QString filePath);
	void removeRow(int row, int column);

private:
	QTableWidget *m_openedFilesViewWidget;
};

#endif
