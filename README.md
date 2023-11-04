#
This project aims to create a robust filament detection and monitoring system for 3D printers. By combining IR sensors, a Nucleo board, temperature sensors, 
LED or LCD displays, the system continuously tracks the presence and temperature of the printing bed during 3D printing. This information is presented 
on the display, ensuring users are informed about the filament's status in real-time. The information of the presence of filament is delivered to and ESP32 
which is connected over UART which then uses Wi-fi to send that information to a website. This website will contain the IP address that is associated with 
the ESP32. 

This system offers improved 3D printing reliability, making it an invaluable addition to a 3D printing setup.
