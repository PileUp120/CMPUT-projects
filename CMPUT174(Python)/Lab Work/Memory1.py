# Memory version 1
# a window of dimensions 500 x 400 opens with a 4 x 4 grid of tiles each 100 x 100 drawn on the left side of the window, the tiles also have a 4 pixel border
# on the right side is a black bar measuring 100 x 400
# each tile contains an image, there are 8 unique image pairs

# importing needed modules
from uagame import Window
import pygame
from pygame.locals import *
import random


# user defined main class
def main():
    game = Game()
    game.play()

# user defined main class
class Game:
    def __init__ (self):
# creates and sets window
        self._window = Window('Memory', 500, 400)
        self._set_window()
        self._surface = self._window.get_surface()
        self.close_selected = False
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
# prepares a list for the tile board and calls the create board function
        self.tile_board = []
        self.create_board()

# adjusts window settings
    def _set_window (self):
        self._window.set_font_name('ariel')
        self._window.set_bg_color('black')        

# creates each row in the board and appends to the set
    def create_board(self):
        for row_index in range(0,4):
            row = self.create_row(row_index)
            self.tile_board.append(row)

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

# draws the entire tile grid
    def draw(self):
        self._window.clear()
        for row in self.tile_board:
            for tile in row:
                tile.draw()
        self._window.update()

# checks to see if the close button is clicked
    def handle_events(self):
        event = pygame.event.poll()
        if event.type == QUIT :
            self.close_selected = True
            
# draws the grid and closes window if the close button is clicked
    def play(self):
        while not self.close_selected:
            self.draw()
            self.handle_events()
        self._window.close()

# user defined tile class
class Tile:
# fixed tile attributes
    bg_color = pygame.Color('black')
    border_thickness = 4

# main initialised properties
    def __init__(self,location,picture,surface,dimensions):
        self.x = location[0]
        self.y = location[1]
        self.image = picture
        self.surface = surface
        self.width = dimensions[0]
        self.height = dimensions[1]
        self.rect = pygame.Rect(location[0],location[1],dimensions[0],dimensions[1])

# draw function to draw a rectangle and paste image onto it
    def draw(self):
        pygame.draw.rect(self.surface,Tile.bg_color,self.rect,Tile.border_thickness)
        self.surface.blit(self.image, (self.x,self.y))   
main()                  