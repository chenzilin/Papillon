#ifndef CODEEDITORWIDGET_H
#define CODEEDITORWIDGET_H

#include <QMap>
#include <QStackedWidget>

#include <codeeditor.h>

class CodeEditorWidget : public QStackedWidget
{
	Q_OBJECT

public:
	CodeEditorWidget(QWidget *parent = 0);
	~CodeEditorWidget(){}

private slots:
	void addCodeEditor(QString filePath);
	void setCurrentCodeEditorWidget(QString filePath);
	void removeCodeEditorWidget(QString filePath);

private:
	QMap<QString, CodeEditor *> m_stackedWidget;
};

#endif
