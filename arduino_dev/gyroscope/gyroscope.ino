#include "_wt901c.h"
#include <HardwareSerial.h> //for rs485 comm
#define RXD2 5
#define TXD2 18
HardwareSerial rs485(2); // rxtx mode 2 of 0,1,2

short recData1[12];
short recData2[12];
short trashBuffer[180];

short initBuffer[3][3];
short prevBuffer[3][3];
short newBuffer[3][3];
float diffBuffer[3][3];

/*
 * buffer structure
 **********************************************
 *           dev1[x] | dev1[y] | dev1[z] |
 *           -----------------------------
 *accel      |       |         |         |
 *           -----------------------------
 *angle      |       |         |         |
 *           -----------------------------
 *angularvel |       |         |         |
 *           -----------------------------
 **********************************************
 */

static float accDiff[6];
static float angDiff[6];
static float angvelDiff[6];

int flag = 0;

void sendCommand(byte command[8], int prt){
  byte data[10];
  for(int i=0;i<8;i++){
    data[i]=command[i];
    }
  if(prt==1){
    for(int i = 0;i<8;i++){
      Serial.print(command[i],HEX);
      if(i != 7){
        Serial.print(",");
        }
      }
    }
  rs485.write(data, 8);
//  Serial.println();
  rs485.flush();
  }

int rs485_receive(short recv[], int num){
    unsigned long t = millis(); 
    while(1){
      if(millis() - t > 10000){
        return -1;
        break;
      }
      for (int i = 0; (rs485.available() > 0) && (i < num); i++) {
        recv[i] = rs485.read();
      }
      return 0;
      break;
    }
  }

void calibrateAcc(){
      Serial.println("---------- Acceleration Calibration Init ----------");
      sendCommand(unlockMaster2,1);
      delay(500);
      sendCommand(accCalmode2,1);
      delay(6000);
      sendCommand(setNormal2,1);
      delay(1000);
      sendCommand(saveConfig2,1);
      delay(1000);
  }
  
void calibrateMag(){
      Serial.println("---------- Magnetic Calibration Init ----------");
      sendCommand(unlockMaster2,1);
      delay(500);
      sendCommand(magCalmode2,1);
      Serial.println("---------- Slowly rotate in 3 axis ----------");
      delay(5000);
      Serial.println("---------- May stop now :) ----------");
      sendCommand(setNormal2,1);
      delay(1000);
      sendCommand(saveConfig2,1);
      delay(1000);  
  }

void readAcceleration(){
    sendCommand(readAcc2,0);
    //Serial.println("Acceleration");
    
    if(rs485_receive(recData1, 11) != -1){
      // for(int i = 0;i<11;i++){
        // Serial.print(recData1[i],HEX);
        // Serial.print(",");
        // }
      }
     else{
      Serial.println("no resp");
      Serial.println();    
      } 
    //printAccel(recData1);
    rs485.flush();
    //Serial.println(); 
    delay(5);
  }


void readSensorAngle(){
    sendCommand(readAngle2,0);
    //Serial.println("Angle");
    
    if(rs485_receive(recData1, 11) != -1){
      // for(int i = 0;i<11;i++){
      //   Serial.print(recData1[i],HEX);
      //   Serial.print(",");
      //   }
      }
     else{
      Serial.println("no resp");
      Serial.println();    
      }
    //printAngle(recData1);
    rs485.flush();
    //Serial.println(); 
    delay(5);
  }


void readAngularVelocity(){
    sendCommand(readAngVel2,0);
    //Serial.println("Angular Velocity");
    
    if(rs485_receive(recData1, 11) != -1){
      
      // for(int i = 0;i<11;i++){
      //   Serial.print(recData1[i],HEX);
      //   Serial.print(",");
      //   }

      }
     else{
      Serial.println("no resp");
      Serial.println();    
      } 
    //printAngVel(recData1);
    rs485.flush();
    //Serial.println(); 
    delay(5);
  }

void savebuffer(short tarbuf[3][3], int type){
    tarbuf[type][0]=(((short)recData1[3]<<8)|recData1[4]);
    tarbuf[type][1]=(((short)recData1[5]<<8)|recData1[6]);
    tarbuf[type][2]=(((short)recData1[7]<<8)|recData1[8]);
  }

void printAccel(short rec[]){
  short data_x = (((short)rec[3]<<8)|rec[4])/(32768/(16*9.81));
  short data_y = (((short)rec[5]<<8)|rec[6])/(32768/(16*9.81));
  short data_z = (((short)rec[7]<<8)|rec[8])/(32768/(16*9.81));
  Serial.print(data_x);Serial.print("   "); Serial.print(data_y);Serial.print("   ");Serial.println(data_z);
  }

void printAngle(short rec[]){
  short data_x = (((short)rec[3]<<8)|rec[4])/(32768/180);
  short data_y = (((short)rec[5]<<8)|rec[6])/(32768/180);
  short data_z = (((short)rec[7]<<8)|rec[8])/(32768/180);
  Serial.print(data_x);Serial.print("   "); Serial.print(data_y);Serial.print("   "); Serial.println(data_z);
  }

void printAngVel(short rec[]){
  short data_x = (((short)rec[3]<<8)|rec[4])/(32768/2000);
  short data_y = (((short)rec[5]<<8)|rec[6])/(32768/2000);
  short data_z = (((short)rec[7]<<8)|rec[8])/(32768/2000);
  Serial.print(data_x);Serial.print("   "); Serial.print(data_y);Serial.print("   "); Serial.println(data_z);
  }

void readSensor(short buf[3][3]){
  readAcceleration();
  savebuffer(buf, 0);
  readSensorAngle();
  savebuffer(buf, 1);
  readAngularVelocity();
  savebuffer(buf, 2);
}

void clearBuffer(){
  for(int i=0; i<3;i++){
    for(int j=0; j<6;j++){
      prevBuffer[i][j] = newBuffer[i][j];
      newBuffer[i][j] = 0;
      }
  }
}

void setup() {
  Serial.begin(115200);
  rs485.begin(9600, SERIAL_8N1, RXD2, TXD2);
  rs485.flush();

  Serial.println("--------------- Serial Initiated ---------------");
  calibrateAcc();
  Serial.println();
  calibrateMag();
  Serial.println();
  
  Serial.println("--------------- Calibration Done ---------------");
  rs485.flush();
  
  if(rs485_receive(trashBuffer, 180) != -1){
    for(int i = 0;i<180;i++){
      Serial.print(trashBuffer[i],HEX);
      Serial.print(",");
      }
      Serial.println();
    }

}

void loop() {
  // put your main code here, to run repeatedly:
  rs485.flush();
//  if(++flag==1){
//    Serial.println("WT901C485 read");
//    readSensor(initBuffer);
//    for(int i = 0;i<3;i++){
//      for(int j = 0; j<3;j++){
//        Serial.print(initBuffer[i][j]);
//        Serial.print("  ");       
//        }
//       Serial.println();
//      }
//    readSensor(prevBuffer);
//    delay(500);
//  }
  readSensor(initBuffer);
  for(int i = 0;i<3;i++){
      for(int j = 0; j<3;j++){
        Serial.print(initBuffer[i][j]);
        Serial.print("  ");       
        }
       Serial.println();
      }
    delay(3000);
}
