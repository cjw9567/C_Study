#include <stdio.h>
#include <stdlib.h>

typedef struct _Data {
    double num1; //�Ǽ������� 1
    double num2; //�Ǽ������� 2
    double res;  // �������� ����
    int sel; //������
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
        printf("�ùٸ��� ���� �����Դϴ�. \n������� ��� �� �� �����ϴ�. \n");
        break;
    }

}

void testFunc2(Data* dat)
{
    result(dat);
    printf("��� : %g \n", dat->res);
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
        printf("�ùٸ��� ���� �����Դϴ�. \n������� ��� �� �� �����ϴ�. \n");
        break;
    }
}




int main(void) {
    Data dat;
    Data* pDat;

    printf("ù��° ���� : ");
    scanf_s("%lf", &dat.num1);
    printf("�ι�° ���� : ");
    scanf_s("%lf", &dat.num2);

    system("cls");
    printf("�Էµ� �� : [%g], [%g] \n", dat.num1, dat.num2);
    printf("���ϱ�(1), ����(2), ���ϱ�(3), ������(4) \n");
    printf("���� ���� : ");
    scanf_s("%d", &dat.sel);

    pDat = &dat;


    testFunc(pDat);

}