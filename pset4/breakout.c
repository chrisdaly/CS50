//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// height and width of the bricks in pixels
#define BRICK_HEIGHT 10
#define BRICK_WIDTH 40

// spaces between the bricks in pixels
#define BRICK_SPACE (50/11)

// height and width of the paddle in pixels
#define PADDLE_HEIGHT 5
#define PADDLE_WIDTH 50

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void reverseDirection(double *velocity);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
		
    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initial velocity
    double magnitude = (drand48()+1)/50;
    int direction = (rand()%2) * 2 - 1;
	double velocity_x = direction * magnitude;
	double velocity_y = .05;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse clicks
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
                {
                    // ensure circle follows top cursor
                    double x = getX(event) - getWidth(paddle) / 2;
                    double y = getY(paddle);
                    setLocation(paddle, x, y);
                }
        }  
        
        // update the ball's position
        move(ball, velocity_x, velocity_y);
        
		// check for ball hitting the walls
		// bounce off right edge of window
		if (getX(ball) + getWidth(ball) >= getWidth(window))
			{
				reverseDirection(&velocity_x);
			}

		// bounce off left edge of window
		else if (getX(ball) <= 0)
			{
				reverseDirection(&velocity_x);
			}
			
		// bounce off top edge of window
		else if (getY(ball) <= 0)
			{
				reverseDirection(&velocity_y);
			}
			
		// hit bottom edge of window
		else if (getY(ball) + getWidth(ball) >= getHeight(window))
			{
				lives--;
				setLocation(ball, WIDTH/2 - RADIUS/2, 150);
				setLocation(paddle, WIDTH/2 - PADDLE_WIDTH/2, HEIGHT-30);
				waitForClick();
			}   
		
        // check for ball hitting the paddle
        GObject collisionObject = detectCollision(window, ball);  
        
		/// check for ball hitting bricks
		if (collisionObject != NULL && strcmp(getType(collisionObject), "GRect") == 0)
        {
            reverseDirection(&velocity_y);
            if (collisionObject != paddle)
            {
                removeGWindow(window, collisionObject);
                bricks--;
                points++;
                updateScoreboard(window, label, points);
                
            }
        }
		
    }
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
	string colour[5] = {"RED", "ORANGE", "CYAN", "GREEN", "BLUE"};
	int offset = 30;
    	
    // TODO
    for (int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
                GRect rect = newGRect((BRICK_SPACE + j*(BRICK_SPACE + BRICK_WIDTH)), (BRICK_SPACE + i*(BRICK_SPACE + BRICK_HEIGHT) + offset), BRICK_WIDTH, BRICK_HEIGHT);
                setColor(rect, colour[i]);
                setFilled(rect, true);
				add(window, rect);
        }    
    }
}

/**
 * Instantiates ball in center of window. Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval circle = newGOval(WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS, RADIUS*2, RADIUS*2);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{

    GRect rect = newGRect(WIDTH/2 - PADDLE_WIDTH, HEIGHT - 30, PADDLE_WIDTH, PADDLE_HEIGHT);
    setColor(rect, "BLACK");
    setFilled(rect, true);
    add(window, rect);
    
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
	GLabel label = newGLabel("0");
    setFont(label, "Calibri-40");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
	setColor(label, "GRAY");
    add(window, label);

    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
/**
 * Switches the ball's velocity in the opposite direction
 */
void reverseDirection(double *velocity)
{
	// dereferencing in order to get the values at the arguments' addresses and store them
	double velocity_copy = *velocity;
	
	*velocity *= -1;
	
	return;	
}

