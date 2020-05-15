#define   K1  1
#define   K2  2

#define   MODE1_L1  0
#define   MODE1_L2  1

#define   MODE2_L1  2
#define   MODE2_L2  3

#define   MODE1_L1_LED  A2
#define   MODE1_L2_LED  A3

#define   MODE2_L1_LED  A5
#define   MODE2_L2_LED  A4

#define   M1_key  A1
#define   M2_key  A0

#define   MOTOR_PIN   10
#define   V1_PIN      8
#define   V2_PIN      7

#define MOTOR_ON  digitalWrite(MOTOR_PIN, HIGH)
#define MOTOR_OFF digitalWrite(MOTOR_PIN, LOW)

#define V1_ON   digitalWrite(V1_PIN, HIGH)
#define V1_OFF  digitalWrite(V1_PIN, LOW)

#define V2_ON   digitalWrite(V2_PIN, HIGH)
#define V2_OFF  digitalWrite(V2_PIN, LOW)

//-----keypad var
bool key_available;
uint8_t key_no;
uint8_t res_key;
uint32_t ref_debounce;
bool debounced;

//-------
uint8_t new_mode_lavel;
uint8_t mode_lavel;
uint8_t stage;
uint32_t ref_delay;
uint32_t delay_P;
bool Delay;

//-----
void F_mode1_L1();
void F_mode1_L2();
void F_mode2_L1();
void F_mode2_L2();

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(V1_PIN, OUTPUT);
  pinMode(V2_PIN, OUTPUT);

  pinMode(M1_key, INPUT_PULLUP);
  pinMode(M2_key, INPUT_PULLUP);


  pinMode(MODE1_L1_LED, OUTPUT);
  pinMode(MODE1_L2_LED, OUTPUT);
  pinMode(MODE2_L1_LED, OUTPUT);
  pinMode(MODE2_L2_LED, OUTPUT);

  digitalWrite(MODE1_L1_LED, LOW);
  digitalWrite(MODE1_L2_LED, HIGH);
  digitalWrite(MODE2_L1_LED, HIGH);
  digitalWrite(MODE2_L2_LED, HIGH);
  
  Serial.begin(9600);
}




void loop() {
  // put your main code here, to run repeatedly:
  uint8_t temp = read_key();
  if (temp == K1)
  {
    Serial.print("key = ");
    Serial.println(temp, HEX);
    if (new_mode_lavel == MODE1_L1)
    {
      new_mode_lavel = MODE1_L2;
      digitalWrite(MODE1_L1_LED, HIGH);
      digitalWrite(MODE1_L2_LED, LOW);
      digitalWrite(MODE2_L1_LED, HIGH);
      digitalWrite(MODE2_L2_LED, HIGH);
    }
    else
    {
      new_mode_lavel = MODE1_L1;
      digitalWrite(MODE1_L1_LED, LOW);
      digitalWrite(MODE1_L2_LED, HIGH);
      digitalWrite(MODE2_L1_LED, HIGH);
      digitalWrite(MODE2_L2_LED, HIGH);
    }
  }
  else if (temp == K2)
  {
    Serial.print("key = ");
    Serial.println(temp, HEX);
    if (new_mode_lavel == MODE2_L1)
    {
      new_mode_lavel = MODE2_L2;
      digitalWrite(MODE1_L1_LED, HIGH);
      digitalWrite(MODE1_L2_LED, HIGH);
      digitalWrite(MODE2_L1_LED, LOW);
      digitalWrite(MODE2_L2_LED, HIGH);
    }
    else
    {
      new_mode_lavel = MODE2_L1;
      digitalWrite(MODE1_L1_LED, HIGH);
      digitalWrite(MODE1_L2_LED, HIGH);
      digitalWrite(MODE2_L1_LED, HIGH);
      digitalWrite(MODE2_L2_LED, LOW);
    }
  }

  switch(mode_lavel)
  {
    case MODE1_L1:
    F_mode1_L1();
    break;
    
    case MODE1_L2:
    F_mode1_L2();
    break;
    
    case MODE2_L1:
    F_mode2_L1();
    break;
    
    case MODE2_L2:
    F_mode2_L2();
    break;
  }
  
  keypad_hamdler();
}



//-------------------------------------------------


void add_delay(uint32_t d)
{
  ref_delay = millis();
  delay_P = d;
  Delay = true;
}

void F_mode1_L1()
{ 
  if (Delay)
  if (!(millis() - ref_delay > delay_P))
  return;
  Delay = false;
  Serial.print("M1_L1,  stage = ");
  Serial.println(stage);
  
  switch(stage)
  {
    case 1:
    MOTOR_ON;
    V1_OFF;
    V2_OFF;
    add_delay(4000);
    stage++;
    break;

    case 2:
    MOTOR_OFF;
    add_delay(1000);
    stage++;
    break;

    case 3:
    MOTOR_ON;
    V1_ON;
    add_delay(3000);
    stage++;
    break;

    case 4:
    MOTOR_OFF;
    add_delay(1000);
    stage++;
    break;

    case 5:
    MOTOR_ON;
    V2_ON;
    add_delay(3000);
    stage++;
    break;

    case 6:
    MOTOR_OFF;
    add_delay(1000);
    stage++;
    break;

    case 7:
    V2_OFF;
    add_delay(1000);
    stage++;
    break;

    case 8:
    V1_OFF;
    add_delay(1000);
    stage++;
    break;

    case 9:
    V1_ON;
    V2_ON;
    add_delay(1200);
    mode_lavel = new_mode_lavel;
    stage = 1;
    break;

    default:
    stage = 1;
    break;
  }
}


void F_mode1_L2()
{
  if (Delay)
  if (!(millis() - ref_delay > delay_P))
  return;
  Delay = false;

  Serial.print("M1_L2,  stage = ");
  Serial.println(stage);
  
  switch(stage)
  {
    case 1:
    MOTOR_ON;
    V1_OFF;
    V2_OFF;
    add_delay(700);
    stage++;
    break;

    case 2:
    MOTOR_OFF;
    add_delay(500);
    stage++;
    break;

    case 3:
    MOTOR_ON;
    V1_ON;
    add_delay(700);
    stage++;
    break;

    case 4:
    MOTOR_OFF;
    add_delay(500);
    stage++;
    break;

    case 5:
    MOTOR_ON;
    V2_ON;
    add_delay(700);
    stage++;
    break;

    case 6:
    MOTOR_OFF;
    add_delay(500);
    stage++;
    break;

    case 7:
    V2_OFF;
    add_delay(250);
    stage++;
    break;

    case 8:
    V1_OFF;
    add_delay(250);
    stage++;
    break;

    case 9:
    V1_ON;
    V2_ON;
    add_delay(500);
    mode_lavel = new_mode_lavel;
    stage = 1;
    break;

    default:
    stage = 1;
    break;
  }
}
void F_mode2_L1()
{
  if (Delay)
  if (!(millis() - ref_delay > delay_P))
  return;
  Delay = false;
  Serial.print("M2_L1,  stage = ");
  Serial.println(stage);
  
  switch(stage)
  {
    case 1:
    MOTOR_ON;
    V1_OFF;
    V2_OFF;
    add_delay(1000);
    stage++;
    break;

    case 2:
    MOTOR_ON;
    V1_ON;
    add_delay(1000);
    stage++;
    break;

    case 3:
    MOTOR_ON;
    V2_ON;
    add_delay(1000);
    stage++;
    break;

    case 4:
    MOTOR_OFF;
    add_delay(500);
    stage++;
    break;

    case 5:
    V2_OFF;
    add_delay(250);
    stage++;
    break;

    case 6:
    V1_OFF;
    add_delay(250);
    stage++;
    break;

    case 7:
    V1_ON;
    V2_ON;
    add_delay(500);
    mode_lavel = new_mode_lavel;
    stage = 1;
    break;

    default:
    stage = 1;
    break;
  }
}


void F_mode2_L2()
{
  if (Delay)
  if (!(millis() - ref_delay > delay_P))
  return;
  Delay = false;
  Serial.print("M2_L2,  stage = ");
  Serial.println(stage);
  switch(stage)
  {
    case 1:
    MOTOR_ON;
    V1_OFF;
    V2_OFF;
    add_delay(700);
    stage++;
    break;

    case 2:
    MOTOR_ON;
    V1_ON;
    add_delay(700);
    stage++;
    break;

    case 3:
    MOTOR_ON;
    V2_ON;
    add_delay(700);
    stage++;
    break;

    case 4:
    MOTOR_OFF;
    add_delay(500);
    stage++;
    break;

    case 5:
    V2_OFF;
    add_delay(250);
    stage++;
    break;

    case 6:
    V1_OFF;
    add_delay(250);
    stage++;
    break;

    case 7:
    V1_ON;
    V2_ON;
    add_delay(500);
    mode_lavel = new_mode_lavel;
    stage = 1;
    break;

    default:
    stage = 1;
    break;
  }
}

void keypad_hamdler()
{
  uint8_t temp = 0xFF;
  if (!digitalRead(M1_key) && digitalRead(M2_key))
  temp = 1;
  else if (digitalRead(M1_key) && !digitalRead(M2_key))
  temp = 2;

  if (temp != res_key)
  {
    debounced = false;
    res_key = temp;
    ref_debounce = millis();
  }

  if (!debounced)
  if (millis() - ref_debounce >= 50)
  {
    key_no = res_key;
    debounced = true;
    if (key_no != 0xFF)
    key_available = true;
  }
}

uint8_t read_key()
{
  if (key_available)
  {
    key_available = false;
    return key_no;
  }
  return 0xFF;
}
