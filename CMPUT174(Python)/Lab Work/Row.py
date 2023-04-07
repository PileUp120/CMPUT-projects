from uagame import Window
from pygame import QUIT, Color, MOUSEBUTTONUP
from pygame.time import Clock, get_ticks
from pygame.event import get as get_events
from pygame.draw import circle as draw_circle
from pygame.draw import line as draw_line
from random import randint
def main():
    game = Game() 
    game.play()
class Game:
    def __init__(self):
        self._window = Window('Colorful Dots', 700, 650)
        self._adjust_window()
        self._window.set_auto_update(False)
        self._frame_rate = 40 # larger is faster game
        self._close_selected = False
        self._clock = Clock()
        self._continue_game = True
        gyb_dot = Dot(['green', 'yellow','blue'], [50 , 75 ], 30, [1,2], self._window)
        wyr_dot = Dot(['white','yellow','red'], [200,100], 40, [2,1], self._window)
        self.dots = [gyb_dot, wyr_dot]
        self.line_color = Color('white')
        middle = self._window.get_width()//2
        self.middle_top = [middle, 0 ]
        self.middle_bottom = [middle, self._window.get_height()]
        self.score = 0
    def _adjust_window(self):
        self._window.set_font_name('ariel')
        self._window.set_font_size(64)
        self._window.set_font_color('white')
        self._window.set_bg_color('black')    
    def play(self):
        while not self._close_selected:
            self.handle_events()
            self.draw()
            self.update()
        self._window.close()

    def handle_events(self):
        event_list = get_events()
        for event in event_list:
            self.handle_one_event(event)
    def handle_one_event(self, event):
        if event.type == QUIT:
            self._close_selected = True
        elif self._continue_game and event.type == MOUSEBUTTONUP:
            self.handle_mouse_up(event)      
    def handle_mouse_up(self,event):
        self.dots[0].randomize()
        self.dots[1].randomize()
        self._frame_rate = 1.1 * self._frame_rate
    def draw(self):
        # Draw all game objects.
        # - self is the Game to draw

        self._window.clear()
        surface = self._window.get_surface()

        #Draw anything you need to draw in between
        # these two lines
        #---------------------#
        for dot in self.dots:
            dot.draw()

        draw_line(surface, self.line_color, self.middle_top, self.middle_bottom)

        self._window.draw_string("Score: " + str(self.score), 0,0)
        self._window.update()

    def update(self):
        # Update the game objects.
        # - self is the Game to update

        if self._continue_game:
            for dot in self.dots:
                dot.move()

            self.score = get_ticks()//1000

        self._clock.tick(self._frame_rate)

        # decide continue
        all_touching = True
        for dot in self.dots:
            if not dot.touching_center():
                all_touching = False
        if all_touching:
            self._continue_game = False


class Dot:
    # An object in this class represents a colored circle.

    def __init__(self, colors, center, radius, velocity, window):
        self.left_color = colors[0]
        self.center_color = colors[1]
        self.right_color = colors[2]
        self.center = center
        self.radius = radius
        self.velocity = velocity
        self._window = window

    def draw(self):
        color = self.pick_color()
        color = Color(color)
        draw_circle(self._window.get_surface(), color, self.center, self.radius)
    def randomize(self):
        size = [self._window.get_width(), self._window.get_height()]
        for index in range(0,2):
            self.center[index] = randint(self.radius,(size[index] - self.radius))    
    def pick_color(self):
        # decides which color the dot should display depending on its current position.
        #- self: the dot object whose color we need to determine
        # return: a pygame.Color object representing the current color of the dot
        middle_line = self._window.get_width()//2
        if self.center[0] + self.radius  < middle_line:
            return self.left_color
        elif self.center[0] - self.radius > middle_line:
            return self.right_color
        else:
            return self.center_color

    def move(self):
        # Move the Dot.
        # - self is the Dot to move
        size = self._window.get_surface().get_size()

        for index in range(len(size)):
            self.center[index] = self.center[index] + self.velocity[index]    
            #Check bounce
            if self.center[index] - self.radius < 0 or self.center[index] + self. radius > size[index]:
                self.bounce_ball(index)


    def bounce_ball(self, index):
        #Bounce the ball along the provided index
        # -self is the dot object to bounce
        # -index is an int telling us whether to bounce along the 0 (x) axis or
        # 1 (y) axis.
        self.velocity[index] = -1* self.velocity[index] 

    def touching_center(self):
        #Checks if the dot is touching the vertical center line of the screen
        # self - the dot object
        # return: True if the dot is touching the center, otherwise False
        middle = self._window.get_width()//2
        return self.center[0] <= middle + self.radius and self.center[0] >= middle - self.radius


main()