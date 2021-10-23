#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "clock.h"
#include "gpio.h"
#include "wait.h"
#include "library.h"


void getsUart0(USER_DATA* data)
{
    uint8_t count = 0;

    while(count <= MAX_CHARS)
    {
        if(count == MAX_CHARS)
        {
            data->buffer[count+1] = '\0';
        }
        char input = getcUart0();

        if(input >= 32 && input != 127)
        {
            data->buffer[count] = input;
            count++;
        }
        if((input == 8 || input == 127) && count > 0)
        {
            count--;
        }
        if(input == 13)
        {
            data->buffer[count] = '\0';
            return;
        }
    }
    return;
}
int isAlpha(char c)
{
    if((c > 57 && c < 127) || (c > 32 && c < 48))
        return 1;
    return 0;
}
int isNum(char c)
{
    if(c > 47 && c < 57)
        return 1;
    return 0;
}
void parseFields(USER_DATA* data)
{
    //loop until null terminator
    //bool firstSeen Var = true when buffer[i] != num | alpha

    uint8_t i = 0;
    int seen = 0;
    data->fieldCount = 0;
    while(data->buffer[i] != '\0') //read until null terminator. Don't read the whole buffer
    {
        if(isAlpha(data->buffer[i]) || isNum(data->buffer[i]))
        {
            if(seen == 0) //new word or number
            {
                data->fieldPosition[data->fieldCount] = i;
                if(isNum(data->buffer[i]))
                {
                    data->fieldType[data->fieldCount] = 'n';
                }
                else
                {
                    data->fieldType[data->fieldCount] = 'a';
                }
                data->fieldCount++;

            }
            seen = 1;
        }
        else
        {
            seen = 0;
            data->buffer[i] = '\0';
        }
        if(data->fieldCount == MAX_FIELDS)
            return;
        i++;
    }
}
bool stringsEqual(char *str1, char *str2) {
    uint8_t str1Length = 0;
    uint8_t str2Length = 0;
    //kill
    //str1Length = 0,1,2,3,4
    while(str1[str1Length] != '\0')
        str1Length++;
    while(str2[str2Length] != '\0')
        str2Length++;
    if(str1Length != str2Length)
        return false;
    uint8_t i = 0;
    for(i = 0; i < str1Length; i++)
    {
        if(str1[i] != str2[i])
            return false;
    }
    return true;
}
bool isCommand(USER_DATA* data, const char strCommand[], uint8_t minArguments)
{
    uint8_t i = 0;
    char * temp = &data->buffer[data->fieldPosition[0]];
    for(i = 0; temp[i] != '\0'; i++)
    {
        if(strCommand[i] != temp[i])
            return false;
    }
    if(data->fieldCount <= minArguments)
        return false;

    return true;
}
bool isValidCommand(USER_DATA* data)
{
    char commands[][10] = {"reboot", "ps", "ipcs", "kill", "pi", "preempt", "sched", "pidof"};
    char * argumentOne = &data->buffer[data->fieldPosition[0]];
    uint8_t argumentNumber = data->fieldCount;
    uint8_t i = 0;
    for(i = 0; i < 9; i++) {
        if(stringsEqual(commands[i], argumentOne))
            return true;
    }
    if(argumentNumber == 2) {
        char * argumentTwo = &data->buffer[data->fieldPosition[1]];
        if(stringsEqual(argumentTwo, "&"))
            return true;
    }
    return false;
}

char* getFieldString(USER_DATA* data, uint8_t fieldNumber)
{
    if(data->fieldType[fieldNumber] == 'a')
        return &data->buffer[data->fieldPosition[fieldNumber]];

    return 0;
}

int32_t getFieldInteger(USER_DATA* data, uint8_t fieldNumber)
{
    if(data->fieldType[fieldNumber] == 'n')
    {
        char * temp = &data->buffer[data->fieldPosition[fieldNumber]];
        int32_t sum = 0;
        int i = 0;
        while(temp[i] != '\0')
        {
            int32_t currentInteger = temp[i] - 48;
            sum = (sum * 10) + currentInteger;
            i++;
        }
        return sum;
    }
    return 0;
}
int myAtoi(char s[])
{
    //discard all white spaces: Loop over the string until current character is not space
    //go to the next char & check if the character is a negative, positive or a number.
    //create an int sign = 1. if the current char== neg -> sign = -1 and incr iterator; if current char==pos -> sign = 1 and incr iterator. if s[0] is not an int or a sign, return 0;
        //loop over the string while s[i] is a number, break if the current sum> INT_MAX or sum < INT_MIN.
//        putsUart0(&s);
//        putsUart0("\n");
//        putcUart0('\n');
//        char s[] = data->buffer;

//        putcUart0(s[0]);
//        putcUart0(s[1]);

        char temp[50];
        int i = 0;
        int sign = 1;
        long sum = 0;
        while(s[i] == ' ') {
            i++;
        }
        if(s[i] == '-'|| s[i] =='+'|| (s[i] > 47 && s[i] < 58)) {
            if(s[i] == '-') {
                sign = -1;
                i++;
                putsUart0("neg\n");
            } else if(s[i] == '+') {
                sign = 1;
                i++;
            }
        } else {
            return 0;
        }
//        putcUart0(s[1]);
        while(s[i] > 47 && s[i] < 58) {
            int currentInteger = s[i] - 48;
            sum = (sum * 10) + currentInteger;
//            sprintf(temp, "%d",sum);
//            putsUart0(s);
//            if(sum > 2147483647)
//                break;
//            else if (sum < -2147483648)
//                break;
        i++;
    }

    sum = sum * sign;

//    if(sum > 2147483647)
//            return 2147483647;
//    else if (sum < -2147483648)
//            return -2147483648;

    return sum;
}
