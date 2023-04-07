"""
gtp_connection.py
Module for playing games of Go using GoTextProtocol

Parts of this code were originally based on the gtp module 
in the Deep-Go project by Isaac Henrion and Amos Storkey 
at the University of Edinburgh.
"""
from cmath import e
from copy import copy
from math import fabs
import time
import eventlet #import this module using pip command "pip install eventlet"
import traceback
from sys import stdin, stdout, stderr
from board_util import (
    GoBoardUtil,
    BLACK,
    WHITE,
    EMPTY,
    BORDER,
    PASS,
    MAXSIZE,
    coord_to_point,
)
import numpy as np
import re


# def signal_handler(signum, frame):
#     raise Exception("Timed out!")

# class MyThread(threading.Thread):
#     def __init__(self, target, args =()):
#         super(MyThread, self).__init__()
#         self.func = target
#         self.args = args
#     def run(self):
#         self.result = self.func(*self.args)
#     def get_result(self):
#         try:
#             return self.result
#         except Exception:
#             return None

def negamax_Boolean(board, original_player):
    player = board.current_player
    legal_moves = GoBoardUtil.generate_legal_moves(board, player)
    if (len(legal_moves) == 0):
        if (player == original_player):
            return False
        elif(player == GoBoardUtil.opponent(original_player)):
            return True
        
    table = {}
    for move in legal_moves:
        heuristic_point = heuristic(board,original_player,move)
        table[move] = heuristic_point

    table = dict(sorted(table.items(), key=lambda item: item[1], reverse = True))

    if player == original_player:
        for item in table:
            copy = board.copy()
            copy.play_move(item, player)
            result = negamax_Boolean(copy, original_player)
            if result == True:
                return True
            else:
                return False
    else:
        for item in table:
            copy = board.copy()
            copy.play_move(item, player)
            result = negamax_Boolean(copy, original_player)
            if result == True:
                return True
            else:
                return False



def heuristic(board,original_player,move):
    player = board.current_player
    legal_moves_oriplayer = GoBoardUtil.generate_legal_moves(board, original_player)
    legal_moves_opponent = GoBoardUtil.generate_legal_moves(board, GoBoardUtil.opponent(original_player))
    copy = board.copy()
    copy.play_move(move, player)
    c_legal_moves_oriplayer = GoBoardUtil.generate_legal_moves(copy, original_player)
    c_legal_moves_opponent = GoBoardUtil.generate_legal_moves(copy, GoBoardUtil.opponent(original_player))


    return (len(c_legal_moves_oriplayer) - len(c_legal_moves_opponent)) - (len(legal_moves_oriplayer) - len(legal_moves_opponent))

class GtpConnection:
    def __init__(self, go_engine, board, debug_mode=False):
        """
        Manage a GTP connection for a Go-playing engine

        Parameters
        ----------
        go_engine:
            a program that can reply to a set of GTP commandsbelow
        board: 
            Represents the current board state.
        """
        self._debug_mode = debug_mode
        self.go_engine = go_engine
        self.board = board
        self.timelimit = 1
        self.commands = {
            "protocol_version": self.protocol_version_cmd,
            "quit": self.quit_cmd,
            "name": self.name_cmd,
            "boardsize": self.boardsize_cmd,
            "showboard": self.showboard_cmd,
            "clear_board": self.clear_board_cmd,
            "komi": self.komi_cmd,
            "version": self.version_cmd,
            "known_command": self.known_command_cmd,
            "genmove": self.genmove_cmd,
            "list_commands": self.list_commands_cmd,
            "play": self.play_cmd,
            "gogui-rules_legal_moves":self.gogui_rules_legal_moves_cmd,
            "gogui-rules_final_result":self.gogui_rules_final_result_cmd,
            "solve":self.solve_cmd,
            "timelimit":self.timelimit_cmd
        }

        # used for argument checking
        # values: (required number of arguments,
        #          error message on argnum failure)
        self.argmap = {
            "boardsize": (1, "Usage: boardsize INT"),
            "komi": (1, "Usage: komi FLOAT"),
            "known_command": (1, "Usage: known_command CMD_NAME"),
            "genmove": (1, "Usage: genmove {w,b}"),
            "play": (2, "Usage: play {b,w} MOVE"),
            "legal_moves": (1, "Usage: legal_moves {w,b}"),
            "solve": (0, "Usage: solve"),
        }
    # def limit_decor(timeout, granularity):
    #     def functions(func):
    #         def run(*args):
    #             thre_func = MyThread(target = func, args = args)
    #             thre_func.setDaemon(True)
    #             thre_func.start()
    #             sleep_num = int(timeout//granularity)
    #             for i in range(0,sleep_num):
    #                 infor = thre_func.get_result()
    #                 if infor:
    #                     return infor
    #                 else:
    #                     time.sleep(granularity)
    #             return None
    #         return run
    #     return functions

    

    def write(self, data):
        stdout.write(data)

    def flush(self):
        stdout.flush()

    def start_connection(self):
        """
        Start a GTP connection. 
        This function continuously monitors standard input for commands.
        """
        line = stdin.readline()
        while line:
            self.get_cmd(line)
            line = stdin.readline()

    def get_cmd(self, command):
        """
        Parse command string and execute it
        """
        if len(command.strip(" \r\t")) == 0:
            return
        if command[0] == "#":
            return
        # Strip leading numbers from regression tests
        if command[0].isdigit():
            command = re.sub("^\d+", "", command).lstrip()

        elements = command.split()
        if not elements:
            return
        command_name = elements[0]
        args = elements[1:]
        if self.has_arg_error(command_name, len(args)):
            return
        if command_name in self.commands:
            try:
                self.commands[command_name](args)
            except Exception as e:
                self.debug_msg("Error executing command {}\n".format(str(e)))
                self.debug_msg("Stack Trace:\n{}\n".format(traceback.format_exc()))
                raise e
        else:
            self.debug_msg("Unknown command: {}\n".format(command_name))
            self.error("Unknown command")
            stdout.flush()

    def has_arg_error(self, cmd, argnum):
        """
        Verify the number of arguments of cmd.
        argnum is the number of parsed arguments
        """
        if cmd in self.argmap and self.argmap[cmd][0] != argnum:
            self.error(self.argmap[cmd][1])
            return True
        return False

    def debug_msg(self, msg):
        """ Write msg to the debug stream """
        if self._debug_mode:
            stderr.write(msg)
            stderr.flush()

    def error(self, error_msg):
        """ Send error msg to stdout """
        stdout.write("? {}\n\n".format(error_msg))
        stdout.flush()

    def respond(self, response=""):
        """ Send response to stdout """
        stdout.write("= {}\n\n".format(response))
        stdout.flush()

    def reset(self, size):
        """
        Reset the board to empty board of given size
        """
        self.board.reset(size)

    def board2d(self):
        return str(GoBoardUtil.get_twoD_board(self.board))

    def protocol_version_cmd(self, args):
        """ Return the GTP protocol version being used (always 2) """
        self.respond("2")

    def quit_cmd(self, args):
        """ Quit game and exit the GTP interface """
        self.respond()
        exit()

    def name_cmd(self, args):
        """ Return the name of the Go engine """
        self.respond(self.go_engine.name)

    def version_cmd(self, args):
        """ Return the version of the  Go engine """
        self.respond(self.go_engine.version)

    def clear_board_cmd(self, args):
        """ clear the board """
        self.reset(self.board.size)
        self.respond()

    def boardsize_cmd(self, args):
        """
        Reset the game with new boardsize args[0]
        """
        self.reset(int(args[0]))
        self.respond()

    def showboard_cmd(self, args):
        self.respond("\n" + self.board2d())

    def komi_cmd(self, args):
        """
        Set the engine's komi to args[0]
        """
        self.go_engine.komi = float(args[0])
        self.respond()

    def known_command_cmd(self, args):
        """
        Check if command args[0] is known to the GTP interface
        """
        if args[0] in self.commands:
            self.respond("true")
        else:
            self.respond("false")

    def list_commands_cmd(self, args):
        """ list all supported GTP commands """
        self.respond(" ".join(list(self.commands.keys())))

    def timelimit_cmd(self, args):
        if(int(args[0]) > 100):
            self.respond("The timelimit is too large")
        elif(int(args[0]) < 1):
            self.respond("The timelimit is too small")
        else:
            self.timelimit = int(args[0])
            self.respond("The timelimit is set to "+ args[0] +" seconds")

    """
    ==========================================================================
    Assignment 2 - game-specific commands start here
    ==========================================================================
    """
    """
    ==========================================================================
    Assignment 2 - commands we already implemented for you
    ==========================================================================
    """
    def gogui_analyze_cmd(self, args):
        """ We already implemented this function for Assignment 2 """
        self.respond("pstring/Legal Moves For ToPlay/gogui-rules_legal_moves\n"
                     "pstring/Side to Play/gogui-rules_side_to_move\n"
                     "pstring/Final Result/gogui-rules_final_result\n"
                     "pstring/Board Size/gogui-rules_board_size\n"
                     "pstring/Rules GameID/gogui-rules_game_id\n"
                     "pstring/Show Board/gogui-rules_board\n"
                     )

    def gogui_rules_game_id_cmd(self, args):
        """ We already implemented this function for Assignment 2 """
        self.respond("NoGo")

    def gogui_rules_board_size_cmd(self, args):
        """ We already implemented this function for Assignment 2 """
        self.respond(str(self.board.size))

    def gogui_rules_side_to_move_cmd(self, args):
        """ We already implemented this function for Assignment 2 """
        color = "black" if self.board.current_player == BLACK else "white"
        self.respond(color)

    def gogui_rules_board_cmd(self, args):
        """ We already implemented this function for Assignment 2 """
        size = self.board.size
        str = ''
        for row in range(size-1, -1, -1):
            start = self.board.row_start(row + 1)
            for i in range(size):
                #str += '.'
                point = self.board.board[start + i]
                if point == BLACK:
                    str += 'X'
                elif point == WHITE:
                    str += 'O'
                elif point == EMPTY:
                    str += '.'
                else:
                    assert False
            str += '\n'
        self.respond(str)

    def gogui_rules_legal_moves_cmd(self, args):
        # get all the legal moves
        legal_moves = GoBoardUtil.generate_legal_moves(self.board, self.board.current_player)
        coords = [point_to_coord(move, self.board.size) for move in legal_moves]
        # convert to point strings
        point_strs  = [ chr(ord('a') + col - 1) + str(row) for row, col in coords]
        point_strs.sort()
        point_strs = ' '.join(point_strs).upper()
        self.respond(point_strs)


    """
    ==========================================================================
    Assignment 2 - game-specific commands you have to implement or modify
    ==========================================================================
    """
    def gogui_rules_final_result_cmd(self, args):
        # implement this method correctly
        legal_moves = GoBoardUtil.generate_legal_moves(self.board, self.board.current_player)
        if len(legal_moves) > 0:
            self.respond('unknown')
        else:
            if self.board.current_player == BLACK:
                self.respond('')
            else:
                self.respond('')

    def play_cmd(self, args):
        """
        play a move args[1] for given color args[0] in {'b','w'}
        """
        # change this method to use your solver
        try:
            board_color = args[0].lower()
            board_move = args[1]
            color = color_to_int(board_color)
            if args[1].lower() == "pass":
                reason = self.board.is_legal(PASS, color)[1]
                self.respond("illegal move: \"{} {}\" {}".format(board_color, board_move, reason))
                return
            coord = move_to_coord(args[1], self.board.size)
            if coord:
                move = coord_to_point(coord[0], coord[1], self.board.size)
            else:
                self.error(
                    "Error executing move {} converted from {}".format(move, args[1])
                )
                return
            if not (self.board.is_legal(move, color)[0]):
                reason = self.board.is_legal(move, color)[1]
                self.respond("illegal move: \"{} {}\" {}".format(board_color, board_move, reason))
                return
            else:
                self.debug_msg(
                    "Move: {}\nBoard:\n{}\n".format(board_move, self.board2d())
                )
                self.board.play_move(move, color)
            self.respond()
        except Exception as e:
            self.respond("Error: {}".format(str(e)))
    
    
    def genmove_cmd(self, args):

        """ generate a move for color args[0] in {'b','w'} """
        # change this method to use your solver
        board_color = self.board.current_player
            #color = color_to_int(board_color)
        move = self.go_engine.get_move(self.board, board_color)
        if(move == PASS):
            self.respond("resign")

        else:
            best_move = self.solve_cmd()
            
            if (best_move == 'unknown'):
                move_coord = point_to_coord(move, self.board.size)
                move_as_string = format_point(move_coord)
                if self.board.is_legal(move, board_color)[0]:
                    self.board.play_move(move, board_color)[0]
                    self.respond(move_as_string)
                else:
                    reason = self.board.is_legal(move, board_color)[1]
                    self.respond("illegal move: \"{} {}\" {}".format(board_color, move, reason))
            else:
                move_coord = point_to_coord(best_move, self.board.size)
                move_as_string = format_point(move_coord)
                self.board.play_move(best_move, board_color)
                self.respond(move_as_string)


    def solve_cmd(self, args):
        player = self.board.current_player
        colors = ['empty', 'b', 'w']
        current_board = self.board
        legal_moves = GoBoardUtil.generate_legal_moves(current_board, player)
        if (len(legal_moves) == 0):
            opponent = GoBoardUtil.opponent(player)
            return(opponent)
        else:
            
            table = {}
            for move in legal_moves:
                
                heuristic_point = heuristic(self.board,player,move)
                table[move] = heuristic_point

            table = dict(sorted(table.items(), key=lambda item: item[1], reverse = True))
            for item in table:
                copy = self.board.copy()
                copy.play_move(item, player)
                result = negamax_Boolean(copy, player)
                if result == True:
                    break
                else:
                    continue
                    
                
            
            if not (result):
                self.respond(colors[GoBoardUtil.opponent(player)])
            else:
                move = max(table, key=table.get)
                move_coord = point_to_coord(move, self.board.size)
                move_as_string = colors[player] + ' ' + format_point(move_coord)
                self.respond(move_as_string) 
            
            
            '''
            eventlet.monkey_patch()
            foundMove = False
            with eventlet.Timeout(self.timelimit,False):
                #negamax search
                for move in legal_moves:
                    win = negamax_Boolean(self.board, player)
                    if (win):
                        foundMove = True
                        return(move)
            if not (foundMove):
                return('unknown')
            '''
    
    
       
    """
    ==========================================================================
    Assignment 2 - game-specific commands end here
    ==========================================================================
    """

def point_to_coord(point, boardsize):
    """
    Transform point given as board array index 
    to (row, col) coordinate representation.
    Special case: PASS is not transformed
    """
    if point == PASS:
        return PASS
    else:
        NS = boardsize + 1
        return divmod(point, NS)


def format_point(move):
    """
    Return move coordinates as a string such as 'A1', or 'PASS'.
    """
    assert MAXSIZE <= 25
    column_letters = "ABCDEFGHJKLMNOPQRSTUVWXYZ"
    if move == PASS:
        return "PASS"
    row, col = move
    if not 0 <= row < MAXSIZE or not 0 <= col < MAXSIZE:
        raise ValueError
    return column_letters[col - 1] + str(row)


def move_to_coord(point_str, board_size):
    """
    Convert a string point_str representing a point, as specified by GTP,
    to a pair of coordinates (row, col) in range 1 .. board_size.
    Raises ValueError if point_str is invalid
    """
    if not 2 <= board_size <= MAXSIZE:
        raise ValueError("board_size out of range")
    s = point_str.lower()
    if s == "pass":
        return PASS
    try:
        col_c = s[0]
        if (not "a" <= col_c <= "z") or col_c == "i":
            raise ValueError
        col = ord(col_c) - ord("a")
        if col_c < "i":
            col += 1
        row = int(s[1:])
        if row < 1:
            raise ValueError
    except (IndexError, ValueError):
        raise ValueError("invalid point: '{}'".format(s))
    if not (col <= board_size and row <= board_size):
        raise ValueError("point off board: '{}'".format(s))
    return row, col


def color_to_int(c):
    """convert character to the appropriate integer code"""
    color_to_int = {"b": BLACK, "w": WHITE, "e": EMPTY, "BORDER": BORDER}
    return color_to_int[c]
