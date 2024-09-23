#include <ModbusMaster.h>
#include <SoftwareSerial.h>

#define RXD2 17
#define TXD2 16

SoftwareSerial RS485(RXD2,TXD2);
#define SLAVE_ID_R 1
#define SLAVE_ID_L 2

ModbusMaster flowMeterRight;
ModbusMaster flowMeterLeft;

//Function Resources
float dataArray[20];
float ReadArrayR[20];
float ReadArrayL[20];
unsigned long data;

float cumulativeTotal_flowmeterR;
float instanteneousTotal_flowmeterR;
float cumulativeTotal_flowmeterL;
float instanteneousTotal_flowmeterL;

long lastFlowmeterRightFetch;

float previousCumulativeTotalR;
float previousCumulativeTotalL;
float displayCumulativeTotalR;
float displayCumulativeTotalL;

float batchBuffer = 0;


// Digital Inputs
const int modeSetter1 = 0;
const int start1 = 1;
const int stop1 = 2;
const int set1 = 3;

// Digital Outputs
const int valve1 = 6;
const int valve2 = 1;
