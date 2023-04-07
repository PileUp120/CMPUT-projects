from reversi import Reversi

def computerMove(userResp,game):
    if userResp == '1':
        pos = game.makeMoveNaive()[1]
    elif userResp == '2':
        pos = game.makeMoveSmart()[1]
    return pos
def changeTurn(turn):
    if turn == 'user':
        turn = 'computer'
    elif turn == 'computer':
        turn = 'user'
playingGame = True
while playingGame:
    print('Starting new game!')
    print('Black goes first, and then white')
    game = Reversi()
    turn = ''
    player = input("Enter 'b' to choose to play black, 'w' to choose white:")
    while not player[0].lower() in ['b','w']:
        player = input("Enter 'b' to choose to play black, 'w' to choose white:")
    game.setPlayerColour(player)
    difficulty = input("Enter '1' to choose easy computer opponent, '2' for hard computer opponent:")
    while not difficulty in ['1','2']:
        difficulty = input("Enter '1' to choose easy computer opponent, '2' for hard computer opponent:")
    game.displayBoard()
    print("Score: white", game.getScore("w"), "black", game.getScore("b"))
    
    if player == 'b':
        turn = 'user'
    else:
        turn = 'computer'
    inSession = True
    while inSession:
        if turn == 'user':
            sameTurn = True
            while sameTurn:
                print('Enter 2 numbers from 0-7 separated by a space to make a move, where the first number is the row and the second number is the column')
                print("Enter 'q' to quit.")
                movE = ''
                while (not len(movE) == 3 and not len(movE.split()) == 2) or not movE == 'q':
                    movE = input('Enter move:')
                    if movE == 'q':
                        inSession = False
                    elif not movE.split()[0].isnumeric() or not movE.split()[0].isnumeric():
                        continue
                movE = movE.split()
                outcome = game.makeMovePlayer(movE)
                if outcome == True:
                    game.displayBoard()
                    changeTurn(turn)                
                    print("Score: white", game.getScore("w"), "black", game.getScore("b"))
                    sameTurn = False
                else:
                    print(outcome)
        elif turn == 'computer':
            pos = computerMove(difficulty,game)
            if game.isGameOver():
                inSession = False
            print("Computer making move:", pos)
            game.displayBoard()
            print("Score: white", game.getScore("w"), "black", game.getScore("b"))
            changeTurn(turn)
    
    print('Game Over!')
    game.displayBoard()
    print("Score: white", game.getScore("w"), "black", game.getScore("b"))    
    while True:
        replay=input("Do you want to play again (y/n)?")
        if replay[0].upper() =="Y" or replay[0].upper() == "N": break
    if replay[0].upper() == "N": 
        playingGame = False    
    
    