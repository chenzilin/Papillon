#include <mainwindow.h>
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QTranslator>
#include <QDockWidget>

#include <helpdlg.h>
#include <aboutdlg.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_taglistDockWidget = new TaglistDockWidget;
	m_fileDirsViewDockWidget = new FileDirsViewDockWidget;
	m_codeEditorsStackedWidget = new CodeEditorsStackedWidget;
	m_openedFilesViewDockWidget = new OpenedFilesViewDockWidget;
	m_applicationOutputDockWidget = new ApplicationOutputDockWidget;

	setCentralWidget(m_codeEditorsStackedWidget);
	addDockWidget(Qt::RightDockWidgetArea, m_taglistDockWidget);
	addDockWidget(Qt::LeftDockWidgetArea, m_fileDirsViewDockWidget);
	addDockWidget(Qt::LeftDockWidgetArea, m_openedFilesViewDockWidget);
	addDockWidget(Qt::BottomDockWidgetArea, m_applicationOutputDockWidget);

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

	QObject::connect(ui->actionEnglish, SIGNAL(triggered()), this, SLOT(actionEnglish_setEnglish()));
	QObject::connect(ui->actionChinese, SIGNAL(triggered()), this, SLOT(actionChinese_setChinese()));

	QObject::connect(ui->actionHelp, SIGNAL(triggered()),this, SLOT(actionHelp_help()));
	QObject::connect(ui->actionAbout, SIGNAL(triggered()),this ,SLOT(actionAbout_about()));

	QObject::connect(m_fileDirsViewDockWidget, SIGNAL(openFileByPath(QString)), m_openedFilesViewDockWidget, SLOT(insertRow(QString)));
//	QObject::connect(m_fileDirsViewDockWidget, SIGNAL(openFileByPath(QString)), m_codeEditorsStackedWidget, SLOT(addCodeEditorWidget(QString)));
	QObject::connect(m_openedFilesViewDockWidget, SIGNAL(displayFileByFilePath(QString)), m_codeEditorsStackedWidget, SLOT(setCurrentCodeEditorWidget(QString)));
	QObject::connect(m_openedFilesViewDockWidget, SIGNAL(removeFileByFilePath(QString)), m_codeEditorsStackedWidget, SLOT(removeCodeEditorWidget(QString)));

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
		m_fileDirsViewDockWidget->setViewProfiles(dlg.selectedFiles()[0]);
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

void MainWindow::actionEnglish_setEnglish()
{
#if 0
	QTranslator translator;
	translator.load(":/translate/english.qm");
	qApp->installTranslator(&translator);
	ui->actionChinese->setChecked(false);
	ui->actionEnglish->setChecked(true);
	ui->retranslateUi(this);
#endif
}

void MainWindow::actionChinese_setChinese()
{
#if 0
	QTranslator translator;
	translator.load(":/translate/chinese.qm");
	qApp->installTranslator(&translator);

	ui->actionChinese->setChecked(true);
	ui->actionEnglish->setChecked(false);
	ui->retranslateUi(this);
#endif
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
