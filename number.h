#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

#define NOT_SET_TYPE 0
#define BINARY 2
#define OCTA 8
#define DECIMAL 10
#define HEX 16

#define MAX_DEGITS 100
#define MAX_LEN 100
#define ESC 27

typedef struct SysNumber
{
	// mang chua gia tri
	char *digits;
	// kieu du lieu: BINARY, OCTA, DECIMAL, HEXA
	int dataType;
};

bool getSysNumber(struct SysNumber *number);
void putSysNumber(struct SysNumber number);
bool isBinary(char *number);
bool isOcta(char *number);
bool isDec(char *number);
bool isHex(char *number);
void deleteSysNumber(struct SysNumber number);
void deleteSysNumbers(struct SysNumber *number, int len);
void setDataType(struct SysNumber *number, int type);
struct SysNumber createBinaryNumber();
struct SysNumber createOctaNumber();
struct SysNumber createDecNumber();
struct SysNumber createHexNumber();
struct SysNumber toDecimal(struct SysNumber number);
long getDecValue(struct SysNumber number);
int countDigits(long value);
char* ltoa(long value, char *result, int radix);

long convertBinaryToDecimal(char *binary);
char* convertDecimalToBinary(long decimal);
long convertDecimalToOctal(long decimalNumber);
long convertOctalToDecimal(long octalNumber);
long convertHextoDec(char *hex);
char* convertDectoHex(long decimal);
//long convertBinarytoOctal(long long binary);
//long long convertOctalToBinary(long octalNumber);

void nhapDay(struct SysNumber *arrNumber, int len, struct SysNumber (*creater)());
void xuatDay(struct SysNumber *arrNumber, int len);
int getAll(struct SysNumber *binNumber, struct SysNumber *octNumber, struct SysNumber *decNumber, struct SysNumber *hexNumber);
void putAll(struct SysNumber *number[], int lenOuter, int lenIner);
int menu1();
int menuPhepToan();
void phepToan(struct SysNumber *number[], int lenOuter, int lenIner);
