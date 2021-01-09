#include <stdio.h>
#include <stdlib.h>

typedef struct _Data {
    double num1;
    double num2;
    double res;
    int sel;
}Data;


void result(Data* dat) {
    switch (dat->sel) {
    case 1:
        dat->res = dat->num1 + dat->num2;
        break;
    case 2:
        dat->res = dat->num1 - dat->num2;
        break;
    case 3:
        dat->res = dat->num1 * dat->num2;
        break;
    case 4:
        dat->res = dat->num1 / dat->num2;
        break;
    default:
        printf("올바르지 않은 선택 \n");
        break;
    }
}


int main(void) {
    Data dat;

    printf("첫번째 숫자 : ");
    scanf_s("%lf", &dat.num1);
    printf("두번째 숫자 : ");
    scanf_s("%lf", &dat.num2);

    system("cls");
    printf("입력된 수 : (%g, %g) \n", dat.num1, dat.num2);
    printf("더하기(1), 빼기(2), 곱하기(3), 나누기(4) \n");
    printf("연산 선택 : ");
    scanf_s("%d", &dat.sel);

    result(&dat);
    printf("결과 : %g \n", dat.res);
    return 0;
}