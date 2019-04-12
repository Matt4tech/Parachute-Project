//Slave Device
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

boolean buttonPressed = false;//if button is pressed
int LEDPIN = 8;//Led Pin

//SD
int CS_PIN = 10;
File file;

//SavingData
float savingDataArray[13];
int cout=0;//counter
boolean TransComp;

//Saving data
int topMotor;
int bottomMotor;

void setup() {
  // put your setup code here, to run once:
  initializeSD();
  createFile("SavingFile.txt");
  writeToFile("This is where the dara will be stored");
  closeFile();

  
  pinMode (LEDPIN, OUTPUT);//
  Wire.begin(0);//starts as slave device at address 0
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes){//update
  while (1 < Wire.available()) { // loop through all but the last
    savingDataArray[cout] = (float) Wire.read(); // receive byte as a float
    cout++;
    if(cout==13){topMotor = (int) Wire.read();}
    if(cout==14){bottomMotor = (int) Wire.read();} 
  }
  boolean TransComp = Wire.read();
  cout=0;
}




void loop() {
  //work with most recent update of data
  openFile("SavingFile.txt");
  saveToFile();
  closeFile();

  
}

void saveToFile(){
  writeToFile("Altitude: "+ (char) savingDataArray[0]);
}



void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}

int createFile(char filename[])
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char text[])
{
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[])
{
  file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return 1;
  } else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}

String readLine()
{
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return "";
}
