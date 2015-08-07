#include <stdio.h>

#include <windows.h>

void main()

{

	LARGE_INTEGER nFreq;

	LARGE_INTEGER nBeginTime;

	LARGE_INTEGER nEndTime;

	double time;



	QueryPerformanceFrequency(&nFreq);

	QueryPerformanceCounter(&nBeginTime);



	Sleep(1000);



	QueryPerformanceCounter(&nEndTime);

	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;



	printf("%f\n", time);

	Sleep(1000);

	system("Pause");

}
