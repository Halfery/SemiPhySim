#include <QMessageBox>
#include <QDebug>
#include "serialSetup.h"

serialSetupWidget::serialSetupWidget(QWidget * parent) : QWidget(parent), ui(new Ui::SerialSetup){
	ui->setupUi(this);
	ui->baudRate->addItems(m_baudRates);
	ui->baudRate->setCurrentText(m_baudRates[10]);
	ui->dataBits->addItems(m_serial_dataBits);
	ui->dataBits->setCurrentText(m_serial_dataBits[3]);
	ui->stopBits->addItems(m_serial_stopBits);
	ui->checkBit->addItems(m_parity_checkBits);
	ui->rBytes->setText("0");
	ui->sBytes->setText("0");

	connect(ui->pb_scanSerialPorts, SIGNAL(clicked()), this, SLOT(m_pb_scanSerialPort()));
	connect(ui->pb_openSerialPort, SIGNAL(clicked()), this, SLOT(m_pb_openSerialPort()));
	connect(ui->pb_setCountNumZero, SIGNAL(clicked()), this, SLOT(m_pb_setCountNumZero()));
	//connect(m_serialPort,SIGNAL(readyRead()), this, SIGNAL(s_receivedData()));
	//connect(this, SIGNAL(readyRead()), this ,SLOT(m_pb_setCountNumZero()));
}
serialSetupWidget::~serialSetupWidget()
{
}

void serialSetupWidget::m_serialDataSend(const QByteArray & data)
{
	if (m_serialPort!=NULL){
		m_serialPort->write(data);
	}	
}

QByteArray serialSetupWidget::m_serialDataReceive()
{
	if (m_serialPort != NULL) {
		QByteArray data = m_serialPort->readAll();
		return data;
	}
}

void serialSetupWidget::m_setReceivedDataNum(unsigned int Num)
{
	ui->rBytes->setText(QString::number(Num));
}


void serialSetupWidget::m_pb_openSerialPort()
{
	if (m_serialPort == NULL)
	{
		m_serialPort = new QSerialPort();
	}
	if (m_serialPort->isOpen())
	{
		m_serialPort->close();
		ui->pb_openSerialPort->setText(ToQString("打开串口"));
	}
	else {
		if (ui->selectSerialPort->count()==0){
			QMessageBox::warning(this, ToQString("警告！"), ToQString("请扫描串口"), QMessageBox::Ok);
			return;
		}
		else
		{
			m_serialPort->setPortName(ui->selectSerialPort->currentText());
			qint32 itemp = ui->baudRate->currentText().toInt();
			m_serialPort->setBaudRate(itemp);
			itemp = ui->dataBits->currentText().toInt();
			switch (itemp)
			{
				case 5:
					m_serialPort->setDataBits(QSerialPort::Data5);
					break;
				case 6:
					m_serialPort->setDataBits(QSerialPort::Data6);
					break;
				case 7:
					m_serialPort->setDataBits(QSerialPort::Data7);
					break;
				case 8:
					m_serialPort->setDataBits(QSerialPort::Data8);
					break;
			default:
				break;
			}
			QString t_parity = ui->checkBit->currentText();
			if (t_parity == ToQString("None"))
			{
				m_serialPort->setParity(QSerialPort::NoParity);
			} 
			else if(t_parity == ToQString("Even"))
			{
				m_serialPort->setParity(QSerialPort::EvenParity);
			}
			else {
				m_serialPort->setParity(QSerialPort::OddParity);
			}
			itemp = ui->stopBits->currentText().toInt();
			switch (itemp)
			{
			case 1:
				m_serialPort->setStopBits(QSerialPort::OneStop);
				break;
			case 2:
				m_serialPort->setStopBits(QSerialPort::TwoStop);
				break;
			default:
				break;
			}
			m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
			m_serialPort->open(QIODevice::ReadWrite);
			m_serialPort->setReadBufferSize(m_readBufferSize);
			//m_serialPort->setDataTerminalReady(true);
			connect(m_serialPort, SIGNAL(readyRead()), this, SIGNAL(s_receivedData()));
		}
		ui->pb_openSerialPort->setText(ToQString("关闭串口"));
	}
}
void serialSetupWidget::m_pb_setCountNumZero()
{
	ui->rBytes->setText("0");
	ui->sBytes->setText("0");
}

QString serialSetupWidget::ToQString(const std::string & cstr)
{
	QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
	QString qstr;
	if (!pCodec)
		return qstr;

	qstr = pCodec->toUnicode(cstr.c_str(), cstr.length());
	return qstr;
	//return QString();
}
void serialSetupWidget::m_pb_scanSerialPort() {
	m_serialPort = new QSerialPort();
	if (m_serialPort != NULL){
		foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
			QSerialPort temp_serial;
			temp_serial.setPort(info);
			if (temp_serial.open(QIODevice::ReadWrite))	{
				unsigned isItemInList = 0;
				for (int i = 0; i < ui->selectSerialPort->count();i++) {
					//qDebug() << "count:" << ui->selectSerialPort->count();
					//qDebug() << "item:" << ui->selectSerialPort->itemText(i);
					//qDebug() << "portname:" << temp_serial.portName();
					if (ui->selectSerialPort->itemText(i) == temp_serial.portName()){
						isItemInList++;
					}
				}
				if (isItemInList == 0){
					ui->selectSerialPort->addItem(temp_serial.portName());
				}
				temp_serial.close();
			}
		}
	} 
	else{
		QMessageBox::warning(this, tr("警告"),tr("串口没有初始化成功"), QMessageBox::Ok);
	}
}