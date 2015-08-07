#include "Common.h"

static GLfloat spin = 0.0f;

void Init(void)
{
	glClearColor(.0f, .0f, .0f, .0f);
	glShadeModel(GL_FLAT);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, .0f, .0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-25.0f, -25.0f, 25.0f, 25.0f);
	glPopMatrix();
	glutSwapBuffers();
}

void SpinDisplay(void)
{
	spin = spin + 2.0f;

	if (spin > 360.f)
		spin -= 360.f;

	glutPostRedisplay();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
	{
		if (state == GLUT_DOWN)
			glutIdleFunc(SpinDisplay);
		break;
	}
	case GLUT_MIDDLE_BUTTON:
	{
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	}
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
//	glutInitContextVersion(3, 0);
//	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutCreateWindow(argv[0]);

	Init();

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	
	glutMainLoop();

	return 0;
}