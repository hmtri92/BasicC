#include "number.h"

int main(void) {
    char state;
    int len, chose;
    struct SysNumber binNumber[MAX_LEN], octNumber[MAX_LEN], decNumber[MAX_LEN], hexNumber[MAX_LEN];
    struct SysNumber *arrOut[4];

    do
    {
        chose = menu1();
        if (chose == 6)
        {
            break;
        }

        switch (chose)
        {
        case 1:
            // nhap day
            len = getAll(binNumber, octNumber, decNumber, hexNumber);
            break;
        case 2:
            // xuat day
            arrOut[0] = binNumber;
            arrOut[1] = octNumber;
            arrOut[2] = decNumber;
            arrOut[3] = hexNumber;
            putAll(arrOut, 4, len);
            break;
        case 3:
            // thuc hien phep toan
            arrOut[0] = binNumber;
            arrOut[1] = octNumber;
            arrOut[2] = decNumber;
            arrOut[3] = hexNumber;
            phepToan(arrOut, 4, len);
            break;
        case 4:
            break;
        case 5:
            break;
        };

        printf("\nPress ESC to STOP.\nPress any key to continue.\n");
        fflush(stdin);
        state = getch();
    } while (state != ESC);

    deleteSysNumbers(binNumber, len);
    deleteSysNumbers(octNumber, len);
    deleteSysNumbers(decNumber, len);
    deleteSysNumbers(hexNumber, len);

    return 0;
}
