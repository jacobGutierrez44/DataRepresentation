#include <stdint.h>
#include <stdio.h>
#include <math.h>
void sub_convert(uint32_t n, double base)
{
    char temp[65]; //holds the converted char array, name kept as temp for consistency
    int pos = 0;
    double largestBase = 0;
    pos = n % (int)base;
    while((n - pow(base, largestBase)) > 0){largestBase++;} //finds the largest power that can be subtracted from n
}
int main()
{
    printf("%i", 257 & 256);
    return 0;
}