# TTT Version 1 Code in 
from uagame import Window
import time
import pygame
from pygame.locals import *

# User-defined functions

def main():

    window = Window('Window Title', 500, 400)
    # create Game object using window as argument
    game = Game(window)
    # Play the Game object
    game.play()
    # Close the window
    window.close()

# User-defined classes

class Game:
    # An object in this class represents a complete game.

    def __init__(self, window):
        # Initialize a Game.
        # - self is the Game to initialize
        # - window is the uagame window object
        
        # Game Class always has the following 4 instance attributes
        self.window = window
        self.pause_time = 0.04 # smaller is faster game
        self.close_clicked = False
        self.continue_game = True
        self.board = []
        self.board_size = 3
        self.player_1 = 'X'
        Tile.set_window(window) # Calling of the Class Method
        self.create_board()
    def create_board(self):
        # for every row_index create a row
        for row_index in range(0,self.board_size):
            row = self.create_row(row_index)
            self.board.append(row)
    def create_row(self,row_index):
        row = []
        width = self.window.get_width()//3
        height = self.window.get_height()//3
        for col_index in range(0,self.board_size):
            x = width * col_index
            y = height * row_index
            tile = Tile(x,y,width,height)
            row.append(tile)
        return row
    def play(self):
        # Play the game until the player presses the close box.
        # - self is the Game that should be continued or not.

        while not self.close_clicked:  # until player clicks close box
            # play frame
            self.handle_event()
            self.draw()            
            if self.continue_game:
                self.update()
                self.decide_continue()
            time.sleep(self.pause_time) # set game velocity by pausing
                       
    def handle_event(self):
        # Handle each user event by changing the game state
        # appropriately.
        # - self is the Game whose events will be handled.

        event = pygame.event.poll()
        if event.type == QUIT:
            self.close_clicked = True
        elif event.type == MOUSEBUTTONUP:
            self.handle_mouse_up(event.pos)
    def handle_mouse_up(self,position):
        for row in self.board:
            for tile in row:
                tile.select(position,self.player_1)

    def draw(self):
        # Draw all game objects.
        # - self is the Game to draw
        
        self.window.clear()
        # Code for drawing the objects should be written here
        for row in self.board:
            for tile in row:
                tile.draw()
        self.window.update()
    
    def update(self):
        # Update the game objects.
        # - self is the Game to update
        # Write code for moving the Game object for the next frame
        pass             
    def decide_continue(self):
        # Check and remember if the game should continue
        # - self is the Game to check
        # Write code to check if game should continue or not
        pass
class Tile:
    # Class Attributes and I will initialize the class attributes
    border_width = 3
    fg_color = 'white'
    font_size = 133
    window = None
    
    @classmethod
    def set_window(cls,window_from_Game):
        cls.window = window_from_Game
    # INSTANCE METHODS
    def __init__(self,x,y,width,height):
        self.rect = pygame.Rect(x,y,width,height) # date of birth
        self.content = ''
        self.flashing = False
    def draw(self):
        surface = Tile.window.get_surface()
        if self.flashing == True:
            # draw white rectangle
            pygame.draw.rect(surface,pygame.Color(Tile.fg_color),self.rect,0)
            self.flashing = False
        else:
            # draw the black rectange with the white border
            pygame.draw.rect(surface,pygame.Color(Tile.fg_color),self.rect,Tile.border_width)
            self.draw_content()
    def draw_content(self):
        Tile.window.set_font_size(Tile.font_size)
        horizontal_left_over = self.rect.width - Tile.window.get_string_width(self.content)
        vertical_left_over = self.rect.height - Tile.window.get_font_height()
        content_x = self.rect.x+horizontal_left_over//2
        content_y = self.rect.y+vertical_left_over//2
        Tile.window.draw_string(self.content, content_x,content_y)
    def select(self,position,player_symbol):
        if self.rect.collidepoint(position):
            if self.content == '':
                self.content = player_symbol
            else:
                self.flashing = True
    
main()




