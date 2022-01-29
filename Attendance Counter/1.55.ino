//Changed buzzer tone.
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>

const int tx=9;
const int rx=10;
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
SoftwareSerial rfid(rx,tx);
int attended[25] = { 0 };
const int view_adjust = A3;
const int add_delete = A2;
const int reset = A5;
const int buzz = A4;
const int authorized_tag[]={2,48,70,48,48,52,52,68,53,56,68,49,51,3};//only one authorized tag allowed to add or remove
int attendance = 0;//attendance count diplayed in view mode
int buffer[14];
char hex[14];//stores the tag in hex
int num,value,trash;//used for reading,error checking, and cleaning the buffer
int count = int(EEPROM[250]);//total number of students registered
int buffer_index=0;//used in reading
long chk,chksum;


void setup() {
  pinMode(view_adjust, INPUT);
  pinMode(add_delete, INPUT);
  pinMode(reset, INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(tx,OUTPUT);
  pinMode(rx,INPUT);
  Serial.begin(9600);
  rfid.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  start: 

  while(rfid.available()>0)trash=rfid.read();//cleans the buffer(used many times in the code)


//=================================================================================VIEW MODE==================================================================================
  while ((digitalRead(view_adjust)==LOW)&&(digitalRead(reset)==LOW)) {//view condition

    lcd.print("Attendance:");
    lcd.print(attendance);
    lcd.setCursor(0,1);
    lcd.print("Absent:");lcd.print(count-attendance);
    lcd.home();

    view_reading:
    while (rfid.available() == 0)if(!((digitalRead(view_adjust)==LOW)&&(digitalRead(reset)==LOW))){lcd.clear();goto start;}
    value=rfid.read();
    if(value==-1){goto view_reading;}
    if (value==2){buffer_index=0;buffer[buffer_index]=value;goto view_reading;}
    if (value==3){buffer_index++;buffer[buffer_index]=value;goto view_done;}
    if(!(value==-1)){buffer_index++;buffer[buffer_index]=value;}
    view_done:
    
    if(buffer_index!=13) goto view_reading;//in case it didnt read the full tag or read more than 14 bits
    //checksum
    chk=0;
    for(int i=0;i<14;i++){hex[i]=buffer[i];}
    chksum=hexstr_to_value(&hex[11]);
    for(int i=1;i<11;i+=2){
      chk ^= hexstr_to_value(hex+i);
      }
    if(chksum!=chk||buffer[0]!=2||buffer[13]!=3){goto view_reading;}

    for(int i=0;i<14;i++) Serial.print(buffer[i]);
    Serial.print('\n');
    num = match(buffer);
    if(check_authorized(buffer)){lcd.clear();lcd.print(" Hi");tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read(); lcd.clear();}
    else if (num == -1) { lcd.clear(); lcd.print("Not Registered"); tone(buzz,500); delay(300);noTone(buzz);delay(700);while(rfid.available()>0)trash=rfid.read(); lcd.clear(); }
    else if (attended[num] == 1) { lcd.clear(); lcd.print("Attended"); tone(buzz,500); delay(300);noTone(buzz);delay(700);while(rfid.available()>0)trash=rfid.read(); lcd.clear(); }
    else if (attended[num] == 0) { attendance++; attended[num] = 1; lcd.clear(); lcd.print("No. "); lcd.print(num); tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read(); lcd.clear(); }

  }


//======================================================================== ASSIGN MODE ====================================================================== 
  while ((digitalRead(view_adjust) == HIGH)&&(digitalRead(add_delete) == LOW)&&(digitalRead(reset)==LOW)) {//assign condition

    authorizeA:
    lcd.print("Assignment mode");
    lcd.setCursor(0,1);
    lcd.print("Authorization");
    lcd.home();
    
    authorizeA_reading:
    while (rfid.available() == 0) if(!((digitalRead(view_adjust) == HIGH)&&(digitalRead(add_delete) == LOW)&&(digitalRead(reset)==LOW))){lcd.clear();goto start;}
    value=rfid.read();
    if(value==-1){goto authorizeA_reading;}
    if (value==2){buffer_index=0;buffer[buffer_index]=value;goto authorizeA_reading;}
    if (value==3){buffer_index++;buffer[buffer_index]=value;goto authorizeA_done;}
    if(!(value==-1)){buffer_index++;buffer[buffer_index]=value;}
    authorizeA_done:
    
    if(buffer_index!=13) goto authorizeA_reading;
    chk=0;
    for(int i=0;i<14;i++){hex[i]=buffer[i];}
    chksum=hexstr_to_value(&hex[11]);
    for(int i=1;i<11;i+=2){
      chk ^= hexstr_to_value(hex+i);
      }
    if(chksum!=chk||buffer[0]!=2||buffer[13]!=3){goto authorizeA_reading;}
 
    if(!check_authorized(buffer)){lcd.setCursor(0,1);lcd.print("Access Denied");tone(buzz,500); delay(300);noTone(buzz);delay(700);while(rfid.available()>0)trash=rfid.read();lcd.clear();goto authorizeA;}
    lcd.clear();lcd.print("Authorized");tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read();lcd.clear();



    assign_start:
    lcd.print("Assignment Mode");
    lcd.setCursor(0, 1);
    lcd.print("Pass a card");
    lcd.home();
    delay(2000);

    assign_reading:
    while (rfid.available() == 0) if(!((digitalRead(view_adjust) == HIGH)&&(digitalRead(add_delete) == LOW)&&(digitalRead(reset)==LOW))){lcd.clear();goto start;}
    
    value=rfid.read();
    if(value==-1){goto assign_reading;}
    if (value==2){buffer_index=0;buffer[buffer_index]=value;goto assign_reading;}
    if (value==3){buffer_index++;buffer[buffer_index]=value;goto assign_done;}
    if(!(value==-1)){buffer_index++;buffer[buffer_index]=value;}
    assign_done:
    if(buffer_index!=13) goto assign_reading;
    chk=0;
    for(int i=0;i<14;i++){hex[i]=buffer[i];}
    chksum=hexstr_to_value(&hex[11]);
    for(int i=1;i<11;i+=2){
      chk ^= hexstr_to_value(hex+i);
      }
    if(chksum!=chk||buffer[0]!=2||buffer[13]!=3){goto assign_reading;}
    while(rfid.available()>0)trash=rfid.read();
    
    num = match(buffer);
    if (check_authorized(buffer)){lcd.clear();lcd.print("Done");tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read();lcd.clear();goto authorizeA;}
    else if(count>=25){lcd.clear();lcd.print("Max No. exceeded");tone(buzz,500); delay(300);noTone(buzz);delay(700);while(rfid.available()>0)trash=rfid.read();lcd.clear();}
    else if (num >= 0) { lcd.clear(); lcd.print("Already assigned"); tone(buzz,500); delay(300);noTone(buzz);delay(700);while(rfid.available()>0)trash=rfid.read(); lcd.clear(); }
    else if (num < 0) { 
      int j=0;
      for(j=0;j<250;j+=10){
        if (EEPROM[j]==0)break;
        }
      assign(buffer, j/10);
      EEPROM[250]++;count = int(EEPROM[250]);lcd.clear(); lcd.print("No. ");lcd.print(j/10);tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read(); lcd.clear(); }
    goto assign_start;
  }




  //=================================================================delete mode=======================================================================================
  while ((digitalRead(view_adjust) == HIGH) && (digitalRead(add_delete) == HIGH) && (digitalRead(reset) == LOW)) {//delete condition

    authorizeD:
    lcd.print("Delete mode");
    lcd.setCursor(0,1);
    lcd.print("Authorization");
    lcd.home();
    
    authorizeD_reading:
      while (rfid.available() == 0) if(!((digitalRead(view_adjust) == HIGH)&&(digitalRead(add_delete) == HIGH)&&(digitalRead(reset)==LOW))){lcd.clear();goto start;}
      value=rfid.read();
    if(value==-1){goto authorizeD_reading;}
    if (value==2){buffer_index=0;buffer[buffer_index]=value;goto authorizeD_reading;}
    if (value==3){buffer_index++;buffer[buffer_index]=value;goto authorizeD_done;}
    if(!(value==-1)){buffer_index++;buffer[buffer_index]=value;}
    authorizeD_done:
    if(buffer_index!=13) goto authorizeD_reading;
    chk=0;
    for(int i=0;i<14;i++){hex[i]=buffer[i];}
    chksum=hexstr_to_value(&hex[11]);
    for(int i=1;i<11;i+=2){
      chk ^= hexstr_to_value(hex+i);
      }
    if(chksum!=chk||buffer[0]!=2||buffer[13]!=3){goto authorizeD_reading;}
    
    if(!check_authorized(buffer)){lcd.setCursor(0,1);lcd.print("Access Denied");tone(buzz,500); delay(300);noTone(buzz);delay(700);while(rfid.available()>0)trash=rfid.read();lcd.clear();goto authorizeD;}
    lcd.clear();lcd.print("Authorized");tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read();lcd.clear();


    
    delete_start:
    lcd.print("Remove Mode");
    lcd.setCursor(0, 1);
    lcd.print("Pass a card");
    lcd.home();
    delay(2000);

    delete_reading:
    while (rfid.available()==0)if(!((digitalRead(view_adjust) == HIGH) && (digitalRead(add_delete) == HIGH) && (digitalRead(reset) == LOW))){lcd.clear();goto start;}
    value=rfid.read();
    if(value==-1){goto delete_reading;}
    if (value==2){buffer_index=0;buffer[buffer_index]=value;goto delete_reading;}
    if (value==3){buffer_index++;buffer[buffer_index]=value;goto delete_done;}
    if(!(value==-1)){buffer_index++;buffer[buffer_index]=value;}  
    delete_done:
    
    if(buffer_index!=13) goto delete_reading;
    chk=0;
    for(int i=0;i<14;i++){hex[i]=buffer[i];}
    chksum=hexstr_to_value(&hex[11]);
    for(int i=1;i<11;i+=2){
      chk ^= hexstr_to_value(hex+i);
      }
    if(chksum!=chk||buffer[0]!=2||buffer[13]!=3){goto delete_reading;}
    while(rfid.available()>0)trash=rfid.read();

    
    num = match(buffer);
    if (check_authorized(buffer)){lcd.clear();lcd.print("Done");tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read();lcd.clear();goto authorizeD;}
    else if (num < 0) { lcd.clear(); lcd.print("Not Found"); tone(buzz,500); delay(300);noTone(buzz);delay(700);while(rfid.available()>0)trash=rfid.read(); lcd.clear(); }
    else if (num >= 0) { del(num); lcd.clear(); lcd.print("No. ");lcd.print(num);EEPROM[250]--;count = int(EEPROM[250]);tone(buzz,1000); delay(100);noTone(buzz);delay(900);while(rfid.available()>0)trash=rfid.read(); lcd.clear(); }
    goto delete_start;

  }

//=============================================================== RESET ===============================================================================
  while (digitalRead(reset)==HIGH) {//reset codition
    attendance = 0;
    count=0;
    for (int i = 0; i <= 250; i++) EEPROM[i] = 0;
    lcd.clear();lcd.print("Memory Erased");tone(buzz,1000); delay(900);noTone(buzz);delay(100);lcd.clear();
  }

    delay(2000);
}


//================================================================ FUNCTIONS ===========================================================================

void assign(int buffer[14], int n) {
  for (int i = 0; i<10; i++) {
    EEPROM[(n*10)+i] = char(buffer[i+1]);
  }
}

int match(int buffer[14]) {//returns the student No. or -1 if not registered
  int j;
  for (int i = 0; i<250; i+=10) {
    j = 0;
    while (j<10) {
      if (buffer[1+j] != int(EEPROM[i+j])) break;
      if (j >= 9) return (i/10);
      j++;
    }
  }
  return -1;
}

bool check_authorized(int buffer[14]){//returns true if the tag is the authorized one and false otherwise
  int i=0;
    while (i<14) {
      if (buffer[i] != authorized_tag[i]) break;
      if (i >= 13) return true;
      i++;
    }
  return false;
  }

void del(int n) {
  //removes a student
  for (int i = 0; i<10; i++) {
    EEPROM[(n*10)+i] = 0;
  }
}

long hexstr_to_value(char *str) { // converts a hexadecimal value (encoded as ASCII string) to a numeric value
  char* copy = malloc((sizeof(char) * 2) + 1); 
  memcpy(copy, str, sizeof(char) * 2);
  copy[2] = '\0'; 
  // the variable "copy" is a copy of the parameter "str". "copy" has an additional '\0' element to make sure that "str" is null-terminated.
  long value = strtol(copy, NULL, 16);  // strtol converts a null-terminated string to a long value
  free(copy); // clean up 
  return value;    
}
