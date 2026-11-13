#include <stdio.h>

/* 求和函数：练习 函数定义 / 数组传参 / 循环 */
int sum_array(const int arr[], int n)
{
    int i;
    int total = 0;
    for (i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

int main(void)
{
    /* 1. 变量与数据类型 */
    int age = 18;
    double pi = 3.14159;
    char grade = 'A';

    printf("age = %d, pi = %.2f, grade = %c\n", age, pi, grade);
    printf("int 占 %zu 字节, double 占 %zu 字节\n", sizeof(int), sizeof(double));

    /* 2. 数组 + for 循环 */
    int nums[5] = {4, 8, 15, 16, 23};
    int i;
    printf("数组元素: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    /* 3. 调用函数 */
    printf("数组和 = %d\n", sum_array(nums, 5));

    /* 4. while 循环 + 条件判断 */
    int n = 100;
    int count = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        count++;
    }
    printf("从100开始的考拉兹序列需要 %d 步到达1\n", count);

    /* 5. 指针初体验 */
    int x = 42;
    int *p = &x;
    printf("x 的地址 = %p, 通过指针读到的值 = %d\n", (void *)p, *p);

    return 0;
}
