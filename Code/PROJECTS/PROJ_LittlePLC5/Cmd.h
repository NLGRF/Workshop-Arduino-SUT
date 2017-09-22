extern "C" {tByte fCmdOpen(void);}
extern "C" {void fCmdRun(void);}

extern "C" {void fCmdNoBacklight(void);}
extern "C" {void fCmdBacklight(void);}

//- I/Os ------------------------------------
#define RELAY 9           // Relay
#define DHTPIN 2          // Digital pin connected to DHT22's OUT pin
#define DHTTYPE DHT22     // DHT22
#define SD_CS 10          // SD Reader's chip select
