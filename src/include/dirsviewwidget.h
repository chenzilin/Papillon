#ifndef DIRSVIEWWIDGET_H
#define DIRSVIEWWIDGET_H

#include <QLabel>
#include <QTreeView>
#include <QDirModel>
#include <QModelIndex>
#include <QDockWidget>
#include <QSortFilterProxyModel>

class DirsViewWidget : public QDockWidget
{
	Q_OBJECT

public:
	DirsViewWidget(QWidget *parent = 0);
	~DirsViewWidget(){}

	void setViewProfiles(QString dirPath);

signals:
	void openFileByPath(QString filePath);

private slots:
	void doubleClicked(QModelIndex index);

private:

	QLabel *m_currentDirPath;
	QDirModel *m_profilesModel;
	QTreeView *m_treeViewProfiles;
};

#endif
