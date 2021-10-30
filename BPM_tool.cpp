#include <conio.h>
#include "BPM_tool.hpp"

int main(void)
{
	init_move();
	ResetBPM();
sStart:
	switch (_getch())
	{
	case ' ':
		UpdateBPM();
		break;
	case 'X':
	case 'x':
		ResetBPM();
		break;
	case 'Q':
	case 'q':
		return 0;
		break;
	default:
		goto sStart;
		break;
	}
	goto sStart;
}