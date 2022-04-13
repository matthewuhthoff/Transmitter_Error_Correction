String putOut = "";
bool a[16];
bool first[11];
int boxNumber, leftOver, stringLength, otherStringLength;
bool p1, p2, p4, p8, test;




char alphabet[33] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', '!', '<', '+', '-'};
int buttonState;
String text = "ayo";
char temp;
int tempInBin;
const int led = 13; // the pin the LED is connected to
const int buttonPin = 2; 
int letternum = text.length();
String letterInBin;
String textInBin = "";

const int interval = 500;

void setup() {
  Serial.begin(9600); // speed of internal on arduino, don't know why but standard is 9600 bits/second
  pinMode(buttonPin, INPUT);

  pinMode(led, OUTPUT);// set the led output on arduino control, here mine is set to the 13 pin

  for (int i = 0; i < letternum; i++)
  {
    temp = text[i];// store char in temp
    for (int k = 0; k < 32; k++)
    {
      if (temp == alphabet[k]) // run through the alphabet and get numerical value for the depending letter
      {
        tempInBin = (k + 1);// +1 cause dealing with 0 is wack

        letterInBin = decToBin(tempInBin); // use function to go drom decimal to binary
        textInBin += letterInBin; //add that binary string into the complete message in binary

        break;
      }
    }


    
  }
  stringLength = textInBin.length();
  boxNumber = stringLength / 11;
  leftOver = stringLength % 11;

  for (int z = 0; z < boxNumber; z++)
  {
    for (int i = 0; i < 11; i++)
    {
      if (textInBin[(z*11)+i] == '1')
      {
        first[i] = 1;
      }
      else
        first[i] = 0;
    }
  }
  p1 = first[1] ^ first[4] ^ first[8] ^ first[0] ^ first[3] ^ first[6] ^ first[10]; // get answers to 4 questions
  p2 = first[2] ^ first[5] ^ first[9] ^ first[0] ^ first[3] ^ first[6] ^ first[10];
  p4 = first[1] ^ first[2] ^ first[3] ^ first[7] ^ first[8] ^ first[9] ^ first[10];
  p8 = first[4] ^ first[5] ^ first[6] ^ first[7] ^ first[8] ^ first[9] ^ first[10];
       
  a[1] = p1; // add answers to a
  a[2] = p2;
  a[4] = p4;
  a[8] = p8;
       
  int counter = 0;
  int firstCounter = 0;
  while (true) // set a with input
  {
      if (counter == 0 || counter == 1 || counter == 2 || counter == 4 || counter == 8)
      {
          counter++;
          continue;
      }
      a[counter] = first[firstCounter];
      firstCounter ++;
      counter ++;
      if (firstCounter == 11)
          break;
  }
  test = a[1]; // run through inter thing for first bit
  for (int i = 1; i < 15; i++)
     {
        test = test ^ a[i+1];
     }
  a[0] = test; // set first bit

  for (int i = 0; i < 16; i++)
  {
     if (a[i] == 1)
         putOut += '1';
     else
         putOut += '0';
  }
  for (int r = (stringLength - leftOver); r < stringLength; r++)
  {
      putOut += textInBin[r];
  }   

  otherStringLength = putOut.length();
  char finale[otherStringLength];

  for (int i = 0; i < boxNumber; i++)
  {
    for (int k = 0; k < 16; k++)
    {
      finale[(k*boxNumber) + i] = putOut[k + (i*16)];
    }
  }
  for (int k = otherStringLength - leftOver; k < otherStringLength; k++)
  {
    finale[k] = putOut[k];
  }
  putOut = "";

  Serial.println(text);
  Serial.println(textInBin);
  for (int i = 0; i < otherStringLength; i++)
  {
    putOut += finale[i];
  }
  Serial.println(putOut);
  putOut += "11011011011";
  Serial.println(putOut);
  Serial.println(putOut.length());
}

void loop() {
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);
  if (buttonState == HIGH)
  {
    digitalWrite(led, HIGH);
    delay(interval);
    for (int k = 0; k < putOut.length(); k++) // 5 bits for every letter so *5
    {
      if (putOut[k] == '0')
      {
        digitalWrite(led, LOW);
      }
  
     if (putOut[k] == '1')
      {
        Serial.println("+++++++++++");
        digitalWrite(led, HIGH);
     }
      delay(interval); // delay set to 500 so its visible with the human eye, this can go down until the receiver no longer works

    }
  digitalWrite(led, LOW);
    



    
  }



}


String decToBin(int x) 
{
  int zeroes = String(x,BIN).length();
  String myStr, finalBin;
  for (int i = 0; i < zeroes; i++)
  {
    myStr = myStr+ "0";
  }
  myStr = myStr + String(x,BIN);

  if (myStr.length() == 2)
  {
    finalBin = "000" + myStr;
  }

  else if(myStr.length() == 4)
  {
    finalBin = "0" + myStr;
  }
  
  else if(myStr.length() == 6)
  {
    finalBin = myStr.substring(1);
  }
  
  else if(myStr.length() == 8)
  {
    finalBin = myStr.substring(3);
  }
  
  else if(myStr.length() == 10)
  {
    finalBin = myStr.substring(5);
  }
  

  return finalBin;
}
