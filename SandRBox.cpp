#include "SandRBox.h"
SandRBoxWidget::SandRBoxWidget(QWidget * parent) : QWidget(parent), ui(new Ui::SandRBox) {
	ui->setupUi(this);

	connect(ui->pb_SbyHand, SIGNAL(clicked()), this, SIGNAL(s_sendButtonClick()));
	connect(ui->pb_Rclean,SIGNAL(clicked()),this, SLOT(m_pb_setTextEditClean()));
	connect(ui->te_receivedData,SIGNAL(textChanged()),this,SIGNAL(s_receivedBytesNum()));
}
SandRBoxWidget::~SandRBoxWidget()
{
}

QTextDocument * SandRBoxWidget::m_getSendData()
{
	return ui->te_sendData->document();
}

void SandRBoxWidget::m_setTextEdit(QByteArray & data)
{
	//data.resize(data.size() - 1);
	//QByteArray qb_temp
	rBytesNum += data.size();
	if (ui->cb_hexReceive->isChecked())
	{
		data = data.toHex(' ');
	}
	ui->te_receivedData->insertPlainText(data);
	QString qs_tmp = ' ';
	ui->te_receivedData->insertPlainText(qs_tmp);
}

unsigned int SandRBoxWidget::m_returnReceivedDataBytesNum()
{
	return rBytesNum;
	//return 0;
}

void SandRBoxWidget::m_pb_setTextEditClean() {
	rBytesNum = 0;
	ui->te_receivedData->setDocument(NULL);
}

