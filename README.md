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
