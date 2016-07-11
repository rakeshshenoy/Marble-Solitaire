#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<math.h>
#include<GLUT/GLUT.h>

char *end = "GAME OVER!";
char *anykey = "PRESS ANY KEY!";
char *pressb = "PRESS B TO GO BACK!";
char *op1 = "1. PLAY";
char *op2 = "2. HOW TO PLAY";
char *op3 = "3.EXIT";
char *selected = "SELECTED!";
char *moved = "MOVED!";
char *removed = "REMOVED!";
char *howtoplay = "A valid move is to jump a marble orthogonally over an adjacent marble into a hole two positions away and then to remove the jumped marble.";
char *howtoplay2 = "Click on the first marble and then click on a hole two positions away to move it.";
char *name1 = "M RAKESH SHENOY (1RN11CS051)";
char *name2 = "RAHUL CHANDRAN (1RN11CS074)";
char rem[5];
char *remaining = "Marbles remaining:";
int flag = 0; //Flag to check if a marble is selected
float xx, yy, x2, y2; //Variables to store coordinates of selected marble
const unsigned int triangles = 20;
int m[9][9]; //Matrix that holds 0 for a hole and 1 for a marble
int a, b;
int count = 0;	//Variable to hold remaining marbles
int start = 0; //Flag holding different values for every screen
int finish = 0; //Flag to check game over
int xmin = 0, xmax = 1000, ymin = 0, ymax = 1000;

void myinit()  //Function that handles all the initializations of OpenGL
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xmin, xmax, ymin, ymax);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)	 //Function to reshape the contents of the window on changing window size
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w > h)
    {
        
        gluOrtho2D(xmin*w / h, xmax*w / h, ymin, ymax);
    }
    else
    {
        gluOrtho2D(xmin, xmax, ymin*h / w, ymax*h / w);
    }
    glMatrixMode(GL_MODELVIEW);
}

void disptext(char text[], int x, int y)  //Function to display a string on the screen
{
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

int check()	 //Function to check if there are any more moves
{
    for (int i = 0; i<9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (m[i][j] == 1)
            {
                if (m[i - 1][j] == 1 && m[i - 2][j] == 0)
                {
                    return 0;
                }
                if (m[i + 1][j] == 1 && m[i + 2][j] == 0)
                {
                    return 0;
                }
                if (m[i][j - 1] == 1 && m[i][j - 2] == 0)
                {
                    return 0;
                }
                if (m[i][j + 1] == 1 && m[i][j + 2] == 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void checkcond()	 //Function to check game over condition
{
    finish = check();
    if (finish == 1)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (m[i][j] == 1)
                {
                    count++;
                }
            }
        }
        std::string rem = std::to_string(count);
        char rem1[3];
        strcpy(rem1, rem.c_str());
        disptext(rem1, 1820, 500);
        disptext(remaining, 1570, 500);
        disptext(end, 1600, 700);
        disptext(anykey, 1570, 300);
    }
}

void drawmarble(int x, int y)	 //Function to draw a marble on the screen
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int k = 0; k <= triangles; k++)
    {
        glVertex2f(x + (25 * cos(k * 2 * 3.142 / triangles)), y + (25 * sin(k * 2 * 3.142 / triangles)));
    }
    glEnd();
}

void movemarble()	 //Function to move a marble from one hole to another
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    flag = 0;
    glutPostRedisplay();
}

void howtoplay1()	 //Function to display the 'How to Play' screen
{
    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    disptext(op2, 900, 950);
    disptext(howtoplay, 100, 900);
    disptext(howtoplay2, 500, 850);
    disptext(selected, 1100, 650);
    disptext(moved, 1100, 450);
    disptext(removed, 1100, 250);
    disptext(pressb, 850, 50);
    glLineWidth(3);
    glColor3f(1, 0, 0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 845; j < 1050; j += 100)
        {
            glBegin(GL_LINE_LOOP);
            glVertex2f(j, 800 - 200 * i);
            glVertex2f(j + 60, 800 - 200 * i);
            glVertex2f(j + 60, 740 - 200 * i);
            glVertex2f(j, 740 - 200 * i);
            glEnd();
        }
    }
    glColor3f(0, 0, 1);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2f(975, 720);
    glVertex2f(975, 620);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(975, 520);
    glVertex2f(975, 420);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(975, 320);
    glVertex2f(975, 220);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(950, 640);
    glVertex2f(975, 620);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(1000, 640);
    glVertex2f(975, 620);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(950, 440);
    glVertex2f(975, 420);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(975, 420);
    glVertex2f(1000, 440);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(975, 220);
    glVertex2f(1000, 240);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(975, 220);
    glVertex2f(950, 240);
    glEnd();
    glColor3f(0, 1, 0);
    drawmarble(875, 770);
    drawmarble(975, 770);
    drawmarble(975, 570);
    drawmarble(975, 370);
    drawmarble(1075, 370);
    drawmarble(1075, 170);
    glColor3f(0, 0, 1);
    drawmarble(875, 570);
    glFlush();
}

void keyboard(unsigned char key, int x, int y)	 //Function to accept keyboard input
{
    if (finish == 1)
    {
        exit(0);
    }
    if (start == 0)
    {
        start = 1;
        glutPostRedisplay();
    }
    if (start == 1)
    {
        if (key == '1')
        {
            start = 2;
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            glutPostRedisplay();
        }
        else if (key == '2')
        {
            start = 3;
            howtoplay1();
        }
        else if (key == '3')
        {
            exit(0);
        }
    }
    if (start == 3)
    {
        if (key == 'b' || key == 'B')
        {
            start = 1;
            glutPostRedisplay();
        }
    }
}

void mouse(int button, int status, int x, int y)	 //Function to accept mouse input
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble worldX, worldY, worldZ;
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    winX = x;
    winY = viewport[3] - y;
    winZ = 0;
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);	//Function call to convert window coordinates to world coordinates
    if (start == 2 && button == GLUT_LEFT_BUTTON && status == GLUT_DOWN && flag == 0)
    {
        for (int i = 0; i<3; i++)
        {
            if (worldX>900 + 100 * i && worldX < 960 + 100 * i)
            {
                for (int j = 0; j<9; j++)
                {
                    if (m[i + 3][j] == 1 && worldY>50 + 100 * j && worldY < 110 + 100 * j)
                    {
                        flag = 1;
                        x2 = 900 + 100 * i;
                        y2 = 50 + 100 * j;
                        a = i + 3;
                        b = j;
                        glColor3f(0, 0, 1);
                        drawmarble(x2 + 30, y2 + 30);
                        glFlush();
                        return;
                    }
                }
            }
        }
        for (int i = 0; i<9; i++)
        {
            if (worldX>600 + 100 * i && worldX < 660 + 100 * i)
            {
                for (int j = 0; j<3; j++)
                {
                    if (m[i][j + 3] == 1 && worldY>350 + 100 * j && worldY < 410 + 100 * j)
                    {
                        flag = 1;
                        x2 = 600 + 100 * i;
                        y2 = 350 + 100 * j;
                        a = i;
                        b = j + 3;
                        glColor3f(0, 0, 1);
                        drawmarble(x2 + 30, y2 + 30);
                        glFlush();
                        return;
                    }
                }
            }
        }
    }
    if (start == 2 && button == GLUT_LEFT_BUTTON && status == GLUT_DOWN && flag == 1)
    {
        if (worldY>y2 && worldY<y2 + 60 && b<6 && b>2)
        {
            if (m[a + 2][b] == 0 && m[a + 1][b] == 1 && worldX>x2 + 200 && worldX<x2 + 260 && worldX<1460)
            {
                m[a][b] = 0;
                m[a + 1][b] = 0;
                m[a + 2][b] = 1;
            }
            else if (m[a - 2][b] == 0 && m[a - 1][b] == 1 && worldX>x2 - 200 && worldX<x2 - 140 && worldX>600)
            {
                m[a][b] = 0;
                m[a - 1][b] = 0;
                m[a - 2][b] = 1;
            }
        }
        if (worldX>x2 && worldX<x2 + 60 && a<6 && a>2)
        {
            if (m[a][b + 2] == 0 && m[a][b + 1] == 1 && worldY>y2 + 200 && worldY<y2 + 260 && worldY<910)
            {
                m[a][b] = 0;
                m[a][b + 1] = 0;
                m[a][b + 2] = 1;
            }
            else if (m[a][b - 2] == 0 && m[a][b - 1] == 1 && worldY>y2 - 200 && worldY<y2 - 140 && worldY>50)
            {
                m[a][b] = 0;
                m[a][b - 1] = 0;
                m[a][b - 2] = 1;
            }
        }
        if (worldX>x2 && worldX<x2 + 60 && ((a<3 && a >= 0) || (a>5 && a<9)))
        {
            if (m[a][b + 2] == 0 && m[a][b + 1] == 1 && worldY>y2 + 200 && worldY<y2 + 260 && worldY<610)
            {
                m[a][b] = 0;
                m[a][b + 1] = 0;
                m[a][b + 2] = 1;
            }
            else if (m[a][b - 2] == 0 && m[a][b - 1] == 1 && worldY>y2 - 200 && worldY<y2 - 140 && worldY>350)
            {
                m[a][b] = 0;
                m[a][b - 1] = 0;
                m[a][b - 2] = 1;
            }
        }
        if (worldY>y2 && worldY<y2 + 60 && ((b<3 && b >= 0) || (b>5 && b<9)))
        {
            if (m[a + 2][b] == 0 && m[a + 1][b] == 1 && worldX>x2 + 200 && worldX<x2 + 260 && worldX<1460)
            {
                m[a][b] = 0;
                m[a + 1][b] = 0;
                m[a + 2][b] = 1;
            }
            else if (m[a - 2][b] == 0 && m[a - 1][b] == 1 && worldX>x2 - 200 && worldX<x2 - 140 && worldX>600)
            {
                m[a][b] = 0;
                m[a - 1][b] = 0;
                m[a - 2][b] = 1;
            }
        }
        movemarble();
        checkcond();
    }
}

void render()	 //Function to display contents on the screen
{
    
    if (start == 0)	 //Title page
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        disptext(name1, 1500, 100);
        disptext(name2, 1500, 50);
        glColor3f(0, 1, 0);
        for (int j = 0; j < 800; j += 360)
        {
            for (int i = 50; i < 1975; i += 50)
            {
                drawmarble(i, 960 - j);
            }
        }
        glLineWidth(15);
        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        glVertex2f(150, 900);
        glVertex2f(150, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(350, 900);
        glVertex2f(350, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(350, 900);
        glVertex2f(250, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(150, 900);
        glVertex2f(250, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(450, 700);
        glVertex2f(550, 900);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(550, 900);
        glVertex2f(650, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(495, 800);
        glVertex2f(605, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(750, 900);
        glVertex2f(750, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(750, 800);
        glVertex2f(950, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(750, 900);
        glVertex2f(950, 900);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(950, 900);
        glVertex2f(950, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(750, 800);
        glVertex2f(950, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1050, 900);
        glVertex2f(1050, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1050, 900);
        glVertex2f(1250, 900);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1250, 900);
        glVertex2f(1250, 850);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1250, 850);
        glVertex2f(1050, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1050, 800);
        glVertex2f(1250, 750);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1250, 750);
        glVertex2f(1250, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1250, 700);
        glVertex2f(1050, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1350, 900);
        glVertex2f(1350, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1350, 700);
        glVertex2f(1550, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1650, 900);
        glVertex2f(1650, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1650, 900);
        glVertex2f(1850, 900);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1650, 800);
        glVertex2f(1800, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1650, 700);
        glVertex2f(1850, 700);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(50, 500);
        glVertex2f(50, 400);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(50, 500);
        glVertex2f(250, 500);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(250, 400);
        glVertex2f(50, 400);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(250, 300);
        glVertex2f(250, 400);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(250, 300);
        glVertex2f(50, 300);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(315, 500);
        glVertex2f(515, 500);
        glVertex2f(515, 300);
        glVertex2f(315, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(580, 500);
        glVertex2f(580, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(580, 300);
        glVertex2f(780, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(845, 500);
        glVertex2f(845, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(910, 500);
        glVertex2f(1110, 500);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1010, 500);
        glVertex2f(1010, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1175, 300);
        glVertex2f(1275, 500);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1275, 500);
        glVertex2f(1375, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1230, 400);
        glVertex2f(1330, 400);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1440, 500);
        glVertex2f(1440, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1505, 500);
        glVertex2f(1505, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1505, 500);
        glVertex2f(1705, 500);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1705, 500);
        glVertex2f(1705, 400);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1705, 400);
        glVertex2f(1505, 400);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1505, 400);
        glVertex2f(1705, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1770, 500);
        glVertex2f(1770, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1770, 500);
        glVertex2f(1970, 500);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1770, 400);
        glVertex2f(1920, 400);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1770, 300);
        glVertex2f(1970, 300);
        glEnd();
        glColor3f(1, 0, 0);
        disptext(anykey, 850, 100);
    }
    if (start == 1)	 //Menu
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        glVertex2f(725, 900);
        glVertex2f(725, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(725, 900);
        glVertex2f(775, 850);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(775, 850);
        glVertex2f(825, 900);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(825, 900);
        glVertex2f(825, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(875, 900);
        glVertex2f(875, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(875, 900);
        glVertex2f(975, 900);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(875, 800);
        glVertex2f(975, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(875, 850);
        glVertex2f(945, 850);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1025, 900);
        glVertex2f(1025, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1025, 900);
        glVertex2f(1125, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1125, 800);
        glVertex2f(1125, 900);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1175, 900);
        glVertex2f(1175, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1175, 800);
        glVertex2f(1275, 800);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(1275, 800);
        glVertex2f(1275, 900);
        glEnd();
        glColor3f(0, 0, 1);
        disptext(op1, 950, 650);
        disptext(op2, 875, 500);
        disptext(op3, 950, 350);
        glColor3f(0, 1, 0);
        for (int j = 0; j <= 950; j += 900)
        {
            for (int i = 650; i < 1400; i += 50)
            {
                drawmarble(i, 960 - j);
            }
        }
        for (int j = 0; j < 800; j += 750)
        {
            for (int i = 960; i > 10; i -= 50)
            {
                drawmarble(650 + j, i);
            }
        }
    }
    if (start == 2)	 //Game screen
    {
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(1030, 480);
        for (int k = 0; k <= 1000; k++)
        {
            glVertex2f(1030 + (475 * cos(k * 2 * 3.142 / 1000)), 480 + (475 * sin(k * 2 * 3.142 / 1000)));
        }
        glEnd();
        glLineWidth(3);
        glColor3f(1, 0, 0);
        for (int i = 900; i < 1200; i += 100)
        {
            for (int j = 50; j < 950; j += 100)
            {
                glBegin(GL_LINE_LOOP);
                glVertex2f(i, j);
                glVertex2f(i, j + 60);
                glVertex2f(i + 60, j + 60);
                glVertex2f(i + 60, j);
                glEnd();
            }
        }
        for (int i = 600; i < 1500; i += 100)
        {
            for (int j = 350; j < 650; j += 100)
            {
                glBegin(GL_LINE_LOOP);
                glVertex2f(i, j);
                glVertex2f(i, j + 60);
                glVertex2f(i + 60, j + 60);
                glVertex2f(i + 60, j);
                glEnd();
            }
        }
        glColor3f(0, 1, 0);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 3; j < 6; j++)
            {
                if (m[i][j] == 1)
                {
                    xx = 630 + 100 * i;
                    yy = 80 + 100 * j;
                    drawmarble(xx, yy);
                }
            }
        }
        for (int i = 3; i < 6; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (m[i][j] == 1)
                {
                    xx = 630 + 100 * i;
                    yy = 80 + 100 * j;
                    drawmarble(xx, yy);
                }
            }
        }
    }
    glFlush();
}

int main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1300, 650);
    glutCreateWindow("Marble Solitaire");
    myinit();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j<9; j++)
        {
            if ((i>2 && i<6) || (j>2 && j < 6))
                m[i][j] = 1;
            else
                m[i][j] = 7;
        }
    }
    m[4][4] = 0;
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}