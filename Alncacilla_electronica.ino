  //Incluir librerias
  #include <Wire.h>
  #include <Servo.h>
  #include <LiquidCrystal_I2C.h>
  #include <Keypad.h>
  Servo miservo;
  //Model HI-06CS
  int interrupcion = 2; // Pin digital para la interrupción (INT0)
    volatile int numero_monedas = -1; // Variable que almacena el número de créditos introducidos
    int n = 0 ; // Variable auxiliar
  
  //CASO DEL KEYPAD 
  #define NO_KEY 0
  const byte ROWS = 4; //4 filas
  const byte COLS = 3; //3 columnas
  char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
  byte rowPins[ROWS] = {9, 8, 7, 6};
  byte colPins[COLS] = {5, 4, 3};
  int keyDelay = 50;
  unsigned int keyVal1 = 0;
  unsigned int keyVal2 = 0;
  String pword; 
  String case1 = String("1234");//contraseña
  String case2 = String("1");//Retirar
  String case3 = String("2");//Ingresar cantidad a retirar
  String case4 = String("4");//Ingresar cantidad a depositar
  String dots = String();
  String message = String();//
  Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
  LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 3F
  int DOOR_OPEN =   180; 
  int DOOR_CLOSE = 0;
  
  //void SETUP
  void setup(){
    //ACTIVAR LCD
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(3,0);
  lcd.print("Bienvenido");
  lcd.setCursor(2,1);
  lcd.print("Alcancia 24H");
  delay(2000);
  lcd.clear();
  initLCD();
  miservo.attach(10);
  
  }
  //void LOOP
    void loop(){
      
    char key = keypad.getKey(); 
    
    if (key != NO_KEY){  
      if (key == 35) {  
        pword = "";  
        dots = "";
        initLCD();   
      }
    else if(key == '*') {  
      checkPass();
    }else{
       pword.concat(key);  
      
      dots += "*";  
    }
    lcd.setCursor(10, 1); 
    lcd.print(dots);   
      }
    }
    
    
  
  
  //Inicializar LCD 
  void initLCD(){  
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.clear();
    pinMode(interrupcion, INPUT_PULLUP); // Pin digital 2 como entrada
  // Interrupción 0 (INT0) por el pin digital 2 que activa la ISR en cada flanco de subida
  attachInterrupt(digitalPinToInterrupt(interrupcion), ServicioMonedero, RISING);
    lcd.print("Ingresar clave : ");
    miservo.write(DOOR_CLOSE);
    
  }
   void ServicioMonedero() // ISR: Rutina de Servicio a la Interrupción
    {
      // Se aumenta en una unidad el número de créditos  
      numero_monedas++;
      delay(100);
    } 
  unsigned int getKey() {
    keyVal1 = analogRead(keypad.getKey()); 
    Serial.println(keyVal1);
    delay(keyDelay);
    keyVal2 = analogRead(keypad.getKey()); 
    if(keyVal1 > keyVal2) {
      keyVal1 = max(keyVal1, keyVal2);
      return getMatrixValue(keyVal1);  
    }
    else  
      return NO_KEY;
  }
  void checkPass() { //cambiar a contraseña
      lcd.clear();
    if(pword == case1) {//contraseña correcta
      lcd.setCursor(0,0);
      lcd.print("[1] Depositar");
      lcd.setCursor(0,1);
      lcd.print("[2] Retirar");
      pword = "";  
      dots = "";  
    }else if (pword == case2){
          Depositar();
      }else if(pword == case3){
        Retirar();
        }else{
      lcd.print("Clave invalida");
      delay(2000);
      lcd.clear();
      pword = "";  
      dots = "";
      lcd.print(message);
      initLCD();
    }
     
  }
void Depositar(){
  lcd.clear();
  if(pword == case2) {  
         Serial.println(numero_monedas);
         lcd.print("Insertar Monedas");
         if(n!=numero_monedas){
          insertar();
         }
    }
    
     
    }

  
void insertar(){
      if(n != numero_monedas){
      lcd.setCursor(0,1);  
      lcd.print("ahorros: S/.");
      lcd.print(numero_monedas);
      n = numero_monedas;

      }
      
      if(n>=6){
      lcd.setCursor(1,1);  
      lcd.print("ALCANCIA LLENA");  
      delay(4000);
      lcd.clear();
      checkPass();
      lcd.setCursor(0,0);
      lcd.print("  [1]  Depositar");
      lcd.setCursor(0,1);
      lcd.print("  [2]  Retirar");
      pword = "";  
      dots = "";  
      }else{
        insertar();
      }
}

  
  void Retirar(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Por favor retire");
    lcd.setCursor(2,1);
    lcd.print("sus  ahorros");
    miservo.write(DOOR_OPEN);
    
     pword = "";  
     dots = "";
      
  }
  
  
  char getMatrixValue(int val) {
    switch(val) {
    case 930 : return keys[0][0];
    case 912 : return keys[0][1];
    case 894 : return keys[0][2];
    case 877 : return keys[0][3];
    case 852 : return keys[1][0];
    case 837 : return keys[1][1];
    case 822 : return keys[1][2];
    case 808 : return keys[1][3];
    case 787 : return keys[2][0];
    case 774 : return keys[2][1];
    case 761 : return keys[2][2];
    case 749 : return keys[2][3];
    case 731 : return keys[3][0];
    case 719 : return keys[3][1];
    case 708 : return keys[3][2];
    case 698 : return keys[3][3];
    default : return NO_KEY;
    }
  } 
