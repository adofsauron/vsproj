#if 0
#include "Common.h"

#include <stdio.h>

//圆周率宏
#define GL_PI 3.1415f
//获取屏幕的宽度
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//设置程序的窗口大小
GLint windowWidth = 400;
GLint windowHeight = 300;
//绕x轴旋转角度
GLfloat xRotAngle = 0.0f;
//绕y轴旋转角度
GLfloat yRotAngle = 0.0f;
//受支持的点大小范围
GLfloat sizes[2];
//受支持的点大小增量
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
	//将窗口颜色清理为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//将模板缓冲区值全部清理为1
	glClearStencil(1);
	//使能模板缓冲区
	glEnable(GL_STENCIL_TEST);
	//把整个窗口清理为当前清理颜色：黑色。清除深度缓冲区、模板缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//将当前Matrix状态入栈
	glPushMatrix();
	//坐标系绕x轴旋转xRotAngle
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	//坐标系绕y轴旋转yRotAngle
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	//进行平滑处理　
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
#endif 

#if 1
	//白色绘制坐标系
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
	//设置绘画颜色为金色
	glColor3f(0.0f, 1.0f, 0.0f);

	// 绘制图形
	glutWireSphere(8.0f, 20, 20);


	//恢复压入栈的Matrix
	glPopMatrix();
	//交换两个缓冲区的指针
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

//设置Redering State 
void setupRederingState(void){
	//设置清理颜色为黑色
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//设置绘画颜色为绿色
	glColor3f(1.0f, 1.0f, 0.0f);
	//使能深度测试
	glEnable(GL_DEPTH_TEST);
	//获取受支持的点大小范围
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	//获取受支持的点大小增量
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
	
	
//	glutAttachMenu(GLUT_RIGHT_BUTTON);//将菜单榜定到鼠标右键上
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