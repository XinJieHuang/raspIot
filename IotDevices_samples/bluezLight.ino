const int lightControl = 2;
const int hc_sr501GND = 3;
const int hc_sr501VCC = 4;
const int hc_sr501OUT = 5;
String comData = "";
String light = "off";

void setup() {
  Serial.begin(9600);
  pinMode(hc_sr501VCC,OUTPUT);
  pinMode(hc_sr501GND,OUTPUT);
  pinMode(hc_sr501OUT,INPUT);
  digitalWrite(hc_sr501VCC, HIGH);
  digitalWrite(hc_sr501GND, LOW);
  delay(500);
}

void loop() {
  int hc_sr501Val = digitalRead(hc_sr501OUT);
  comData = readString();
  if(comData.equals("on")){
    lightUp();
    comData = "";
  }
  else if(comData.equals("off")){
    lightsOut();
    comData = "";
  }
  
}

//开灯
void lightUp(){
  if(!light.equals("on")){    //当灯已经开了,便不再执行开灯操作
      light = "on";
      pinMode(lightControl,OUTPUT);
      digitalWrite(lightControl, HIGH);
      Serial.print("325-left light:");
      Serial.print(light);
  }
}

//关灯
void lightsOut(){
  if(!light.equals("off")){   //当灯已经关了,便不再执行关灯操作
      light = "off";
      pinMode(lightControl,OUTPUT);
      digitalWrite(lightControl, LOW);
      Serial.print("325-left light:");
      Serial.print(light);
      pinMode(lightControl,INPUT); //关灯后将控制权交还触摸开关
  }
}

//读取串口数据
String readString(){
  while(Serial.available() > 0){
    comData += char(Serial.read());
    delay(2);   
  }
  return comData;
}

