#pragma once

#include "ui_SandRBox.h"
//#include "serialSetup.h"

namespace UI {
	class SandRBoxWidget;
}

class SandRBoxWidget :public QWidget{
	Q_OBJECT
public:
	SandRBoxWidget(QWidget * parent = NULL);
	~SandRBoxWidget();
	QTextDocument * m_getSendData();
	void m_setTextEdit(QByteArray &data);
	unsigned int m_returnReceivedDataBytesNum();

private:
	Ui::SandRBox *ui;
	unsigned int rBytesNum = 0;
private slots:
	void m_pb_setTextEditClean();

signals:
	void s_sendButtonClick();
	void s_receivedBytesNum();

};
