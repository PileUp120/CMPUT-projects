import pygame

class Tile:

    def __init__(self, x, y, image, cover):
        self.image = image
        self.cover = cover
        self.rect = pygame.Rect(x, y, 60, 60)
        self.covered = True
        self.time_to_cover = None

    def draw(self, screen):
        # draw cover or image
        if self.covered:
            screen.blit(self.cover, self.rect)
        else:
            screen.blit(self.image, self.rect)

    def update(self):
        # hide card (after 2000ms)
        if not self.covered and pygame.time.get_ticks() >= self.time_to_cover:
            self.covered = True

    def handle_event(self, event):
        # check left button click
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            # check position 
            if self.rect.collidepoint(event.pos):
                self.covered = not self.covered
                if not self.covered:
                    # if uncovered then set +2000ms to cover
                    self.time_to_cover = pygame.time.get_ticks() + 2000

#----------------------------------------------------------------------

# init

pygame.init()

screen = pygame.display.set_mode((320,320))

# create images

img = pygame.surface.Surface((60, 60))
img.fill((255,0,0))

cov = pygame.surface.Surface((60, 60))
cov.fill((0,255,0))

# create tiles

tiles = []
for y in range(5):
    for x in range(5):
        tiles.append( Tile(x*65, y*65, img, cov) )

# mainloop

clock = pygame.time.Clock()
running = True

while running:

    # events

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        for x in tiles:
            x.handle_event(event)

    # updates

    for x in tiles:
        x.update()

    # draws

    for x in tiles:
        x.draw(screen)

    pygame.display.flip()

    # clock

    clock.tick(25)

pygame.quit()