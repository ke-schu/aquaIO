# AquaIO Firmware für ATtiny84A

Dieses Repository enthält die Firmware für den ATtiny84A auf der AquaIO-Platine der Aquasonic-Rakete. Die Firmware wurde entwickelt, um die zeitgesteuerte Steuerung der Fallschirme und die Kommunikation mit AquaBrain über I²C zu ermöglichen.

## Funktionen

- **Fallschirmansteuerung:** Zeitgesteuertes Auslösen von Haupt- und Vorfallschirmen.
- **I²C-Kommunikation:** Austausch von Statusinformationen mit AquaBrain (I²C-Master).
- **Anpassbare Timer-Einstellungen:** Ermöglicht eine Anpassung der Timer an unterschiedliche Flugprofile.
- **Entwicklungstools:** Erstellt mit ATTinyCore und PlatformIO.

## Entwicklung

Die Firmware wurde in **C++** entwickelt, unter Verwendung von:
- **PlatformIO:** Als Entwicklungsumgebung für Coding, Kompilierung und Testen.
- **ATTinyCore:** Zur Unterstützung der Arduino-Framework-Funktionen auf dem ATtiny84A.

## Pinout Diagram
![Pinout Diagram](doc/ATtiny_Test.jpg)

## About Aquasonic
Aquasonic 3 is the third rocket project by Hochschule Bremen, conducted as part of the STERN program (Student Experimental Rockets) of the German Aerospace Center (DLR). The goal of this project is to design and build a functional sounding rocket.

Within the Aquasonic 3 project, the Aquasonic Avionics subproject focuses on developing and integrating the rocket's avionics systems. These systems are responsible for electronic control, data processing, and communication interfaces for the rocket.
