#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#define DOORS 3

// A function that gets a valid door input from the user
int chooseDoor()
{
    int choice = 0;
    while (choice < 1 || choice > DOORS) //repeatedly ask user for input unless users enters 1,2 or 3
    {
        printf("Choose a door from 1 to 3: ");
        scanf("%d", &choice);
	getchar(); //get rid of trailing newline
    }
    return choice;
}

// A function to get a valid yes or no response from the user
bool validateYn()
{
    char yn[1];
    char dump[16]; //buffer to get rid of newline
    scanf("%1[^\n]", yn);
    scanf("%1[\n]",dump);
    while (yn[0] != 'Y' && yn[0] != 'y' && yn[0] != 'N' && yn[0] != 'n')
    {
        printf("Error: Please enter Y or N: ");
        scanf("%1[^\n]", yn);
        scanf("%1[\n]",dump);
    }
    if (yn[0] == 'Y' || yn[0] == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    bool play = true; //conditional boolean to repeat the game
    while (play)
    {
        int car, shown, other, choice; //initialisers for the door with the car, door that monty will reveal, the remaining door and door chosen by player
        bool swap;
        car = 1 + rand() % DOORS;      //select a random door between 1 and 3
        choice = chooseDoor(); //call function to get user input of chosen door
        printf("You chose door #%d\n", choice);
        // A loop to find the lowest door that is not picked by the user and has a goat behind it
        for (int i = 1; i <= DOORS; i++) 
        {
            if (i == car || i == choice)
            {
                continue;
            }
            shown = i;
            break;
        }
        // Switch statement to find the door besides the one user chose and the one Monty revealed
        switch(choice)
        {
            case 1:
                switch(car)
                {
                    case 1:
                        other = 3;
                        break;
                    case 2:
                        other = 2;
                        break;
                    default:
                        other = 3;
                        break;
                }
                break;
            case 2:
                switch(car)
                {
                    case 1:
                        other = 1;
                        break;
                    case 2:
                        other = 3;
                        break;
                    default:
                        other = 3;
                        break;
                }
                break;
            default:
                switch(car)
                {
                    case 1:
                        other = 1;
                        break;
                    case 2:
                        other = 2;
                        break;
                    default:
                        other = 2;
                        break;
                }
                break;
        }
        printf("Monty opens door #%d, revealing a goat!\nWould you like to switch to door #%d? ", shown, other);
        swap = validateYn();
        // Change user choice if user says yes to swap
        if (swap)
        {
            choice = other;
        }
        // win if user choice had car, lose otherwise
        if (choice == car)
        {
            printf("Monty opens door #%d, revealing a car! You win!", car);
        }
        else
        {
            printf("Monty opens door #%d, revealing a goat. You lose ", choice);
        }
        printf("\nWould you like to play again?");
        play = validateYn();
    }
    return 0;
}