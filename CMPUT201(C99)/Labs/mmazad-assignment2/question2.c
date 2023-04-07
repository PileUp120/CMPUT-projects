#include <stdio.h>
#include <stdlib.h>

int main()
{
    int input, line, num, u; //initialise storage for user input, line number in loop, number to print and loop control for printing underscore
    printf("Enter a number between 1 and 9: ");
    scanf("%d", &input);
    if(input < 1 || input > 9) //exit with error code 1 if invalid input
    {
        printf("Invalid input\n");
        exit(1);
    }
    
    for(line = 1;line <= input; line++) //loop to go line by line of output
    {
        for(u = 0; u < (input-line); u++) //pad with underscores based on difference between line number and user input
        {
            printf("_");
        }
        for(num=line;num>1;num--) //print numbers in sequence from line number to 2
        {
            printf("%d",num);
        }
        for(num=1;num<=line;num++) //print numbers in sequence from 1 to line number
        {
            printf("%d",num);
        }
        for(u = 0; u < (input-1); u++) //pad with one less underscores than user input 
        {
            printf("_");
        }
        for(num=(1+input-line);num > 1;num--) //print numbers in sequence from input to 2
        {
            printf("%d", num);
        }
        for(num=1;num <= (input - line + 1);num++) //print numbers in sequence from 1 to input
        {
            printf("%d", num);
        }
        for(u = input-1; u > (input-line); u--) //pad with underscores based on line number
        {
            printf("_");
        }
        printf("\n");
    }

    return 0;
}
