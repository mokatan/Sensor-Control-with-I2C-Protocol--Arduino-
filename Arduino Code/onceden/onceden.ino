
#include <Wire.h>

#define SRF08A         0x7C             // Address SRF08a
#define SRF08         0x71              // Address SRF08
#define CMD                 (byte)0x00  
#define LIGHTBYTE           0x01        
#define RANGEBYTE           0x02  
byte highByte = 0x00;   // high byte okunan
byte lowByte = 0x00;    // low byte okunan

void setup(){
  Serial.begin(9600); // seri port baslıyo
  Wire.begin();                               
  delay(100);                                    

}

void loop(){
Serial.print("MESAFE-1"); 
Serial.println();
int mesafeaData = mesafea();    // mesafe a fonksuyonunu cagır
Serial.print(mesafeaData); 
Serial.print(" cm ");
Serial.println(); 
//delay(1000);                         
  
Serial.print("MESAFE-2"); 
Serial.println();  
int mesafeData = mesafe();       // mesafe fonksuyonunu cagır
Serial.print(mesafeData);
Serial.print(" cm ");
Serial.println();
delay(100);

Serial.print("SICAKLIK-1"); 
Serial.println();  
int isiData = isi();       // ısı fonksuyonunu cagır
Serial.print(isiData);
Serial.print(" C ");
Serial.println();

Serial.print("SICAKLIK-2"); 
Serial.println();  
int isiaData = isia();       // ısı fonksuyonunu cagır
Serial.print(isiData);
Serial.print(" C ");
Serial.println();

delay(2000);







}

int isi(){      
                Serial.print("");

                // mesale 1 yada 8 goz okumak ıcın
                for (int i=0; i<=8; i++)
                {                        
                        Wire.beginTransmission(0x69); // tpa81 adresi                        
                        Wire.write(i);
                        Wire.endTransmission();
                        Wire.requestFrom(0x69, 1);
                        while(Wire.available() < 1) ;
                        int b = Wire.read();
                        Serial.write(35); //ASCII.bosluk verdı34 cift tırnak verıyo vc
                        Serial.print(b); // 
                }
}
int isia(){      
                Serial.print("");

                // mesale 1 yada 8 goz okumak ıcın
                for (int i=0; i<=8; i++)
                {                        
                        Wire.beginTransmission(0x68); // tpa81 adresi                        
                        Wire.write(i);
                        Wire.endTransmission();
                        Wire.requestFrom(0x68, 1);
                        while(Wire.available() < 1) ;
                        int b = Wire.read();
                        Serial.write(35); //ASCII.bosluk verdı34 cift tırnak verıyo vc
                        Serial.print(b); // 
                }
}

int mesafe(){                     // fonksiyon  SRF08
  int range = 0; 
  Wire.beginTransmission(SRF08);  // Start SRF08
  Wire.write(CMD);               
  Wire.write(0x51);                                
  Wire.endTransmission(); 
  delay(100);                                      
  Wire.beginTransmission(SRF08); // start SRFmodule
  Wire.write(RANGEBYTE);         // data bekleniyor
  Wire.endTransmission();
  Wire.requestFrom(SRF08, 2);                
  while(Wire.available() < 2);                     
  highByte = Wire.read();                          
  lowByte = Wire.read();                           
  range = (highByte << 8) + lowByte;               
  return(range);                                   
}
int mesafea(){                                   
  int range = 0; 
  Wire.beginTransmission(SRF08A);             
  Wire.write(CMD);                                 
  Wire.write(0x51);                                
  Wire.endTransmission(); 
  delay(100);                                     
  Wire.beginTransmission(SRF08A);             
  Wire.write(RANGEBYTE);                           
  Wire.endTransmission();
  Wire.requestFrom(SRF08A, 2);                
  while(Wire.available() < 2);                    
  highByte = Wire.read();                         
  lowByte = Wire.read();                           
  range = (highByte << 8) + lowByte;               
  return(range);                                   
}
