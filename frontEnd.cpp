#include "frontEnd.h"

frontEndWidget::frontEndWidget(QWidget * parent) : QWidget(parent), ui(new Ui::frontEnd) {
	ui->setupUi(this);


}
frontEndWidget::~frontEndWidget()
{
}

void frontEndWidget::setInstructionID(uint8_t ID)
{
	this->instructionID = ID;
}

void frontEndWidget::increaseFrameNum()
{
	this->frameNum++;
}

void frontEndWidget::setDataSeg(uint8_t * data, uint8_t dataLength)
{
	this->dataSeg[0] = this->instructionID;
	this->dataSeglength++;
	this->dataSeg[4] = this->frameNum;
	this->dataSeg[3] = this->frameNum >> 8;
	this->dataSeg[2] = this->frameNum >> 16;
	this->dataSeg[1] = this->frameNum >> 24;
	this->dataSeglength += 4;
	for (int i = 0;i < dataLength;i++) {
		this->dataSeg[5 + i] = data[i];
	}
	this->dataSeglength += dataLength;
}
