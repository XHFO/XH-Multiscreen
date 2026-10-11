# Form Monitor C6 · development source

Version: 2.0.0-formlabs-alpha.9
Hardware: Waveshare ESP32-C6-LCD-1.3 / 4 MB

This is the dedicated Formlabs target, not the macOS app or the generic C6 target.
Requires Node.js and PlatformIO Core. Build: `node scripts/embed-formlabs-c6-portal.mjs`, then `pio run -d Tools/FormlabsC6Firmware -e formlabs-c6`.
macOS development tests additionally need Xcode Command Line Tools and the PlatformIO ESP-IDF cJSON dependency: `bash scripts/test-formlabs-c6.sh`.
Details and known limitations: `Tools/FormlabsC6Firmware/README.md`.

Project code: MIT. Third-party fonts/QR code retain their included notices.
Enclosure models, website and photos are not included and are not covered by MIT.
No Wi-Fi/printing credentials, full-flash dumps or private test outputs are included.
No promised cloud availability, OTA reliability, long-term or real multi-printer validation.
Public alpha source, not a stable release. Start with the root README.md.
