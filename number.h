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
char* zero_justify(char *value);
void deleteSysNumber(struct SysNumber number);
void deleteSysNumbers(struct SysNumber *number, int len);
void setDataType(struct SysNumber *number, int type);

struct SysNumber createBinaryNumber();
struct SysNumber _createBinaryNumber(long decVal);
struct SysNumber createOctaNumber();
struct SysNumber _createOctaNumber(long decVal);
struct SysNumber createDecNumber();
struct SysNumber _createDecNumber(long decVal);
struct SysNumber createHexNumber();
struct SysNumber _createHexNumber(long decVal);
struct SysNumber createSysNumFactory(long decVal, int radix);

struct SysNumber toDecimal(struct SysNumber number);
long getDecValue(struct SysNumber number);
struct SysNumber* setValue(struct SysNumber *number, char *value);
int countDigits(long value);
char* ltoa(long value, char *result, int radix);

long convertBinaryToDecimal(char *binary);
char* convertDecimalToBinary(long decimal);
long convertDecimalToOctal(long decimalNumber);
long convertOctalToDecimal(long octalNumber);
long convertHextoDec(char *hex);
char* convertDectoHex(long decimal);
struct SysNumber convertSysNumber(struct SysNumber number, int radix);

void nhapDay(struct SysNumber *arrNumber, int len, struct SysNumber (*creater)());
void xuatDay(struct SysNumber *arrNumber, int len);
struct SysNumber plus(struct SysNumber numberA, struct SysNumber numberB, int radixResult);
int arrPlus(struct SysNumber *arrA, int lenA, struct SysNumber *arrB, int lenB, struct SysNumber *arrC, int radixResult);
struct SysNumber sub(struct SysNumber numberA, struct SysNumber numberB, int radixResult);
int arrSub(struct SysNumber *arrA, int lenA, struct SysNumber *arrB, int lenB, struct SysNumber *arrC, int radixResult);
struct SysNumber multi(struct SysNumber numberA, struct SysNumber numberB, int radixResult);
int arrMulti(struct SysNumber *arrA, int lenA, struct SysNumber *arrB, int lenB, struct SysNumber *arrC, int radixResult);
struct SysNumber divi(struct SysNumber numberA, struct SysNumber numberB, int radixResult);
int arrDivi(struct SysNumber *arrA, int lenA, struct SysNumber *arrB, int lenB, struct SysNumber *arrC, int radixResult);
long sum(struct SysNumber *number, int len);
long average(struct SysNumber *number, int len);
bool checkPerfectSysNumber(struct SysNumber number);
bool checkPerfectNumber(long number);
bool isPrime(long number);

int getAll(struct SysNumber *binNumber, struct SysNumber *octNumber, struct SysNumber *decNumber, struct SysNumber *hexNumber);
void putAll(struct SysNumber *number[], int lenOuter, int lenIner);
void phepToan(struct SysNumber *number[], int lenOuter, int lenIner);
void chuyenDoiHeSo(struct SysNumber *number[], int lenOuter, int lenIner);
void trungBinhCong_hoanHao(struct SysNumber *number[], int lenOuter, int lenIner);

int menu1();
int menuPhepToan();
void menuChonHeso(int *a, int *b, int *c);
void menuChuyenHeDem(int *position, int *radix);
void menuTrungBinhCong(int *position, int *radix);

