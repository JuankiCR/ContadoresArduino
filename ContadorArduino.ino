int program = 1;
int pinSalida = 5;
int numeros[10][8] = {{12,13,8,7,6,11,-10,-9},{13,8,-6,-7,-10,-11,-12,-9},{12,13,7,6,10,-8,-11,-9},{12,13,8,7,10,-6,-11,-9},{13,8,11,10,-6,-7,-12,-9},{12,8,7,11,10,-6,-13,-9},{12,8,7,6,11,10,-13,-9},{12,13,8,-6,-7,-10,-11,-9},{12,13,8,7,6,11,10,-9},{12,13,8,7,11,10,-6,-9}};
void CambiarSalida(int pinState){digitalWrite(pinSalida, pinState);}
void LimpiarSalidas(){
  for(int i=6; i<14; i++){
    digitalWrite(i, LOW);
  }
}
void PrendeApaga(int prende, int apaga, int espera){
  digitalWrite(prende, HIGH);
  delay(espera);
  digitalWrite(apaga, LOW);
  delay(espera);
}
void PrenderNum(int numPos, int espera){
  for(int j=0; j<8; j++){
    int num = numeros[numPos][j];
    if(num < 0){
      num = abs(num);
      digitalWrite((num), LOW);
    }else{
      digitalWrite(num, HIGH);
    }
  }
  delay(espera);
}
void PrenderBinario(int numBin, int espera){
  int pin = 0;
  for(int j=0; j<8; j++){
      pin=j+6;
      if(((numBin >> j)& 1) == 1){
        digitalWrite(pin, HIGH);
      }else{
        digitalWrite(pin, LOW);
      }
    }
    delay(espera);
}
void RecorridoNumManual(){
  int accion = 1, num = 0;
  CambiarSalida(HIGH);
  while (accion != -1){
    PrenderNum(num,0);
    if(digitalRead(2) == 1 && num < 9){num += 1;}
    if(digitalRead(3) == 1 && num > 0){num -= 1;}
    if(digitalRead(4) == 1){
      accion = -1;
      LimpiarSalidas();
    }
    delay(100);
  }
}
void RecorridoLedManual(){
  int accion = 1;
  int ledAn = 13, ledAc = 6, aux = 0;
  CambiarSalida(LOW);
  digitalWrite(ledAc, HIGH);
  while (accion != -1){
    if (digitalRead(2) == 1 && ledAc < 13){
      aux = ledAn;
      ledAn = ledAc;
      ledAc += 1;
    }
    if (digitalRead(3) == 1 && ledAc > 6){
      aux = ledAn;
      ledAn = ledAc;
      ledAc -= 1;
    }
    if(digitalRead(4) == 1){
      accion = -1;
      LimpiarSalidas();
    }
    PrendeApaga(ledAc,ledAn,0);
    delay(100);
  }
}
void ContadorBinManual(){
  int accion = 1;
  int num = 0;
  CambiarSalida(LOW);
  while (accion != -1){
    if (digitalRead(2) == 1 && num < 255){
      num += 1;
    }
    if (digitalRead(3) == 1 &&  num > 0){
      num -= 1;
    }
    if(digitalRead(4) == 1){
      accion = -1;
      LimpiarSalidas();
    }
    PrenderBinario(num,0);
    delay(100);
  }
}
void RecorridoLed(){
  CambiarSalida(LOW);
  for(int i=6; i<13; i++){
    PrendeApaga(i,i,100);
  }
  for(int i=13; i>5; i--){
    PrendeApaga(i,i,100);
  }
  LimpiarSalidas();
}
void RecorridoNum(){
  CambiarSalida(HIGH);
  for(int i=0; i<10; i++){
    PrenderNum(i, 250);
  }
  for(int i=8; i>-1; i--){
    PrenderNum(i, 250);
  }
  LimpiarSalidas();
}
void ContadorBinario(){
  CambiarSalida(LOW);
  for(int i=0; i<256; i++){
    PrenderBinario(i, 50);
  }
  LimpiarSalidas();
}
void setup() {
  for (int i=5; i<14; i++){
    pinMode(i, OUTPUT);
  }
  for (int i=2; i<5; i++){
    pinMode(i, INPUT);
  }
}
void loop() {
  int ejecutar = 0;
  while (ejecutar != 1){
    CambiarSalida(HIGH);
    PrenderNum(program,0);
    if(digitalRead(2) == 1 && program < 6){program += 1;}
    if(digitalRead(3) == 1 && program > 1){program -= 1;}
    PrenderNum(program,0);
    if(digitalRead(4) == 1){
      ejecutar = 1;
      LimpiarSalidas();
    }
    delay(100);
  }
  switch (program){
    case 1:
      RecorridoNum();
    break;
    case 2:
      RecorridoNumManual();
    break;
    case 3:
      RecorridoLed();
    break;
    case 4:
      RecorridoLedManual();
    break;
    case 5:
      ContadorBinario();
    break;
    case 6:
      ContadorBinManual();
    break;
    default:
    break;
  }
  delay(1000);
}
