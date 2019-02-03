/* Robo Project
 * Arduino Interpreter for the Raspberry Pi commands
 * Commands are specified in ReadMe file
 */
 

#define MAX_MSG_LENGTH 7
#define MSG_END 0xFF
#define MSG_SRT 0xFF

#define STATUS  0x10
#define EYE     0x20
#define MOTOR   0x30
#define WRITE   0x01
#define READ    0x02


// ERROR Codes
#define ERROR_ASW            'F'
#define ERROR_MSG_LENGTH      1
#define ERROR_COMPONEND       2
#define ERROR_OPTYPE          3


void interpret(char*);
char* buildErrorString(char, char);
char* buildAnswerString(void);

