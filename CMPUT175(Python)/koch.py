import turtle

def Koch(length, order):
    if order == 0:
        turtle.forward(length)
    else:
        Koch(length/3,order-1)
        turtle.left(60)
        Koch(length/3,order-1)
        turtle.right(120)
        Koch(length/3,order-1)
        turtle.left(60)
        Koch(length/3,order-1)
                
            

#test
def main():
    turtle.setworldcoordinates(-1, -1, 150, 150)
    turtle.penup()
    turtle.goto(10,70)
    turtle.pendown()
    Koch(120, 3)
    turtle.mainloop()  
    
main()