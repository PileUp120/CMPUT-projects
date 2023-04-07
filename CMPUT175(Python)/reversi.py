class Reversi:
    WHITE = "w"
    BLACK = "b"
    EMPTY = "."
    SIZE = 8
    def __init__(self):
        # sets up a new game board and displays it, also activates player and computer
        self.newGame()
        self.playerCanMove = True
        self.computerCanMove = True
    def newGame(self):
        self.gameBoard = []
        # makes a list containing 8 tiles with the empty status and apends it 8 times into the game board list
        # sets the 4 default pieces to their respective colors
        for i in range(Reversi.SIZE):
            self.gameBoard.append([Reversi.EMPTY] * Reversi.SIZE)        
        self.gameBoard[3][3] = Reversi.WHITE
        self.gameBoard[4][4] = Reversi.WHITE
        self.gameBoard[3][4] = Reversi.BLACK
        self.gameBoard[4][3] = Reversi.BLACK
    def getScore(self, colour):
        # loops through the game board lists and increments the score by 1 for every peice matching the given colour
        pieceScore = 0
        for x in range(Reversi.SIZE):
            for y in range(Reversi.SIZE):
                if self.gameBoard[x][y] == colour:
                    pieceScore += 1
        return pieceScore
    def setPlayerColour(self, colour):
        # sets the player and computer colour accoring to the user's choice
        if colour == Reversi.WHITE:
            self.playerColour = Reversi.WHITE
            self.computerColour = Reversi.BLACK
        else:
            self.playerColour = Reversi.BLACK
            self.computerColour = Reversi.WHITE            
    def displayBoard(self):
        # prints the game board, with the position co-odinates above and to the left of the board
        print('  0 1 2 3 4 5 6 7')
        for y in range(Reversi.SIZE):
            print(y)
            for x in range(Reversi.SIZE):
                print('%s' % (self.gameBoard[x][y]))
    
    def isPositionValid(self, position, colour):
        
    # Returns False, with appropriate error message if the move on given position is invalid.
    # otherwise returns a list of spots that would become change to the given colour when the move is made.
        if self.gameBoard[position[0]][position[1]] != '.':
            return [False,'Invalid position: position full']
        
        if not (position[0] >= 0 and position[0] <= 7 and position[1] >= 0 and position[1] <=7):
            return [False,'Invalid position: out of bounds']

        self.gameBoard[position[0]][position[1]] = colour # temporarily set the colour on the board.
        # to compare the pieces
        if colour == Reversi.BLACK:
            opponent = Reversi.WHITE
        else:
            opponent = Reversi.BLACK
        # empty list to store changed tiles
        taken = []
        for xMove, yMove in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:# 8-way directions to move from current position
            x, y = position[0],position[1]
            x += xMove # first step in the horizontal direction
            y += yMove # first step in the vertical direction
            if (x >= 0 and x <= 7 and y >= 0 and y <=7) and self.gameBoard[x][y] == opponent:
            # There is a piece belonging to the opponent next to our piece.
                x += xMove
                y += yMove
                if not (x >= 0 and x <= 7 and y >= 0 and y <=7): # not the end of the board
                    continue
                while self.gameBoard[x][y] == opponent: # multiple opponent pieces but not at the end of the board
                    x += xMove
                    y += yMove
                    if not (x >= 0 and x <= 7 and y >= 0 and y <=7): # break out of while loop, then continue in for loop if not the end of the board
                        break
                if not (x >= 0 and x <= 7 and y >= 0 and y <=7):# continue till a matching piece is found, or the end of the board
                    continue
                if self.gameBoard[x][y] == colour:
                # There are pieces to flip over. Go in the reverse direction until we reach the original space, noting all the tiles along the way.
                    while True:
                        x -= xMove
                        y -= yMove
                        if x == position[0] and y == position[1]:
                            break
                        taken.append([x, y])

            self.gameBoard[position[0]][position[1]] = '.' # restore the empty space
            if len(taken) == 0: # If no tiles were flipped, the move is invalid.
                return [False,"Invalid position: piece doesn't surround line of opponent pieces"]
            return taken
    
    def isGameOver(self):
        # check if aplyer has any available moves left
        playerMoves = []
        for x in range(8):
            for y in range(8):
                if self.isPositionValid([x,y], self.playerColour)[0] != False:
                    playerMoves.append([x, y])
        if playerMoves == []:
            self.playerCanMove = False        
        return (not self.playerCanMove or not self.computerCanMove) # return true is either the player or the computer has no available moves left

    def makeMovePlayer(self, position):
        # run the valid moves function to get whether or not the playermoves
        tilesToFlip = self.isPositionValid(position, self.playerColour)
    
        if tilesToFlip[0] == False: # if invalid move, return the appropriate error message
            return tilesToFlip[1]
    
        self.gameBoard[position[0]][position[1]] = self.playerColour # if valid move, flip all appropriate tiles and return true(that player has made a move)
        for x, y in tilesToFlip:
            self.gameBoard[x][y] = self.playerColour       
        
        return True        

    def makeMoveNaive(self):
        # runs to all available moves on the board and appends to a list
        # if no availablemoves left, triggers game over condition
        availableMoves = []
        for x in range(8):
            for y in range(8):
                if self.isPositionValid([x,y], self.computerColour)[0] != False:
                    availableMoves.append([x, y])
        if availableMoves == []:
            self.computerCanMove = False
            return
        # chooses the first available move and flips all appropriate tiles then return true(computer has made a move and what the move was)
        move = self.isPositionValid(availableMoves[0], self.computerColour)
        xM = availableMoves[0][0]
        yM = availableMoves[0][1]
        self.gameBoard[xM][yM] = self.computerColour
        for x, y in move:
            self.gameBoard[x][y] = self.computerColour
        return [True,availableMoves[0]]

    def makeMoveSmart(self):
        # checks board for all available moves
        # if no available moves, trigger game over condition
        possibleMoves = []
        for x in range(8):
            for y in range(8):
                if self.isPositionValid([x,y], self.computerColour)[0] != False:
                    possibleMoves.append([x, y])
        if possibleMoves == []:
            self.computerCanMove = False
            return
        # always go for a corner position if available.
        for x, y in possibleMoves:
            if (x == 0 and y == 0) or (x == 7 and y == 0) or (x == 0 and y == 7) or (x == 7 and y == 7):
                move = self.isPositionValid([x,y], self.computerColour)
                self.gameBoard[x][y] = self.computerColour
                for x, y in move:
                    self.gameBoard[x][y] = self.computerColour
            return [True,[x,y]]
        # Go through all the possible moves and remember the best scoring move
        bestScore = 0
        defBoard = self.gameBoard # save the game board
        for x, y in possibleMoves:
            tryMove = self.isPositionValid([x,y], self.computerColour) # try the move on the board and calculate how much it scores
            self.gameBoard[x][y] = self.computerColour
            for x, y in move:
                self.gameBoard[x][y] = self.computerColour
            score = self.getScore(self.computerColour)
            self.gameBoard = defBoard # reset the board to what it was before the loop for the next available move
            if score > bestScore: # save the best scoring move and the score it gets in appropriate variables
                bestMove = [x, y]
                bestScore = score
        # after the loop to search for the best move ends, use that move on the board and return true(computer has moved and what the move was)
        move = self.isPositionValid(bestMove, self.computerColour)
        self.gameBoard[bestMove[0]][bestMove[1]] = self.computerColour
        for x, y in move:
            self.gameBoard[x][y] = self.computerColour
        return [True,bestMove]        