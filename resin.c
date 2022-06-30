/*
 * by SuInk uid 143177803 https://suink.cn
 */
#define     CONTROL     11
#define     GM     5
#define     D12    12 //不显示主板led灯
#define     D13    13

#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <string.h>
#include <MD5Builder.h>
#include <Adafruit_GFX.h>      
#include <Adafruit_ST7735.h> 
#define TFT_SCLK 2  // Clock out  
#define TFT_MOSI 3  // Data out
#define TFT_RST  10      
#define TFT_DC   6     
#define TFT_CS   7


 
  
//config
const char* ssid     = "**";     // WIFI账户
const char* password = "****"; // WIFI密码

String uid = "143******"; //原神uid
String server = "cn_gf01" ; //如果是b服，填cn_qd01
String cookie = "cookie_token=**; account_id=**";//抓包获取的cookie

const String day[] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};



String url = "https://api-takumi-record.mihoyo.com/game_record/app/genshin/api/dailyNote?server="+server+"&role_id="+uid;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 8*3600, 60000);


void setup()
{   
    pinMode(D12, OUTPUT);
    pinMode(D13, OUTPUT);
    pinMode(CONTROL, OUTPUT);//定义控制串口
    pinMode(GM,INPUT);  //连接光控传感器DO口
    digitalWrite(D12,LOW);
    digitalWrite(D13,LOW);
    tft.initR(INITR_BLACKTAB); 
    //tft.setRotation(1); //竖屏显示
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_BLUE);
    tft.setTextSize(1);
    Serial.begin(115200);
    Serial.print("Connecting WiFi");
    tft.print("Conecting Wifi");
    WiFi.begin(ssid, password);     // ssid , password
    while (WiFi.status() != WL_CONNECTED) {delay(1000); Serial.print("."); tft.print(".");}
    Serial.print("\nWiFi connected! IP:");Serial.println(WiFi.localIP());
    delay(1000);
    timeClient.begin();
}
 
void loop()
{
    int gm=digitalRead(GM); //读出光敏DO的高低电平赋值给gm
    if(gm==1)
    {
      digitalWrite(CONTROL,LOW);//当检测到天暗，关闭屏幕
      //delay(1000);//延时1秒
    }
    else{digitalWrite(CONTROL,HIGH);}
    timeClient.update();
    unsigned long timestamp = timeClient.getEpochTime() - 8*3600;   // 时间戳
    Serial.print("Epoch Time:");
    Serial.println(timestamp);
    
    struct tm *ptm = gmtime((time_t *)&timestamp);
    String date = String(ptm->tm_mday);
    Serial.print("Month day:");
    Serial.println(date);
    String month = String(ptm->tm_mon + 1);
    Serial.print("Month:");
    Serial.println(month);
    String timestampstr = String(timestamp);
    //char str_int[41];
    //ultoa(timestamp, str_int ,10);
    String str1 = "salt=xV8v4Qu54lUKrEYFZkJhB8cuOh9Asafs&t="+ timestampstr +"&r=143177&b=&q=role_id="+ uid+"&server="+server;
    HTTPClient http ;
    Serial.println(url);
    http.begin(url);
    
    MD5Builder md5;
    md5.begin();
    md5.add(str1);
    md5.calculate();
    String sign = md5.toString();
    //setClock();
    String ds = timestampstr + ",143177," + sign;
    http.addHeader("DS", ds);
    http.addHeader("x-rpc-app_version", "2.19.1");
    http.addHeader( "User-Agent", "Mozilla/5.0 (iPhone; CPU iPhone OS 13_2_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) miHoYoBBS/2.11.1");
    http.addHeader("x-rpc-client_type", "5");
    http.addHeader( "Referer", "https://webstatic.mihoyo.com/");
    http.addHeader("Cookie",cookie);
    int    website_return_code = http.GET()        ; //请求米哈游服务器
    String website_return_text = http.getString()  ;
    
    Serial.println(website_return_code);
    Serial.println(website_return_text);
 
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, website_return_text); //将response转化为json格式
    JsonObject obj = doc.as<JsonObject>(); 

      
    String current_resin = obj["data"]["current_resin"];
    int    resin_recovery_time  = obj["data"]["resin_recovery_time"];

    
    
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.print(month + "/" + date + "  ");tft.print(timeClient.getFormattedTime());tft.println(" " + day[timeClient.getDay()]); //获取日期时间
    tft.println("");

    tft.setTextSize(3);
    tft.println(current_resin + "/160");
    tft.setTextSize(2);
    tft.print(resin_recovery_time/3600);tft.print("h");tft.print((resin_recovery_time%3600)/60);tft.println("min"); //显示回满所需时间

    
    delay(5000); //设置刷新时间
    
}