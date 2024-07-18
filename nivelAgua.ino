#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET);


//**********************variables******************************
const int trigger=A0;
const int echo=A1;
long tiempo;
float distancia;
int porciento= 0;
int buzzer= 4;
int buzzerDelay= 10000;


void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  pinMode(buzzer, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trigger,OUTPUT);
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  medir();
  convertirPorcentaje();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Distancia: ");
  display.setCursor(50,5);
  display.println(distancia);
  display.setCursor(50,7);
  display.println("cm");
  display.setCursor(0,25);
  display.println(porciento);
  display.println("%");
  display.display();
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();

  if(porciento>=99){alerta();}
}

void medir(){

  digitalWrite(trigger,LOW);
  delayMicroseconds (2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds (10);
  digitalWrite(trigger,LOW);

  tiempo= pulseIn(echo, HIGH);
  distancia= float(tiempo*0.0343)/2;
  delay(10);
}

void alerta(){
  digitalWrite(buzzer, HIGH);
  delayMicroseconds(buzzerDelay);
  digitalWrite(buzzer, LOW);
  delayMicroseconds(buzzerDelay);
}

void convertirPorcentaje()
{
  porciento = map(distancia,5,90,100,0);//convertir de cm a %
}
