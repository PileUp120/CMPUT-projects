#!/usr/bin/python3
# /usr/bin/python3
# Set the path to your python3 above

from gtp_connection import GtpConnection
from board_util import GoBoardUtil
from board import GoBoard
from simulation_util import writeMoves, select_best_move
from ucb import runUcb
from ucb import INFINITY
import time
import signal
#import numpy as np
#################################################
'''
This is a uniform random NoGo player served as the starter code
for your (possibly) stronger player. Good luck!
'''

class NoGo:
    def __init__(self, pattern_list):
        """
        NoGo player that selects moves randomly from the set of legal moves.

        Parameters
        ----------
        name : str
            name of the player (used by the GTP interface).
        version : float
            version number (used by the GTP interface).
        """

        self.name = "NoGo4"
        self.version = 1.0
        self.sim = 10
        self.limit = 100
        self.pattern_list = pattern_list
        signal.signal(signal.SIGALRM, self.handler)
       
    def handler(self, signum, fram):
        self.board = self.sboard
        raise Exception("unknown")

    def simulate(self, board, move, toplay):
        """
        Run a simulated game for a given move.
        """
        cboard = board.copy()
        cboard.play_move(move, toplay)
        opp = GoBoardUtil.opponent(toplay)
        return self.playGame(cboard, opp)

    def simulateMove(self, board, move, toplay):
        """
        Run simulations for a given move.
        """
        wins = 0
        for _ in range(self.sim):
            result = self.simulate(board, move, toplay)
            if result == toplay:
                wins += 1
        return wins

    def call_ucb(self, board, moves, color):
        cboard = board.copy()
        if not moves:
            return None
        moves.append(None)
        C = 0.4  # sqrt(2) is safe, this is more aggressive
        move = runUcb(self, cboard, C, moves, color)
        return move

    def get_move(self, board, color):
        """
        Run one-ply MC simulations to get a move to play.
        """

        max_legal_moves = board.size**2
        
        moves = GoBoardUtil.generate_legal_moves(board, color)
        start_time = time.process_time()

        # move = None
        # try:
        #     signal.alarm(25)
        #     for current_move in moves:
        #         move = current_move
        #         result = self.generate_best_move(board, current_move, color, color)
        #         if(result == 1):
        #             break
        #     signal.alarm(0)
        # except Exception as e:
        #     print("Time up")
        #     move = self.call_ucb(board, moves, color)
	
        if(len(moves) >= (1/4)*max_legal_moves):
            try:
                signal.alarm(28)
                move = self.call_ucb(board, moves, color)
                signal.alarm(0)
            except Exception as e:
                print("Time up")
                move = GoBoardUtil.generate_random_move(board, color)
        elif(len(moves) < (1/4)*max_legal_moves):
            
            move = None
            try:
                signal.alarm(25)
                for current_move in moves:
                    move = current_move
                    result = self.generate_best_move(board, current_move, color, color)
                    if(result == 1):
                        break
                signal.alarm(0)
            except Exception as e:
                print("Time up")
                move = self.call_ucb(board, moves, color)
        end_time = time.process_time() - start_time
        print(end_time)
        
        return move

    def generate_best_move(self, board, move, original_color, current_color):
        
        cboard = board.copy()
        cboard.play_move(move, current_color)
        opponent_moves = GoBoardUtil.generate_legal_moves(cboard, GoBoardUtil.opponent(current_color))
        #if on the next turn, opponent has no legal moves
        if (len(opponent_moves) == 0):
            if (original_color == current_color):
                return 1
            else:
                return -1
        else:
            if (original_color == current_color):
                for current_move in opponent_moves:
                    result = self.generate_best_move(cboard, current_move, original_color, GoBoardUtil.opponent(current_color))
                    if (result == 1):
                        break
            elif (original_color != current_color):
                for current_move in opponent_moves:
                    result = self.generate_best_move(cboard, current_move, original_color, GoBoardUtil.opponent(current_color))
                    if (result == -1):
                        break
            return result

        # if original_color == current_color:
        #     if moves == None:
        #         return -1
        #     for move in moves:
        #         copy_board = board.copy()
        #         copy_board.play_move(move, current_color)
        #         if GoBoardUtil.generate_best_move(copy_board, original_color, GoBoardUtil.opponent(current_color)) == 1:
        #             return 1
        #         return -1
        # else:
        #     if moves == None:
        #         return 1
        #     for move in moves:
        #         copy_board = board.copy()
        #         copy_board.play_move(move, current_color)
        #         if GoBoardUtil.generate_best_move(copy_board, original_color, GoBoardUtil.opponent(current_color)) == -1:
        #             return -1
        #         return 1

    def find_pattern_probablilites(self, board, moves):
        weights = [] #0.5, 0.9, 0.7, total = 0.5+0.9+0.7
                #0.5/total
        move_probability = {}
                #[move, probability]
        for move in moves:
            move_weight = board.weight_finder(move, self.pattern_list)
            weights.append(move_weight)
                
        total = 0
        for wt in weights:
            total += wt
        for i in range(len(moves)):
            move_probability[moves[i]] = round((weights[i]/total),3)

        return move_probability


    def playGame(self, board, color):
        """
        Run a simulation game.
        """
        for _ in range(self.limit):
            color = board.current_player
            moves = GoBoardUtil.generate_legal_moves(board, color)
            if (len(moves) ==0):
                winner = GoBoardUtil.opponent(color)
                break

            moves_probailites = self.find_pattern_probablilites(board, moves)
                
            move = max(moves_probailites, key=moves_probailites.get)

            board.play_move(move, color)

        return winner #change this for nogo
        
def run():
    """
    start the gtp connection and wait for commands.
    """
    board = GoBoard(7)
    file = 'go_grand/weights.txt'
    pattern_list = GoBoardUtil.get_pattern_list(file)
    con = GtpConnection(NoGo(pattern_list), board)
    con.start_connection()

if __name__ == "__main__":
    run()
