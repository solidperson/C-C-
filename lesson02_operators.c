#include <stdio.h>

/*
 * 第1课：运算符、类型转换、分支结构
 * 重点两件事：
 *   1. 整数除法 / 取模的行为（新手最容易踩坑的地方）
 *   2. 位运算（后面学嵌入式操作寄存器全靠它）
 */

int main(void)
{
    /* ---------- 一、算术运算与整数除法的坑 ---------- */
    int a = 7, b = 2;
    printf("7 / 2   = %d      <- 整数除法，小数部分被直接丢掉\n", a / b);
    printf("7 %% 2   = %d      <- 取余，得到余数\n", a % b);
    printf("7.0/2   = %.1f    <- 有一个是小数，才是真除法\n", 7.0 / 2);

    /* ---------- 二、强制类型转换 ---------- */
    double d = 3.99;
    int i = (int)d;                  /* 截断取整，不是四舍五入 */
    printf("(int)3.99 = %d            <- 截断，不是四舍五入\n", i);

    double avg = (double)(10 + 20 + 31) / 3;
    printf("平均分 = %.2f              <- 先转 double 再除，否则会得到 20\n", avg);

    /* ---------- 三、自增 ++ 的位置差别 ---------- */
    int n1 = 5, n2 = 5;
    int r1 = n1++;                   /* 先取值，再加1 */
    int r2 = ++n2;                   /* 先加1，再取值 */
    printf("n1++ 得到 %d，之后 n1 = %d\n", r1, n1);
    printf("++n2 得到 %d，之后 n2 = %d\n", r2, n2);

    /* ---------- 四、位运算（嵌入式必会） ---------- */
    unsigned char reg = 0x00;
    reg |= (1 << 2);                 /* 把第2位置1  -> 0x04 */
    printf("置位后 reg = 0x%02X\n", reg);
    reg |= (1 << 5);                 /* 再置第5位    -> 0x24 */
    printf("再置第5位   = 0x%02X\n", reg);
    reg &= ~(1 << 2);                /* 把第2位清0   -> 0x20 */
    printf("清第2位后   = 0x%02X\n", reg);
    printf("读第5位     = %d          <- 用 & 判断某位是0还是1\n",
           (reg & (1 << 5)) ? 1 : 0);
    printf("左移1位     = 0x%02X        <- 位移：<< 乘2，>> 除2\n",
           (unsigned char)(reg << 1));

    /* ---------- 五、分支：if / else if / switch ---------- */
    int score = 87;
    if (score >= 90) {
        printf("等级：优秀\n");
    } else if (score >= 80) {
        printf("等级：良好\n");
    } else if (score >= 60) {
        printf("等级：及格\n");
    } else {
        printf("等级：不及格\n");
    }

    int key = 2;
    switch (key) {
    case 1:
        printf("按下了按键1\n");
        break;                       /* 忘了 break 会继续往下执行 */
    case 2:
        printf("按下了按键2\n");
        break;
    default:
        printf("未知按键\n");
        break;
    }

    /* ---------- 六、溢出：小心无符号数减过头 ---------- */
    unsigned int u = 3;
    printf("3u - 5u = %u              <- 无符号数减过头会绕回很大的数\n", u - 5);

    return 0;
}
