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

#if 0
typedef float Float4[4];

// STRASSEN But Useless
Float4 Add01, Add02, Add03, Add04, Add05, Add06, Add07, Add08, Add09, Add10, Add11, Add12, Add13, Add14;
// Add01 A11 + A22
Add01[0] = M1[0][0] + M1[2][2];
Add01[1] = M1[0][1] + M1[2][3];
Add01[2] = M1[1][0] + M1[3][2];
Add01[3] = M1[1][1] + M1[3][3];
// Add02 B11 + B22
Add02[0] = M2[0][0] + M2[2][2];
Add02[1] = M2[0][1] + M2[2][3];
Add02[2] = M2[1][0] + M2[3][2];
Add02[3] = M2[1][1] + M2[3][3];
// Add03 A21 + A22
Add03[0] = M1[0][2] + M1[2][2];
Add03[1] = M1[0][3] + M1[2][3];
Add03[2] = M1[1][2] + M1[3][2];
Add03[3] = M1[1][3] + M1[3][3];
// Add04 B11
Add04[0] = M2[0][0];
Add04[1] = M2[0][1];
Add04[2] = M2[1][0];
Add04[3] = M2[1][1];
// Add05 A11
Add05[0] = M1[0][0];
Add05[1] = M1[0][1];
Add05[2] = M1[1][0];
Add05[3] = M1[1][1];
// Add06 B12 - B22
Add06[0] = M2[0][2] - M2[2][2];
Add06[1] = M2[0][3] - M2[2][3];
Add06[2] = M2[1][2] - M2[3][2];
Add06[3] = M2[1][3] - M2[3][3];
// Add07 A22
Add07[0] = M1[2][2];
Add07[1] = M1[2][3];
Add07[2] = M1[3][2];
Add07[3] = M1[3][3];
// Add08 B21 - B11
Add08[0] = M2[2][0] - M2[0][0];
Add08[1] = M2[2][1] - M2[0][1];
Add08[2] = M2[3][0] - M2[1][0];
Add08[3] = M2[3][1] - M2[1][1];
// Add09 A11 + A12
Add09[0] = M1[0][0] + M1[0][2];
Add09[1] = M1[0][1] + M1[0][3];
Add09[2] = M1[1][0] + M1[1][2];
Add09[3] = M1[1][1] + M1[1][3];
// Add10 B22
Add10[0] = M2[2][2];
Add10[1] = M2[2][3];
Add10[2] = M2[3][2];
Add10[3] = M2[3][3];
// Add11 A21 - A11
Add11[0] = M1[2][0] - M1[0][0];
Add11[1] = M1[2][1] - M1[0][1];
Add11[2] = M1[3][0] - M1[1][0];
Add11[3] = M1[3][1] - M1[1][1];
// Add12 B11 + B12
Add12[0] = M2[0][0] + M2[0][2];
Add12[1] = M2[0][1] + M2[0][3];
Add12[2] = M2[1][0] + M2[1][2];
Add12[3] = M2[1][1] + M2[1][3];
// Add13 A12 - A22
Add13[0] = M1[0][2] - M1[2][2];
Add13[1] = M1[0][3] - M1[2][3];
Add13[2] = M1[1][2] - M1[3][2];
Add13[3] = M1[1][3] - M1[3][3];
// Add14 B21 + B22
Add14[0] = M2[0][2] + M2[2][2];
Add14[1] = M2[0][3] + M2[2][3];
Add14[2] = M2[1][2] + M2[3][2];
Add14[3] = M2[1][3] + M2[3][3];

Float4 Mul1, Mul2, Mul3, Mul4, Mul5, Mul6, Mul7;
float FMul1, FMul2, FMul3, FMul4, FMul5, FMul6, FMul7;

// MULTIPLY 1
FMul1 = (Add01[0] + Add01[3]) * (Add02[0] + Add02[3]);
FMul2 = (Add01[2] + Add01[3]) * Add02[0];
FMul3 = Add01[0] * (Add02[1] - Add02[3]);
FMul4 = Add01[3] * (Add02[2] - Add02[0]);
FMul5 = (Add01[0] + Add01[1]) * Add02[3];
FMul6 = (Add01[2] - Add01[0]) * (Add02[0] + Add02[1]);
FMul7 = (Add01[1] - Add01[3]) * (Add02[2] + Add02[3]);

Mul1[0] = FMul1 + FMul4 - FMul5 + FMul7;
Mul1[1] = FMul3 + FMul5;
Mul1[2] = FMul2 + FMul4;
Mul1[3] = FMul1 - FMul2 + FMul3 + FMul6;

// MULTIPLY 2
FMul1 = (Add03[0] + Add03[3]) * (Add04[0] + Add04[3]);
FMul2 = (Add03[2] + Add03[3]) * Add04[0];
FMul3 = Add03[0] * (Add04[1] - Add04[3]);
FMul4 = Add03[3] * (Add04[2] - Add04[0]);
FMul5 = (Add03[0] + Add03[1]) * Add04[3];
FMul6 = (Add03[2] - Add03[0]) * (Add04[0] + Add04[1]);
FMul7 = (Add03[1] - Add03[3]) * (Add04[2] + Add04[3]);

Mul2[0] = FMul1 + FMul4 - FMul5 + FMul7;
Mul2[1] = FMul3 + FMul5;
Mul2[2] = FMul2 + FMul4;
Mul2[3] = FMul1 - FMul2 + FMul3 + FMul6;

// MULTIPLY 3
FMul1 = (Add05[0] + Add05[3]) * (Add06[0] + Add06[3]);
FMul2 = (Add05[2] + Add05[3]) * Add06[0];
FMul3 = Add05[0] * (Add06[1] - Add06[3]);
FMul4 = Add05[3] * (Add06[2] - Add06[0]);
FMul5 = (Add05[0] + Add05[1]) * Add06[3];
FMul6 = (Add05[2] - Add05[0]) * (Add06[0] + Add06[1]);
FMul7 = (Add05[1] - Add05[3]) * (Add06[2] + Add06[3]);

Mul3[0] = FMul1 + FMul4 - FMul5 + FMul7;
Mul3[1] = FMul3 + FMul5;
Mul3[2] = FMul2 + FMul4;
Mul3[3] = FMul1 - FMul2 + FMul3 + FMul6;

// MULTIPLY 4
FMul1 = (Add07[0] + Add07[3]) * (Add08[0] + Add08[3]);
FMul2 = (Add07[2] + Add07[3]) * Add08[0];
FMul3 = Add07[0] * (Add08[1] - Add08[3]);
FMul4 = Add07[3] * (Add08[2] - Add08[0]);
FMul5 = (Add07[0] + Add07[1]) * Add08[3];
FMul6 = (Add07[2] - Add07[0]) * (Add08[0] + Add08[1]);
FMul7 = (Add07[1] - Add07[3]) * (Add08[2] + Add08[3]);

Mul4[0] = FMul1 + FMul4 - FMul5 + FMul7;
Mul4[1] = FMul3 + FMul5;
Mul4[2] = FMul2 + FMul4;
Mul4[3] = FMul1 - FMul2 + FMul3 + FMul6;

// MULTIPLY 5
FMul1 = (Add09[0] + Add09[3]) * (Add10[0] + Add10[3]);
FMul2 = (Add09[2] + Add09[3]) * Add10[0];
FMul3 = Add09[0] * (Add10[1] - Add10[3]);
FMul4 = Add09[3] * (Add10[2] - Add10[0]);
FMul5 = (Add09[0] + Add09[1]) * Add10[3];
FMul6 = (Add09[2] - Add09[0]) * (Add10[0] + Add10[1]);
FMul7 = (Add09[1] - Add09[3]) * (Add10[2] + Add10[3]);

Mul5[0] = FMul1 + FMul4 - FMul5 + FMul7;
Mul5[1] = FMul3 + FMul5;
Mul5[2] = FMul2 + FMul4;
Mul5[3] = FMul1 - FMul2 + FMul3 + FMul6;

// MULTIPLY 6
FMul1 = (Add11[0] + Add11[3]) * (Add12[0] + Add12[3]);
FMul2 = (Add11[2] + Add11[3]) * Add12[0];
FMul3 = Add11[0] * (Add12[1] - Add12[3]);
FMul4 = Add11[3] * (Add12[2] - Add12[0]);
FMul5 = (Add11[0] + Add11[1]) * Add12[3];
FMul6 = (Add11[2] - Add11[0]) * (Add12[0] + Add12[1]);
FMul7 = (Add11[1] - Add11[3]) * (Add12[2] + Add12[3]);

Mul6[0] = FMul1 + FMul4 - FMul5 + FMul7;
Mul6[1] = FMul3 + FMul5;
Mul6[2] = FMul2 + FMul4;
Mul6[3] = FMul1 - FMul2 + FMul3 + FMul6;

// MULTIPLY 7
FMul1 = (Add13[0] + Add13[3]) * (Add14[0] + Add14[3]);
FMul2 = (Add13[2] + Add13[3]) * Add14[0];
FMul3 = Add13[0] * (Add14[1] - Add14[3]);
FMul4 = Add13[3] * (Add14[2] - Add14[0]);
FMul5 = (Add13[0] + Add13[1]) * Add14[3];
FMul6 = (Add13[2] - Add13[0]) * (Add14[0] + Add14[1]);
FMul7 = (Add13[1] - Add13[3]) * (Add14[2] + Add14[3]);

Mul7[0] = FMul1 + FMul4 - FMul5 + FMul7;
Mul7[1] = FMul3 + FMul5;
Mul7[2] = FMul2 + FMul4;
Mul7[3] = FMul1 - FMul2 + FMul3 + FMul6;

/*MatrixMultiply2x2(&Mul1, &Add01, &Add02);
MatrixMultiply2x2(&Mul2, &Add03, &Add04);
MatrixMultiply2x2(&Mul3, &Add05, &Add06);
MatrixMultiply2x2(&Mul4, &Add07, &Add08);
MatrixMultiply2x2(&Mul5, &Add09, &Add10);
MatrixMultiply2x2(&Mul6, &Add11, &Add12);
MatrixMultiply2x2(&Mul7, &Add13, &Add14);*/

ResultMat[0][0] = Mul1[0] + Mul4[0] - Mul5[0] + Mul7[0];
ResultMat[0][1] = Mul1[1] + Mul4[1] - Mul5[1] + Mul7[1];
ResultMat[1][0] = Mul1[2] + Mul4[2] - Mul5[2] + Mul7[2];
ResultMat[1][1] = Mul1[3] + Mul4[3] - Mul5[3] + Mul7[3];

ResultMat[0][2] = Mul3[0] + Mul5[0];
ResultMat[0][3] = Mul3[1] + Mul5[1];
ResultMat[1][2] = Mul3[2] + Mul5[2];
ResultMat[1][3] = Mul3[3] + Mul5[3];

ResultMat[2][0] = Mul2[0] + Mul4[0];
ResultMat[2][1] = Mul2[1] + Mul4[1];
ResultMat[3][0] = Mul2[2] + Mul4[2];
ResultMat[3][1] = Mul2[3] + Mul4[3];

ResultMat[2][2] = Mul1[0] - Mul2[0] + Mul3[0] + Mul6[0];
ResultMat[2][3] = Mul1[1] - Mul2[1] + Mul3[1] + Mul6[1];
ResultMat[3][2] = Mul1[2] - Mul2[2] + Mul3[2] + Mul6[2];
ResultMat[3][3] = Mul1[3] - Mul2[3] + Mul3[3] + Mul6[3];
#endif
