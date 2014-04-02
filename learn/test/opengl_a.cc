/*
 *--------------------------------------------------------------------------
 *   File Name:	a.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Nov 20 18:02:25 2009
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<GL/glut.h>

void	drawGround(unsigned int m, unsigned int n, unsigned int d)
{
	int w = m>>1;
	int h = n>>1;

	
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	for(int i=-w; i<w; i+=d)
	{
		glVertex3f(-h, 0, i);
		glVertex3f(h, 0, i);
	}
	for(int i=-h; i<h; i+=d)
	{
		glVertex3f(i, 0, -w);
		glVertex3f(i, 0, w);
	}
	glEnd();
	glPopMatrix();
}

void	drawAxis(GLfloat length)
{
	glPushMatrix();
	glBegin(GL_LINES);
		// draw x
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(length, 0.0, 0.0);
		// draw y
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, length, 0.0);
		// draw z
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, length);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, -length);
		
		

		//
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(length/2,length/2,length/2);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(length/2, 0.0, 0.0);
		glVertex3f(0.0, length/2, 0.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(length/2, 0.0, 0.0);
		glVertex3f(0.0, 0.0, length/2);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, length/2, 0.0);
		glVertex3f(0.0, 0.0, length/2);
	glEnd();
	glPopMatrix();
}

void	display()
{
	static float a = 0.0;
	static float b = 0.0;
	static float c = 0.0;
	a += 0.05;
	//b = (b>45)?30:60;
	b += 0.05;
	c += 0.05;
	

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#define	D
#ifdef	D
	gluLookAt(0, 60, 100, 0, 0, 0, 0, 1, 0);
#else


#endif

#ifdef	D
/*
	glPushMatrix();
		c = 0.0;
		//b = 0.0;
		a = 0.0;
		glTranslatef(-20, -00, 0);
		glRotatef(c, 0, 0, 1);
		glRotatef(b, 0, 1, 0);
		glRotatef(a, 1, 0, 0);
		glTranslatef(+20, +00, 0);
		glRotatef(90, 0, 1, 0);
		drawAxis(29);
	glPopMatrix();
*/
/*
	drawAxis(5);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-30, 0, 0);
	glRotatef(a, 0, 1, 0);
	glTranslatef(30, 0, 0);
*/

	glTranslatef(0, 0, 0);
	
	glRotatef(a, 0, 1, 0);

	//glPushMatrix();
	drawAxis(20);
	drawGround(200, 200, 4);
	//glPopMatrix();
#endif

	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, w/h, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Idle()
{
	
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	static bool stop = false;

	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		stop = stop ? false : true;
	}

	if(stop)
	{
		glutIdleFunc(Idle);
	}
	else
	{
		glutIdleFunc(NULL);
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1280, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("puppy game engine");
	
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutPostRedisplay();
	//glutPostDisplay();
	glutIdleFunc(Idle);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
