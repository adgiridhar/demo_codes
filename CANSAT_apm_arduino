#include<Servo.h>
#include <FastSerial.h>
#include <SPI.h>
#include <I2C.h>
#include <Arduino_Mega_ISR_Registry.h>
#include <AP_PeriodicProcess.h>
#include <AP_InertialSensor.h>
#include <AP_IMU.h>
#include <AP_GPS.h>
#include <AP_AHRS.h>
#include <AP_Math.h>
#include <AP_AnalogSource_Arduino.h>
#include <AP_Common.h>
#include <AP_Compass.h>
#include <AP_Airspeed.h>
#include <AP_Baro.h>
#include <Filter.h>

// uncomment this for a APM2 board
#define APM2_HARDWARE


#define WITH_GPS 0

FastSerialPort0(Serial);
FastSerialPort1(Serial1);
FastSerialPort2(Serial2);

AP_Compass_HMC5843 compass;


Arduino_Mega_ISR_Registry isr_registry;
AP_TimerProcess scheduler;
Arduino_Mega_ISR_Registry isr_registry1;
AP_TimerProcess scheduler1;

#define TeamID 2531
#define Buzzer A0
#define Temp_Out A2
long   MISSION_TIME,data[15],PacketCount;
float altitude, temp_apm,climb, temp_out, roll,prev_roll,final_roll,diff,pitch, yaw,voltage,fsw_state,bonus_acc_x, bonus_acc_y, bonus_acc_z, image_yaw=0.0;
boolean climb_flag=0;


AP_InertialSensor_MPU6000 ins;
static GPS         *g_gps;

//AP_GPS_Auto     g_gps_driver(&Serial1, &g_gps);


AP_IMU_INS imu(&ins);
AP_AHRS_DCM  ahrs(&imu, g_gps);
AP_Baro_MS5611 baro;

unsigned long timer;


#ifdef APM2_HARDWARE
# define A_LED_PIN        27
# define C_LED_PIN        25
# define LED_ON           LOW
# define LED_OFF          HIGH
# define MAG_ORIENTATION  AP_COMPASS_APM2_SHIELD
#else
# define A_LED_PIN        37
# define C_LED_PIN        35
# define LED_ON           HIGH
# define LED_OFF          LOW
# define MAG_ORIENTATION  AP_COMPASS_COMPONENTS_DOWN_PINS_FORWARD
#endif


static void flash_leds(bool on)
{
  digitalWrite(A_LED_PIN, on ? LED_OFF : LED_ON);
  digitalWrite(C_LED_PIN, on ? LED_ON : LED_OFF);
}

void setup()
{

  Serial.begin(9600);
  Serial2.begin(9600);
  setupCommunication();

  I2c.begin();
  I2c.timeOut(5);
  I2c.setSpeed(true);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  // we need to stop the barometer from holding the SPI bus
  pinMode(40, OUTPUT);
  digitalWrite(40, HIGH);
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);


  isr_registry.init();
  scheduler.init(&isr_registry);

  imu.init(IMU::COLD_START, delay, flash_leds, &scheduler);
  compass.set_orientation(MAG_ORIENTATION);
  ahrs.init();
  ahrs.set_compass(&compass);

}

static uint16_t counter=0;
static uint32_t last_t=0, last_print=0;
uint32_t now=0;


void loop(void)
{
  now = micros();
  if (last_t == 0) {
    last_t = now;
    return;
  }

  ahrs.update();
  counter++;

  if (now - last_print >= 2000) {
    Vector3f drift  = ahrs.get_gyro_drift();

    roll=ToDeg(ahrs.roll);
    pitch=ToDeg(ahrs.pitch);
    yaw=ToDeg(ahrs.yaw);

    Vector3f accel = imu.get_accel();

    bonus_acc_x=accel.x;
    bonus_acc_y=accel.y;
    bonus_acc_z=accel.z;

    updateBaro();

    image_yaw+=ToDeg(ahrs.get_roll_rate_earth());


    last_print = now;
    counter = 0;
    
    diff=roll-prev_roll;
    //if(abs(diff)>180) {roll*=-1;diff=roll-prev_roll;}
    //if(diff<=180)
    if(roll<-100 && prev_roll>100){diff=(180+roll)+(180-prev_roll);}
    if(prev_roll<-100 && roll>100){diff=(180-roll)+(180+prev_roll);}
    final_roll+=diff;
    //else if(roll>180)
    //final_roll-=diff;
    prev_roll = roll;
  }
  if (now - last_t >= 100000) {
    updateComunication();
    send_gyro();
    last_t=now;
  }

}
//Baro

void setupBaro()
{
  delay(1000);

  isr_registry.init();
  scheduler.init(&isr_registry);

  pinMode(63, OUTPUT);
  digitalWrite(63, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV32);     // 500khz for debugging, increase later

  baro.init(&scheduler);
  baro.calibrate(delay);
  timer = millis();
}

int r=0;

void updateBaro()
{
  if(r==0)
  {
    r=1;
    setupBaro();
  }



  if((micros() - timer) > 100000UL) {
    timer = micros();
    baro.read();
    uint32_t read_time = micros() - timer;
    temp_apm=(float)(baro.get_temperature()/10);
   temp_out=get_temp_out(); 
    altitude=(float)baro.get_altitude();
    climb=(float)baro.get_climb_rate();
    fsw_state=get_fsw_state();



  }
}

float get_temp_out()
{
  return ((analogRead(Temp_Out)/1024.0)*500);
}

//FSW_State
int get_fsw_state()
{
  if(MISSION_TIME<2)
  {
  return 0;
  }
  
  else if(MISSION_TIME<10)
  {
  return 1;
  }
  
  else if(MISSION_TIME >= 10 && (climb > -1.0 && climb < 1.0))
  {
  return 2;
  }
  
  else if(climb>15)
  {
  return 3;
  }
  
  else if(climb<10 && altitude>500)
  {
  return 4;
  }
  
  else if(climb<0 && altitude>300)
  {
  return 5;
  }
  
  else if(climb< -2 && altitude<300)
  {
  return 6;
  }
  
  else if(climb_flag==1 && altitude<2)
  {
  return 7;
  }
}
  
//Serial
//<TEAM ID>,<MISSION_TIME>,<ALT SENSOR>,<OUTSIDE_TEMP>,<INSIDE_TEMP>,<VOLTAGE>,<FSW_STATE>, <BONUS_ACCELEROMETER>, <PACKET_COUNT_MAYBE>, <GYRO_ROLL>, <GYRO_PITCH>, <GYRO_YAW> 

// In Use CSV

void setupCommunication()
{
  Serial.flush();
  PacketCount=1;
  pinMode(A0,OUTPUT);
  pinMode(A2,INPUT);

}
void updateComunication()
{
  updateData();
  SendData();

}

void SendData()
{
//  Serial.print(roll);
//  Serial.print("\t");
//  Serial.print(diff);
//  Serial.print("\t");
//  Serial.print(final_roll);
//  Serial.print("\t");
//  Serial.println(prev_roll);
  for(int j=0; j<15; j++)
  {
    Serial.print(data[j]);
    if(j!=14)
      Serial.print(',');
    else
      Serial.println();
  }
  PacketCount=PacketCount+1;
}
void send_gyro()
{
  if(Serial2.available())
  {
  if(Serial2.read()=='x')
  Serial2.print((int)final_roll);
  Serial2.print('a');
  delay(10);
 }
}
void updateData()
{
  MISSION_TIME=millis()/1000;
  //Set Data
  data[0]=TeamID;
  data[1]=MISSION_TIME;
  data[2]=altitude*100;
  data[3]=temp_apm*100;
  data[4]=temp_out*100;
  data[5]=voltage*100;
  data[6]=fsw_state;
  data[7]=bonus_acc_x*100;
  data[8]=bonus_acc_y*100;
  data[9]=bonus_acc_z*100;
  data[10]=PacketCount;
  data[11]=final_roll;//(roll); //yaw
  data[12]=(pitch); 
  data[13]=(yaw); //roll
  data[14]=(climb);
  // BUZZER
  
  if((int)(climb)>10 && altitude>30) 
  climb_flag=1;
  
  if(climb_flag==1 && altitude<20)
    digitalWrite(Buzzer,HIGH);
  else
    digitalWrite(Buzzer,LOW);

}

