/* Robo Project
 * Arduino Interpreter for the Raspberry Pi commands
 * Commands are specified in ReadMe file
 */
 

#define MSG_SRT 'S'
#define MSG_END '\n'
#define MAX_MSG_LENGTH 7
#define STATUS_MSG "Hello World!"

#define MOTOR 'M'
#define EYE 'E'
#define STATUS 'P'
#define READ 'R'
#define WRITE 'W'

//ERROR Codes
#define ERROR_MsgToLong "ERROR: Message to long"
#define ERROR_NoMsgEnd "ERROR: Recived message without end"
#define ERROR_NoMsgStart "ERROR: Recived message without start"
#define ERROR_NoComponendMatch "ERROR: No matching componend"
#define ERROR_MsgOpType "ERROR: No matching OP Type"
#define ERROR_MsgTypeNumber "ERROR: No matching Type Number"
#define ERROR_MsgData "ERROR: Data failure"

void interpret(char*);


#if 0
#define ComponendMask 0b11100000
#define ValueMask 0b00011111
#define COMPONEND(command) ((command & ComponendMask) >> 5)
#define VALUE(command) (command & ValueMask)
#endif
