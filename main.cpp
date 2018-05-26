#include "mainwindow.h"
#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
	//prevent multi-open
	HANDLE hMutex = CreateMutex(NULL, false, (LPCTSTR)"TaskBarKiller");
	if (GetLastError() == ERROR_ALREADY_EXISTS){
		return 0;
	}

	QApplication a(argc, argv);
	MainWindow w;

	if (argc > 1 && (argv[1] == MainWindow::tr("autoStart"))){
		w.hide();
	} else {
		w.show();
	}

	return a.exec();
}
