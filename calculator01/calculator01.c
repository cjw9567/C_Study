#include<stdio.h>


double add(double num1, double num2) {
    return num1 + num2;
}

double min(double num1, double num2) {
    return num1 - num2;
}

double multi(double num1, double num2) {
    return num1 * num2;
}

double div(double num1, double num2) {
    return num1 / num2;
}

int main(void) {
    double num1, num2;

    printf("ù��° ���� : ");
    scanf_s("%lf", &num1);
    printf("�ι�° ���� : ");
    scanf_s("%lf", &num2);

    printf("%g + %g = %g \n", num1, num2, add(num1, num2));
    printf("%g - %g = %g \n", num1, num2, min(num1, num2));
    printf("%g �� %g = %g \n", num1, num2, multi(num1, num2));
    printf("%g �� %g = %g \n", num1, num2, div(num1, num2));
    return 0;
}