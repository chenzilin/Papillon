#include <QtGui>
#include "syntaxhighlighter.h"

SyntaxHighLighter::SyntaxHighLighter(QTextDocument *parent)
	: QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	keywordPatterns << "\\balignas\\b" << "\\balignof\\b" << "\\band\\b"
					<< "\\band_eq\\b" << "\\basm\\b" << "\\bauto\\b"
					<< "\\bbitand\\b" << "\\bbitor\\b" << "\\bbool\\b"
					<< "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b"
					<< "\\bchar\\b" << "\\bchar16_t\\b" << "\\bchar32_t\\b"
					<< "\\bclass\\b" << "\\bcompl\\b" << "\\bconst\\b"
					<< "\\bconstexpr\\b" << "\\bconst_cast\\b" << "\\bcontunue\\b"
					<< "\\bdecltype\\b" << "\\bdefault\\b" << "\\bdelete\\b"
					<< "\\bdo\\b" << "\\bdouble\\b" << "\\bdynamic_cast\\b"
					<< "\\belse\\b" << "\\benum\\b" << "\\bfinal\\b"
					<< "\\bexplicit\\b" << "\\bexport\\b" << "\\bextern\\b"
					<< "\\bfalse\\b" << "\\bfloat\\b" << "\\bfor\\b"
					<< "\\bfriend\\b" << "\\bgoto\\b" << "\\bif\\b"
					<< "\\binline\\b" << "\\bint\\b" << "\\blong\\b"
					<< "\\bmutable\\b" << "\\bnamespace\\b" << "\\bnew\\b"
					<< "\\bnoexcept\\b" << "\\bnot\\b" << "\\bnot_eq\\b"
					<< "\\bnullptr\\b" << "\\boperator\\b" << "\\bor\\b"
					<< "\\bor_eq\\b" << "\\bprivate\\b" << "\\bprotected\\b"
					<< "\\bpublic\\b" << "\\bregister\\b" << "\\breinterpret_cast\\b"
					<< "\\bsigned\\b" << "\\bsizeof\\b" << "\\bstatic\\b"
					<< "\\bstatic_cast\\b" << "\\bstatic_assert\\b" << "\\bstruct\\b"
					<< "\\bswitch\\b" << "\\btemplate\\b" << "\\bthis\\b"
					<< "\\bthread_local\\b" << "\\bthrow\\b" << "\\btrue\\b"
					<< "\\btry\\b" << "\\btypedef\\b" << "\\btypeid\\b"
					<< "\\btypename\\b" << "\\bunion\\b" << "\\bunsigned\\b"
					<< "\\busing\\b" << "\\bvirtual\\b" << "\\bvoid\\b"
					<< "\\bvolatile\\b" << "\\bwchar_t\\b" << "\\bwhile\\b"
					<< "\\bxor\\b" << "\\bxor_eq\\b" << "\\boverride\\b"
					<< "\\breturn\\b" << "\\bshort\\b";

	foreach(const QString &pattern, keywordPatterns)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
	rule.format = classFormat;
	highlightingRules.append(rule);

	includeFormat.setFontWeight(QFont::Bold);
	includeFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("#include");
	rule.format = includeFormat;
	highlightingRules.append(rule);

	classAreaFormat.setFontWeight(QFont::Bold);
	classAreaFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("[A-Za-z_]+::");
	rule.format = classAreaFormat;
	highlightingRules.append(rule);


	singleLineCommentFormat.setForeground(Qt::red);
	rule.pattern = QRegExp("//[^\n]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);

	multiLineCommentFormat.setForeground(Qt::red);

	quotationFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("\".*\"");
	rule.format = quotationFormat;
	highlightingRules.append(rule);

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(Qt::blue);
	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat;
	highlightingRules.append(rule);

	commentStartExpression = QRegExp("/\\*");
	commentEndExpression = QRegExp("\\*/");
}

void SyntaxHighLighter::highlightBlock(const QString &text)
{
	foreach (const HighlightingRule &rule, highlightingRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {

			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}
	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = commentStartExpression.indexIn(text);

	while (startIndex >= 0) {
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if (endIndex == -1) {

			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}
		else {
			commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
	}
}
