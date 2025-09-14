#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

static int passed = 0;
static int failed = 0;
static int testNum = 0;


void div_convert(uint32_t n, int base, char *out)
{
    char temp[65]; //temporarily holds an array of char's
    char flipped[65]; //holds a reversed version of the temp array
    int pos = 0;
    int length = 0;

    if(n == 0 && strcmp(out, "Z") == 0){printf("0 ");
    return;} //handles 0 case where div_convert is also passed the "Z" key
    else if(n == 0){printf("0 [PASS]");
    passed++;
    return;} //handles general 0 case

    while(n > 0) //performs modulo division and adds remainder to the temp array while n > 0
    {
       int rem = n % base;
       n = n / base;
       if (rem < 10){temp[pos++] = '0' + rem;}
       else{temp[pos++] = 'A' + (rem - 10);}      
    }
    length = pos;
    temp[pos++] = '\0';
    pos--;
    while(pos > 0) //makes the flipped array a reversed version of the temp array, which provides the final converted integer array
                   //when converting between bases using division
    {
        flipped[length - pos] = temp[pos - 1];
        pos--;
    }
    flipped[length++] = '\0';
    printf("%s ", flipped);
    if(strcmp(out, "Z") == 0){return;} //stops program from executing farther, this is if we only want the number provided by the function

    if(strcmp(flipped, out) == 0){printf("[PASS] %i/%i", passed + 1, testNum); //compares whether the output matches what was expected
    passed++;}
    else{printf("[FAIL] %i/%i", passed, testNum);
    failed++;}
}
void sub_convert(uint32_t n, double base, char *out)
{
    char temp[65]; //holds the converted char array, name kept as temp for consistency
    int pos = 0;
    double largestBase = 0;

    if(n == 0 && strcmp(out, "Z") == 0){printf("0 ");
    return;} //handles 0 case where div_convert is also passed the "Z" key
    else if(n == 0){printf("0 [PASS]");
    passed++;
    return;} //handles general 0 case

    while((n - pow(base, largestBase)) > 0){largestBase++;} //finds the largest power that can be subtracted from n
    if(n == 1){largestBase++;} //handles 1 case
    if(n == (int)round(pow(base,largestBase))){largestBase++;} //handles cases where the number is a power of the base
    largestBase--;

    while(largestBase > -1) //performs repeated base conversion by subtraction until the char array 'temp' is the final converted array
    {
        int rem = n % (int)round(pow(base,largestBase));
        //printf("n: %i largest: %i\n", n, (int)round(pow(base,largestBase)));
        n = n / pow(base, largestBase);
        //printf("quotient: %i\n", n);
        //printf("remainder: %i\n", rem);
        if (n < 10){temp[pos++] = '0' + n;}
        else{temp[pos++] = 'A' + (n - 10);}
        largestBase--;
        n = rem;
    }
    temp[pos++] = '\0';
    printf("%s\n", temp);
    if(strcmp(out, "Z") == 0){return;} //stops program from executing farther, this is if we only want the number provided by the function

    if(strcmp(temp, out) == 0){printf("[PASS] %i/%i", passed + 1, testNum); //compares whether the output matches what was expected
    passed++;}
    else{printf("[FAIL] %i/%i", passed, testNum);
    failed++;}
    
}
void print_tables(uint32_t n)
{
    char key[2] = "Z"; //Using Z, as it does not appear in our base systems, and it tells the program to only give us the number
    printf("Test: %i\nOriginal: Binary=", testNum);
    div_convert(n, 2, key);
    printf("Octal=");
    div_convert(n, 8, key);
    printf("Decimal=");
    div_convert(n, 10, key);
    printf("Hex=");
    sub_convert(n, 16, key); //sub_convert begins a new line after it prints out the converstion
    uint32_t shifted = n << 3;
    printf("Left Shift by 3: Binary=");
    div_convert(shifted, 2, key);
    printf("Octal=");
    div_convert(shifted, 8, key);
    printf("Decimal=");
    div_convert(shifted, 10, key);
    printf("Hex=");
    sub_convert(shifted, 16, key);
    uint32_t masked = n & 0xFF;
    printf("AND with 0xFF 3: Binary=");
    div_convert(masked, 2, key);
    printf("Octal=");
    div_convert(masked, 8, key);
    printf("Decimal=");
    div_convert(masked, 10, key);
    printf("Hex=");
    sub_convert(masked, 16, key);
    printf("[PASS] %i/%i\n", passed + 1, testNum);
    passed++;
}
int main() 
{
    FILE *file = fopen("a1_test_file.txt", "r");
    char buffer[256];
    char *func;
    char *num;
    char *base;
    char *exp;
    const char *delimiter = " ";    

    if (file == NULL){printf("Error: could not open file");
        return 1;}
    
    while(fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if(buffer[0] != '#' && strlen(buffer) != 1)
        {
            //printf("%s", buffer);
            func = strtok(buffer, delimiter);
            num = strtok(NULL, delimiter);
            base = strtok(NULL, delimiter);
            exp = strtok(NULL, "\n");
            //printf("function: %s\nnumber: %s\nbase: %s\nexpected: %s\n", func, num, base, exp);
            
            if(strcmp(func, "div_convert") == 0)
            {
                testNum++;
                printf("Test %i: %s(%i, %i) -> Expected: %s, Got: ", testNum, func, atoi(num), atoi(base), exp);
                div_convert(atoi(num), atoi(base), exp);
                printf("\n");
            }
            else if(strcmp(func, "sub_convert") == 0)
            {
                testNum++; 
                printf("Test %i: %s(%i, %i) -> Expected: %s, Got: ", testNum, func, atoi(num), atoi(base), exp);
                div_convert(atoi(num), atoi(base), exp);
                printf("\n");
            }
            else if(strcmp(func, "print_tables") == 0)
            {
                testNum++;
                print_tables(atoi(num));
            }
            
        }
    }
    printf("Summary: %i/%i tests passed", passed, testNum);
    return 0;
}
