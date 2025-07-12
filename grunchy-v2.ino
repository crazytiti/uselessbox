/*
 * Grunchy box
 * useless box un peu vener
 */

// PIN
#define servo_pin 3
#define inter_pin 4
#define led_pin 1

// configuration des positions
#define pos_inter 160
#define pos_hesite 135
#define pos_entreouvre 70
#define pos_hide 65
#define pos_repos 55

#define max_move 57
const int moves[]={0,4,3,6,6,0,6,2,5,2,5,2,3,6,6,4,0,6,6,1,3,2,2,6,5,1,1,2,1,3,0,2,4,6,2,5,2,6,6,2,1,5,4,4,3,3,0,0,4,5,1,6,1,4,6,2,1};

#include "SimpleServo.h"
#include <EEPROM.h>

SimpleServo myservo;  // create servo object to control a servo
byte pos = 0;
int move_nb = 0;  //numéro du mouvement
char var_repos = pos_repos;

void setup() {
  pinMode(inter_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, 1);
  myservo.attach(servo_pin);  // attaches the servo 
  myservo.setMaximumDegrees(180);
  myservo.setMillisPer60Degrees(150);
  myservo.setMaximumMillis(250);
  //randomSeed(analogRead(1));  
  //move_nb = random(0,max_move);
  pos = EEPROM.read(0);
  if (pos > max_move) {
    pos = 0;
  }
  move_nb = moves[pos];
  pos++;
  EEPROM.write(0,pos);
}

void loop() {
  delay(100);
  myservo.write(pos_repos);
  delay(10);
        
  /*
  digitalWrite(led_pin, 0);
  delay(300);
  for(pos = 0; pos < move_nb; pos++){
    digitalWrite(led_pin, 1);
    delay(300);
    digitalWrite(led_pin, 0);
    delay(300);
  }*/
  reponse(move_nb);
  //reponse(0);
}

void reponse(int move_nb){
  switch (move_nb){
    case 0: //classique
      myservo.write(pos_inter);
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
      break;
      
    case 1: //marque 1 pause
      myservo.write(pos_hesite);
      delay(700);
      myservo.write(pos_inter);
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
      break;
      
    case 2: //hesite
      myservo.write(pos_hesite);
      delay(700);
      myservo.write(pos_entreouvre);
      delay(700);
      myservo.write(pos_inter);
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
      break;
      
    case 3: //à couvert
      myservo.write(pos_entreouvre);
      delay(700);
      myservo.write(pos_hide);
      delay(700);
      myservo.write(pos_entreouvre);
      delay(700);
      myservo.write(pos_inter);
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
      break;

    case 4: //revient et surveille
      myservo.write(pos_hesite);
      delay(700);
      myservo.write(pos_inter);
      myservo.write(pos_entreouvre);
      delay(700);
      myservo.write(pos_hide);
      delay(700);
      myservo.write(pos_hesite);
      delay(700);
      while(digitalRead(inter_pin)){
        myservo.write(pos_inter);
      }
      break;

      case 5: //patiente
      delay(4200);
      myservo.write(pos_inter);
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
      break;

      case 6: //parkinson
      myservo.write(pos_hesite);
      myservo.write(pos_entreouvre);
      myservo.write(pos_hide);
      myservo.write(pos_entreouvre);
      myservo.write(pos_hide);
      myservo.write(pos_hesite);
      myservo.write(pos_inter);
      myservo.write(pos_hesite);
      myservo.write(pos_entreouvre);
      myservo.write(pos_hide);
      myservo.write(pos_entreouvre);
      myservo.write(pos_hide);
      myservo.write(pos_hesite);
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
      break;
      
    default:
      myservo.write(pos_inter);
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
      while(1){
        myservo.write(pos_repos);
        delay(7);
      }
      if(digitalRead(inter_pin)){myservo.write(pos_inter+10);}
      if(digitalRead(inter_pin)){myservo.write(pos_inter+20);}
  }
  // retour à l'arret
  while(1){
    myservo.write(var_repos);
    var_repos-=1;
    delay(7);
  }
}
