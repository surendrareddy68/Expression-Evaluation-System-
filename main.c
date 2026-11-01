#include <stdio.h>
#include <ctype.h>

#define MAX 100

int numbers[MAX], nTop = -1;
char operators[MAX];
int oTop = -1;

void pushNum(int n)
{
    numbers[++nTop] = n;
}

int popNum()
{
    return numbers[nTop--];
}

void pushOp(char op)
{
    operators[++oTop] = op;
}

char popOp()
{
    return operators[oTop--];
}

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void calculate()
{
    int b = popNum();
    int a = popNum();
    char op = popOp();

    if (op == '+')
        pushNum(a + b);
    else if (op == '-')
        pushNum(a - b);
    else if (op == '*')
        pushNum(a * b);
    else if (op == '/') {
        if (b == 0) {
            printf("Error: Division by zero!\n");
            return;
        }
        pushNum(a / b);
    }
}

int main()
{
    char exp[MAX];
    int i = 0;

    printf("EXPRESSION EVALUATION SYSTEM\n");
    printf("Enter expression: ");
    fgets(exp, MAX, stdin);

    while (exp[i] != '\0' && exp[i] != '\n') {

        if (isspace((unsigned char)exp[i])) {
            i++;
        }
        else if (isdigit((unsigned char)exp[i])) {
            int n = 0;

            while (isdigit((unsigned char)exp[i])) {
                n = n * 10 + exp[i] - '0';
                i++;
            }

            pushNum(n);
        }
        else if (exp[i] == '(') {
            pushOp(exp[i]);
            i++;
        }
        else if (exp[i] == ')') {
            while (oTop >= 0 && operators[oTop] != '(')
                calculate();

            if (oTop >= 0)
                popOp();

            i++;
        }
        else if (exp[i] == '+' || exp[i] == '-' ||
                 exp[i] == '*' || exp[i] == '/') {

            while (oTop >= 0 && operators[oTop] != '(' &&
                   priority(operators[oTop]) >= priority(exp[i]))
                calculate();

            pushOp(exp[i]);
            i++;
        }
        else {
            printf("Invalid character!\n");
            return 1;
        }
    }

    while (oTop >= 0)
        calculate();

    if (nTop == 0)
        printf("Result = %d\n", popNum());
    else
        printf("Invalid expression!\n");

    return 0;
}
