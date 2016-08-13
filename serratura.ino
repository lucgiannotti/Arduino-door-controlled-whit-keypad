
 
//include library Password.h
#include <Password.h>;
 
Password password = Password( "xxxxxxx" ); // Set code
 

const int telecomando = 10; 
const int utelecomando = 11;
const int pulsante = 12;
const int upulsante = 13;
const int numRows = 4; // number of rows in the keypad
const int numCols = 4; // number of columns
const char keymap[numRows][numCols] = { // Define the Keymap
{ '1', '2', '3', 'A' } ,
{ '4', '5', '6', 'B' } ,
{ '7', '8', '9', 'C' } ,
{ '*', '0', '#', 'D' }
};
 
const int rowPins[numRows] = { 2, 3, 4, 5 }; // Collegamento righe
const int colPins[numCols] = { 6, 7, 8, 9 }; // Collegamento colonne
 
const int debounceTime = 20;

 
void setup() {
pinMode(10, INPUT);
pinMode(11, OUTPUT);
pinMode(12, INPUT);
pinMode(13, OUTPUT);
  
  Serial.begin(9600);
delay(200);
 
pinMode(13, OUTPUT); // green led - flash 1 time if the password is correct and you can to open the door
pinMode(12, OUTPUT); // red led - flash 5 time if access denied
pinMode(11, OUTPUT); // relay for light of keypad
pinMode(10, INPUT); //bottom to start light at keypad


for (int row = 0; row < numRows; row++) {
pinMode(rowPins[row],INPUT); // Imposta i pin delle righe come OUTPUT
digitalWrite(rowPins[row],HIGH); // Abilita le resistenze di Pull-ups
}
 
for (int column = 0; column < numCols; column++) {
pinMode(colPins[column],OUTPUT); // Imposta i pin delle righe come INPUT per la lettura
digitalWrite(colPins[column],HIGH); // Abilita le resistenze di Pull-ups
}
}
 
void loop() {

   digitalRead(telecomando);
  if (telecomando == HIGH) {     
       
    digitalWrite(utelecomando, HIGH);  
  } 
  else {
    digitalWrite(utelecomando, LOW);
    
  }
  
  
   digitalRead(pulsante);
  if (pulsante == HIGH) {     
       
    digitalWrite(upulsante, HIGH);  
  } 
  else {
   
    digitalWrite(upulsante, LOW); 
  }
  
  
  
  char key = getKey();
if( key != 0) { // Controllo che sia stato premuto un tasto valido
Serial.print("Got key ");
Serial.println(key);
delay(10);
 
switch (key) {
case 'A': checkPassword(); delay(1); break; // write  password
case 'B': password.reset(); delay(1); break; // clear buffer
default: password.append(key); delay(1); // add bottom to password
}
}
}
 
void checkPassword() {
if (password.evaluate()) { // if the password is correct...
Serial.println("Accesso Consentito"); // access ok
delay(12);
password.reset(); delay(1);
 
digitalWrite(13, HIGH); // turn on green led
delay(2000); // wait two second
digitalWrite(13, LOW); // off
 
} else {
Serial.println("Accesso Negato"); // if the password is wrong
delay(10);
password.reset(); delay(1);
 
for (int t = 0; t < 5; t++) {
digitalWrite(12, HIGH); // turn on red led
delay(100); // delay 
digitalWrite(12, LOW); // turn off
delay(100);
}
}
}
 
char getKey() {
char key = 0; // 0 indica un tasto premuto
for(int column = 0; column < numCols; column++) {
digitalWrite(colPins[column],LOW); // Attiva la colonnaorrente colonna
for(int row = 0; row < numRows; row++) { // Controlla le righe per tasto premuto
if(digitalRead(rowPins[row]) == LOW) { // E' premuto un tasto?
delay(debounceTime); // debounce
while(digitalRead(rowPins[row]) == LOW) ; // Aspetta che il tasto venga rilasciato
key = keymap[row][column]; // Ricorda il tasto che è stato premuto
}
}
digitalWrite(colPins[column],HIGH); // Disattiva la colonna corrente
}
return key; // Riporta lo stato del tasto a 0
}
