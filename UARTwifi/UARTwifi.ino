#include "driver/uart.h"
#include <WiFi.h>
#define RX_PIN 16 // Rx0 is GPIO3
#define TX_PIN 17 // Tx0 is GPIO1
#define BAUD_RATE 9600

const char* ssid     = "ssid";
const char* password = "password";
bool messageSend = false;

WiFiServer server(80);

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(2, OUTPUT);      // set the LED pin mode
  delay(10);
  Serial.println("UART communication using ESP32's uart library");

  // We start by connecting to a WiFi network

    Serial.println();
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
    
    server.begin();

  // Configure UART1 with baud rate of 9600, 8 data bits, no parity bit and 1 stop bit
  uart_config_t uart_config = {
      .baud_rate = BAUD_RATE,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
  };

  // Set UART1 pins as Rx0 and Tx0
  uart_param_config(UART_NUM_1, &uart_config);
  uart_set_pin(UART_NUM_1, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART_NUM_1, 256, 0, 0, NULL, 0);
}

void loop() {


WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          messageSend = true;
          String data = "a";
          digitalWrite(2, HIGH);               // GET /H turns the LED on
          uart_write_bytes(UART_NUM_1, data.c_str(), data.length());
        }
        if (currentLine.endsWith("GET /L")) {
          messageSend = false;
          String data = "b";
          digitalWrite(2, LOW);                // GET /L turns the LED off
          uart_write_bytes(UART_NUM_1, data.c_str(), data.length());
          
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  
//  // Check if there is any data available to read from UART1
//  uint8_t data[64];
//  int len = uart_read_bytes(UART_NUM_1, data, sizeof(data), 20 / portTICK_RATE_MS);
//  if (len > 0) {
//    Serial.print("Received data from STM32: ");
//    for (int i = 0; i < len; i++) {
//      Serial.print((char)data[i]);
//    }
//    Serial.println();
//
//    // Send back the received data to STM32
//    uart_write_bytes(UART_NUM_1, (const char*)data, len);
//  }

  // Check if there is any data available to read from Serial Monitor
  if (Serial.available()) {
    String data = Serial.readString();
    Serial.print("Sending data to STM32: ");
    Serial.println(data);

    // Send the data to STM32 over UART1
    uart_write_bytes(UART_NUM_1, data.c_str(), data.length());
  }
}
