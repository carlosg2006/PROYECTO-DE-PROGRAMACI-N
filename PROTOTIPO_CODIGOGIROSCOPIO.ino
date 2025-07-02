#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
int16_t accX, accY, accZ;
float angleX, angleY;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 conectado correctamente.");
  } else {
    Serial.println("Error: MPU6050 no detectado.");
    while (1); 
  }
}

void loop() {
  mpu.getAcceleration(&accX, &accY, &accZ);
  float ax = accX / 16384.0; // Escala típica del MPU6050
  float ay = accY / 16384.0;
  float az = accZ / 16384.0;
  angleX = atan2(ay, az) * 180.0 / PI;
  angleY = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  if (angleX < 0) angleX += 360;
  if (angleY < 0) angleY += 360;

  // Mostrar resultados
  Serial.print("Ángulo X (Pitch): ");
  Serial.print(angleX);
  Serial.print("° | Ángulo Y (Roll): ");
  Serial.print(angleY);
  Serial.println("°");


  //CASOS SEGÚN VALORES DEL GIROSCOPIP
if ( (340 < angleX or angleX < 20) & (340 <=angleY or angleY <= 20)){
  Serial.print ("Detenido");
}else if ( 20 <= angleX & angleX <= 80 & (340 <=angleY or angleY <= 20)){
  Serial.print ("Atras");
}else if ( 270 <= angleX & angleX <=340  & (340 <=angleY or angleY <= 20)){
  Serial.print ("Adelante");
  Serial.print (map(angleX, 340, 270, 0 , 1023)); //GENERA EL VALOR SEGÚN LO MEDIDO
}
else if ( 270 <= angleX & angleX <= 340 & 270 <=angleY & angleY <= 340){
  Serial.print ("Derecha");
}else if ( 270 <= angleX & angleX <= 340 & 20 <=angleY & angleY <= 80){
  Serial.print ("izquierda");
}
  delay(300); 
}
