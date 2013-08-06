#include <QApplication>
#include "daughterWindow.h" 

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	daughterWindow fifille; 

	fifille.show();

	return app.exec();
}
