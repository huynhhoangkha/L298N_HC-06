// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       L298N_Bluetooth.ino
    Created:	16/01/2019 1:59:44 CH
    Author:     KHAHUYNH\huynh
*/

//#define INVERSE_LEFT
//#define INVERSE_RIGHT

#define DIR_L1	8
#define DIR_L2	11
#define SPEED_L	9
#define DIR_R1	12
#define DIR_R2	13
#define SPEED_R	10

#define FORWARD			'F'
#define BACK			'B'
#define LEFT			'L'
#define RIGHT			'R'
#define FORWARD_LEFT	'G'
#define FORWARD_RIGHT	'I'
#define BACK_LEFT		'H'
#define STOP			'S'
#define STOP_ALL		'D'

// The setup() function runs once each time the micro-controller starts
void setup() {
	pinMode(DIR_L1, OUTPUT);
	pinMode(DIR_L2, OUTPUT);
	pinMode(SPEED_L, OUTPUT);
	pinMode(DIR_R1, OUTPUT);
	pinMode(DIR_R2, OUTPUT);
	pinMode(SPEED_R, OUTPUT);
	Serial.begin(115200);
}

void runLeftWheel(int dir, int speed) {
#ifdef INVERSE_LEFT
	dir = dir * (-1);
#endif // !INVERSE_LEFT

	if (dir == 1) {
		digitalWrite(DIR_L1, LOW);
		digitalWrite(DIR_L2, HIGH);
	}
	else if (dir == -1) {
		digitalWrite(DIR_L1, HIGH);
		digitalWrite(DIR_L2, LOW);
	}
	else if (dir == 0) {
		digitalWrite(DIR_L1, HIGH);
		digitalWrite(DIR_L2, HIGH);
	}
	analogWrite(SPEED_L, speed);
}

void runRightWheel(int dir, int speed) {
#ifdef INVERSE_RIGHT
	dir = dir * (-1);
#endif // !INVERSE_LEFT
	if (dir == 1) {
		digitalWrite(DIR_R1, LOW);
		digitalWrite(DIR_R2, HIGH);
	}
	else if (dir == -1) {
		digitalWrite(DIR_R1, HIGH);
		digitalWrite(DIR_R2, LOW);
	}
	else if (dir == 0) {
		digitalWrite(DIR_R1, HIGH);
		digitalWrite(DIR_R2, HIGH);
	}
	analogWrite(SPEED_R, speed);
}


char command = '\0';

void readSerial() {
	if (Serial.available()) {
		command = Serial.read();
	}
}

// Add the main program code into the continuous loop() function
void loop() {
	readSerial();
	switch (command)
	{
	case STOP:
		runLeftWheel(1, 0);
		runRightWheel(1, 0);
		break;
	case FORWARD:
		runLeftWheel(1, 255);
		runRightWheel(1, 255);
		break;
	case BACK:
		runLeftWheel(-1, 255);
		runRightWheel(-1, 255);
		break;
	case LEFT:
		runLeftWheel(-1, 255);
		runRightWheel(1, 255);
		break;
	case RIGHT:
		runLeftWheel(1, 255);
		runRightWheel(-1, 255);
		break;
	default:
		break;
	}
}
