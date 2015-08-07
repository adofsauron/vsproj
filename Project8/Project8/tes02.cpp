#if 0
#include "Common.h"

#include <stdio.h>

//Բ���ʺ�
#define GL_PI 3.1415f
//��ȡ��Ļ�Ŀ��
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//���ó���Ĵ��ڴ�С
GLint windowWidth = 400;
GLint windowHeight = 300;
//��x����ת�Ƕ�
GLfloat xRotAngle = 0.0f;
//��y����ת�Ƕ�
GLfloat yRotAngle = 0.0f;
//��֧�ֵĵ��С��Χ
GLfloat sizes[2];
//��֧�ֵĵ��С����
GLfloat step;

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//glColor3f(1.0f, 0.0f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(.25f, .25f, .0f);
	glColor3f(.75f, .25f, .0f);
	glColor3f(.75f, .75f, .0f);
	glColor3f(.25f, .75f, .0f);
	glEnd();


	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

void myRender()
{
//	glClear(GL_COLOR_BUFFER_BIT);
#if 1
	//��������ɫ����Ϊ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//��ģ�建����ֵȫ������Ϊ1
	glClearStencil(1);
	//ʹ��ģ�建����
	glEnable(GL_STENCIL_TEST);
	//��������������Ϊ��ǰ������ɫ����ɫ�������Ȼ�������ģ�建����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//����ǰMatrix״̬��ջ
	glPushMatrix();
	//����ϵ��x����תxRotAngle
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	//����ϵ��y����תyRotAngle
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	//����ƽ������
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
#endif 

#if 1
	//��ɫ��������ϵ
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(-9.0f, 0.0f, 0.0f);
	glVertex3f(9.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -9.0f, 0.0f);
	glVertex3f(0.0f, 9.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -9.0f);
	glVertex3f(0.0f, 0.0f, 9.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(9.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 9.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();
#endif 
	//���û滭��ɫΪ��ɫ
	glColor3f(0.0f, 1.0f, 0.0f);

	// ����ͼ��
	glutWireSphere(8.0f, 20, 20);


	//�ָ�ѹ��ջ��Matrix
	glPopMatrix();
	//����������������ָ��
	glutSwapBuffers();


	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();


}

void myReshape(int w, int h)
{
	static int num = 0;

	++num;

	printf("<myReshape> num=[%5d] w=[%5d] h=[%5d]\n",num, w, h);
}

void myKeybord(unsigned char key, int x, int y)
{
	static int num = 0;

	++num;

	printf("<myKeybord> num=[%5d] key=[%5d] x=[%5d] y=[%5d]\n", num, key, x, y);
}

void myMOtion(int x, int y)
{
	static int num = 0;

	++num;

	printf("<myMOtion> num=[%5d] x=[%5d] y=[%5d]\n", num, x, y);
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,0, 1.0, 0.0, 1.0, -1.0);
}

//����Redering State 
void setupRederingState(void){
	//����������ɫΪ��ɫ
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//���û滭��ɫΪ��ɫ
	glColor3f(1.0f, 1.0f, 0.0f);
	//ʹ����Ȳ���
	glEnable(GL_DEPTH_TEST);
	//��ȡ��֧�ֵĵ��С��Χ
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	//��ȡ��֧�ֵĵ��С����
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	printf("point size range:%f-%f\n", sizes[0], sizes[1]);
	printf("point step:%f\n", step);
}

int main(int argc, char*argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
	glutCreateWindow("OPENGL");

	init();

//	glutDisplayFunc(myDisplay);
	
	
//	glutAttachMenu(GLUT_RIGHT_BUTTON);//���˵��񶨵�����Ҽ���
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeybord);
	glutMotionFunc(myMOtion);

	glutDisplayFunc(myRender);

//	glutWireCube(100.0);

	setupRederingState();
	glutMainLoop();
	return 0;
}

#endif 