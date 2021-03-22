
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ESP32_Servo.h>

static const int servoPin = 19;
Servo myServo;

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
int angle = 90;
int secs = 0;
String rotation = "";
String seconds = ""; 

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string value = pCharacteristic->getValue();

      if(value == "R1"){
          myServo.write(30);
          delay(1000);
          myServo.write(90);
          delay(10);
      }else if(value == "R2"){
          myServo.write(30);
          delay(2000);
          myServo.write(90);
          delay(10);
      }else if(value == "R3"){
          myServo.write(30);
          delay(3000);
          myServo.write(90);
          delay(10);
      }else if(value == "R4"){
          myServo.write(30);
          delay(4000);
          myServo.write(90);
          delay(10);
      }else if(value == "R5"){
          myServo.write(30);
          delay(5000);
          myServo.write(90);
          delay(10);
      }else if(value == "R6"){
          myServo.write(30);
          delay(6000);
          myServo.write(90);
          delay(10);
      }else if(value == "L1"){
          myServo.write(150);
          delay(1000);
          myServo.write(90);
          delay(10);
      }else if(value == "L2"){
          myServo.write(150);
          delay(2000);
          myServo.write(90);
          delay(10);
       }else if(value == "L3"){
          myServo.write(150);
          delay(3000);
          myServo.write(90);
          delay(10);
          }
        else if(value == "L4"){
          myServo.write(150);
          delay(4000);
          myServo.write(90);
          delay(10);
          }
        else if(value == "L5"){
          myServo.write(150);
          delay(5000);
          myServo.write(90);
          delay(10);
          }
        else if(value == "L6"){
          myServo.write(150);
          delay(6000);
          myServo.write(90);
          delay(10);
          }
    }
};

void setup() {
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("아이오토LITE");

  myServo.attach(servoPin);
  
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
                  
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
    // notify changed value
//    if (deviceConnected) {
//        pCharacteristic->setValue((uint8_t*)&value, 4);
//        pCharacteristic->notify();
//        value++;
//        delay(10);   
//        }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
