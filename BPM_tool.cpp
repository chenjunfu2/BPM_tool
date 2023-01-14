#include <Windows.h>
#include <conio.h>
#include <stdio.h>

#define move_g(x, y) SetConsoleCursorPosition(g_hConsoleHandle, COORD{ x,y })
HANDLE g_hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void ClearScreenAndPrintBaseText(void)
{
	system("cls");
	puts("---------------------乐谱测速器(BPM counter)---------------------");
	puts("这个软件通过你按空格键来测量速度，比如一边听鼓声，一边按空格键。");
	puts("(This software through you press the space bar to measure speed,");
	puts("such as while listening to drums, press the space bar.)\n");

	puts("按\"空格\"键测量速度(Press the \"space\" bar to measure the speed)");
	puts("按\"X\"重置测量结果(Press \"X\" to clear it)");
	puts("按\"Q\"退出程序(Press \"Q\" to quit)\n");

	puts("等待中(Wating):\n乐谱速度(BPM):0.000000\n按键次数(Count):0");
}

int main(void)
{
	ULONGLONG ullBeginTime, ullNowTime;
	ULONGLONG ullBeats = 0;

	ClearScreenAndPrintBaseText();

	while (true)
	{
		//初始化状态，直到按下空格
		switch (_getch())
		{
		case ' ':
			ullBeginTime = GetTickCount64();
			++ullBeats;

			move_g(0, 9);
			puts("测试中(Testing):\n乐谱速度(BPM):1.000000\n按键次数(Count):1");
			break;
		case 'Q':
		case 'q':
			system("pause");
			return 0;
			break;
		default:
			continue;
			break;
		}

		//计数状态，直到按下x返回初始化状态
		while (true)
		{
			switch (_getch())
			{
			case ' ':
				ullNowTime = GetTickCount64();
				++ullBeats;

				move_g(0, 9);
				printf("测试中(Testing):\n乐谱速度(BPM):%.6lf\n按键次数(Count):%lld\n",
					(long double)(ullBeats - 1) / (long double)(ullNowTime - ullBeginTime) * (long double)60000.00, ullBeats);
				break;
			case 'X':
			case 'x':
				ullBeats = 0;
				ClearScreenAndPrintBaseText();
				goto Reset;
				break;
			case 'Q':
			case 'q':
				system("pause");
				return 0;
				break;
			default:
				continue;
				break;
			}
		}

	Reset:
		continue;
	}

	return 0;
}