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
        dat->res = 123;
        break;
    }

}



int main(void) {
    Data dat;

    printf("ù��° ���� : ");
    scanf_s("%lf", &dat.num1);
    printf("�ι�° ���� : ");
    scanf_s("%lf", &dat.num2);

    system("cls");
    printf("�Էµ� �� : [%g], [%g] \n", dat.num1, dat.num2);
    printf("���ϱ�(1), ����(2), ���ϱ�(3), ������(4) \n");
    printf("���� ���� : ");
    scanf_s("%d", &dat.sel);


    if (dat.sel == 1) {
        result(&dat);
        printf("��� : %g \n", dat.res); // ���� ��쿡 ����� ���� 
    }
    else if (dat.sel == 2) {
        result(&dat);
        printf("��� : %g \n", dat.res); // ���� ��쿡 ����� ���� 
    }
    else if (dat.sel == 3) {
        result(&dat);
        printf("��� : %g \n", dat.res); // ���� ��쿡 ����� ���� 
    }
    else if (dat.sel == 4) {
        result(&dat);
        printf("��� : %g \n", dat.res); // ���� ��쿡 ����� ���� 
    }
    else {
        printf("�ùٸ��� ���� �����Դϴ�. \n������� ��� �� �� �����ϴ�. \n"); // ���� ���ǽĿ� �ƹ��͵� �ش����� ������ ����� ���� 
    }

}