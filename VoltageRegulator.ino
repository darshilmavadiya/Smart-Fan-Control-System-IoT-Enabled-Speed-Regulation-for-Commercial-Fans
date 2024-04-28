
// ........Function Declarations........
void FanSpeedWrite(void);
int FanRegFeedRead(void);
int FanSpeedByServer(void);

// Fan Regulator Pin/variable Configuration
int FanRegFeed = 0;   //regulator connected to analog pin
int FanRegMuxS = 15;  //select pin of MUX
int FanRegMuxD0 = 2;  // Data pin of MUX
int FanRegMuxD1 = 4;  // Data pin of MUX

// ........Variable Declarations........
int FanSpeedServer = 0, FanSpeedBoard = 0, FanSpeedSet = 0;
int Tem_board = 0,Tem_Server=0;



// ........setup Function start........
void setup() {

  Serial.begin(115200);

  pinMode(FanRegMuxS, OUTPUT);
  pinMode(FanRegMuxD0, OUTPUT);
  pinMode(FanRegMuxD1, OUTPUT);
  analogReadResolution(12);  //Analog Value 0-4096
}


// ........loop Function start........

void loop() {

  void FanSpeedWrite();
}

// ........Function Definition Start........


// function for set the final speed of fan
void FanSpeedWrite(void) {

   Tem_board = FanRegFeedRead();
   Tem_Server = FanSpeedByServer();

  Serial.println("Fan Speed read From Server:");
  Serial.print(Tem_Server);
  Serial.println("Fan Speed read From Fan Regulator:");
  Serial.print(Tem_board);

  if (Tem_board != FanSpeedBoard) {
    FanSpeedBoard = Tem_board;
    FanSpeedSet = Tem_board;
  }

  if (Tem_Server != FanSpeedServer) {
    FanSpeedBoard = Tem_Server;
    FanSpeedSet = Tem_Server;
  }

  switch (FanSpeedSet) {
    case 0:
      digitalWrite(FanRegMuxD0, 0);
      digitalWrite(FanRegMuxD1, 0);
      Serial.println("Final Speed of Fan:0");
      break;

    case 1:
      digitalWrite(FanRegMuxD0, 0);
      digitalWrite(FanRegMuxD1, 1);
      Serial.println("Final Speed of Fan:1");
      break;

    case 2:
      digitalWrite(FanRegMuxD0, 1);
      digitalWrite(FanRegMuxD1, 0);
      Serial.println("Final Speed of Fan:2");
      break;

    case 3:
      digitalWrite(FanRegMuxD0, 1);
      digitalWrite(FanRegMuxD1, 1);
      Serial.println("Final Speed of Fan:3");
      break;

    default:
      digitalWrite(FanRegMuxD0, 0);
      digitalWrite(FanRegMuxD1, 0);
      Serial.println("Final Speed of Fan:0");
      break;
  }
}

// Function for read the value of fan regulator feedback
int FanRegFeedRead(void) {
  int FanRegFeedValue = analogRead(FanRegFeed);

  if ((FanRegFeedValue > 99) && (FanRegFeedValue <= 1024)) {
    return 0;
  } else if ((FanRegFeedValue > 1024) && (FanRegFeedValue <= 2048)) {
    return 1;
  } else if ((FanRegFeedValue > 2048) && (FanRegFeedValue <= 3072)) {
    return 2;
  } else if (FanRegFeedValue > 3072) {
    return 3;
  } else {
    return 0;
  }
}

// Function for read the value from server to decide fan speed

int FanSpeedByServer(void) {

  if (Serial.available()) {
    int value = Serial.read();
// value must be (0<=value<=3)
    if (value >= 0 && value < 4) {
      return value;
    } else {
      return Tem_Server;
    }
  } else {
    return Tem_Server;
  }
}
