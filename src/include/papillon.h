#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <taglistdockwidget.h>
#include <filedirsviewdockwidget.h>
#include <codeeditorsstackedwidget.h>
#include <openedfilesviewdockwidget.h>
#include <applicationoutputdockwidget.h>

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

	void actionEnglish_setEnglish();
	void actionChinese_setChinese();

	void actionHelp_help();
	void actionAbout_about();

	void actionQuit_quit();

private:

	//QString m_currentFile;

	TaglistDockWidget *m_taglistDockWidget;
	FileDirsViewDockWidget *m_fileDirsViewDockWidget;
	CodeEditorsStackedWidget *m_codeEditorsStackedWidget;
	OpenedFilesViewDockWidget *m_openedFilesViewDockWidget;
	ApplicationOutputDockWidget *m_applicationOutputDockWidget;

	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
