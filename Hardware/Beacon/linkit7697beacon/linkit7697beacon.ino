#include <LBLE.h>
#include <LBLEPeriphral.h>

// Define a simple GATT service with only 1 characteristic
LBLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214");
LBLECharacteristicInt switchCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", LBLE_READ | LBLE_WRITE);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  //Modify this variable to change the name of beacon
  const char *beaconname = "beacon69";


  Serial.begin(9600);

  //初始化BLE
  Serial.println("BLE begin");
  LBLE.begin();
  while (!LBLE.ready()) {
    delay(100);
  }
  Serial.println("BLE ready");
  Serial.print("device address is:");
  Serial.println(LBLE.getDeviceAddress()); //顯示7697 BLE addr



  //設定廣播資料
  // In this case, we simply create an advertisement that represents an
  // connectable device with a device name
  LBLEAdvertisementData advertisement;
  advertisement.configAsConnectableDevice(beaconname);

  // Configure our device's Generic Access Profile's device name
  // Ususally this is the same as the name in the advertisement data.
  LBLEPeripheral.setName(beaconname);

  // Add characteristics into ledService
  ledService.addAttribute(switchCharacteristic);

  // Add service to GATT server (peripheral)
  LBLEPeripheral.addService(ledService);

  //啟動GATT伺服器，此時已可被連線
  LBLEPeripheral.begin();

  //開始廣播
  LBLEPeripheral.advertise(advertisement);


}

void loop() {
  delay(100);
  if (switchCharacteristic.isWritten()) {
    const char value = switchCharacteristic.getValue();
    switch (value) {
      case '1':
        digitalWrite(LED_BUILTIN, HIGH); //7697就是D7, 其他Arduino為D13
        break;
      case '0':
        digitalWrite(LED_BUILTIN, LOW);
        break;
      default:
        break;
    }
  }
}
