#include <WiFi.h>
/*Agrega la biblioteca HTTPClient al proyecto.*/
#include <HTTPClient.h>

WiFiClient client;
HTTPClient http;

/*URL del servidor y ruta para la solicitud POST*/
const String serverName = "http://tu_servidor.com:100/datos/create";

float num;

/*Conectar el dispositivo al WIFI*/
void setup() {
  Serial.begin(115200);
  WiFi.begin("TU_SSID", "TU_PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
}

/*Funciones para crear diferentes datos con valores aleatorios*/
void temperatura() {
  num = random(10, 35);
  String type = "Temperatura";
  PostData(num, type);
}
void watts() {
  num = random(120, 300);
  String type = "Watts";
  PostData(num, type);
}
void humedad() {
  num = random(0, 100);
  String type = "Humedad";
  PostData(num, type);
}
void presion() {
   num = random(130, 251) / 100.0;
  String type = "Presion";
  PostData(num, type);
}
/*Funcion que realiza la peticion POST para guardar el dato y valor enviado*/
void PostData(float data, String type) {
  /* Crear el dato JSON*/
 String httpRequestData = "{\"nombre\": \"Dispositivo1\",\"dato\": " + String(data) + ",\"type\":\"" + type + "\",\"NoSerie\": \"TU_NUMERO_DE_SERIE\"}";
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/json");
  int code = http.POST(httpRequestData);
  Serial.println("PETICION" + String(code));
  Serial.println(http.getString());
  http.end();
}
/*Funcion qpara postear diferentes datos en tiempos aleatorios*/
void loop() {
  Serial.println("-> Send temperatura");
  temperatura();
  delay(random(1000, 300000));
  Serial.println("-> Send watts");
  watts();
  delay(random(1000, 300000));
  Serial.println("-> Send humedad");
  humedad();
   delay(random(1000, 300000));
  Serial.println("-> Send presion");
  presion();
  delay(random(3600000, 7200000));
}
