#include "esphome.h"

#include "receiver.h"

// D1 pin
#define RF_PIN D1

#define MAX_PULSES 16
static Frame frame;
static Receiver receiver;

int pulses[MAX_PULSES];
size_t pulseIndex;
int lastTime;
uint32_t add;
uint8_t control;
uint16_t rolling;
int flag;
int pulses2[MAX_PULSES];
size_t pulseIndex2;

class SomfySniffer: public PollingComponent,  public Sensor {
  public: 
      Sensor *adress_sensor = new Sensor();
      Sensor *controlCode_sensor = new Sensor();
      Sensor *rollingCode_sensor = new Sensor();
      //TimeSensor *time_sensor = new Sensor();


  static void IRAM_ATTR pinChanged()

  {
    int time = micros();
    int duration = time - lastTime;
    lastTime = time;
    if (pulseIndex < MAX_PULSES) pulses[pulseIndex++] = duration;
    
    noInterrupts();
    pulseIndex2 = pulseIndex;
    for (size_t i = 0; i < pulseIndex2; i++) pulses2[i] = pulses[i];
    pulseIndex = 0;
    interrupts();
 
    for (size_t i = 0; i < pulseIndex2; i++) {
      receiver.pulse(pulses2[i]);
   }}

  SomfySniffer(): PollingComponent(100) {}

  void setup() override {

    pulseIndex = 0;
    flag = 0;
    pinMode(RF_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RF_PIN), pinChanged, CHANGE);
  }
  void update() override {

	if (!receiver.storeFrame(&frame))
	{
       //ESP_LOGI("Debug","failed");
	}

      if (receiver.hasFrame()) {

        //ESP_LOGI("adress","%u",frame.address);
        
        add = frame.address;
        control = frame.controlCode;
        rolling= frame.rollingCode;
        flag = 1;
        receiver.reset();
        
      } else { //ESP_LOGD("test","noFrame")
      }
  
    if (flag == 1) {

      ESP_LOGI("Debug","data about to be published, adresse is %u", add);
      //publishing all sensors
      adress_sensor ->publish_state(add);
      controlCode_sensor -> publish_state(control);
      rollingCode_sensor ->publish_state(rolling);
      //time_sensor->publish_state(micros());
      //set flag to zero not to publish every X ms
      flag = 0;
    }
  }
};
