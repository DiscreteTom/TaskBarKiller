#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qhotkey.h>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	//----------------- hot key
	QHotkey * hotkey;

	//------------------ state
	bool taskBarIsHidden;

	//-------------------- system icon
	QSystemTrayIcon * icon;
	QAction * actionShow;
	QAction * actionClose;
	QMenu * menu;
public slots:
	void getHotKeyPressed();
	void trayClicked(QSystemTrayIcon::ActivationReason reason);
	void getShow();
	void getExit();

protected:
	void closeEvent(QCloseEvent * e);
};

#endif // MAINWINDOW_H
