#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;
ESP8266WebServer server(80);  // khai bao doi tuong webserver voi port la 80

int in3 = 9;    //Khai báo IN3 trên L298N
int in4 = 10;   //Khai báo IN4 trên L298N
int ctht1 = 2;  //Khai báo Công tắc hành trình 1
int ctht2 = 3;  //Khai báo công tắc hành trình 2
int cbmua = 7;

const char* rootHTML = R"html(
  <!DOCTYPE html>
<html>

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>Điều khiển thiết bị</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            overflow-x: hidden;
            padding: 0;
            margin: 0 auto;
        }

        .header {
            display: flex;
            justify-content: center;
            background-color: bisque;
            text-transform: uppercase;
        }

        .b {
            width: 100px;
            height: 40px;
            font-size: 21px;
            color: #FFF;
            background-color: #4caf50;
            border-radius: 10px;
        }

        .t {
            width: 100px;
            height: 40px;
            font-size: 21px;
            color: #FFF;
            background-color: #f44336;
            border-radius: 10px;
        }

        .d {
            width: 208%;
            height: 40px;
            font-size: 21px;
            color: #FFF;
            background-color: #2196F3;
            border-radius: 10px;
        }
    </style>
</head>

<body>
    <div class="header">
        <h1>Nhóm 4 - Thiết bị điều khiển mái hiên</h1>
    </div>


    <div style="width: 330px;height: auto;margin: 0 auto;margin-top: 70px">
        <h1 align="center">Điều khiển thiết bị qua WIFI</h1>
        <table align="center">
            <tr>
                <td><a href='/ON'><button class='b'>ON</button></a>
                <td>
                <td><a href='/OFF'><button class='t'>OFF</button></a>
                <td>
            <tr>
            <tr>
                <td><a href='/STOP'><button class='d'>STOP</button></a>
                <td>
            <tr>
        </table>
    </div>
</body>

</html>
)html";

void handleRootWebPage() {
  server.send(200, "text/html", webPage);
}

void handleCanopyOn() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void handleCanopyOff() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void handleStoppingCanopy() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void handleNotFound() {
  server.send(404, "text/plain", "Khong tim thay trang web");
}

void setup() {
  Serial.begin(9600);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ctht1, INPUT);
  pinMode(ctht2, INPUT);
  pinMode(cbmua, INPUT);
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin("#tenwifi", "#matkhau");  // sửa tên wifi và mật khẩu

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to wifi ");
    Serial.print(".........");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("esp8266", WiFi.localIP()))
    Serial.println("MDNS responder started");

  server.on("/", handleRootWebPage);
  server.on("/ON", handleCanopyOn);
  server.on("/OFF", handleCanopyOff);
  server.on("/STOP", handleStoppingCanopy);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Webserver is executing !");
}

void loop() {
  server.handleClient();
  // int trangthaict1 = digitalRead(ctht1);  //Đọc trạng thái CTHT1
  // int trangthaict2 = digitalRead(ctht2);  // Đọc trạng thái CTHT2
  // int thcbmua = digitalRead(cbmua);       //Đọc trạng thái CB mưa
  // Serial.print(trangthaict1);
  // Serial.print(trangthaict2);
  // Serial.print(trangthainutlen);
  // Serial.println(trangthainutxuong);

  // if (thcbmua == 1)  //Dang khong mua
  // {
  //   if (trangthainutxuong == 0 && trangthainutlen != 0 && trangthaict2 != 1) {
  //     xuong();
  //   } else if (trangthainutxuong != 0 && trangthainutlen == 0 && trangthaict1 != 1) {
  //     len();
  //   } else {
  //     dung();
  //   }
  // } else  //Co Mua
  // {
  //   if (trangthaict2 != 1)  //co mua va cua dang mo
  //   {
  //     xuong();
  //   } else {
  //     dung();
  //   }
  // }
}
