#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <resultwidget.h>
#include <taglistwidget.h>
#include <dirsviewwidget.h>
#include <openedfilesviewwidget.h>
#include <codeeditorwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:

	void actionNew_newFile();
	void actionOpen_openFile();
	void actionSave_saveFile();
	void actionSaveAs_saveAsFile();

	void actionOpen_openProfiles();

	void actionHelp_help();
	void actionAbout_about();

	void actionQuit_quit();

private:

	//QString m_currentFile;

	TaglistWidget *m_taglistWidget;
	DirsViewWidget *m_dirsViewWidget;
	CodeEditorWidget *m_codeEditorWidget;
	OpenedFilesViewWidget *m_openedFilesViewWidget;
	ResultWidget *m_resultWidget;

	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
