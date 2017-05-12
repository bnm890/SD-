#include <SPI.h>
#include <SD.h>
#define CS_Pin  10
int num1,num2;
File myFile;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!SD.begin(CS_Pin)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  Serial.println(F("initialization done"));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    myFile = SD.open("app01.txt");
    if (myFile) {
      while (myFile.available()){
        if(myFile.find("app ")){
          num1=GetSD_Value();
        }
        if(myFile.find("abc ")){
          num2=GetSD_Value();
        }
        myFile.close();
      }
    }
    Serial.print("No.1="); 
    Serial.println(num1);
    Serial.print("No.2=");
    Serial.println(num2);
  }
  delay(1000);
}

int GetSD_Value(){
  int theNum=0;
  byte i=0;
  char j=' ';
  bool OK=0;
  while(!OK){
    j=myFile.read();
    if(j>='0' && j<='9'){
      theNum = theNum*10;
      theNum += getCharToNum(j);
    }
    if(j==10) OK=1;
  }
  return theNum;
}

int getCharToNum(char c) {
  char numList[10] = { '0','1','2','3','4','5','6','7','8','9' };
  int theNum;
  for(int i = 0 ;i < 10;i++) {
    if(c == numList[i]) {
      theNum = i;
      break;
    }
  }
  return theNum;
}
