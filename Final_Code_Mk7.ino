#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//SDA = A4
//SCL = A5

const int buttonNumber = 10;             // Number of input buttons used
const int buttonPins[] = {3,4,5,6,7,8,9,10,11,13};    // Which Arduino pins assigned to button inputs
const int resetButton = 2;

int buttonState[] = {1,1,1,1,1,1,1,1,1,1};          // The current reading from the input pins
int lastButtonState[] = {1,1,1,1,1,1,1,1,1,1};      // The previous reading from the input pins
int resetState = 1;
int resetLastState = 1;
int resetCheck = 0;

int i = 0;
int j = 0;
int k = 0;

int currentState = 0;
int whilebreak = 0;  //Used to break waiting while loop
int DoublePrevent = 0;

int CursorPosition = 0;

int displayNumber[] = {0,0,0,0,0,0,0,0,0,0};
int Unpressed[] = {0,0,0,0,0,0,0,0,0,0};

void setup() {
  for (i = 0; i < buttonNumber; i++){
  pinMode(buttonPins[i], INPUT);
     }
  pinMode(resetButton,INPUT);

  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  lcd.setCursor(0,0);
  lcd.print("Team Order:");
} //Breaks void Setup



void loop() {


for (i=0; i < buttonNumber; i++){
  whilebreak = 0;
  while(whilebreak != 1){
  for (k = 0; k < buttonNumber; k++){
     DoublePrevent = 0;
     currentState = ButtonRead( buttonState, lastButtonState, k);
      if (currentState == 0){
            Unpressed[k] = 1;
          }
      
      if (currentState == 1){
            if (displayNumber[k] == 1){
              DoublePrevent = 1; 
                  } //Breaks Double Prevent if

           if (DoublePrevent == 0 && Unpressed[k] == 1){
           displayNumber[k] = 1;
           lcd.setCursor(CursorPosition,1);
           lcd.print(++k);
           CursorPosition = ++CursorPosition;
           if (k == 10){
            CursorPosition = ++CursorPosition;
              }
          k = buttonNumber;
          whilebreak = 1;
          DoublePrevent = 0;
           }  //Breaks dobule prevent if
        } //Breaks if statement
      } //Breaks for loop
      
  resetCheck = ResetButton(resetState, resetLastState);
      if (resetCheck == 1){
        lcd.clear();
        lcd.setCursor(0,0);
         lcd.print("Team Order:");
        whilebreak = 1;
        DoublePrevent = 0;
        CursorPosition = 0;
        resetCheck = 0;
         for (j = 0; j < buttonNumber; j++){
              buttonState[j] = 1;
              lastButtonState[j] = 1;
              displayNumber[j] = 0;
              Unpressed[j] = 0;
            } //Breaks reset for loop 
         i = buttonNumber; 
      } //Breaks the if resetCheck
     
  } //Breaks while loop
} //Breaks master for loop

 resetCheck = ResetButton(resetState, resetLastState);
      if (resetCheck == 1){
        lcd.clear();
        lcd.setCursor(0,0);
         lcd.print("Team Order:");
        whilebreak = 1;
        DoublePrevent = 0;
        CursorPosition = 0;
        resetCheck = 0;
         for (j = 0; j < buttonNumber; j++){
              buttonState[j] = 1;
              lastButtonState[j] = 1;
              displayNumber[j] = 0;
              Unpressed[j] = 0;
            } //Breaks reset for loop 
         i = buttonNumber; 
      } //Breaks the if resetCheck
  
} //Breaks void loop







int ButtonRead( int buttonState[], int lastButtonState[], int k){
  unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// read the state of the switch into a local variable:
  int reading = digitalRead(buttonPins[k]);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState[k]) {
    // reset the debouncing timer
    lastDebounceTime = millis();

    while((millis() - lastDebounceTime) < debounceDelay) {  //Makes it wait until debounce time is over
                }  //Breaks waiting while loop       
    if (reading != buttonState[k]) {
      buttonState[k] = reading;

      // only toggle the LED if the new button state is LOW
      if (buttonState[k] == LOW) {
        return 1;
      } //Breaks buttonState High if check
    } //Breaks second if

  } //Break first if

     else {
        return 0;
        } //Breaks else 
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[k] = reading;
} //Break function









int ResetButton( int resetState, int resetLastState){
  unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// read the state of the switch into a local variable:
  int reading = digitalRead(resetButton);

  // If the switch changed, due to noise or pressing:
  if (reading != resetLastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  
  while((millis() - lastDebounceTime) < debounceDelay) {  //Makes it wait until debounce time is over
                }  //Breaks waiting while loop       
    if (reading != resetState) {
      resetState = reading;

      // only toggle the LED if the new button state is LOW
      if (resetState == LOW) {
        return 1;
      } //Breaks buttonState High if check
    } //Breaks second if

  } //Break first if

     else {
        return 0;
        } //Breaks else 
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  resetLastState = reading;
} //Break function
