/*
 * lesson01_drills_answer.c —— 第 1 课练习参考答案
 *
 * 先自己做，卡住了再看。每道题后面写了"为什么"。
 */

#include <stdio.h>

static int g_pass = 0;
static int g_total = 0;

static void checki(const char *name, int got, int want)
{
    g_total++;
    if (got == want) {
        g_pass++;
        printf("  [%s] 通过 ✓  （你的结果 %d）\n", name, got);
    } else {
        printf("  [%s] 不对 ✗  （你的结果 %d，应为 %d）\n", name, got, want);
    }
}

static void checkd(const char *name, double got, double want)
{
    double diff = got - want;
    if (diff < 0) diff = -diff;
    g_total++;
    if (diff < 0.01) {
        g_pass++;
        printf("  [%s] 通过 ✓  （你的结果 %.2f）\n", name, got);
    } else {
        printf("  [%s] 不对 ✗  （你的结果 %.2f，应为 %.2f）\n", name, got, want);
    }
}

/* D3：从头扫到尾，谁大记谁 */
int max_of(const int arr[], int n)
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

int main(void)
{
    printf("===== 第 1 课练习（参考答案）=====\n\n");

    /* D1：7 和 3 都是 int，7/3 会被截成 2。
       让其中一个变成 double（写 7.0 或 (double)7），除法才会保留小数。 */
    printf("D1 整数除法\n");
    double d1;
    d1 = 7.0 / 3.0;
    checkd("D1", d1, 7.0 / 3.0);

    /* D2：累加从 0 开始，逐个加进 sum */
    printf("\nD2 数组求和\n");
    int nums[6] = {3, 1, 4, 1, 5, 9};
    int sum = 0;
    int i;
    for (i = 0; i < 6; i++) {
        sum += nums[i];
    }
    checki("D2", sum, 23);

    /* D3：调用函数，注意要把长度一起传进去 */
    printf("\nD3 求最大值\n");
    int maxv;
    maxv = max_of(nums, 6);
    checki("D3", maxv, 9);

    /* D4：能被 3 或 5 整除，用 || 连接两个条件 */
    printf("\nD4 3或5的倍数之和\n");
    int d4 = 0;
    for (i = 1; i <= 100; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            d4 += i;
        }
    }
    checki("D4", d4, 2418);

    /* D5：指针参数让函数能改外面的变量本身，而不是改副本。
       交换时用一个临时变量 tmp 保存其中一个值。 */
    printf("\nD5 指针交换\n");
    int x = 10;
    int y = 20;
    int *px = &x;
    int *py = &y;
    int tmp = *px;
    *px = *py;
    *py = tmp;
    checki("D5a", x, 20);
    checki("D5b", y, 10);

    /* D6：i 从 0 往后，j 从 n-1 往前，交换到 i >= j 停止。
       这样每对元素只交换一次，不会换回去。 */
    printf("\nD6 数组反转\n");
    int arr[5] = {1, 2, 3, 4, 5};
    int j;
    for (i = 0, j = 4; i < j; i++, j--) {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    checki("D6a", arr[0], 5);
    checki("D6b", arr[1], 4);
    checki("D6c", arr[2], 3);
    checki("D6d", arr[3], 2);
    checki("D6e", arr[4], 1);

    printf("\n===== 得分：%d / %d =====\n", g_pass, g_total);
    if (g_pass == g_total) {
        printf("全部通过，第 1 课可以过关了。\n");
    } else {
        printf("还有 %d 项没过，改完再跑一次。\n", g_total - g_pass);
    }
    return 0;
}
