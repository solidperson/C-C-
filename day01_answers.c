/*
 * day01_answers.c —— Day 1 三道练习题的参考答案
 *
 * 先自己做，卡住了再看。每题后面写了"为什么"。
 */

#include <stdio.h>

/* ------------------------------------------------------------------
 * 第 1 题答案
 * 关键：让 c 先变成 double，否则 c*9/5 全是整数运算，
 *       37*9=333，333/5=66（不是 66.6），最后得到 98 而不是 98.6。
 * ------------------------------------------------------------------ */
static void ex1_temperature(void)
{
    int c = 37;
    double f = (double)c * 9 / 5 + 32;

    printf("[第1题] 摄氏 %d 度 = 华氏 %.1f 度\n", c, f);
}

/* ------------------------------------------------------------------
 * 第 2 题答案
 * average：求和后转 double 再除，避免整数除法截断
 * max_value：以第一个元素为擂主，后面谁大谁登台
 * ------------------------------------------------------------------ */
double average(const int arr[], int n)
{
    int i;
    int total = 0;

    for (i = 0; i < n; i++) {
        total += arr[i];
    }
    return (double)total / n;
}

int max_value(const int arr[], int n)
{
    int i;
    int best = arr[0];

    for (i = 1; i < n; i++) {
        if (arr[i] > best) {
            best = arr[i];
        }
    }
    return best;
}

static void ex2_scores(void)
{
    int scores[5] = {78, 92, 65, 88, 95};

    printf("[第2题] 平均分 = %.2f, 最高分 = %d\n",
           average(scores, 5), max_value(scores, 5));
}

/* ------------------------------------------------------------------
 * 第 3 题答案
 * swap 拿到的是 x、y 的地址，通过 *a / *b 改的是外面的变量本身。
 * 三个动作：先存一个，再覆盖，最后放回。
 * ------------------------------------------------------------------ */
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void ex3_swap(void)
{
    int x = 11;
    int y = 22;

    swap(&x, &y);

    printf("[第3题] 交换后：x = %d, y = %d\n", x, y);
}

int main(void)
{
    printf("===== Day 1 练习题（参考答案）=====\n\n");

    ex1_temperature();
    printf("\n");
    ex2_scores();
    printf("\n");
    ex3_swap();

    printf("\n===== 三道题结束 =====\n");
    return 0;
}
