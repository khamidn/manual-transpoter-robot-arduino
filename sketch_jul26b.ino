
#include <PS2X_lib.h> 
#include <Servo.h> 
//MOTOR BELAKANG//
#define dirka_bel   28
#define pwmka_bel   12
#define pwmki_bel   11
#define dirki_bel   26

//MOTOR DEPAN
#define dirka_dep   30
#define pwmka_dep   9
#define pwmki_dep   10
#define dirki_dep   32

//////////////////////////////PIN SERVO//////////////////////////////
Servo angkatKanan;
Servo jepitKanan;
Servo angkatKiri;
Servo jepitKiri;
Servo angkatBelakang;
Servo jepitBelakang;



PS2X ps2x;
 
int countJepitKanan=0,countJepitKiri=0,countAngkatKanan=0,countAngkatKiri=0;
int countR1=0, countR2=0,countL1=0;;
int   error   = 0;
byte  type    = 0;
byte  vibrate = 0;
int   set_pwm = 100,set_MaxPwm=255, pwm_belok=130,pwm_mundur=-180;

int RX,RY,LX,LY;
int L1,L2,R1,R2;
int tombol_atas,tombol_bawah,tombol_kanan,tombol_kiri;
int kotak,X,segitiga,bulet;



void motBel(int kiri, int kanan){
  if(kiri>=0){digitalWrite(dirki_bel,LOW);}
         else{digitalWrite(dirki_bel,HIGH);kiri=255+kiri;}
              analogWrite(pwmki_bel,abs(kiri));
                   
  if(kanan>=0){digitalWrite(dirka_bel,LOW);}
          else{digitalWrite(dirka_bel,HIGH);kanan=255+kanan;}
               analogWrite(pwmka_bel,abs(kanan));
  }

void motDep(int kiri, int kanan){
  if(kiri>=0){digitalWrite(dirki_dep,LOW);}
         else{digitalWrite(dirki_dep,HIGH);kiri=255+kiri;}
              analogWrite(pwmki_dep,abs(kiri));
                   
  if(kanan>=0){digitalWrite(dirka_dep,LOW);}
          else{digitalWrite(dirka_dep,HIGH);kanan=255+kanan;}
               analogWrite(pwmka_dep,abs(kanan));
  }

void setup(){
 Serial.begin(57600);

  pinMode(dirka_bel,OUTPUT);
  pinMode(pwmka_bel,OUTPUT);
  pinMode(pwmki_bel,OUTPUT);
  pinMode(dirki_bel,OUTPUT);

  pinMode(dirka_dep,OUTPUT);
  pinMode(pwmka_dep,OUTPUT);
  pinMode(pwmki_dep,OUTPUT);
  pinMode(dirki_dep,OUTPUT);


  jepitKanan.attach(2);
  angkatKanan.attach(3);
  angkatKiri.attach(6);
  jepitKiri.attach(7);
  angkatBelakang.attach(5);
  jepitBelakang.attach(4);

  angkatKiri.write(125);
  angkatKanan.write(35);
  jepitKanan.write(45);
  jepitKiri.write(95);
  angkatBelakang.write(35);
  jepitBelakang.write(40);
  
 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
delay(350);
error = ps2x.config_gamepad(52,51,53,50, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 if(error == 0){
   Serial.println("Found Controller, configured successful");
 
 }

  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

   //Serial.print(ps2x.Analog(1), HEX);

   type = ps2x.readType();
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       
     }

     

}


void loop()
{

error = 0;type = 1;  
ps2x.read_gamepad(false, vibrate);

RX=ps2x.Analog(PSS_RX);                   RY=ps2x.Analog(PSS_RY); 
LX=ps2x.Analog(PSS_LX);                   LY=ps2x.Analog(PSS_LY);
L1=ps2x.Button(PSB_L1);                   L2=ps2x.Button(PSB_L2); 
R1=ps2x.Button(PSB_R1);                   R2=ps2x.Button(PSB_R2);
tombol_atas=ps2x.Button(PSB_PAD_UP);      tombol_bawah=ps2x.Button(PSB_PAD_DOWN);                           
tombol_kanan=ps2x.Button(PSB_PAD_RIGHT);  tombol_kiri=ps2x.Button(PSB_PAD_LEFT);
kotak=ps2x.Button(PSB_PINK);             bulet=ps2x.Button(PSB_RED);
X=ps2x.Button(PSB_BLUE);                 segitiga=ps2x.Button(PSB_GREEN);


      if(((LX>=120) && (LX<=130)) && ((LY>=0) && (LY<=50))){ //ROBOT MAJU
          Serial.println("Maju");
          motDep(103,100);motBel(105,94);
      }
      else if(((LY> 240) && (LY<=255)) && ((LX>= 64) && (LX<= 192))){ //ROBOT MUNDUR
          Serial.println("mundur");
          motDep(-set_pwm,-set_pwm);motBel(-set_pwm,-set_pwm);
      }
      else if(((LX>=0) && (LX<=50)) && ((LY>=0) && (LY<=50))){
          Serial.println("Serong maju ke kiri");
          motDep(0,set_pwm+20);motBel(set_pwm+20,0);
      }
      else if(((LX>=150) && (LX<=255)) && ((LY>=0) && (LY<=50))){
          Serial.println("Serong maju ke kanan");
          motDep(set_pwm+20,0);motBel(0,set_pwm+10);
      }
      else if(((LY>=150) && (LY<=255)) && ((LX>=0) && (LX<=50))){
          Serial.println("Serong mudur ke kiri");
          motDep(-set_pwm-20,0);motBel(0,-set_pwm-10);
      }
      else if(((LY>=150) && (LY<=255)) && ((LX>=150) && (LX<=255))){
          Serial.println("Serong mundur ke kanan");
          motDep(0,-set_pwm-20);motBel(-set_pwm-20,0);
      }
     
      else if((LX > 192) && ((LY >= 64) && (LY <= 192))){
          Serial.println("Geser ke kanan");
          motDep(130,-128);motBel(-123,124);        
      }
      else if((LX < 64) && ((LY >= 64) && (LY <= 192))){
          Serial.println("Geser ke kiri");
          motDep(-130,130);motBel(131,-130);
      }
      else if(((LY>=100 && LY<=140) && (LX>=100 && LX<=140))){
          Serial.println("Diam");
          motDep(0,0);motBel(0,0);
      }
      
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if((RX > 192) && ((RY >= 64) && (RY <= 192))){
              Serial.println("Putar ke kanan");
              motDep(set_pwm,-set_pwm);motBel(set_pwm,-set_pwm); 
      }
      else if((RX < 64) && ((RY >= 64) && (RY <= 192))){
              Serial.println("Putar ke kiri");
              motDep(-set_pwm,set_pwm);motBel(-set_pwm,set_pwm);
      }
       
 
///////////////////////////////////////////////KENDALI GRIPPER////////////////////////////////////////////////////
  if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
          if(R2){
            countR2++;
            Serial.print(countR2);
            delay(150);
            if(countR2>=4){
              countR2=0;
            }

            if(countR2==0){
              angkatBelakang.write(35);
              Serial.println(":Belakang Naik");
              }
              
            if(countR2==1){
              angkatBelakang.write(135);
              Serial.println(":Belakang Turun");
              }
            
            if(countR2==2){
              jepitBelakang.write(145);
              Serial.println(": Jepit Belakang Buka");
              }
            if(countR2==3){
              jepitBelakang.write(40);
              Serial.println(": Jepit Belakang Tutup");
              }
          }

          if(R1){
            countR1++;
            Serial.print(countR2);
            delay(150);
            if(countR1>=4){
              countR1=0;
            }

            if(countR1==0){
              angkatKanan.write(35);
              Serial.println(":Kanan Naik");
              }
              
            if(countR1==1){
              angkatKanan.write(155);
              Serial.println(":Kanan Turun");
              }
            
            if(countR1==2){
              jepitKanan.write(145);
              Serial.println(": Jepit Kanan Buka");
              }
            if(countR1==3){
              jepitKanan.write(45);
              Serial.println(": Jepit Kanan Tutup");
              }
          }

          if(L1){
            countL1++;
            Serial.print(countL1);
            delay(150);
            if(countL1>=4){
              countL1=0;
            }

            if(countL1==0){
              angkatKiri.write(125);
              Serial.println(": Kiri Naik");
            }

            if(countL1==1){
              angkatKiri.write(20);
              Serial.println(": Kiri Turun");
            }

            if(countL1==2){
              jepitKiri.write(10);
              Serial.println(": Jepit Kiri Buka");
            }

            if(countL1==3){
              jepitKiri.write(98);
              Serial.println(": Jepit Kiri Tutup");
            }
          }
    }
 delay(50); 
}
