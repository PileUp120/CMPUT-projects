
from uagame import Window
from random import randint
from pygame.time import Clock, get_ticks
from pygame.event import get as get_events
from pygame import QUIT, Color, MOUSEBUTTONUP
from pygame.draw import circle as draw_circle
from math import sqrt
class Dot:
    def __init__(self,colour, radius, center, velocity, window):
        self.colour = colour
        self.radius = radius
        self.center = center
        self.velocity = velocity
        self.window = window
    def draw (self):
        surface = self.window.get_surface()
        colour = Color(self.colour)
        draw_circle(surface, colour, self.center, self.radius)
    def move (self):
        size = [self.window.get_width(), self.window.get_height()]
        for index in range(0,2):
            self.center[index] = self.center[index] + self.velocity[index]
            if (self.center[index] < self.radius) or ((self.center[index] + self.radius) > size[index]):
                self.velocity[index] = -self.velocity[index]
    def randomize(self):
        size = [self.window.get_width(), self.window.get_height()]
        for index in range(0,2):
            self.center[index] = randint(self.radius,(size[index] - self.radius))
    def intersects(self,dot):
        dist = sqrt((self.center[0] - dot.center[0])**2 + (self.center[1] - dot.center[1])**2)
        return dist <= self.radius + dot.radius
    def get_color(self):
        return self.colour
class Game:
    def __init__ (self):
        self.window = Window('Poke the Dots', 500, 400)
        self.set_window()
        self.frame_rate = 90
        self.close_selected = False
        self.clock = Clock()
        self.small_dot = Dot('red',30,[50,75],[1,2],self.window)
        self.big_dot = Dot('blue', 40, [200,100], [2,1],self.window)
        self.small_dot.randomize()
        self.big_dot.randomize()
        self.score = 0
        self.continue_poke = True
    def set_window (self):
        self.window.set_font_name('ariel')
        self.window.set_font_size(64)
        self.window.set_font_color('white')
        self.window.set_bg_color('black')
    def play (self):
        while not self.close_selected:
            self.handle_events()
            self.draw()
            self.update()
        self.window.close()
    def handle_events (self):
        event_list = get_events()
        for event in event_list:
            self.handle_one_event(event)
    def handle_one_event (self,event):
        if event.type == QUIT:
            self.close_selected = True
        elif self.continue_poke and event.type == MOUSEBUTTONUP:
            self.handle_mouse_up(event)
    def handle_mouse_up(self,event):
        self.small_dot.randomize()
        self.big_dot.randomize()
    def draw (self):
        self.window.clear()
        self.draw_score()
        self.small_dot.draw()
        self.big_dot.draw()
        if not self.continue_poke:
            self.draw_game_over()
        self.window.update()
    def update(self):
        if self.continue_poke:
            self.small_dot.move()
            self.big_dot.move()
            self.score = get_ticks() // 1000            
        self.clock.tick(self.frame_rate)
        if self.small_dot.intersects(self.big_dot):
            self.continue_poke = False
    def draw_score(self):
        string = 'Score: ' +str(self.score)
        self.window.draw_string(string,0,0)
    def draw_game_over(self):
        string = 'GAME OVER'
        font_colour = self.small_dot.get_color()
        bg_colour = self.big_dot.get_color()
        original_font_colour = self.window.get_font_color()
        original_bg_colour = self.window.get_bg_color()
        self.window.set_font_color(font_colour)
        self.window.set_bg_color(bg_colour)
        height = self.window.get_height() - self.window.get_font_height()
        self.window.draw_string(string,0,height)
        self.window.set_font_color(original_font_colour)
        self.window.set_bg_color(original_bg_colour)        
def main():
    game = Game()
    game.play()
main()
