
#ifndef LIBRARY_H_
#define LIBRARY_H_

#define MAX_CHARS 80
#define MAX_FIELDS 5
#define COMMAND_NUM 9

typedef struct _USER_DATA
{
    char buffer[MAX_CHARS+1];
    uint8_t fieldCount;
    uint8_t fieldPosition[MAX_FIELDS];
    char fieldType[MAX_FIELDS];
} USER_DATA;


void getsUart0(USER_DATA* data);
int isAlpha(char c);
int isNum(char c);
void parseFields(USER_DATA* data);
bool stringsEqual(char *str1, char *str2);
bool isCommand(USER_DATA* data, const char strCommand[], uint8_t minArguments);
bool isValidCommand(USER_DATA* data);
char* getFieldString(USER_DATA* data, uint8_t fieldNumber);
int32_t getFieldInteger(USER_DATA* data, uint8_t fieldNumber);
int myAtoi(char s[]);

#endif
