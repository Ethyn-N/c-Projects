#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define CYCLE 360

float DegToRad(float deg);

int main()
{
    float deg;
    float radians;
    
    printf("Enter an angle in degrees: ");
    scanf("%f", &deg);
    
    radians = DegToRad(deg);
    
    printf("%.2f radians\n", radians);
    
    return 0;
}

float DegToRad(float deg)
{
    int numOfcycles = deg/CYCLE;
    float reduced;
    float radians;
    
    if(fmod(deg,CYCLE) != 0)
        reduced = (deg - (CYCLE * numOfcycles));
    else if(numOfcycles > 0)
        reduced = CYCLE;
    else
        reduced = -CYCLE;                
 
        
    if((deg <= CYCLE && deg >= 0) || (deg < 0 && deg >= -CYCLE))
        radians = deg * (M_PI/180); 
    else
        radians = reduced * (M_PI/180);
        
    return radians; 
}
