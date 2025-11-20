#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

// サーバーポート (Python側の設定と合わせる)
const int port = 8080;

WiFiServer server(port);

void setup() {
  Serial.begin(115200);
  
  // Wi-Fi接続
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // サーバー開始
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
            // 改行コードは無視するか、コマンドの区切りとして使う
        } else {
            currentLine += c;
        }
        
        // コマンド受信完了判定 (簡易的にデータがあれば処理)
        // 実際にはデリミタを決めたほうが良いが、今回は単発送信を想定
      }
      
      // データを受信しきったら処理
      if (currentLine.length() > 0 && !client.available()) {
        Serial.print("Received: ");
        Serial.println(currentLine);

        if (currentLine.startsWith("FIRE:")) {
            String shellType = currentLine.substring(5);
            Serial.print("Firing shell: ");
            Serial.println(shellType);

            // ここでソレノイドなどのハードウェア制御を行う
            // シミュレーションとして少し待機
            delay(500); 

            // レスポンス送信
            client.println("DONE");
            Serial.println("Sent: DONE");
        }
        
        currentLine = "";
        break; // 一回処理したら切断する設計 (必要に応じて維持)
      }
    }
    
    client.stop();
    Serial.println("Client Disconnected.");
  }
}