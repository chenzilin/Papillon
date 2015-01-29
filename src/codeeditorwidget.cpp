#include <QRegExp>
#include <QMessageBox>

#include <codeeditorwidget.h>

CodeEditorWidget::CodeEditorWidget(QWidget *parent)
	:QStackedWidget(parent)
{
}

void CodeEditorWidget::addCodeEditor(QString filePath)
{
	CodeEditor *codeEditor = new CodeEditor(this);
	codeEditor->setObjectName(filePath);

	this->addWidget(codeEditor);

	for (int i = 0; i < this->count(); ++i) {

		if(filePath == this->widget(i)->objectName()) {

			this->setCurrentIndex(i);
			dynamic_cast<CodeEditor *>(currentWidget())->setCodeText(filePath);
			break;
		}
	}
}

void CodeEditorWidget::setCurrentCodeEditorWidget(QString  filePath)
{
	for (int i = 0; i < this->count(); ++i) {

		if (filePath == this->widget(i)->objectName()) {

			this->setCurrentIndex(i);
			break;
		}
	}
}

void CodeEditorWidget::removeCodeEditorWidget(QString filePath)
{
	for (int i = 0; i < this->count(); ++i) {

		if (filePath == this->widget(i)->objectName()) {

			this->removeWidget(this->widget(i));
			break;
		}
	}

	QMessageBox::information(0, QString::number(this->count()), QString::number(this->count()));
}
