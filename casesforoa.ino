    #include <Servo.h>
    
    #define trigPin1 10 //left
    #define echoPin1 11
    #define trigPin2 8  //back
    #define echoPin2 9
    #define trigPin3 2 //right
    #define echoPin3 3
    #define trigPin4 4  //fronta
    #define echoPin4 5

    #define rollRead 15
    #define pitchRead 14

    
    //gray, yellow, orange, purple
    //g, brown, green, black

    
    Servo pitch, roll;
  
    int pwm_roll, pwm_pitch;
    long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;

    void setup()
    
    {
    
    Serial.begin (115200);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
    pinMode(trigPin4, OUTPUT);
    pinMode(echoPin4, INPUT);
    pinMode(rollRead, INPUT);
    pinMode(pitchRead, INPUT);
    pitch.attach(13);
    roll.attach(12);
    }

    void loop() {
    
    SonarSensor(trigPin1, echoPin1);
    RightSensor = distance;
    Serial.print("Right: ");
    Serial.println(RightSensor);
    SonarSensor(trigPin2, echoPin2);
    FrontSensor = distance;
    Serial.print("Front: ");
    Serial.println(FrontSensor);
    SonarSensor(trigPin3, echoPin3);
    LeftSensor = distance;
    Serial.print("Left: ");
    Serial.println(LeftSensor);
    SonarSensor(trigPin4, echoPin4);
    BackSensor = distance;
    Serial.print("Back: ");
    Serial.println(BackSensor);

    pwm_roll = pulseIn(rollRead, HIGH);
    pwm_pitch = pulseIn(pitchRead, HIGH);

    Serial.print("Pwm Roll : ");
    Serial.println(pwm_roll);

    Serial.print("Pwm Pitch : ");
    Serial.println(pwm_pitch);
    
    
   
    

    //16 Cases for 4 Sensors
    

    //case 1: no obstacle at any sensor
    if (FrontSensor > 60 && BackSensor > 60 && LeftSensor > 60 && RightSensor > 60) {
      //Do nothing
    }

    //case 2: Obstacle at right sensor
    else if (FrontSensor > 60 && BackSensor > 60 && LeftSensor > 60 && RightSensor <= 60) {
      //Roll Left
      //pitch from rx.
      pwm_roll=1250;
    }

    //case 3: Obstacle at left sensor
    else if (FrontSensor > 60 && BackSensor > 60 && LeftSensor <= 60 && RightSensor > 60) {
      //Roll Right
      //pitch from rx.
      pwm_roll=1750;
    }

    //case 4: Obstacle at both left and right sensor
    else if (FrontSensor > 60 && BackSensor > 60 && LeftSensor <= 60 && RightSensor <= 60) {
      //Send zero roll
      //Pitch from rx.
      pwm_roll=1500;
    }

    //case 5: Obstacle at back sensor
    else if (FrontSensor > 60 && BackSensor <= 60 && LeftSensor > 60 && RightSensor > 60) {
      //Send roll from rx.
      //Pitch forward
      pwm_pitch=1250;
    }

    //case 6: Obstacle at back and right sensor
    else if (FrontSensor > 60 && BackSensor <= 60 && LeftSensor > 60 && RightSensor <= 60) {
      //Roll Left
      //Pitch forward
      pwm_roll=1250;
      pwm_pitch=1250;
    }

    //case 7: Obstacle at back and left sensor
    else if (FrontSensor > 60 && BackSensor <= 60 && LeftSensor <= 60 && RightSensor > 60) {
      //Roll Right
      //Pitch forward
      pwm_roll=1750;
      pwm_pitch=1250;
    }

    //case 8: Obstacle at back, left and right sensor
    else if (FrontSensor > 60 && BackSensor <= 60 && LeftSensor <= 60 && RightSensor <= 60) {
      //Zero Roll
      //Pitch forward
      pwm_roll=1500;
      pwm_pitch=1250;
    }

    //case 9: Obstacle at Front sensor
    else if (FrontSensor <= 60 && BackSensor > 60 && LeftSensor > 60 && RightSensor > 60) {
      //Roll from rx.
      //Pitch backward
      pwm_pitch=1750;
    }

    //case 9: Obstacle at Front sensor
    else if (FrontSensor <= 60 && BackSensor > 60 && LeftSensor > 60 && RightSensor > 60) {
      //Roll from rx.
      //Pitch backward
      pwm_pitch=1750;
    }

    //case 10: Obstacle at Front and right sensor
    else if (FrontSensor <= 60 && BackSensor > 60 && LeftSensor > 60 && RightSensor <= 60) {
      //Roll left.
      //Pitch backward
      pwm_roll=1250;
      pwm_pitch=1750;
    }

    //case 11: Obstacle at Front and left sensor
    else if (FrontSensor <= 60 && BackSensor > 60 && LeftSensor <= 60 && RightSensor > 60) {
      //Roll right.
      //Pitch backward
      pwm_roll=1750;
      pwm_pitch=1750;
    }

    //case 12: Obstacle at Front, left and right sensor
    else if (FrontSensor <= 60 && BackSensor > 60 && LeftSensor <= 60 && RightSensor <= 60) {
      //Roll zero.
      //Pitch backward
      pwm_roll=1500;
      pwm_pitch=1750;
    }

    //case 13: Obstacle at Front and back sensor
    else if (FrontSensor <= 60 && BackSensor <= 60 && LeftSensor > 60 && RightSensor > 60) {
      //Roll from rx.
      //Pitch zero.
      
      pwm_pitch=1500;
    }

    //case 14: Obstacle at Front, back and right sensor
    else if (FrontSensor <= 60 && BackSensor <= 60 && LeftSensor > 60 && RightSensor <= 60) {
      //Roll left.
      //Pitch zero.
       pwm_roll=1250;
      pwm_pitch=1500;
    }

    //case 15: Obstacle at Front, back and left sensor
    else if (FrontSensor <= 60 && BackSensor <= 60 && LeftSensor <= 60 && RightSensor > 60) {
      //Roll right.
      //Pitch zero
      pwm_roll=1750;
      pwm_pitch=1500;
    }

    //case 16: Obstacle at Front, left, right and back sensor
    else if (FrontSensor <= 60 && BackSensor <= 60 && LeftSensor <= 60 && RightSensor <= 60) {
      //loiter
      
    }
  
    pitch.writeMicroseconds(pwm_pitch);
    roll.writeMicroseconds(pwm_roll);
    delayMicroseconds(5);
  
   
    
    }

    void SonarSensor(int trigPin,int echoPin)
    {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 4500);
    distance = (duration/2) / 29.1;
    if (distance==0)
     distance = 100;
   
    }

