#include <stdio.h>
#define SLen 1024
int main(){
  char name[SLen];
  char quest[SLen];
  char color[SLen];
  char dump[16];
  printf("Hello World!\n");
  printf("I was written by Mohammed Azad\n");
  printf("Bridgekeeper: What...is your name?\n");
  scanf("%1024[^\n]", name);
  scanf("%1[\n]",dump);
  printf("Bridgekeeper: Ahh your name is %s\n", name);
  printf("Bridgekeeper: What...is your quest?\n");
  scanf("%1024[^\n]", quest);
  scanf("%1[\n]",dump);
  printf("Bridgekeeper: Ahh your purpose is %s\n", quest);
  printf("Bridgekeeper: What...is your favorite color?\n");
  scanf("%1024[^\n]", color);
  scanf("%1[\n]",dump);
  printf("Bridgekeeper: Ahh your favorite color is %s\n", color);
  printf("Bridgekeeper: Right, off you go.\n");
  return 0;}
  
