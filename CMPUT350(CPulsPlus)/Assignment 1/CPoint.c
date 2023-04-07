#include <stdio.h>
#include <stdlib.h>

typedef struct {	//define structure Point with attribues x and y
        int x,y;
    } Point;
    
void point_init (Point *p); //declaration for pointer initialization function

void point_add (Point *p, Point *const q); //declaration for pointer addition function

void point_print (Point *p); //declaration for pointer printing function

int main()
{
    const int N = 200;
    Point sum;
    point_init(&sum); //create and initialize Point object sum
    Point *A = malloc(N*sizeof(Point)); /*allocate memory for 200 Point objects and return the address of
    the first memory block to A*/
    
    for (int i=0; i < N; ++i) { /*for every int from 0 to N-1, set x value of A[i] to i and y value of A[i]
    to -i, then add the current x and y values of A[i] to the x and y values of sum*/
        A[i].x = i; A[i].y = -i;
        point_add(&sum, &A[i]);
    }
    
    point_print(&sum); //print the x and y values of sum
    free(A); //free memory saved for A
    
    return 0;
}

void point_init (Point *p) { //initialize point object by setting it's x and y values to 0
    p->x = 0;
    p->y = 0;
}

void point_add (Point *p, Point *const q) { /*add the x and y values of q to the x and y values of
    p, while making sure not to alter the values of q, as indicated by const*/
    p->x += q->x;
    p->y += q->y;
}

void point_print (Point *p) { /*print the x and y values of p in this format [x,y]*/
    printf("[%d,%d]\n", p->x, p->y);
}