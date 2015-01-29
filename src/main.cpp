#include <QPixmap>
#include <QSplashScreen>
#include <QApplication>

#include <mainwindow.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSplashScreen splashScreen;
	splashScreen.setPixmap(QPixmap(":/images/splashscreen.jpg"));
	splashScreen.setFixedSize(splashScreen.width(), splashScreen.height());
	splashScreen.show();

	Qt::Alignment bottomRight = Qt::AlignBottom|Qt::AlignRight;

	for (int i = 1; i <= 10; ++i) {
		splashScreen.showMessage(QObject::tr("Loading....."), bottomRight , Qt::red);
	}

	MainWindow w;
	splashScreen.finish(&w);
	w.show();

	return a.exec();
}
