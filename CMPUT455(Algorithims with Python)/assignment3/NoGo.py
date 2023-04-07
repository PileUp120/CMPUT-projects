#!/usr/local/bin/python3
# /usr/bin/python3
# Set the path to your python3 above

from ucb import INFINITY
from gtp_connection import GtpConnection
from board_util import GoBoardUtil
from board import GoBoard
#!/usr/local/bin/python3
# /usr/bin/python3
# Set the path to your python3 above
#from board_score import winner
from board_util import GoBoardUtil, PASS
#from pattern_util import PatternUtil
from board import GoBoard
from simulation_util import writeMoves, select_best_move
from ucb import runUcb
import numpy as np
import argparse
import sys

class NoGo:
    def __init__(self, sim, move_select, sim_rule, move_filter, pattern_list, size=7, limit=100):
        """
        Go player that selects moves by simulation.
        """
        self.name = "Go3"
        self.version = 1.0
        #self.komi = 6.5
        self.sim = sim
        self.limit = limit
        self.use_ucb = False if move_select == "rr" else True
        self.random_simulation = True if sim_rule == "random" else False
        self.use_pattern = not self.random_simulation
        self.check_selfatari = move_filter
        self.pattern_list = pattern_list

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

    def get_move(self, board, color):
        """
        Run one-ply MC simulations to get a move to play.
        """
        cboard = board.copy()
        emptyPoints = board.get_empty_points()
        moves = []
        for p in emptyPoints:
            if board.is_legal(p, color):
                moves.append(p)
        if not moves:
            return None
        moves.append(None)

        if self.use_ucb:
            C = 0.4  # sqrt(2) is safe, this is more aggressive
            best = runUcb(self, cboard, C, moves, color)
            return best
        else:
            moveWins = []
            for move in moves:
                wins = self.simulateMove(cboard, move, color)
                moveWins.append(wins)
            writeMoves(cboard, moves, moveWins, self.sim)
            return select_best_move(board, moves, moveWins)

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

            if self.random_simulation:
                move = GoBoardUtil.generate_random_move(board, color, False)
            else:
                moves_probailites = self.find_pattern_probablilites(board, moves)
                
                move = max(moves_probailites, key=moves_probailites.get)

            board.play_move(move, color)

        return winner #change this for nogo

def run(sim, move_select, sim_rule, move_filter):
    """
    Start the gtp connection and wait for commands.
    """
    board = GoBoard(7)
    file = 'weights.txt'
    pattern_list = GoBoardUtil.get_pattern_list(file)
    con = GtpConnection(NoGo(sim, move_select, sim_rule, move_filter, pattern_list), board)
    con.start_connection()


def parse_args():
    """
    Parse the arguments of the program.
    """
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    parser.add_argument(
        "--sim",
        type=int,
        default=10,
        help="number of simulations per move, so total playouts=sim*legal_moves",
    )
    parser.add_argument(
        "--moveselect",
        type=str,
        default="simple",
        help="type of move selection: simple or ucb",
    )
    parser.add_argument(
        "--simrule",
        type=str,
        default="random",
        help="type of simulation policy: random or pattern",
    )
    parser.add_argument(
        "--movefilter",
        action="store_true",
        default=False,
        help="whether use move filter or not",
    )

    args = parser.parse_args()
    sim = args.sim
    move_select = args.moveselect
    sim_rule = args.simrule
    move_filter = args.movefilter

    if move_select != "simple" and move_select != "ucb":
        print("moveselect must be simple or ucb")
        sys.exit(0)
    if sim_rule != "random" and sim_rule != "pattern":
        print("simrule must be random or pattern")
        sys.exit(0)

    return sim, move_select, sim_rule, move_filter


if __name__ == "__main__":
    sim, move_select, sim_rule, move_filter = parse_args()
    run(sim, move_select, sim_rule, move_filter)
