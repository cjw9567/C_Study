#include <stdio.h>
#include <stdlib.h>

typedef struct _Data {
    double num1; //실수형변수 1
    double num2; //실수형변수 2
    double res;  // 연산결과를 저장
    int sel; //연산자
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
        printf("올바르지 않은 선택입니다. \n결과값을 출력 할 수 없습니다. \n");
        break;
    }

}

void testFunc2(Data* dat)
{
    result(dat);
    printf("결과 : %g \n", dat->res);
}


void testFunc(Data* dat)
{

    switch (dat->sel) {
    case 1:
        testFunc2(dat);
       break;
    case 2:
        testFunc2(dat);
        break;
    case 3:
        testFunc2(dat);
        break;
    case 4:
        testFunc2(dat);
        break;
    default:
        printf("올바르지 않은 선택입니다. \n결과값을 출력 할 수 없습니다. \n");
        break;
    }
}




int main(void) {
    Data dat;
    Data* pDat;

    printf("첫번째 숫자 : ");
    scanf_s("%lf", &dat.num1);
    printf("두번째 숫자 : ");
    scanf_s("%lf", &dat.num2);

    system("cls");
    printf("입력된 수 : [%g], [%g] \n", dat.num1, dat.num2);
    printf("더하기(1), 빼기(2), 곱하기(3), 나누기(4) \n");
    printf("연산 선택 : ");
    scanf_s("%d", &dat.sel);

    pDat = &dat;


    testFunc(pDat);

}