void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(3, OUTPUT);
}

void setAngle(int angle)
{
    Serial.print("ACK a: ");
    Serial.println(angle);
}

void setSpeed(int speed)
{
    Serial.print("ACK s: ");
    Serial.println(speed);
}

const int MAX_SIZE = 16;

int incomingByte = 0;
char buffer[MAX_SIZE];
int count = 0;

void loop()
{
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
                setSpeed(value);
            }
        }
        else
        {
            Serial.println("ACK e");
        }


        memset(&buffer[0], 0, sizeof(buffer));
        count = 0;
    }
}
