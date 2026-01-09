#include <SoftwareSerial.h>
#include <Servo.h>

// --- Function Declarations ---
void forward();
void backward();
void left();
void right();
void stopMotors();

// Bluetooth pins (connect RX to TX and TX to RX)
SoftwareSerial BT(10, 11); // RX, TX

// Servo motor object
Servo myservo; 

// Motor A pins (for one side of the wheelchair)
const int in1 = 4;
const int in2 = 5;
const int ena = 8; // Connect to a PWM pin for speed control

// Motor B pins (for the other side of the wheelchair)
const int in3 = 6;
const int in4 = 7;
const int enb = 9; // Connect to a PWM pin for speed control

// Ultrasonic sensor pins
const int trigPin = 12;
const int echoPin = 13;

// New: Physical forward control switch pin
const int FORWARD_SWITCH_PIN = A0; // Using analog pin A0 as a digital input

// Variables for sensor and command handling
char command;
long duration;
int distance;

void setup() {
    // Attach the servo motor to a digital pin
    myservo.attach(3); 

    // Set motor driver control pins as outputs
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(enb, OUTPUT);
    
    // Set ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    // Set up the forward switch pin with an internal pull-up resistor
   
    
    // Set enable pins to HIGH to allow the motors to be controlled
    digitalWrite(ena, HIGH);
    digitalWrite(enb, HIGH);
    
    // Start Bluetooth and Serial communication for debugging
    BT.begin(9600);
    Serial.begin(9600);
    
    // Set initial servo position to center (90 degrees)
    myservo.write(90);

    Serial.println("System Initialized and Ready.");
    Serial.println("Waiting for Bluetooth commands...");
}

void loop() {
    // --- Ultrasonic Distance Measurement ---
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // --- Check for physical switch control ---
    if (digitalRead(FORWARD_SWITCH_PIN) == HIGH) { // Switch is ON
        if (distance > 15) { // Check for obstacles before moving
            forward();
            Serial.println("Switch ON: Moving Forward");
        } 
        myservo.write(90); // Keep servo centered
    } else { // Switch is OFF, listen for Bluetooth commands
        if (BT.available()) {
            command = BT.read();
            Serial.print("Received command: ");
            Serial.println(command);
            
            switch (command) {
                case 'F': // Forward
                    // This case is only used when the switch is OFF
                    if (distance > 15) {
                        forward(); 
                        Serial.println("Command: Moving Forward");
                    } else {
                        stopMotors();
                        Serial.println("Command: Obstacle too close, not moving forward.");
                    }
                    myservo.write(90); 
                    break;
                case 'B': // Backward
                    backward();
                    Serial.println("Command: Moving Backward");
                    myservo.write(90); 
                    break;
                case 'L': // Left turn
                    stopMotors();
                    Serial.println("Command: Turning Left");
                    myservo.write(180); 
                    delay(500); 
                    left(); 
                    break;
                case 'R': // Right turn
                    stopMotors();
                    Serial.println("Command: Turning Right");
                    myservo.write(0); 
                    delay(500); 
                    right(); 
                    break;
                case 'S': // Stop
                    stopMotors();
                    Serial.println("Command: Stopping Motors");
                    myservo.write(90); 
                    break;
            }
        }
    }
    
    delay(50); 
}

// Motor control functions
void forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
}

void backward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void left() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void right() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void stopMotors() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

