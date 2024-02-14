#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

const char *ssid = "aiot5";
const char *password = "aiot51234";
const int server_port = 12345;

IPAddress staticIP(10, 10, 15, 200);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(10, 10, 15, 254);

WiFiServer server(server_port);
WiFiClient client;

SoftwareSerial SUART(D2, D1);

void setup() {
  Serial.begin(115200);
  SUART.begin(115200);

  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("연결 중...");
  }
  Serial.println("Wi-Fi 연결 성공");

  server.begin();
  Serial.println("서버 시작");
}

void loop() {
  client = server.available();
  if (client) {
    Serial.println("클라이언트 연결됨");

    while (client.connected()) {
      String data_received = client.readStringUntil('\n');

      if (data_received.length() > 0) {
        Serial.println("수신된 데이터: " + data_received);

        // String을 char 배열로 변환
        char sendData[data_received.length() + 2]; // +2는 '\n'과 null 문자('\0')를 추가하기 위함
        data_received.toCharArray(sendData, data_received.length() + 1);
        sendData[data_received.length()] = '\n';  // 데이터 끝에 개행 문자 추가
        sendData[data_received.length() + 1] = '\0'; // 문자열 끝에 null 문자 추가

        // NodeMCU에서 STM32로 데이터 전송
        SUART.print(sendData);
        Serial.print("전송한 데이터: ");
        Serial.println(sendData);
        // 수신된 데이터를 STM32가 처리할 시간을 확보하기 위해 작은 지연 추가
        delay(100);

        // 클라이언트에 응답 전송
        client.print("서버에서 응답: 데이터 수신 완료\n");
      }
    }

    Serial.println("클라이언트와 연결 종료");
  }
}
