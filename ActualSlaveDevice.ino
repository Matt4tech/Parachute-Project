//Slave Device
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

//SD
int CS_PIN = 10;
File file;

//SavingData
float savingDataArray[16];
int cout=0;//counter
boolean TransComp;

//Saving data
int topMotor;
int bottomMotor;

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up SD card");
  // put your setup code here, to run once:
  initializeSD();
  SD.begin();
  Serial.println("Succesful");
  Serial.println("Creating a file if not already made");
  createFile("TEST.txt");
  writeToFile("This is where the data will be stored");
  closeFile();
  Serial.println("Succesful");
  
  //pinMode (LEDPIN, OUTPUT);
  Serial.println("Setting up device as slave");
  Wire.begin(0);//starts as slave device at address 0
  Wire.onReceive(receiveEvent);
  Serial.println("Succesful");
}

void receiveEvent(int bytes){//update
  Serial.println("Starting Reciving event");
  while (1 < Wire.available()) { // loop through all but the last
    savingDataArray[cout] = (float) Wire.read(); // receive byte as a float
    cout++;
    if(cout==13){topMotor = (int) Wire.read();}
    if(cout==14){bottomMotor = (int) Wire.read();} 
  }
  boolean TransComp = Wire.read();
  cout=0;
  Serial.println("completed Reciving event");
}




void loop() {
  Serial.println("Starting loop...");
  //work with most recent update of data
  openFile("TEST.txt");
  saveToFile();
  //writeToFile("This is a test mark");
  closeFile();
  Serial.println("Succesful end loop");

}

void saveToFile(){
//  Serial.println("Saving Saving Event...");
//  writeToFile("Altitude: "+ (char) savingDataArray[0]);
//  writeToFile("Ax: "+ (char) savingDataArray[1]);
//  writeToFile("Ay: "+ (char) savingDataArray[2]);
//  writeToFile("Az: "+ (char) savingDataArray[3]);
//  writeToFile("Gx: "+ (char) savingDataArray[4]);
//  writeToFile("Gy: "+ (char) savingDataArray[5]);
//  writeToFile("Gz: "+ (char) savingDataArray[6]);
//  writeToFile("Hx: "+ (char) savingDataArray[7]);
//  writeToFile("Hy: "+ (char) savingDataArray[8]);
//  writeToFile("Hz: "+ (char) savingDataArray[9]);
//  writeToFile("Temp: "+ (char) savingDataArray[10]);
//  writeToFile("Lat: "+ (char) savingDataArray[11]);
//  writeToFile("Long: "+ (char) savingDataArray[12]);
//  writeToFile("Top Motor: "+ (char) savingDataArray[13]);
//  writeToFile("Bottom Motor: "+ (char) savingDataArray[14]);
//  writeToFile("Boolean: "+ (char) savingDataArray[15]);
//  writeToFile("Testing Data Mark");
//  Serial.println("Succesful");

    Serial.println("Saving Saving Event...");
    char const *p = "mark1";
    char m = "mark2";
  writeToFile(p);
  writeToFile(m);
  writeToFile("Ay: ");
  writeToFile("Az: ");
  writeToFile("Gx: ");
  writeToFile("Gy: ");
  writeToFile("Gz: ");
  writeToFile("Hx: ");
  writeToFile("Hy: ");
  writeToFile("Hz: ");
  writeToFile("Temp: ");
  writeToFile("Lat: ");
  writeToFile("Long: ");
  writeToFile("Top Motor: ");
  writeToFile("Bottom Motor: ");
  writeToFile("Boolean: ");
  writeToFile("Testing Data Mark");
  Serial.println("Succesful");
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
