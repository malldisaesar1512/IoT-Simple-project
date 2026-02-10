#define BLYNK_TEMPLATE_ID "TMPL6W85fxK1C"
#define BLYNK_TEMPLATE_NAME "ALS"
#define BLYNK_AUTH_TOKEN "7rsiMcQOvyaoKCCtV1f-ebnSWDEAG6zY"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define TRIG_PIN 32
#define ECHO_PIN 25    
#define LED_PIN 33

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

int threshold = 200;

BLYNK_WRITE(V0){
  int Buttonstatus = param.asInt();

  if (Buttonstatus == 1){
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  int ledValue = digitalRead(LED_PIN);

  //inisiasi pengambilan data
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //hitung hasil
  int duration = pulseIn(ECHO_PIN, HIGH);
  int result = (duration / 58);

  // put your main code here, to run repeatedly: 
  Blynk.virtualWrite(V1, result);
  
  Serial.print("Jarak: ");
  Serial.println(String(result) + " CM");

  // Jika jarak lebih dari threshold → lampu mati
  if (result > threshold) {
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V0, ledValue);
  } 
  // Jika jarak kurang dari threshold → lampu nyala
  else {
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(V0, ledValue);
  }

  delay(500);
}
