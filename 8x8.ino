const int units = 8;
const int units_index = units - 1;

const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;

byte matrix[units + 1] = {0};

class Column
{
  public:
    Column(){
      this->_byte = 0;
      this->y = -1;
      this->moving = false;
      this->heading = 0;
    }
    void set_y(){
      bitSet(_byte, y);
    }
    void move(){
      y += heading;
    }
    void set_bit(int bit_id){
      bitSet(_byte, bit_id);
    }
    void set_byte(byte new_byte){
      _byte = new_byte;
    }
    void write_bit(int y, int value){
      bitWrite(_byte, y, value);
    }
    int read_bit(int y){
      return bitRead(_byte, y);
    }
    byte _byte;
    int y;
    bool moving;
    int heading;
};

Column columns[sq(units)];

// replacements for digitalWrite
#define setPin(b) ( (b)<8 ? PORTD |=(1<<(b)) : PORTB |=(1<<(b-8)) )
#define clrPin(b) ( (b)<8 ? PORTD &=~(1<<(b)) : PORTB &=~(1<<(b-8)) )

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  randomSeed(analogRead(A7));
  Serial.begin(9600);
}

void loop() {
  all_off();
  fadder_rows();
  fadder_levels();
  square();
  cube();
  ping_pong();
  wave();
  text();
  rain(true);
  rain(false);
//  rain_old(false);
//  rain_old(true);
  snake_game();
}

void all_off() {
  for(int i = 0; i < sq(units); i++){
    columns[i].set_byte(0);
  }

  for (int i = 0; i < 9; i++){
    matrix[i] = 0;
  }

  deploy_matrix();
}

int get_column_id(int x, int z){
  return x + (z * units);
}

void update_matrix(int duration){
  update_matrix_no_clear(duration);

  all_off();
}

void update_matrix_no_clear(int duration){
  unsigned long start = millis();

  while(millis() - start < duration) {
    for (int y = 0; y < units; y++){
      for (int z = 0; z < units; z++){
        for (int x = 0; x < units; x++){
          int c = get_column_id(x, z);

          if (columns[c].read_bit(y)){
            bitSet(matrix[z], x);
            bitSet(matrix[8], y);
          }
        }
        deploy_matrix();
        matrix[z] = 0;
      }
      bitClear(matrix[8], y);
    }
  }
}
void deploy_matrix(){
  clrPin(latchPin);

  // replacement for shiftOut()
  for (int m = 8; m >= 0; m--){
    for (uint8_t i = 8; i > 0; i--)  {
      if (!!(matrix[m] & (1 << (i - 1)))){
        setPin(dataPin);
      } else {
        clrPin(dataPin);
      }

      setPin(clockPin);
      clrPin(clockPin);
    }
  }

  setPin(latchPin);
}
