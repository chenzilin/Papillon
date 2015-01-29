#include <QPainter>
#include <QTextStream>

#include <codeeditor.h>

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
	lineNumberArea = new LineNumberArea(this);
	m_syntaxHighLighter = new SyntaxHighLighter(this->document());

	QFont font;
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(12);
	this->setFont(font);
	this->setTabStopWidth(40);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
	updateLineNumberAreaWidth(0);
}


void CodeEditor::setCodeText(QString filePath)
{
	QFile fp(filePath);
	if (fp.open(QFile::ReadOnly)) {

		QTextStream stm(&fp);
		this->clear();
		while (!stm.atEnd()) {

			this->appendPlainText(stm.readLine(120));
		}
		fp.close();
		this->moveCursor(QTextCursor::Start);
	}
}

int CodeEditor::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {

		max /= 10;
		++digits;
	}

	return 10 + fontMetrics().width(QLatin1Char('9')) * digits;
}


void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{ 
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
	QPlainTextEdit::resizeEvent(event);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QPainter painter(lineNumberArea);
	painter.setPen(Qt::black);
	painter.fillRect(event->rect(), QColor(189, 252, 201));

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {

		if (block.isVisible() && bottom >= event->rect().top()) {

			QString number = QString::number(blockNumber + 1);
			painter.drawText(QRect(0, top, lineNumberArea->width(), fontMetrics().height()), Qt::AlignCenter, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}
