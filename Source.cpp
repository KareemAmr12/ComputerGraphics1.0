#include <stdio.h>
#include <glew.h>
#include <glut.h>
#include <freeglut.h>
#include <cmath>
#include <string>


#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600 // in pixels
#define WIN_W 600

#define TORSO_HEIGHT 5.0
#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_LEG_SIZE  0.5
#define LOWER_LEG_SIZE  0.5
#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_SIZE  0.5
#define TORSO_SIZE 0.5
#define UPPER_ARM_SIZE 0.5
#define LOWER_ARM_SIZE  0.5
#define HEAD_HEIGHT 0.4
#define HEAD_RADIUS 0.4



float angle = 0;
float rotateX = 0;
float rotateY = 0;
float rotateZ = 0;

float red = 0;
float green = 0;
float blue = 1;

float temp1 = 0;
float temp2 = 0;
float temp3 = 0;

float zoom = 0;

bool display_WF = false;
bool display_axis = true;
bool clear = false;
bool White_Done = false;
bool display_heart = false;

void* m_glutFont = GLUT_BITMAP_9_BY_15;

bool bMouseDown = false;


//Function acquired from https://www.youtube.com/watch?v=elE__Nouv54

void drawText(const std::string& text, const unsigned int x, const unsigned int y, const float r, const float g, const float b)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, WIN_W, 0, WIN_H, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	for (const char c : text)
		glutBitmapCharacter(m_glutFont, (int)c);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//use transform for zoom

//see examples posted for the submenues

//Solids
void solid_head()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glTranslatef(0.0, 1.1 * HEAD_HEIGHT , 0.0);
	glScalef( HEAD_RADIUS ,  HEAD_HEIGHT  ,  HEAD_RADIUS );
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glColor3f(red, green, blue);
	glutSolidSphere(HEAD_RADIUS, 100,100);
	glPopMatrix();
}

void solid_torso()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.9 ,  1.14 ,  0.9 );
	glColor3f(red, green, blue);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutSolidCube(TORSO_SIZE);
	glPopMatrix();
}

void solid_left_upper_arm()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.6 ,  0.09 ,  0.25 );
	glTranslatef(0.7, 1.9, 0);
	glColor3f(red, green, blue);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutSolidCube(1);
	glPopMatrix();
}



void solid_right_upper_arm()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.6 ,  0.09 ,  0.25 );
	glTranslatef(-0.7, 1.9, 0);
	glColor3f(red, green, blue);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutSolidCube(1);
	glPopMatrix();
}

void solid_left_upper_leg()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.13 ,  0.7 ,  0.25 );
	glTranslatef(0.9, -0.7, 0);
	glColor3f(red, green, blue);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutSolidCube(1);
	glPopMatrix();
}



void solid_right_upper_leg()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.13 ,  0.7 ,  0.25 );
	glTranslatef(-0.9, -0.7, 0);
	glColor3f(red, green, blue);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutSolidCube(1);
	glPopMatrix();
}




//wireframes

void wire_head()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glTranslatef(0.0, 1.1 * HEAD_HEIGHT, 0.0);
	glScalef( HEAD_RADIUS,  HEAD_HEIGHT,  HEAD_RADIUS);
	glColor3f(1, 1, 1);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutWireSphere(HEAD_RADIUS, 20, 20);
	glPopMatrix();
}

void wire_torso()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	// if white true
	// make white
	// if white false
	// make robot blue
	// color( int red, int blue, int green)
	glScalef( 0.9,  0.9,  1.14);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutWireCube(TORSO_SIZE);
	glPopMatrix();
}

void wire_left_upper_arm()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.6,  0.09,  0.25);
	glTranslatef(0.7, 1.9, 0);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutWireCube(1);
	glPopMatrix();
}



void wire_right_upper_arm()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.6,  0.09,  0.25);
	glTranslatef(-0.7, 1.9, 0);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutWireCube(1);
	glPopMatrix();
}


void wire_left_upper_leg()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.13,  0.7,  0.25);
	glTranslatef(0.9, -0.7, 0);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutWireCube(1);
	glPopMatrix();
}


void wire_right_upper_leg()
{
	glPushMatrix();
	//the first translate for the zooming
	glTranslatef(0.0, 0.0, zoom);
	glScalef( 0.13,  0.7,  0.25);
	glTranslatef(-0.9, -0.7, 0);
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glutWireCube(1);
	glPopMatrix();
}




void heart()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2, 2, -2, 2);

	//drawing heart
	//function adapated from https://gist.github.com/tuanpt216/6e01873e50528c17a35e

	glPointSize(1);
	glColor3ub(255, 0, 0);  // Color Red
	glBegin(GL_POINTS);
	for (float x = -1.139; x <= 1.139; x += 0.001)
	{
		float delta = cbrt(x * x) * cbrt(x * x) - 4 * x * x + 4;
		float y1 = (cbrt(x * x) + sqrt(delta)) / 2;
		float y2 = (cbrt(x * x) - sqrt(delta)) / 2;
		glVertex2f(x, y1);
		glVertex2f(x, y2);
	}
	glEnd();

	//displaying text
	std::string name;
	name = "Nouran";
	drawText(name.data(), WIN_W / 2 - name.size() - 21, WIN_H / 2 + 20, 1, 0, 0);
}


void axis()
{
	glPushMatrix();
	// Draw a red x-axis, a green y-axis and a blue z-axis
	glRotatef(angle, rotateX, rotateY, rotateZ);
	glBegin(GL_LINES);
	
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
	glEnd();
	glPopMatrix();
}

void MyDisplay() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (display_heart)
	{
		heart();
	}

	if (!clear)
	{

		if (display_WF)
		{
			wire_head();
			wire_torso();
			wire_left_upper_arm();
			wire_right_upper_arm();
			wire_left_upper_leg();
			wire_right_upper_leg();
		}
		else
		{
			solid_right_upper_arm();
			solid_left_upper_arm();
			solid_head();
			solid_torso();
			solid_left_upper_leg();
			solid_right_upper_leg();

		}
	}
	if (display_axis)
	{
		axis();
	}
	
	
	
	if ((red && green && blue) != 1)
	{
		temp1 = red;
		temp2 = green;
		temp3 = blue;
	}
	if (bMouseDown)
	{
		White_Done = true;
		red = 1;
		green = 1;
		blue = 1;
		
	}
	else
	{
		if (White_Done)
		{
			red = temp1;
			green = temp2;
			blue = temp3;
			White_Done = false;
		}
		
	}
	glFlush();
	glutSwapBuffers();
}



void procKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		display_WF = true;
		
		break;
	case 's':
		display_WF = false;
		
		break;
	case 'c':
		clear = true;
		display_axis = false;
		display_heart = false;
		break;
	case 'm':
		clear = false;
		display_heart = false;
		break;
	case 'a':
		display_axis = !display_axis;
		
		break;

	case 'h':
		clear = true;
		display_WF = false;
		display_axis = false;
		display_heart = !display_heart;
		
		break;
	case 27:
		exit(0);
		break;
	}
}

void procMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		bMouseDown = !bMouseDown;
	
}

void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		zoom = zoom + 0.2;
	}
	else
	{
		zoom = zoom - 0.2;
	}

	return;
}

void rotationXMenu(int value) {
	switch (value) {
	case 1:
		angle = 30;
		rotateX = 1;
		break;
	case 2:
		angle = 60;
		rotateX = 1;
		break;
	case 3: 
		angle = 90;
		rotateX = 1;
		break;
	case 4:
		angle = 120;
		rotateX = 1;
		break;
	case 5:
		angle = 180;
		rotateX = 1;
		break;
	default:
		angle = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		break;
	}
	

}

void rotationYMenu(int value) {
	switch (value) {
	case 1:
		angle = 30;
		rotateZ = 1;
		break;
	case 2:
		angle = 60;
		rotateZ = 1;
		break;
	case 3:
		angle = 90;
		rotateZ = 1;
		break;
	case 4:
		angle = 120;
		rotateZ = 1;
		break;
	case 5:
		angle = 180;
		rotateZ = 1;
		break;
	default:
		angle = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		break;
	}
}

void rotationZMenu(int value) {
	switch (value) {
	case 1:
		angle = 30;
		rotateZ = 1;
		break;
	case 2:
		angle = 60;
		rotateZ = 1;
		break;
	case 3:
		angle = 90;
		rotateZ = 1;
		break;
	case 4:
		angle = 120;
		rotateZ = 1;
		break;
	case 5:
		angle = 180;
		rotateZ = 1;
		break;
	default:
		angle = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		break;
	}
}

void color(int value) {
	if (value == 1)
	{
		red = 1;
		green = 0;
		blue = 0;
	}

	if (value == 2)
	{
		red = 0;
		green = 1;
		blue = 0;
	}

	if (value == 3)
	{
		red = 0;
		green = 0;
		blue = 1;
	}
}

void mymenu(int value) {

	switch (value) {

	case 27:
		exit(0);
		break;
	}
}

void projectionViewMenu(int value) {

	if (value == 1)
	{
		//Orthographic
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-7, 7, -7, 7, -100, 100);
		glutPostRedisplay();

	}

	if (value == 2)
	{ //Perspective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.7, 1.7, -1.7, 1.7, -100, 100);
		glutPostRedisplay();
	}

}

void createPopupMenu() {

	int rotationXDegreeMenu = glutCreateMenu(rotationXMenu);
	glutAddMenuEntry("30", 1);
	glutAddMenuEntry("60", 2);
	glutAddMenuEntry("90", 3);
	glutAddMenuEntry("120", 4);
	glutAddMenuEntry("180", 5);

	int rotationYDegreeMenu = glutCreateMenu(rotationYMenu);
	glutAddMenuEntry("30", 1);
	glutAddMenuEntry("60", 2);
	glutAddMenuEntry("90", 3);
	glutAddMenuEntry("120", 4);
	glutAddMenuEntry("180", 5);

	int rotationZDegreeMenu = glutCreateMenu(rotationZMenu);
	glutAddMenuEntry("30", 1);
	glutAddMenuEntry("60", 2);
	glutAddMenuEntry("90", 3);
	glutAddMenuEntry("120", 4);
	glutAddMenuEntry("180", 5);

	int mainRotationMenu = glutCreateMenu(mymenu);
	glutAddSubMenu("X", rotationXDegreeMenu);
	glutAddSubMenu("Y", rotationYDegreeMenu);
	glutAddSubMenu("Z", rotationZDegreeMenu);

	int projectionMenu = glutCreateMenu(projectionViewMenu);
	glutAddMenuEntry("Orthographic", 1);
	glutAddMenuEntry("Perspective", 2);

	int colorMenu = glutCreateMenu(color);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	glutCreateMenu(mymenu);
	glutAddSubMenu("Rotations", mainRotationMenu);
	glutAddSubMenu("Projection View", projectionMenu);
	glutAddSubMenu("Color", colorMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}





int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // RGB mode
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("(Karim Amr Mohamed Talaat Mohamed Hassan) (811238841)");

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay); // call the drawing function
	glutIdleFunc(MyDisplay);
	glutKeyboardFunc(procKeys);

	// mouse callback
	glutMouseFunc(procMouse);

	glutMouseWheelFunc(mouseWheel);

	createPopupMenu();

	glutMainLoop();
	return 0;
}