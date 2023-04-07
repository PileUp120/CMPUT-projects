from random import randint
playing_game = True
while playing_game:
    print('I am thinking of a 3 digit number. Try to guess what it is. You have 10 attempts.')
    print('If you guess none of the digits I will answer WRONG')
    print('I will answer DING for every correct digit in the right position and will answer DONG for every correct digit in the wrong position.')
    class Secret_Number:
        def __init__(self):
            self.number = ''
            self.generate_number()
        def generate_number(self):
            dig1 = ''
            dig2 = ''
            dig3 = ''
            dig1 += str(randint(1,9))
            while dig2 == '' or dig2 == dig1:
                dig2 = str(randint(0,8))
            while dig3 == '' or dig3 == dig1 or dig3 == dig2:
                dig3 = str(randint(2,7))
            self.number = dig1+dig2+dig3
        def get(self):
            return self.number
        def getClues(self,guess):
            responses = ''
            allWrong = 0
            if self.number == guess:
                responses = 'CORRECT'
            else:
                for e in guess:
                    if e in self.number and (self.number.index(e) == guess.index(e)):
                        responses += 'DING '
                    elif e in self.number and (self.number.index(e) != guess.index(e)):
                        responses += 'DONG '
                    elif e not in self.number:    
                        allWrong+=1
                if allWrong == 3:
                    responses = 'WRONG'
            return responses
    def readNumber(attempts):
        valid_input = False
        guess = input('Enter a three digit number with non-repeating digits'+'\n'+'Guess attempt {0:d}:'.format(attempts))
        try:
            int(guess)
            if len(guess) == 3 and guess.isnumeric():
                valid_input = True
                if guess[0] == guess[1] or guess[0] == guess[2] or guess[1] == guess[2]:
                    valid_input = False        
        except ValueError:
            valid_input = False
        while not valid_input:
            guess = input('Enter a three digit number with non-repeating digits'+'\n'+'Guess attempt {0:d}:'.format(attempts))
            if len(guess) == 3 and guess.isnumeric():
                valid_input = True        
        return guess       
    
    maxAttempts = 10
    randomisedNum = Secret_Number()
    for i in range(0,10):
        guess = readNumber(i+1)
        response = randomisedNum.getClues(guess)
        maxAttempts -= 1
        print(response)
        if response == 'CORRECT':
            print('You guessed it after {0:d} attempts. The number is indeed {1:s}'.format(i+1,randomisedNum.get()))
            break
    if maxAttempts == 0 and response != 'CORRECT':
        print('You failed to guess the number, it was {0:s}'.format(randomisedNum.get()))
    while True:
        replay=input("Do you want to play again (y/n)?")
        if replay[0].upper() =="Y" or replay[0].upper() == "N": break
    if replay[0].upper() == "N": 
        playing_game = False  