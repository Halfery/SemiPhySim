#pragma once

#include <QWidget>
#include <QTextCodec>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "ui_serialSetup.h"
#include "SandRBox.h"

namespace UI {
	class serialSetupWidget;
}

class serialSetupWidget : public QWidget {
	Q_OBJECT
public:
	serialSetupWidget(QWidget * parent = NULL);
	~serialSetupWidget();
	void m_serialDataSend(const QByteArray &data);
	QByteArray m_serialDataReceive();
	void m_setReceivedDataNum(unsigned int Num);
private:
	//friend void SandRBoxWidget::m_sendData(const char * data);
	Ui::SerialSetup *ui;
	const QStringList m_baudRates = {"300","600","1200","2400","4800","9600","19200","38400","76800","115200","230400","460800","921600"};
	const QStringList m_serial_dataBits = {"5","6","7","8"};
	const QStringList m_parity_checkBits = { "None","Even","Odd" };
	const QStringList m_serial_stopBits = {"1","2"};
	QStringList m_serialPortsName = {};

private slots:
	void m_pb_scanSerialPort();
	void m_pb_openSerialPort();
	void m_pb_setCountNumZero();

private:
	static QString ToQString(const std::string& cstr);
	QSerialPort * m_serialPort = NULL;
	const qint64 m_readBufferSize = 256;
signals:
	void s_receivedData();

};
