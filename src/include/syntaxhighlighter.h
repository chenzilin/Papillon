#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QHash>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QSyntaxHighlighter>

class SyntaxHighLighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	SyntaxHighLighter(QTextDocument *parent = 0);

protected:
	void highlightBlock(const QString &text);

private:
	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};
	QVector<HighlightingRule> highlightingRules;

	QRegExp commentStartExpression;
	QRegExp commentEndExpression;

	QTextCharFormat classFormat;
	QTextCharFormat classAreaFormat;
	QTextCharFormat keywordFormat;
	QTextCharFormat includeFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;
};

#endif // SYNTAXHIGHLIGHTER_H
