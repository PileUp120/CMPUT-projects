# Memory version 3
# a window of dimensions 500 x 400 opens with a 4 x 4 grid of tiles each 100 x 100 drawn on the left side of the window, the tiles also have a 4 pixel border
# on the right side is a black bar measuring 100 x 400, which has a score displayed on it that increases by 1 every second while the game runs
# each tile is blue in color with a red question mark, when clicked on, the tiles reveal an image, if two consecutive shown tiles don't match they flip back
# there are 8 unique pairs of images, when all images are revealed, the score stops counting and the game ends

# importing needed modules
from uagame import Window
import pygame, time
from pygame.locals import *
import random

# user defined main class
def main():
    game = Game()
    game.play()

# user defined Game class, to manage all game activities
class Game:
    def __init__ (self):
# creates and sets window,clock and frame rate for tile image showing speed
        self._window = Window('Memory', 500, 400)
        self._set_window()
        self._surface = self._window.get_surface()
        self.close_selected = False
        self.continue_game = True
        self.clock = pygame.time.Clock()
        self.score = 0
        self.frame_rate = 60
# loads images and puts them in a list
        self.image_list = ['image1.bmp','image2.bmp','image3.bmp','image4.bmp','image5.bmp','image6.bmp','image7.bmp','image8.bmp']
        self.picture_list = []
        for filename in self.image_list:
            picture = pygame.image.load(filename)
            self.picture_list.append(picture)
# makes a new list with each image duplicated and randomized
        self.tile_images = []
        for p in self.picture_list:
            self.tile_images.extend([p,p])
        random.shuffle(self.tile_images)
# prepares a list for the tile board and calls the create board function, sets a variable to check 
# number of uncovered tiles, and a list to contain all uncovered tiles 
        self.tile_board = []
        self.create_board()
        self.tiles_uncovered = 0
        self.tiles_open = []
        
# adjusts window settings
    def _set_window (self):
        self._window.set_font_name('ariel')
        self._window.set_bg_color('black')
        self._window.set_font_size(64)

# creates each row in the board and appends to the set
    def create_board(self):
        for row_index in range(0,4):
            row = self.create_row(row_index)
            self.tile_board.append(row)

# checks if tiles in the board is uncovered
    def check_uncovered(self):
        total_uncovered = 0
        for row in self.tile_board:
            for tile in row:
                if not tile.tile_covered():
                    total_uncovered += 1
        return total_uncovered

# creates each tile in a row and appends to the row
    def create_row(self,row_index):
        row = []
        width = (self._window.get_width() // 5)
        height = (self._window.get_height() // 4)
        dimensions = [width,height]
        for col_index in range(0,4):
            x = width * col_index
            y = height * row_index
            location = [x,y]
            tile = Tile(location,self.tile_images[(row_index * 4) + col_index],self._surface,dimensions)
            row.append(tile)
        return row

# compares two uncovered tiles, if they match,keep them uncovered,if they don't flip them back
    def compare_tiles(self,tile1,tile2):
        if tile1 == tile2:
            tile1.match()
            tile2.match()
        else:
            time.sleep(1)
            tile1.cover_up()
            tile1.not_open()
            tile2.cover_up()
            tile2.not_open()
        self.tiles_open = []
            
# draws the entire tile grid 
    def draw(self):
        self._window.clear()
        self.draw_score()        
        for row in self.tile_board:
            for tile in row:
                tile.draw()
        self._window.update()

# checks to see if the close button is clicked
    def handle_game_events(self):
# gets all current events
        event = pygame.event.poll()
# sets condition for the close button
        if event.type == QUIT :
            self.close_selected = True
# sets condition for mouse click events
        elif event.type == MOUSEBUTTONUP:
            for row in self.tile_board:
                for tile in row:
                    if not tile.matched and self.continue_game:
                        tile.handle_tile_event(event)
                        if not tile.covered and not tile.opened:
                            self.tiles_open.append(tile)
                            tile.open_display()                                            
            self.tiles_uncovered = self.check_uncovered()
             
# draws the grid and closes window if the close button is clicked
    def play(self):
        while not self.close_selected:
            self.handle_game_events()
            self.draw()
            if self.continue_game == True:
                self.update()                
        self._window.close()

# updates the game score
    def update(self):
        if self.tiles_uncovered == 16:
            self.continue_game = False
        if self.continue_game:
            self.score = pygame.time.get_ticks() // 1000
        if len(self.tiles_open) == 2:
            self.compare_tiles(self.tiles_open[0],self.tiles_open[1])        
        self.clock.tick(self.frame_rate)
        self._window.update()

# prints the score in the upper corner of the window
    def draw_score(self):
        x_coord = self._window.get_width() - self._window.get_string_width(str(self.score))
        string = str(self.score)
        self._window.draw_string(string,x_coord,0)    

# user defined tile class to handle tile properties
class Tile:
# shared tile attributes, including cover image
    bg_color = pygame.Color('black')
    border_thickness = 4
    cover_picture = pygame.image.load('image0.bmp')

# method to compare images of two tiles    
    def __eq__(self,other_tile):
        return self.image == other_tile.image

# main initialised properties
    def __init__(self,location,picture,surface,dimensions):
        self.x = location[0]
        self.y = location[1]
        self.image = picture
        self.surface = surface
        self.width = dimensions[0]
        self.height = dimensions[1]
        self.rect = pygame.Rect(location[0],location[1],dimensions[0],dimensions[1])
        self.covered = True
        self.matched = False
        self.opened = False

# draw function to draw a rectangle and paste appropriate image onto it
    def draw(self):
        pygame.draw.rect(self.surface,Tile.bg_color,self.rect,Tile.border_thickness)
        if self.covered :
            self.surface.blit(Tile.cover_picture, (self.x,self.y))
        else:
            self.surface.blit(self.image, (self.x,self.y))

# changes state for image if clicked
    def handle_tile_event(self,event):
        pos = pygame.mouse.get_pos()
        if event.type == MOUSEBUTTONUP and event.button == 1 and self.rect.collidepoint(pos):
            self.covered = False

# returns boolean of tile covered or not
    def tile_covered(self):
        return self.covered

# covers up image    
    def cover_up(self):
        self.covered = True

# sets matched property to true
    def match(self):
        self.matched = True

# sets open property of the tile to false
    def not_open(self):
        self.opened = False

# sets open property of the tile to true   
    def open_display(self):
        self.opened = True

main()