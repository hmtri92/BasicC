#include "number.h"

// get data from keyboard
bool getSysNumber(struct SysNumber *number)
{
  if (number->dataType == NOT_SET_TYPE) {
    printf("\nPlease set value type.\n");
    return false;
  }

  fflush(stdin);
  char *value = (char*) malloc(MAX_DEGITS + 1);
  gets(value);
  int length = strlen(value);
  if (MAX_DEGITS <= length) {
    printf("Out of memory.");
    return false;
  }

  // check data input
  bool status = false;
  switch (number->dataType)
  {
    case NOT_SET_TYPE:
      break;
    case BINARY:
      status = isBinary(value);
      break;
    case OCTA:
      status = isOcta(value);
      break;
    case DECIMAL:
      status = isDec(value);
      break;
    case HEX:
      status = isHex(value);
      break;
  };

  if (status == true)
  {
    number->digits = (char*) malloc(length + 1);
    if (number->digits == NULL)
    {
      printf("\nCan not allocate memory\n");
      return false;
    }
    strcpy(number->digits, value);
  } else {
    printf("\nNot math value type\n");
  }

  free(value);
  return status;
}

void putSysNumber(struct SysNumber number)
{
  printf("%s", number.digits);
}

bool isBinary(char *number)
{
  int length = strlen(number);
  for (int i = 0; i < length; i++)
  {
    char currentChar = number[i];
    if (currentChar != '0' && currentChar != '1')
    {
      return false;
    }
  }

  return true;
}

bool isOcta(char *number)
{
  int length = strlen(number);
  for (int i = 0; i < length; i++)
  {
    char currentChar = number[i];
    if (currentChar < '0' || currentChar > '8')
    {
      return false;
    }
  }

  return true;
}

bool isDec(char *number)
{
  int length = strlen(number);
  for (int i = 0; i < length; i++)
  {
    char currentChar = number[i];
    if (!isdigit(currentChar))
    {
      return false;
    }
  }

  return true;
}

bool isHex(char *number)
{
  int length = strlen(number);
  for (int i = 0; i < length; i++)
  {
    char currentChar = number[i];
    if (!isxdigit(currentChar)) {
      return false;
    }
  }

  return true;
}

void deleteSysNumber(struct SysNumber number)
{
  free(number.digits);
}

void deleteSysNumbers(struct SysNumber *numbers, int len)
{
    for (int i = 0; i < len; i++)
    {
        deleteSysNumber(numbers[i]);
    }
}

// BINARY 1, OCTA 2, DECIMAL 3, HEX 4
void setDataType(struct SysNumber *number, int type)
{
  number->dataType = type;
}

struct SysNumber createBinaryNumber()
{
  struct SysNumber sysNumber;
  sysNumber.dataType = BINARY;

  return sysNumber;
}

struct SysNumber _createBinaryNumber(long decVal)
{
    struct SysNumber number = createBinaryNumber();
    char *binary = convertDecimalToBinary(decVal);
    setValue(&number, binary);

    return number;
};

struct SysNumber createOctaNumber()
{
  struct SysNumber sysNumber;
  sysNumber.dataType = OCTA;

  return sysNumber;
}

struct SysNumber _createOctaNumber(long decVal)
{
    struct SysNumber number = createOctaNumber();
    char *octa = convertDecimalToOctal(decVal);
    setValue(&number, octa);

    return number;
};

struct SysNumber createDecNumber()
{
  struct SysNumber sysNumber;
  sysNumber.dataType = DECIMAL;

  return sysNumber;
}

struct SysNumber _createDecNumber(long decVal)
{
    struct SysNumber number = createDecNumber();
    char *octa = (char*) malloc(countDigits(decVal) + 1);
    ltoa(decVal, octa, DECIMAL);
    setValue(&number, octa);

    return number;
};

struct SysNumber createHexNumber()
{
  struct SysNumber sysNumber;
  sysNumber.dataType = HEX;

  return sysNumber;
}

struct SysNumber _createHexNumber(long decVal)
{
    struct SysNumber number = createHexNumber();
    char *octa = convertDectoHex(decVal);
    setValue(&number, octa);

    return number;
};

struct SysNumber toDecimal(struct SysNumber number)
{
    if (number.dataType == DECIMAL)
    {
        return number;
    }

    struct SysNumber result = number;
    long dec_val = 0;
    int size;

    if (number.dataType == BINARY) {
    dec_val = convertBinaryToDecimal(number.digits);
    } else if (number.dataType == OCTA) {
    dec_val = convertOctalToDecimal(atol(number.digits));
    } else if (number.dataType == HEX) {
    dec_val = convertHextoDec(number.digits);
    }

    size = countDigits(dec_val);
    result.digits = (char*) malloc(size + 1);
    ltoa(dec_val, result.digits, DECIMAL);
    result.dataType = DECIMAL;

    return result;
}

long getDecValue(struct SysNumber number)
{
  number = toDecimal(number);
  return atol(number.digits);
}

struct SysNumber* setValue(struct SysNumber *number, char *value)
{
    int length = strlen(value);
    number->digits = (char*) malloc(length + 1);
    if (number->digits == NULL)
    {
      printf("\nCan not allocate memory\n");
      return false;
    }
    strcpy(number->digits, value);

    return number;
}

int countDigits(long value)
{
  int count = 0;
  while (value != 0)
  {
    value /= 10;
    count++;
  }

  return count;
}

char* ltoa(long value, char *result, int radix)
{
  if (radix == OCTA)
  {
    sprintf(result, "%lo", value);
  }
  if (radix == DECIMAL)
  {
    sprintf(result, "%ld", value);
  }
  if (radix == HEX)
  {
    sprintf(result, "%lx", value);
  }

  return result;
}

//======================

long convertBinaryToDecimal(char *binary)
{
  long decimalNumber = 0, temp = 1;
  int exp = 0;

	for (int i = strlen(binary) - 1; i >= 0; i--)
	{
	  temp = pow(2, exp++);
	  if (binary[i] == '1') {
	    decimalNumber += temp;
	  }
	}

  return decimalNumber;
}

char* convertDecimalToBinary(long decimal)
{
    char *binary = (char*) malloc(MAX_DEGITS + 1);
    long remainder;
	  int index = 0;

    while (decimal != 0)
    {
      remainder = decimal % 2 + '0';
      binary[index] = remainder;
		  decimal /= 2;
		  index++;
    }
    binary[index] = '\0';
    strrev(binary);

    return binary;
}

long convertDecimalToOctal(long decimalNumber)
{
    long octalNumber = 0;
	int i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}

long convertOctalToDecimal(long octalNumber)
{
  long decimalNumber = 0;
  int i = 0;

  while(octalNumber != 0)
  {
      decimalNumber += (octalNumber%10) * pow(8,i);
      i++;
      octalNumber /= 10;
  }

  return decimalNumber;
}

long convertHextoDec(char *hex)
{
  long decimal = 0;
  int len = strlen(hex), val;
  for (int i = 0; hex[i] != '\0'; i++)
  {
    if(hex[i] >= '0' && hex[i] <= '9')
    {
        val = hex[i] - 48;
    }
    else if(hex[i] >= 'a' && hex[i] <= 'f')
    {
        val = hex[i] - 97 + 10;
    }
    else if(hex[i] >= 'A' && hex[i] <= 'F')
    {
        val = hex[i] - 65 + 10;
    }

    decimal += val * pow(16, len);
    len--;
  }

  return decimal;
}

char* convertDectoHex(long decimal)
{
  char HEXVALUE[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  char *hex = (char*)malloc(MAX_DEGITS + 1);
  int index = 0, rem;

  /* Decimal to hexadecimal conversion */
  while(decimal != 0)
  {
    rem = decimal % 16;
    hex[index] = HEXVALUE[rem];

    decimal /= 16;
    index++;
  }
  hex[index] = '\0';
  strrev(hex);
  return hex;
}

/*long convertBinarytoOctal(long long binary)
{
	long decimalNumber = convertBinaryToDecimal(binary);
	return convertDecimalToOctal(decimalNumber);
}

long long convertOctalToBinary(long octalNumber)
{
    long decimalNumber = convertOctalToDecimal(octalNumber);
    return convertDecimalToBinary(decimalNumber);
}*/

//============

void nhapDay(struct SysNumber *arrNumber, int len, struct SysNumber (*creater)())
{
  for (int index = 0; index < len; index++)
  {
    arrNumber[index] = creater();
    while (!getSysNumber(&arrNumber[index]))
    {
        printf("Nhap lai: ");
    }
  }
}

void xuatDay(struct SysNumber *arrNumber, int len)
{
    switch (arrNumber[0].dataType)
    {
    case BINARY:
        printf("\nDay nhi phan\n");
        break;
    case OCTA:
        printf("\nDay bat phan\n");
        break;
    case DECIMAL:
        printf("\nDay thap phan\n");
        break;
    case HEX:
        printf("\nDay thap luc phan\n");
        break;
    }
    for (int index = 0; index < len; index++)
    {
        putSysNumber(arrNumber[index]);
        if (index < (len-1)) {
            printf(", ");
        }
    }
}

// Nhap 4 day nhi phan, bat phan, thap phan, thap luc phan
// return: kich thuoc day
int getAll(struct SysNumber *binNumber, struct SysNumber *octNumber, struct SysNumber *decNumber, struct SysNumber *hexNumber)
{
  int len;
  do {
    printf("Nhap so luong phan tu < %d: ", MAX_LEN);
    scanf("%d", &len);
  } while(len > MAX_LEN);

  printf("Nhap day nhi phan(ket thuc moi ky tu bang phim Enter)\n");
  nhapDay(binNumber, len, createBinaryNumber);

  printf("Nhap day bat phan(ket thuc moi ky tu bang phim Enter)\n");
  nhapDay(octNumber, len, createOctaNumber);

  printf("Nhap day thap(ket thuc moi ky tu bang phim Enter)\n");
  nhapDay(decNumber, len, createDecNumber);

  printf("Nhap day thap luc phan(ket thuc moi ky tu bang phim Enter)\n");
  nhapDay(hexNumber, len, createHexNumber);

  return len;
}

void putAll(struct SysNumber *number[], int lenOuter, int lenIner)
{
    printf("\nXuat ta ca day so");
    for (int out = 0; out < lenOuter; out++)
    {
        xuatDay(number[out], lenIner);
    }
}

void phepToan(struct SysNumber *number[], int lenOuter, int lenIner)
{
    int pheptoan, a = 0, b = 0, c = 0;
    long resultMath;
    struct SysNumber resultNum;

    pheptoan = menuPhepToan();
    menuChonHeso(&a, &b, &c);
    printf("%d ", a);
    printf("%d ", b);
    printf("%d\n", c);

    // math
    switch (pheptoan)
    {
    case 1:
        // +
        resultMath = plus(number[a-1], lenIner, number[b-1], lenIner);
        break;
    case 2:
        // -
        resultMath = sub(number[a-1], lenIner, number[b-1], lenIner);
        break;
    case 3:
        // *
        resultMath = multi(number[a-1], lenIner, number[b-1], lenIner);
        break;
    case 4:
        // /
        resultMath = divi(number[a-1], lenIner, number[b-1], lenIner);
        break;
    };

    // convert to system number
    switch (c)
    {
    case 1:
        // binary
        resultNum = _createBinaryNumber(resultMath);
        break;
    case 2:
        // octa
        resultNum = _createOctaNumber(resultMath);
        break;
    case 3:
        //dec
        resultNum = _createDecNumber(resultMath);
        break;
    case 4:
        //dex
        resultNum = _createHexNumber(resultMath);
        break;

    }

    printf("\nKet qua phep toan = ");
    putSysNumber(resultNum);
}

long plus(struct SysNumber *numberA, int lenA, struct SysNumber *numberB, int lenB)
{
    long valA, valB;
    valA = sum(numberA, lenA);
    valB = sum(numberB, lenB);

    return valA + valB;
}

long sub(struct SysNumber *numberA, int lenA, struct SysNumber *numberB, int lenB)
{
    long valA, valB;
    valA = sum(numberA, lenA);
    valB = sum(numberB, lenB);

    return valA - valB;
}
long multi(struct SysNumber *numberA, int lenA, struct SysNumber *numberB, int lenB)
{
    long valA, valB;
    valA = sum(numberA, lenA);
    valB = sum(numberB, lenB);

    return valA * valB;
}

long divi(struct SysNumber *numberA, int lenA, struct SysNumber *numberB, int lenB)
{
    long valA, valB;
    valA = sum(numberA, lenA);
    valB = sum(numberB, lenB);
    if (valB == 0)
    {
        printf("\nKhong the thuc hien phep chia, tong gia tri trong day bang 0");
        return 0;
    }

    return valA / valB;
}

long sum(struct SysNumber *number, int len)
{
    long result = 0;
    for (int i = 0; i < len; i++)
    {
        result += getDecValue(number[i]);
    }

    return result;
}

//=================

int menu1()
{
    int choose;
    system("cls");
    printf("\n---------- Menu ----------\n");
    printf(" 1. Nhap tat ca\n");
    printf(" 2. Xuat tat ca\n");
    printf(" 3. Phep toan\n");
    printf(" 4. Chuyen doi he dem\n");
    printf(" 5. Tinh trung binh cong - kiem tra tinh hoan hao\n");
    printf(" 6. Thoat\n");

    do {
        scanf("%d", &choose);
    } while (choose <= 0 || choose > 6);

    return choose;
}

int menuPhepToan()
{
    int choose;
    system("cls");
    printf("\n--- Chon phep toan ---\n");
    printf(" 1. Cong (c = a + b)\n");
    printf(" 2. Tru (c = a - b)\n");
    printf(" 3. Nhan (c = a * b)\n");
    printf(" 4. Chia (c = a / b)\n");
    printf(" 5. Quay lai (<--)\n");

    do {
    scanf("%d", &choose);
    } while (choose < 1 || choose > 5);
    return choose;
}

void menuChonHeso(int *a, int *b, int *c)
{
    int aa, bb, cc;
    printf("\n 1. Nhi phan");
    printf("\n 2. Bat phan");
    printf("\n 3. Thap phan");
    printf("\n 4. Thap luc phan");
    printf("\n Chon he so cho a, b, c cach nhau khoang trang (c = a [+-*/] b): ");

    do {
        scanf("%d%d%d", &aa, &bb, &cc);
    } while ((aa<1 || aa>4) || (bb<1 || bb>4) || (cc<1 || cc>4));

    *a = aa;
    *b = bb;
    *c = cc;
}
