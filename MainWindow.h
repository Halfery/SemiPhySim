#pragma once

#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include <QTextCodec>
#include "ui_MainWindow.h"
#include "serialSetup.h"
#include "SandRBox.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	void createDockWindows();
	static QString ToQString(const std::string& cstr);

private:
    serialSetupWidget * m_serialSetup;
    SandRBoxWidget * m_sandrbox;
	Ui::MainWindowClass ui;
	
private slots:
	void sendDataByHand();
	void receiveData();
	void setReceiveDataNum();
};
