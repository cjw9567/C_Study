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
        dat->res = 123;
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
    printf("입력된 수 : [%g], [%g] \n", dat.num1, dat.num2);
    printf("더하기(1), 빼기(2), 곱하기(3), 나누기(4) \n");
    printf("연산 선택 : ");
    scanf_s("%d", &dat.sel);


    if (dat.sel == 1) {
        result(&dat);
        printf("결과 : %g \n", dat.res); // 참일 경우에 실행될 문장 
    }
    else if (dat.sel == 2) {
        result(&dat);
        printf("결과 : %g \n", dat.res); // 참일 경우에 실행될 문장 
    }
    else if (dat.sel == 3) {
        result(&dat);
        printf("결과 : %g \n", dat.res); // 참일 경우에 실행될 문장 
    }
    else if (dat.sel == 4) {
        result(&dat);
        printf("결과 : %g \n", dat.res); // 참일 경우에 실행될 문장 
    }
    else {
        printf("올바르지 않은 선택입니다. \n결과값을 출력 할 수 없습니다. \n"); // 위의 조건식에 아무것도 해당하지 않을때 실행될 문장 
    }

}