#include <microDS3231.h>
MicroDS3231 rtc;

#define A 2;
#define F 3;
#define B 4;
#define D 5;
#define C 6;
#define E 7;
#define G 8;

#define D1 9;
#define D2 10;
#define D3 11;
#define D4 12;

#define BUTTON 13;

boolean lastButton = LOW;

const int MODES_COUNT = 3;
const char* MODES[MODES_COUNT] = { "time", "date", "temp" };
int modeIndex = 0;

void setup()
{
  Serial.begin(9600);
  rtc.begin();
  
  // rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);

  pinMode(A,OUTPUT);  
  pinMode(F,OUTPUT); 
  pinMode(B,OUTPUT); 
  pinMode(D,OUTPUT); 
  pinMode(C,OUTPUT);
  pinMode(E,OUTPUT); 
  pinMode(G,OUTPUT);  

  pinMode(D1,OUTPUT);  
  pinMode(D2,OUTPUT);  
  pinMode(D3,OUTPUT);  
  pinMode(D4,OUTPUT);  

  pinMode(BUTTON,INPUT);
}   

void loop()
{
  currentButton = debounce(lastButton);

  if (lastButton == LOW && currentButton == HIGH)
  {
    changeMode();
  }

  switch (MODES[mode])
  {
  case "time":
    int hours = rtc.getHours();
    int minutes = rtc.getMinutes();
    int hour1 = hours / 10;
    int hour2 = hours % 10;
    int minutes1 = minutes / 10;
    int minutes2 = minutes % 10;

    showNumbers(hour1, hour2, minutes1, minutes2);
    break;

  case "date":
    int day = rtc.getDay(); 
    int day1 = day / 10;
    int day2 = day % 10;
    int month = rtc.getMonth(); 
    int month1 = month / 10;
    int month2 = month % 10;

    showNumbers(
      day1, 
      day2,
      month1, 
      month2
    );
    break;
  
  case "temp":
    int temp = rtc.getTemperatureFloat(); 
    int temp1 = temp / 10;
    int temp2 = temp % 10;

    showNumbers(
      0, 
      temp < 0 ? -1 : 0,
      temp1, 
      temp2
    );
    break;
  
  default:
    break;
  }
}

void changeMode()
{
  modeIndex++;
  modeIndex = modeIndex % MODES_COUNT;
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);

  if (last != current)
  {
    delay(5);
    current = digitalRead(BUTTON);
    return current;
 }
}

void showNumbers(int firstLamp, int secondLamp, int thirdLamp, int quadrupleLamp)
{
  clearLEDs();
  pickDigit(0); 
  picSymbol(quadrupleLamp);
  delay(5);

  clearLEDs();
  pickDigit(1); 
  picSymbol(thirdLamp);
  delay(5);

  clearLEDs();
  pickDigit(2); 
  picSymbol(secondLamp);
  delay(5);

  clearLEDs();
  pickDigit(3); 
  picSymbol(firstLamp);
  delay(5);

  clearLEDs();
}

void pickDigit(int x) 
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  switch (x) 
  {
    case 0: digitalWrite(D1, HIGH);  
      break;
    case 1: digitalWrite(D2, HIGH);  
      break;
    case 2: digitalWrite(D3, HIGH);  
      break;
    default: digitalWrite(D4, HIGH); 
      break;
  }
}

void picSymbol(int x) 
{
  switch (x) 
  {
    default: zero();   
      break;
    case 1: one();     
      break;
    case 2: two();     
      break;
    case 3: three();  
      break;
    case 4: four();    
      break;
    case 5: five();    
      break;
    case 6: six();       
      break;
    case 7: seven(); 
      break;
    case 8: eight();  
      break;
    case 9: nine();  
      break;
    case -1: minus();  
      break;
  }
}

void clearLEDs() 
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void zero() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void one() 
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void two() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void three() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void four() 
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void five() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void six() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void seven() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void eight() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void nine() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void minus() 
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}