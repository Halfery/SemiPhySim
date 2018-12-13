#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	createDockWindows();
	connect(m_sandrbox, SIGNAL(s_sendButtonClick()),this, SLOT(sendDataByHand()));
	connect(m_serialSetup, SIGNAL(s_receivedData()), this, SLOT(receiveData()));
	connect(m_sandrbox, SIGNAL(s_receivedBytesNum()), this, SLOT(setReceiveDataNum()));
	//connect(m_serialSetup, , this, SLOT(receiveData()));
}

void MainWindow::sendDataByHand() {
	QTextDocument * text = m_sandrbox->m_getSendData();
	QString qstr = text->toPlainText();
	QByteArray qba_temp;
	qba_temp = qstr.toLocal8Bit();
	qba_temp = qba_temp.fromHex(qba_temp);
	m_serialSetup->m_serialDataSend(qba_temp);
	//qDebug() << qba_temp;
}

void MainWindow::createDockWindows()
{
	QDockWidget *dock = new QDockWidget(ToQString("串口设置"),this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea);
	m_serialSetup = new serialSetupWidget(this);
	dock->setWidget(m_serialSetup);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	QDockWidget *sandr_dock = new QDockWidget(ToQString("发送接收"),this);
	sandr_dock->setAllowedAreas(Qt::RightDockWidgetArea);
	m_sandrbox = new SandRBoxWidget(this);
	sandr_dock->setWidget(m_sandrbox);
	addDockWidget(Qt::RightDockWidgetArea, sandr_dock);
}

QString MainWindow::ToQString(const std::string & cstr)
{
	QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
	QString qstr;
	if (!pCodec)
		return qstr;

	qstr = pCodec->toUnicode(cstr.c_str(), cstr.length());
	return qstr;
	//return QString();
}

void MainWindow::receiveData()
{
	QByteArray qba_temp;
	qba_temp = m_serialSetup->m_serialDataReceive();
	m_sandrbox->m_setTextEdit(qba_temp);
}

void MainWindow::setReceiveDataNum()
{
	unsigned int i_tmp = 0;
	i_tmp = m_sandrbox->m_returnReceivedDataBytesNum();
	m_serialSetup->m_setReceivedDataNum(i_tmp);
}
