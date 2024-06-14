#include <QApplication>
#include "resume.h"
#include <QFontDatabase>
#include <QDebug>
#include <unistd.h>
#include <stdio.h>

#define MAX(a,b) (a > b ? a : b)

int main(int argc, char *argv[]) {
	if (argc != 2) {
		qDebug() << argv[0] << "<output.pdf>";
		return EXIT_FAILURE;
	}

	int appArgc = 3;
	char *appArgv[3];
	appArgv[0] = new char[strlen(argv[0])];
	appArgv[1] = new char[10];
	appArgv[2] = new char[9];

	sprintf(appArgv[0], "%s", argv[0]);
	sprintf(appArgv[1], "--platform");
	sprintf(appArgv[2], "offscreen");
	QApplication app(appArgc, appArgv);

	QFontDatabase::addApplicationFont("fonts/Lora/Lora.ttf");

	Resume resume;
	resume.craft(argv[1]);

	delete appArgv[0];
	delete appArgv[1];
	delete appArgv[2];

	//app.exec();
	return EXIT_SUCCESS;
}


