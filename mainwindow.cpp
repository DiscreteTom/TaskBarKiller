#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <QSettings>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//---------------- about hot key
	hotkey = new QHotkey(QKeySequence("Ctrl+`"), true, this);
	connect(hotkey, &QHotkey::activated, this, &MainWindow::getHotKeyPressed);

	//------------------ state
	taskBarIsHidden = false;

	//---------------- tray icon
	icon = new QSystemTrayIcon(this);
	QIcon thisIcon(":/img/TaskBarKiller.png");
	icon->setIcon(thisIcon);
	connect(icon, &QSystemTrayIcon::activated, this, &MainWindow::trayClicked);
	icon->show();
	actionShow = new QAction(tr("Show(&S)"), this);
	actionClose = new QAction(tr("Exit(&E)"), this);
	menu = new QMenu(this);
	menu->addAction(actionShow);
	menu->addAction(actionClose);
	connect(actionShow, &QAction::triggered, this, &MainWindow::getShow);
	connect(actionClose, &QAction::triggered, this, &MainWindow::getExit);
	icon->setToolTip(tr("Press Ctrl+~ to hide your task bar"));

	//--------------------------------------------- auto start
	/* if auto start for all users
	 * HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	 * else if auto start for current user
	 * HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	 */
	QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	QString appName = QApplication::applicationName();
	QString strAppPath=QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
	reg.setValue(appName,strAppPath);
}

MainWindow::~MainWindow()
{
	HWND hwnd=::FindWindow(L"Shell_TrayWnd",NULL);
	ShowWindow(hwnd, 1);//show
	delete ui;
}

void MainWindow::getHotKeyPressed()
{
	HWND hwnd=::FindWindow(L"Shell_TrayWnd",NULL);
	taskBarIsHidden = !taskBarIsHidden;
	if (taskBarIsHidden){
		ShowWindow(hwnd, 0);//hide
	} else {
		ShowWindow(hwnd, 1);//show
	}
}

void MainWindow::trayClicked(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason){
	case QSystemTrayIcon::Context://right click
		menu->exec(this->cursor().pos());//attention NOT show()
		break;
	case QSystemTrayIcon::Trigger://left click
		show();
		break;
	}
}

void MainWindow::getShow()
{
	show();
}

void MainWindow::getExit()
{
	qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
	e->ignore();
	hide();
}
