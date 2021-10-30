#pragma once

#include <Windows.h>
#include <stdio.h>

//Timer Typ2 & Str1 & Def3
typedef long double LONG_DOUBLE;

typedef struct htimer
{
	LARGE_INTEGER freq;
	LARGE_INTEGER begin_time;
	LARGE_INTEGER end_time;
}HTIMER;

#define STARTTIME(HTIMER_STRUCT)	(QueryPerformanceFrequency(&HTIMER_STRUCT.freq) && QueryPerformanceCounter(&HTIMER_STRUCT.begin_time))
#define ENDINTIME(HTIMER_STRUCT)	(QueryPerformanceCounter(&HTIMER_STRUCT.end_time))
#define RESULTS_S(HTIMER_STRUCT)	((LONG_DOUBLE)((LONG_DOUBLE)(HTIMER_STRUCT.end_time.QuadPart - HTIMER_STRUCT.begin_time.QuadPart)/ (LONG_DOUBLE)HTIMER_STRUCT.freq.QuadPart))


//Console Var1 & Def1 & Fun1
static HANDLE ConsoleHandle;

#define move_g(x, y) SetConsoleCursorPosition(ConsoleHandle, COORD{ x,y })

void init_move(void)
{
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}


//BPM Typ1 & Var2 & Fun3
typedef long long LONG_LONG;

LONG_LONG beats;
HTIMER timer;

LONG_DOUBLE CalculateBPM(void)
{
	if (beats > 1)
	{
		ENDINTIME(timer);
		return (LONG_DOUBLE)(beats - 1) / (RESULTS_S(timer) / (LONG_DOUBLE)60.00);
	}
	else
		return (LONG_DOUBLE)beats;
}

void ResetBPM(void)
{
	beats = 0;
	memset(&timer, 0, sizeof(HTIMER));

	system("cls");
	puts("---------------------------BPM counter---------------------------");
	puts("This software through you press the space bar to measure speed,");
	puts("such as while listening to drums, press the space bar.\n");
	puts("Press the space bar to measure the speed");
	puts("Press \"X\" to clear it");
	puts("Press \"Q\" to quit\n\n");
	printf("BPM:0.000000\nCount:0\n");
}

void UpdateBPM(void)
{
	if (beats++ == 0)
		STARTTIME(timer);

	move_g(0, 9);
	printf("BPM:%.6lf\t\t\t\t\t\t\nCount:%lld\n", CalculateBPM(), beats);
}