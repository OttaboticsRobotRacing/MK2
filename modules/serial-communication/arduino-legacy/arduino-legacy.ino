/**
 * Divides a given PWM pin frequency by a divisor.
 * 
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 * 
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 * 
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 * 
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://forum.arduino.cc/index.php?topic=16612#msg121031
 */
const int CH1 = 9;
const int CH2 = 10;

int incomingByte = 0;
int ang=47;
int vel=47;

const int MAX_SIZE = 16;
char buffer[MAX_SIZE];
int count = 0;

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void setAngle(int angle)
{
    ang=angle;    
    Serial.print("ACK a: ");
    Serial.println(angle);
}

void setVelocity(int velocity)
{
    vel=velocity;
    Serial.print("ACK s: ");
    Serial.println(velocity);
}
void setup() {
  Serial.begin(9600);
  setPwmFrequency(CH1, 256);     // CH1: Stearing
  setPwmFrequency(CH2, 256);     // CH2: Speed Control
  delay(2000);
}

void loop() {
  if (Serial.available() > 0)
    {
        count = 0;
        //Serial.println("---SERIAL AVAILABLE---");
        while (Serial.available())
        {
            incomingByte = Serial.read();

            //Serial.println(char(incomingByte));

            delay(5);


            if (count >= MAX_SIZE-1)
            {
                count = 0;
                memset(&buffer[0], 0, sizeof(buffer));
                return;
            }

            buffer[count] = char(incomingByte);
            count++;
        }
        //buffer[count] = '\0';

        //Serial.print("buffer: ");
        //Serial.println(buffer);

        String b = (buffer);


        if (b.length() >= 3 && b.length() <= 5)
        {
            int value = 0;
            if (b.length() == 3)
            {
                char tmp[1];
                tmp[0] = b[1];
                value = atoi(tmp);
            }
            else if (b.length() == 4)
            {
                char tmp[2];
                tmp[0] = b[1];
                tmp[1] = b[2];
                value = atoi(tmp);
            }
            else if (b.length() == 5)
            {
                char tmp[3];
                tmp[0] = b[1];
                tmp[1] = b[2];
                tmp[2] = b[3];
                value = atoi(tmp);
            }


            if (b[0] == 'a')
            {
                setAngle(value);
            }
            else if (b[0] == 's')
            {
                setVelocity(value);
            }
        }
        else
        {
            Serial.println("ACK e");
        }


        memset(&buffer[0], 0, sizeof(buffer));
        count = 0;
    }
  
  analogWrite (CH1, ang); delay(10); //tweak delay time
  analogWrite (CH2, vel); delay(10); //tweek delay time
  //analogWrite (CH1, 32); delay(2000);       // Left    @1ms  
  //analogWrite(CH1, 50);  delay(2000);       // Neutral @1.615ms
  //analogWrite(CH1, 62);  delay(2000);       // Right   @1.975ms
  
  //analogWrite (CH2, 32); delay(2000);       // Back    @1ms
  //analogWrite(CH2, 47);  delay(2000);       // Neutral @1.5ms
  //analogWrite(CH2, 65);  delay(2000);       // Forward @2ms
}
