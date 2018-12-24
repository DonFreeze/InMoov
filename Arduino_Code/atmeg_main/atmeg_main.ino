
#define MSG_START '\1'
#define MSG_END  '\0'
#define MSG_LENGTH 6     // Max length of message in byte

int received_num_bytes = 0;
char receivedChars[MSG_LENGTH]; // an array to store the received data
boolean newData = false;


void setup() 
{
  Serial.begin(9600);
}


void loop() 
{

  ReadMessage();
  WriteMessage();
  
}



void ReadMessage()
{
  static byte index = 0;
  char received_char;
  
  if (Serial.available() > 0 && newData == false) 
  {

    if (Serial.read() == '\1') // start of command
    {
      
      while (Serial.available() > 0 && newData == false) 
      {
        
        received_char = Serial.read();
        
        if (received_char != '\0') 
        {
          receivedChars[index] = received_char;
          index++;
          
          if (index >= MSG_LENGTH) 
          {
            index = MSG_LENGTH - 1;
          }
        }
        else 
        {
          received_num_bytes = index;
          receivedChars[index] = '\0'; // terminate the string
          index = 0;
          newData = true;
        }
      }
    }
    else // ERROR
    {
      Serial.print("ERROR ");
    }
  }
}

void WriteMessage() 
{
  
  if (newData == true) 
  {
    Serial.print("Received message: ");
    Serial.print(received_num_bytes);
    Serial.println(receivedChars);
    newData = false;
  }
}
