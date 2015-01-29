#include <QFileInfo>
#include <QMessageBox>
#include <QHeaderView>
#include <QVBoxLayout>

#include <dirsviewwidget.h>

DirsViewWidget::DirsViewWidget(QWidget *parent)
	:QDockWidget(parent)
{
	m_currentDirPath = new QLabel(this);

	m_profilesModel = new QDirModel(this);
	m_profilesModel->setSorting(QDir::Name | QDir::DirsFirst);
	m_treeViewProfiles = new QTreeView(this);
	m_treeViewProfiles->setModel(m_profilesModel);
	m_treeViewProfiles->setAnimated(false);
	m_treeViewProfiles->setIndentation(20);
	m_treeViewProfiles->setSortingEnabled(true);
	m_treeViewProfiles->hideColumn(1);
	m_treeViewProfiles->hideColumn(2);
	m_treeViewProfiles->hideColumn(3);
	m_treeViewProfiles->setHeaderHidden(true);

	setMaximumWidth(300);
	setWidget(m_treeViewProfiles);
	setTitleBarWidget(m_currentDirPath);
	setFeatures(QDockWidget::NoDockWidgetFeatures);

	QObject::connect(m_treeViewProfiles, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClicked(QModelIndex)));
}

void DirsViewWidget::setViewProfiles(QString dirPath)
{
	m_treeViewProfiles->setRootIndex(m_profilesModel->index(dirPath));

	if (dirPath.length() >= 40) {
		dirPath = dirPath.right(35);
		dirPath.push_front("...");
	}
	m_currentDirPath->setText(dirPath);
}

void DirsViewWidget::doubleClicked(QModelIndex index)
{
	QFileInfo fileInfo(m_profilesModel->filePath(index));

	if(fileInfo.isFile())
		emit openFileByPath(m_profilesModel->filePath(index));
}
