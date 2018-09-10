// Original code by Joey Meyer and Chase Cooley and used with kind permission

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Tone.h>

Tone tone1;

int Scount = 10; // count seconds (change this to the number of seconds to start from
int Mcount = 5; // count minutes (change this to the number of minutes you want to start from)
int Hcount = 0; // count hours
int DefuseTimer = 0; // set timer to 0

long secMillis = 0; // store last time for second add
long interval = 1000; // interval for seconds

char password[4]; // number of characters in our password
int currentLength = 0; //defines which number we are currently writing
int i = 0; 
char entered[4];

int ledPin = 4; //red led
int ledPin2 = 3; //yellow led
int ledPin3 = 2; //green led

LiquidCrystal lcd(7,8,10,11,12,13); // the pins we use on the LCD

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, A5, A4, A2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A1, A0, A3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
  pinMode(ledPin, OUTPUT); // sets the digital pin as output
  pinMode(ledPin2, OUTPUT); // sets the digital pin as output
  pinMode(ledPin3, OUTPUT); // sets the digital pin as output
  tone1.begin(9);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Code: ");
  while (currentLength < 4)
  {
    lcd.setCursor(currentLength + 6, 1);
    lcd.cursor();
    char key = keypad.getKey();
    key == NO_KEY;
    if (key != NO_KEY)
    {
      if ((key != '*')&&(key != '#'))
      { 
      lcd.print(key);
      password[currentLength] = key;
      currentLength++;
      tone1.play(NOTE_C6, 200);
      }
    }
  }

  if (currentLength == 4)
  {
    delay(500);
    lcd.noCursor();
    lcd.clear();
    lcd.home();
    lcd.print("You've Entered: ");
    lcd.setCursor(6,1);
    lcd.print(password[0]);
    lcd.print(password[1]);
    lcd.print(password[2]);
    lcd.print(password[3]);

    tone1.play(NOTE_E6, 200);
    delay(3000);
    lcd.clear();
    currentLength = 0;
  }
}

void loop()
{
  timer();
  char key2 = keypad.getKey(); // get the key
  
  if (key2 == '*')
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Code: ");
      
      while (currentLength < 4)
        {
          
          timer();
          
          char key2 = keypad.getKey(); 
          if (key2 == '#')
            {
              currentLength = 0;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Code: ");
            }
          else                  
          if (key2 != NO_KEY)    
            {
              
              lcd.setCursor(currentLength + 7, 0);
              lcd.cursor();
              
              lcd.print(key2);
              entered[currentLength] = key2;
              currentLength++;
              tone1.play(NOTE_C6, 200);
              delay(100);
              lcd.noCursor();
              lcd.setCursor(currentLength + 6, 0);
              lcd.print("*");
              lcd.setCursor(currentLength + 7, 0);
              lcd.cursor();
            }
        }

      if (currentLength == 4) 
        {
          if (entered[0] == password[0] && entered[1] == password[1] && entered[2] == password[2] && entered[3] == password[3])
            {
              lcd.noCursor();
              lcd.clear();
              lcd.home();
              lcd.print("Bomb Defused");
              currentLength = 0;
              digitalWrite(ledPin3, HIGH);
              delay(2500);
              lcd.setCursor(0,1);
              lcd.print("Reset the Bomb");
              delay(1000000);
            }
      else
        {
          lcd.noCursor();
          lcd.clear();
          lcd.home();
          lcd.print("Wrong Password!");
    
          if (Hcount > 0)
            {
              Hcount = Hcount - 1;
            }
    
          if (Mcount > 0)
            {
              Mcount = Mcount - 59;
            }
          if (Scount > 0)
            {
              Scount = Scount - 59;
            }
        delay(1500);
        currentLength = 0;
  
        }
      }  
    }
}

void timer()
{
  Serial.print(Scount);
  Serial.println();
  
  if (Hcount <= 0)
  {
    if ( Mcount < 0 )
    {
      lcd.noCursor();
      lcd.clear();
      lcd.home();
      lcd.print("The Bomb Has ");
      lcd.setCursor (0,1);
      lcd.print("Exploded!");
      
      while (Mcount < 0) 
      {
        digitalWrite(ledPin, HIGH); // sets the LED on
        tone1.play(NOTE_A2, 90);
        delay(100); 
        digitalWrite(ledPin, LOW); // sets the LED off
        tone1.play(NOTE_A2, 90);
        delay(100); 
        digitalWrite(ledPin2, HIGH); // sets the LED on
        tone1.play(NOTE_A2, 90);
        delay(100); 
        digitalWrite(ledPin2, LOW); // sets the LED off
        tone1.play(NOTE_A2, 90);
        delay(100); 
        digitalWrite(ledPin3, HIGH); // sets the LED on
        tone1.play(NOTE_A2, 90);
        delay(100); 
        digitalWrite(ledPin3, LOW); // sets the LED off
        tone1.play(NOTE_A2, 90);
        delay(100);
      }
    } 
  }

  lcd.setCursor (0,1); // sets cursor to 2nd line
  lcd.print ("Timer:");

  if (Hcount >= 10)
    {
      lcd.setCursor (7,1);
      lcd.print (Hcount);
    }
  if (Hcount < 10) 
    {
      lcd.setCursor (7,1);
      lcd.write ("0");
      lcd.setCursor (8,1);
      lcd.print (Hcount);
    }

  lcd.print (":");

  if (Mcount >= 10)
    {
      lcd.setCursor (10,1);
      lcd.print (Mcount);
    }
  if (Mcount < 10) 
    {
      lcd.setCursor (10,1);
      lcd.write ("0");
      lcd.setCursor (11,1);
      lcd.print (Mcount);
    }
    
  lcd.print (":");

  if (Scount >= 10) 
    {
      lcd.setCursor (13,1);
      lcd.print (Scount);
    }
  if (Scount < 10) 
    {
      lcd.setCursor (13,1);
      lcd.write ("0");
      lcd.setCursor (14,1);
      lcd.print (Scount);
    }

  if (Hcount <0) 
    {
      Hcount = 0; 
    }

  if (Mcount <0) 
    {
      Hcount --; 
      Mcount = 59; 
    }

  if (Scount <1) // if 60 do this operation
    {
      Mcount --; // add 1 to Mcount
      Scount = 59; // reset Scount
    }

  if (Scount > 0) // do this oper. 59 times
    {
      unsigned long currentMillis = millis();
  
      if(currentMillis - secMillis > interval) 
        {
          tone1.play(NOTE_G5, 200);
          secMillis = currentMillis;
          Scount --; // add 1 to Scount
          digitalWrite(ledPin2, HIGH); // sets the LED on
          delay(10); // waits for a second
          digitalWrite(ledPin2, LOW); // sets the LED off
          delay(10); // waits for a second
          
        }
    }
}





