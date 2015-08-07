#ifndef __COMMON_H__
#define __COMMON_H__

#define GLUT_DISABLE_ATEXIT_HACK // 必须使用此宏

#include <windows.h> 

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include <gl/glext.h>
#include <gl/wglext.h>



#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#endif // __COMMON_H__