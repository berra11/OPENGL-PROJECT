/*********
   CTIS164 - Template Source Program
----------
STUDENT : Berra Turgut
SECTION : 04
HOMEWORK: #1
----------
PROBLEMS: -
----------
ADDITIONAL FEATURES: 
- When press F2, the light of the spaceship turn on/off
- When press right click, the light of the spaceship changes
- Animated background 
*********/

/* Imp Note: That moving in the opposite direction has been calculated considering the light of the spaceship. */


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD    24 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer


#define D2R 0.0174532



// for arrow keys
#define RIGHT 4
#define LEFT  5
#define UP    6
#define DOWN  7

// mode
#define AUTO 3
#define MAN -3



int xb = 0, yb = 0; //initial position of spaceship
int r = 156, g = 217, b = 220; //colour variables
int specialkey; // variable change the direction 
int spaceship = 0;
int mode; 
int shipR = 50; //Spaceship glass's initial radius // 

bool light = true; // the light of the spaceship 


/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int xs; // star variable 


// to draw circle, center at (x,y)
// radius r

void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}



void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}



void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void lightofship() {

    glColor3ub((r + 204) % 256, (g + 170) % 256, (b + 170) % 256);
    glBegin(GL_QUADS);
    glVertex2f(-50 + xb, 0 + yb);
    glVertex2f(150 + xb, -300 + yb);
    glVertex2f(50 + xb, 0 + yb);
    glVertex2f(-150 + xb, -300 + yb);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-200 + xb, -300 + yb);
    glVertex2f(0 + xb, 100 + yb);
    glVertex2f(200 + xb, -300 + yb);
    glEnd();
}


void drawspaceship() {
    //spaceship's glass
    glColor3ub(232, 241, 250);
    circle(0 + xb, 65 + yb, 50);

    // fins 
    glColor3ub(30, 8, 86);
    glBegin(GL_QUADS);
    glVertex2f(-30 + xb, 30 + yb);
    glVertex2f(-60 + xb, 0 + yb);
    glVertex2f(30 + xb, 30 + yb);
    glVertex2f(60 + xb, 0 + yb);
    glEnd();

    //body
    glColor3ub(232, 241, 250);
    circle(0 + xb, 60 + yb, 50);

    glColor3ub(17, 74, 131);
    glRectf(-60 + xb, 70 + yb, 60 + xb, 50 + yb);
    circle(-55 + xb, 60 + yb, 10);
    circle(55 + xb, 60 + yb, 10);

    glColor3ub(10, 48, 86);
    glRectf(-70 + xb, 60 + yb, 70 + xb, 40 + yb);
    circle(0 + xb, 60 + yb, 5);
    circle(-70 + xb, 50 + yb, 10);
    circle(70 + xb, 50 + yb, 10);

    glColor3ub(9, 34, 57);
    circle(20 + xb, 60 + yb, 5);
    glColor3ub(9, 34, 57);
    circle(-20 + xb, 60 + yb, 5);

    glEnd();
    glColor3f(1, 0.5, 0.5);

    glColor3ub(30, 8, 86);
    circle(0 + xb, 5 + yb, 5);

    glColor3f(1, 0.5, 0.5);

    glEnd();
}

void background() {
    glClearColor(0.29, 0.25, 0.65, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(200, 100, 600);
}

void moon() {
    glColor3ub(234, 180, 13);
    circle(0, -800, 700);

    glColor3ub(156, 158, 31);
    circle(300, -350, 70);
    circle(-100, -200, 70);
    circle(-400, -400, 70);

    //Star
    glColor3ub(128, 161, 188);
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 -200; i += 90)
        vprint2(i + xs, 300, 0.5, "*");
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 -200; i += 90)
        vprint2(i + xs,250 , 0.3, "*");
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 -200; i += 90)
        vprint2(i + xs, 200, 0.5, "*");
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 -200; i += 90)
        vprint2(i + xs, 150, 0.3, "*"); 
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 -200; i += 90)
        vprint2(i + xs, 100, 0.5, "*");
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 - 200; i += 90)
        vprint2(i + xs, 50, 0.3, "*");
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 - 200; i += 90)
        vprint2(i + xs, 0, 0.5, "*");
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 - 200; i += 90)
        vprint2(i + xs, -50, 0.3, "*");
    for (int i = -winWidth / 2 + 10; i <= winWidth / 2 - 200; i += 90)
        vprint2(i + xs, -100, 0.5, "*");
   
}

void earth() {

    glColor3ub(61, 133, 198);
    circle(0, 200, 70);
    glColor3f(1, 1, 1);
    circle(0, 265, 20);
    circle(25, 250, 20);
    circle(-25, 250, 20);
    glRectf(20, 230, -20, 250);
    circle(-60, 200, 20);
    circle(-40, 190, 20);
    circle(-75, 190, 20);
    glRectf(-70, 170, -40, 190);
    circle(60, 200, 20);
    circle(40, 190, 20);
    circle(75, 190, 20);
    glRectf(70, 170, 40, 190);
}

void dispbackground() {
    // bacground colour 
    glColor3ub(15, 7, 5);
    glBegin(GL_POLYGON);
    glVertex2d(-300, 300);
    glVertex2d(300 + xb, 300);
    glColor3ub(21 + xb, 80, 160);
    glVertex2d(300 + xb, -300);
    glVertex2d(-300 + xb, -300);
    glEnd();

    background();
    glColor3ub(32, 32, 32);

    // Sky
    glColor3ub(181, 229, 243);
    glBegin(GL_POLYGON);
    glVertex2f(-900, 600);
    glVertex2f(900, 600);
    glColor3ub(192, 155, 240);
    glVertex2f(900, -600);
    glVertex2f(-900, -600);
    glEnd();
}



//
// To display onto window using OpenGL commands
//
void display() {


   
    glClear(GL_COLOR_BUFFER_BIT);

    
    if (spaceship == 1)
    {
        

            dispbackground();
            moon();
            earth();
            drawspaceship();

            if (light)
            {
               
                lightofship();
                drawspaceship();
            }
    }
    else
    {
        
        dispbackground();
        moon();
        earth();
        
    }

    if (spaceship == 0) {

        glColor3f(0, 1, 0); // green
        vprint((winWidth / 2) - 750, -(winHeight / 2) + 400,GLUT_BITMAP_9_BY_15, "<Click to teleport the spaceship>");
    }



    // to display the direction 
    glColor3ub(104, 0, 104); 
        if (specialkey == LEFT)
            vprint((winWidth / 2) - 220, -(winHeight / 2) + 700, GLUT_BITMAP_HELVETICA_18, "Direction: Left");
        else if (specialkey == RIGHT)
            vprint((winWidth / 2) - 220, -(winHeight / 2) + 700, GLUT_BITMAP_HELVETICA_18, "Direction: Right");
        else if (specialkey == UP)
            vprint((winWidth / 2) - 220, -(winHeight / 2) + 700, GLUT_BITMAP_HELVETICA_18, "Direction: Up");
        else if (specialkey == DOWN)
            vprint((winWidth / 2) - 220, -(winHeight / 2) + 700, GLUT_BITMAP_HELVETICA_18, "Direction: Down");
        else 
            vprint((winWidth / 2) - 220, -(winHeight / 2) + 700, GLUT_BITMAP_HELVETICA_18, "Direction: -  ");

      
           
        // t0 display the name of the mode 
    if (mode == AUTO) {
            glColor3ub(187, 144, 187);
            vprint((winWidth / 2) - 500, -(winHeight / 2) + 750, GLUT_BITMAP_HELVETICA_18, "AUTONOMOUS MOD: PRESS <F1> TO SWITCH MODE");
    }
       
   else {
            glColor3ub(187, 144, 187);
            vprint((winWidth / 2) - 500, -(winHeight / 2) + 750, GLUT_BITMAP_HELVETICA_18, "MANUAL MODE: PRESS <F1> TO SWITCH MODE");
   }

   
    // display commands 
    glColor3f(0, 1, 1); 
    vprint((winWidth / 2) - 410, -(winHeight / 2) + 80, GLUT_BITMAP_8_BY_13, "Right Click : Change color of the spaceship's light");
    vprint((winWidth / 2) - 410, -(winHeight / 2) + 60, GLUT_BITMAP_8_BY_13, "Left Click  : Change the location of shape");
    vprint((winWidth / 2) - 410, -(winHeight / 2) + 40, GLUT_BITMAP_8_BY_13, "Arrow Keys  : go left, go right, go up, go down");
    glColor3ub(67, 69, 9);
    vprint((winWidth / 2) - 800 , -(winHeight / 2) + 10, GLUT_BITMAP_9_BY_15, "Press <F2> to turn on/off the light of the spaceship");


   
    // Name-Surname-Id
    glColor3ub(47, 12, 140);
    glRectf(-400, 400, -600, 310);
    glColor3ub(218, 191, 223);
    vprint(-600, 350, GLUT_BITMAP_9_BY_15, "Berra Turgut");
    vprint(-600, 370, GLUT_BITMAP_9_BY_15, "21903363");


    glutSwapBuffers();
}


//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.

        switch (key)
        {
        case GLUT_KEY_UP:
            up = true;
            break;
        case GLUT_KEY_DOWN:
            down = true;
            break;
        case GLUT_KEY_LEFT:
            left = true;
            break;
        case GLUT_KEY_RIGHT:
            right = true;
            break;
        }

        
        
        switch (key)
        {
        case GLUT_KEY_UP:
            if (yb < (winHeight / 2) - 200);
            yb++;
            break;
        case GLUT_KEY_DOWN:
            if (yb < -(winHeight / 2) - 200);
            yb--;
            break;
        case GLUT_KEY_LEFT:
            if (xb < (winHeight / 2) - 200);
            xb--;
            break;
        case GLUT_KEY_RIGHT:
            if (xb < -(winHeight / 2) - 200);
            xb++;
            break;
        }

    

    if (key == GLUT_KEY_UP) {
        specialkey = UP; 
    }
    if (key == GLUT_KEY_DOWN) {
        specialkey = DOWN;
    }
    if (key == GLUT_KEY_RIGHT) {
        specialkey = RIGHT;
    }
    if (key == GLUT_KEY_LEFT) {
        specialkey = LEFT;
    }


    //change game mode (AUTO/MANUAL)
    if (key == GLUT_KEY_F1) {
        if (mode == AUTO)
            mode = MAN;
        else
            mode = AUTO; 
    }
    if (key == GLUT_KEY_F2) {
        light = !light; 
    }
    
   
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.
    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
    }
   
    

    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN ) {
        spaceship = 1;
        xb = x - winWidth / 2;
        yb = winHeight / 2 - y;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.




    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.

    // to change the direction of the spaceship
    if (mode == AUTO)
    {
        
        if (specialkey == LEFT)
        {
            if (xb > -(winWidth / 2 - 200))
                xb--;
            if (xb == -(winWidth / 2 - 200))
                specialkey = RIGHT;
        }
        if (specialkey == RIGHT)
        {
            if (xb < (winWidth / 2 - 200))
                xb++;
            if (xb == (winWidth / 2 - 200))
                specialkey = LEFT;
        }
        if (specialkey == UP) {

            if (yb < (winWidth / 2 - 320))
                yb++;
            if (yb == (winWidth / 2 - 320))
                specialkey = DOWN;
        }
        if (specialkey == DOWN) {

            if (yb > (winWidth / 2 - 700))
                yb--;
            if (yb == (winWidth / 2 - 700))
                specialkey = UP;
        }

    }

    // move stars
    if (xs  < winHeight / 2 + 1400 )
        xs++;

    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("BERRA TURGUT: SPACESHIP ANIMATION");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

  

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}