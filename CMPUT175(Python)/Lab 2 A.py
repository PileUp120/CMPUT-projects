from random import randint
continue_game = True
while continue_game:
    targetVal = randint(1,99)
    inputSum = 0
    exitLoop = False
    print("Enter coins values as 1-penny, 5-nickel, 10-dime, and 25-quarter.")
    print("Enter coins that add up to",targetVal,"cents, one per line.")
    while not exitLoop:
        userEntry = input("Enter a valid coin value >")
        if userEntry != '':
            try:
                int(userEntry)
                if int(userEntry) not in [1,5,10,25]:
                    print("Invalid entry - Try again!")
                else:
                    inputSum += int(userEntry)
            except ValueError:
                print("Invalid entry - Try again!")
        else:
            exitLoop = True
    print("Here is the outcome :")
    if inputSum == targetVal:
        print("Success!")
    else:
        if targetVal > inputSum:
            print("Failure - you only entered",inputSum,"cents")
            print("You are short of",(targetVal - inputSum),"cents")
        else:
            print("Failure - you entered",inputSum,"cents")
            print("The amount exceeds",targetVal,"cents by",(inputSum - targetVal),"cents")    
    replay=input("Play another game session (y/n)?")
    if replay[0].upper() !="Y":
            continue_game = False
print("Thanks for playing ... goodbye")    