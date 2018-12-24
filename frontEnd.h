#pragma once

#include "ui_frontEnd.h"
#include "protocols.h"

namespace UI {
	class frontEndWidget;
}

class frontEndWidget :public QWidget {
	Q_OBJECT
public:
	frontEndWidget(QWidget * parent = NULL);
	~frontEndWidget();
	void setInstructionID(uint8_t ID);
	void increaseFrameNum();
	void setDataSeg(uint8_t *data,uint8_t dataLength);
	
private:
	Ui::frontEnd *ui;
	uint8_t dataSeg[253];
	uint32_t frameNum = 0;
	uint8_t dataSeglength = 0;
	uint8_t instructionID = 0;
	c_serial_protocol serialP;
	uint8_t tempData[249];
};