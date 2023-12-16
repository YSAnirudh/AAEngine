#pragma once

// BIT WISE Right Shift
#define BIT(x) 1 << x

#ifdef AA_PLATFORM_WINDOWS 

// --- CONSOLE COLOR MACRO ----------------------------------------
#define SET_PLATFORM_LOG_COLOR(Color)	{					\
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);	\
		int ConsoleColor = 7;									\
		if (#Color == "FColor::Blue") ConsoleColor = 1;			\
		else if (#Color == "FColor::Green") ConsoleColor = 2;		\
		else if (#Color == "FColor::Cyan") ConsoleColor = 3;		\
		else if (#Color == "FColor::Red") ConsoleColor = 4;		\
		else if (#Color == "FColor::Magenta") ConsoleColor = 5;	\
		else if (#Color == "FColor::Yellow") ConsoleColor = 6;		\
		else if (#Color == "FColor::White") ConsoleColor = 7;		\
		SetConsoleTextAttribute(ConsoleHandle, ConsoleColor); \
	}
// ----------------------------------------------------------------
#else
	#error AA Engine only supports Windows!
#endif
