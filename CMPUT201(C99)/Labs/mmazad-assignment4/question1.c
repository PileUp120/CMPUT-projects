#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max_rounds 32000
#define max_dim 16000

void setupArray(int rows, int cols, int map[rows][cols]);

void printArray(int rows, int cols, int map[rows][cols]);

void calculateNextMap(int rows, int cols, int map[rows][cols], int nextMap[rows][cols], int zeroArray[rows][cols]);

void setNextMapAsMap(int rows, int cols, int map[rows][cols], int nextMap[rows][cols]);

int main()
{
    printf("Enter rounds, rows, columns and the initial grid map separated by newline or space: ");
    
    int rounds,rows,cols;
    scanf("%d",&rounds);
    scanf("%d",&rows);
    scanf("%d",&cols);
    if (rounds >max_rounds || rows>max_dim || cols>max_dim){
        printf("Invalid input!");
        exit(1);
    }
    
    int map[rows][cols];
    int zeroArray[rows][cols];
    for (int row = 0; row < rows ; row++)
    {
        for (int col = 0; col < cols ; col++) 
        {
            zeroArray[row][col] = 0;
        }
    }
    setupArray(rows,cols,map);
    printf("%d\n",rounds);
    printf("%d %d\n",rows,cols);
    printArray(rows, cols, map);
    int nextMap[rows][cols];
    for (int row = 0; row < rows ; row++)
    {
        for (int col = 0; col < cols ; col++) 
        {
            nextMap[row][col] = 0;
        }
    }
    
    for (int step = 0; step < rounds; step++)
    {
        printf("Round %d!\n", step+1);
        calculateNextMap(rows, cols, map, nextMap, zeroArray);
        printArray(rows, cols, nextMap);
        setNextMapAsMap(rows, cols, map, nextMap);
        
    }
    
    return 0;
}

void setupArray(int rows, int cols, int map[rows][cols])
{
    int cell;
    for (int row = 0; row < rows; row++) 
    {
        for (int col = 0; col < cols; col++) 
        {
            scanf("%d",&cell);
            map[row][col] = cell;
        }
    }
}

void printArray(int rows, int cols, int map[rows][cols]) 
{
   for (int row = 0; row < rows; row++) 
   {
        for (int col = 0; col < cols; col++) 
        {
            printf("%d\t", (map[row][col]));
        }
        printf("\n");
    }
}

void calculateNextMap(int rows, int cols, int map[rows][cols], int nextMap[rows][cols], int zeroArray[rows][cols])
{
    bool allZero = true;
    for (int row = 0; row < rows; row++) 
    {
        for (int col = 0; col < cols; col++) 
        {
            if (map[row][col] != zeroArray[row][col])
            {
                allZero = false;
                break;
            }
        }
    }
    
    if(allZero)
    {
        nextMap[0][0] = 1;
    }
    else
    {
        for (int row = 0; row < rows-1; row++) 
        {
            for (int col = 0; col < cols; col++) 
            {
                nextMap[row][col] = (map[row][col] + map[row+1][col])%10 ;
            }
            
        }
        
        for (int row = 1; row < rows; row++) 
        {
            for (int col = 0; col < cols; col++) 
            {
                nextMap[row][col] = (nextMap[row][col] + map[row-1][col])%10 ;
            }
            
        }
        
        for (int col= 0; col < cols-1; col++) 
        {
            for (int row = 0; row < rows; row++) 
            {
                nextMap[row][col] = (nextMap[row][col] + map[row][col+1])%10 ;
            }
            
        }
        
        for (int col= 1; col < cols; col++)
        {
            for (int row = 0; row < rows; row++) 
            {
                nextMap[row][col] = (nextMap[row][col] + map[row][col-1])%10;
            }
            
        }
    }    
}

void setNextMapAsMap(int rows, int cols, int map[rows][cols], int nextMap[rows][cols])
{
    for (int row = 0; row < rows; row++) 
    {
        for (int col = 0; col < cols; col++) 
        {
            map[row][col] = nextMap[row][col];
        }
    }
}