#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void Trib(int inp)
{
    //initialise values for tribonacci function
    unsigned long t1 = 0, t2 = 0, t3 = 1, tn;
    double f1 = 0, f2 = 0, f3 = 1, fn;
    //calcualte all of the different format values for output
    if(inp == 1 || inp == 0)
    {
        tn = 0;
        fn = 0;
    }
    else if(inp == 2)
    {
        tn = 1;
        fn = 1;
    }
    else
    {
        for(int i = 2;i < inp;++i)
        {
            tn = t1 + t2 + t3;
            t1 = t2;
            t2 = t3;
            t3 = tn;
        }
        for(int j = 2;j < inp;++j)
        {
            fn = f1 + f2 + f3;
            f1 = f2;
            f2 = f3;
            f3 = fn;
        }
    }
    printf("16bit Tribonacci %hi\n", (short)tn);
    printf("32bit Tribonacci %u\n", (unsigned)tn);
    printf("64bit Tribonacci %lu\n", tn);
    printf("Float Tribonacci  %.6e\n", (float)fn);
    printf("Double Tribonacci  %.6e\n", (double)fn);
    
}

int main()
{
    printf("Tribonacci! Type in a positive tribonacci input:");
    unsigned pos;
    char inp;
    fgets(&inp, 5, stdin); //get input from user
    float pass = atof(&inp); //get float value
    pos = (unsigned)pass; //make an unsigned version to test for negative or decimal
    if(pos == pass && pass <= 1023 && (isdigit(inp) || inp == '\n')) //pass to function if all values correct
    {
        Trib((int)pass);
    }
    else
    {
        printf("invalid input");
        exit(1);
    }
    

    return 0;
}