#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define ARSIZE 26

int main()
{
    bool count = true;
    printf("Welcome to variable counter! Please record your counts! Type X to end.\n");
    
    // initialise array of size 26 with zeros
    int cSet[26];
    for(int i = 0;i<ARSIZE;i++)
    {
        cSet[i]=0;
    }
    // keep counting while count bool is true
    while(count)
    {
        char ltr, Aclr, Nclr; //initialisers for user input and buffer clearers
        int val;
        
        printf("Input character variable a-z:\n");
        // get a letter from the user
        scanf("%c", &ltr);
        // keep reading all following characters to clear buffer
        Aclr = getchar();
        while(Aclr != '\n')
        {
            Aclr = getchar();
        }
        if(ltr == 'X' || isdigit(ltr))
        {
            count = false;
            break;
        }
        
        printf("Input count variable a-z:\n");
        
        // get a number from user
        scanf("%d", &val);
        // keep reading all following characters to clear buffer
        Nclr = getchar();
        while(Nclr != '\n')
        {
            Nclr = getchar();
        }
        
        //if user entered a valid letter, add to counter
        if(tolower(ltr) >= 'a' && tolower(ltr) <= 'z')
        {
            cSet[tolower(ltr) - 97] += val;
        }
    }
    
    //print all counter values which are more than zero
    for(int i =0;i<ARSIZE;i++)
    {
        if(cSet[i] > 0)
        {
            printf("%c - %d ", i+97, cSet[i]);
        }
    }
    return 0;
}