#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QDockWidget>

#include <helpdlg.h>
#include <aboutdlg.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_taglistWidget = new TaglistWidget;
	m_dirsViewWidget = new DirsViewWidget;
	m_codeEditorWidget = new CodeEditorWidget;
	m_openedFilesViewWidget = new OpenedFilesViewWidget;
	m_resultWidget = new ResultWidget;

	setCentralWidget(m_codeEditorWidget);
	addDockWidget(Qt::RightDockWidgetArea, m_taglistWidget);
	addDockWidget(Qt::LeftDockWidgetArea, m_dirsViewWidget);
	addDockWidget(Qt::LeftDockWidgetArea, m_openedFilesViewWidget);
	addDockWidget(Qt::BottomDockWidgetArea, m_resultWidget);

	QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(actionOpen_openFile()));
	QObject::connect(ui->actionOpen_Profiles, SIGNAL(triggered()), this, SLOT(actionOpen_openProfiles()));
	QObject::connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(actionNew_newFile()));
	QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(actionSave_saveFile()));
	QObject::connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(actionSaveAs_saveAsFile()));
	QObject::connect(ui->actionQuit, SIGNAL(triggered()),this ,SLOT(actionQuit_quit()));

#if 0
	QObject::connect(ui->actionCopy, SIGNAL(triggered()), m_codeEditor, SLOT(copy()));
	QObject::connect(ui->actionCut, SIGNAL(triggered()), m_codeEditor, SLOT(cut()));
	QObject::connect(ui->actionPaste, SIGNAL(triggered()), m_codeEditor, SLOT(paste()));
	QObject::connect(ui->actionUndo, SIGNAL(triggered()), m_codeEditor, SLOT(undo()));
	QObject::connect(ui->actionRedo, SIGNAL(triggered()), m_codeEditor, SLOT(redo()));
#endif

	QObject::connect(ui->actionHelp, SIGNAL(triggered()),this, SLOT(actionHelp_help()));
	QObject::connect(ui->actionAbout, SIGNAL(triggered()),this ,SLOT(actionAbout_about()));

	QObject::connect(m_dirsViewWidget, SIGNAL(openFileByPath(QString)), m_openedFilesViewWidget, SLOT(insertRow(QString)));
	QObject::connect(m_dirsViewWidget, SIGNAL(openFileByPath(QString)), m_codeEditorWidget, SLOT(addCodeEditor(QString)));
	QObject::connect(m_openedFilesViewWidget, SIGNAL(displayFileByFilePath(QString)), m_codeEditorWidget, SLOT(setCurrentCodeEditorWidget(QString)));
	QObject::connect(m_openedFilesViewWidget, SIGNAL(removeFileByFilePath(QString)), m_codeEditorWidget, SLOT(removeCodeEditorWidget(QString)));

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::actionOpen_openProfiles()
{
	QFileDialog dlg(this, tr("Open Profiles..."));

	dlg.setFileMode(QFileDialog::Directory);
	dlg.setOption(QFileDialog::ShowDirsOnly);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	dlg.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);

	if (QFileDialog::Accepted == dlg.exec()) {
		m_dirsViewWidget->setViewProfiles(dlg.selectedFiles()[0]);
	}
}

void MainWindow::actionOpen_openFile()
{
#if 0
	if("" != m_currentFile)
	{
		if(QMessageBox::Yes == QMessageBox::information(0, tr("Tips")
														, tr("Are you wang to save the current file ?"), QMessageBox::No,  QMessageBox::Yes))
		{
			actionSave_saveFile();

			m_currentFile = "";
			m_codeEditor->clear();
		}
	}

	QFileDialog dlg(this,tr("Open file..."));
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	if(QFileDialog::Accepted == dlg.exec())
	{
		m_currentFile = dlg.selectedFiles()[0];

		QFile fp(m_currentFile);
		if(fp.open(QFile::ReadOnly))
		{
			QTextStream stm(&fp);
			m_codeEditor->clear();
			while(!stm.atEnd())
			{
				m_codeEditor->appendPlainText(stm.readLine(120));
			}
			fp.close();

			setWindowTitle(QString(QString("Papillon ") + m_currentFile));
		}
		else
		{
			QMessageBox::warning(0, tr("Warning"), tr("Failed to open file !"), QMessageBox::Yes);
		}
	}
#endif
}

void MainWindow::actionNew_newFile()
{
#if 0
	if("" != m_currentFile)
	{
		if(QMessageBox::Yes == QMessageBox::information(0, tr("Tips")
														, tr("Are you wang to save the current file  ?"), QMessageBox::No,  QMessageBox::Yes))
		{
			actionSave_saveFile();

			m_currentFile = "";
			setWindowTitle(QString(QString("Papillon ") + "untitled"));
			m_codeEditor->clear();
		}
	}

	setWindowTitle(QString(QString("Papillon ") + "untitled"));
#endif
}

void MainWindow::actionSave_saveFile()
{
#if 0
	if("" == m_currentFile)
	{
		actionSaveAs_saveAsFile();
	}
	else
	{
		QFile fp(m_currentFile);
		fp.open(QFile::WriteOnly | QFile::Truncate);
		QTextStream stmf(&fp);

		stmf << m_codeEditor->toPlainText();

		fp.close();
	}
#endif
}

void MainWindow::actionSaveAs_saveAsFile()
{
#if 0

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As..."));

	QFile fp(fileName);
	fp.open(QFile::WriteOnly | QFile::Truncate);
	QTextStream stmf(&fp);

	stmf << m_codeEditor->toPlainText();

	fp.close();

	if("" == m_currentFile)
	{
		m_currentFile = fileName;
		setWindowTitle(QString(QString("Papillon ") + m_currentFile));
	}
#endif
}


void MainWindow::actionQuit_quit()
{
#if 0
	QString curString = m_codeEditor->toPlainText();

	if("" != curString)
	{
		if(QMessageBox::Yes == QMessageBox::information(0, tr("Tips")
														, tr("Are you wang to save the current file ?"), QMessageBox::No,  QMessageBox::Yes))
		{
			if("" != m_currentFile)
			{
				QFile fp(m_currentFile);
				fp.open(QFile::WriteOnly | QFile::Truncate);
				QTextStream stmf(&fp);

				stmf << m_codeEditor->toPlainText();

				fp.close();
			}
			else
			{
				actionSaveAs_saveAsFile();
			}
		}

		m_currentFile = "";
		m_codeEditor->clear();
	}
#endif
	MainWindow::close();
}

void MainWindow::actionHelp_help()
{
	HelpDlg hDlg;
	hDlg.exec();
}

void MainWindow::actionAbout_about()
{
	AboutDlg aDlg;
	aDlg.exec();
}
