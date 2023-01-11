#include "./Net/DataReceiver.h"

namespace
{

    // Structure to receive data
    // Must match sender structure
    typedef struct data_message
    {
        int id;
        bool status;
    } data_message;

    // Create a data_message to store received data
    data_message myData;

    void OnReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len)
    {
        char macStr[18];
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
                 mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        Serial.print("Package received from: ");
        Serial.println(macStr);

        memcpy(&myData, data, sizeof(myData));

        Sensors::SetSensorStatus(myData.id, myData.status);

        Serial.print("New status from sensor " + String(myData.id) + ": ");

        Serial.println(myData.status);

        DataReceiver::dataReceived = true;
    };
}

bool DataReceiver::dataReceived = false;

DataReceiver::DataReceiver()
{
}

void DataReceiver::Init()
{
    Serial.println("DataReceiver starting...");

    // Set WiFi mode to station
    WiFi.mode(WIFI_MODE_STA);

    ESPNow.set_mac(mac);
    WiFi.disconnect();

    int initResult = ESPNow.init();

    if (initResult != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    DataReceiver::dataReceived = false;

    ESPNow.reg_recv_cb(OnReceive);
}