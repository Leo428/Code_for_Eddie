#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           fRCtrl,        tmotorVex393_HBridge, PIDControl, encoderPort, I2C_1)
#pragma config(Motor,  port2,           fRDrive,       tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           bRCtrl,        tmotorVex393_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port4,           bRDrive,       tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port7,           bLCtrl,        tmotorVex393_MC29, PIDControl, encoderPort, I2C_3)
#pragma config(Motor,  port8,           bLDrive,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port9,           fLDrive,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          fLCtrl,        tmotorVex393_HBridge, PIDControl, encoderPort, I2C_4)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#define PID_DRIVE_MAX 127
#define PID_DRIVE_MIN -127

float  pid_Kp = 2.0;
float  pid_Ki = 0.04;
float  pid_Kd = 0.0;

static bool pidRunning = true;
static float pidRequestedValue = 0.0;

void clearAllEnc(){
	resetMotorEncoder(motor[fLCtrl]);
	resetMotorEncoder(motor[bLCtrl]);
	resetMotorEncoder(motor[fRCtrl]);
	resetMotorEncoder(motor[bRCtrl]);
}

task pidController() {
	float  pidSensorCurrentValue;
	float  pidError;
	float  pidLastError;

	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;
	//clear all encoders !
	clearAllEnc();
	//init
	pidLastError = 0;
  pidIntegral = 0;

  //looping >_<
  while(true) {
  	if(pidRunning) {
  		pidSensorCurrentValue = SensorValue[I2C_1];

  		pidError = pidSensorCurrentValue - pidRequestedValue;

  		if(pid_Ki != 0) {
  			// shall we have a limit???
  			pidIntegral = pidIntegral + pidError;
  		}
  		else {
  			pidIntegral = 0;
  		}

  		// derivative
  		pidDerivative = pidError - pidLastError;
  		pidLastError = pidError;

  		// outputs
  		pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

  		// limit drive
      if(pidDrive > PID_DRIVE_MAX ) pidDrive = PID_DRIVE_MAX;
      else if(pidDrive < PID_DRIVE_MIN ) pidDrive = PID_DRIVE_MIN;

      motor[fRCtrl] = pidDrive;
  	}
  	else {
  		pidError      = 0;
      pidLastError  = 0;
      pidIntegral   = 0;
      pidDerivative = 0;
  		motor[fRCtrl] = 0;
  	}
  	wait1Msec(25);
  }
}

task main()
{


	while(true) {

	}

}
