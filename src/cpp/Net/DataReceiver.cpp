#include "./Net/DataReceiver.h"

namespace
{

    // Structure to receive data
    // Must match sender structure
    typedef struct data_message
    {
        int id;
        bool status;
        float temperature;
        float idealTemperature;
        float humidity;
        float idealHumidity;
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

        // Sensors::SetSensorStatus(myData.id, myData.status);
        Sensors::SetSensorData(
            myData.id,
            myData.status,
            myData.temperature,
            myData.idealTemperature,
            myData.humidity,
            myData.idealHumidity);

        Serial.print("New data from sensor " + String(myData.id) + ": ");

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

    Serial.println("MAC ADDRESS:");
    Serial.println(WiFi.macAddress());

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