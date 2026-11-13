/*
 * lesson03_embedded_basics.c
 * 嵌入式 C 的地基 —— 七个必须刻进肌肉记忆的点
 *
 * 目标：这一课不教语法，教"MCU 里为什么要这么写"。
 * 编译：gcc -Wall -Wextra -g lesson03_embedded_basics.c -o lesson03_embedded_basics.exe
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ============================================================
 * 1. 定宽整数类型：永远不要假设 int 是 4 字节
 * ============================================================
 * PC 上 int=4、long=4(Windows)/8(Linux)，而在 MCU 上
 * short/int/long 的宽度随编译器变。跨平台代码必须用 stdint.h。
 */
static void lesson_types(void)
{
    printf("[1] 定宽类型宽度（字节）\n");
    printf("    int8_t  = %zu   uint8_t  = %zu\n", sizeof(int8_t), sizeof(uint8_t));
    printf("    int16_t = %zu   uint16_t = %zu\n", sizeof(int16_t), sizeof(uint16_t));
    printf("    int32_t = %zu   uint32_t = %zu\n", sizeof(int32_t), sizeof(uint32_t));
    printf("    int64_t = %zu   uint64_t = %zu\n", sizeof(int64_t), sizeof(uint64_t));
    printf("    size_t  = %zu   (用于下标/长度，不要用 int)\n", sizeof(size_t));
    printf("    本机 int = %zu（平台相关，不能用它表示寄存器）\n", sizeof(int));
}

/* ============================================================
 * 2. 位操作：嵌入式 80%% 的硬件控制都是这四招
 * ============================================================ */
#define BIT(n)              (1u << (n))
#define SET_BIT(reg, n)     ((reg) |=  BIT(n))
#define CLEAR_BIT(reg, n)   ((reg) &= ~BIT(n))
#define TOGGLE_BIT(reg, n)  ((reg) ^=  BIT(n))
#define TEST_BIT(reg, n)    (((reg) >> (n)) & 1u)

static void lesson_bitops(void)
{
    uint32_t reg = 0x0000;

    printf("[2] 位操作演示\n");
    printf("    初始       reg = 0x%04X\n", reg);

    SET_BIT(reg, 3);           /* 第 3 位置 1 */
    printf("    置位 bit3  reg = 0x%04X\n", reg);

    SET_BIT(reg, 5);           /* 第 5 位置 1 */
    printf("    置位 bit5  reg = 0x%04X\n", reg);

    CLEAR_BIT(reg, 3);         /* 第 3 位清 0 */
    printf("    清零 bit3  reg = 0x%04X\n", reg);

    TOGGLE_BIT(reg, 5);        /* 翻转第 5 位 */
    printf("    翻转 bit5  reg = 0x%04X\n", reg);

    reg = 0x00A4;
    printf("    reg = 0x%04X 时：bit2=%u, bit5=%u\n",
           reg, (unsigned)TEST_BIT(reg, 2), (unsigned)TEST_BIT(reg, 5));

    /* 一次性改多个位：先清掩码再写值，避免"读-改-写"踩到别的位 */
    reg = 0xFFFF;
    reg &= ~(0x3u << 4);       /* 清 bit5:4 */
    reg |=  (0x1u << 4);       /* 写 bit5:4 = 01 */
    printf("    改 bit5:4 = 01 后 reg = 0x%04X\n", reg);
}

/* ============================================================
 * 3. volatile：告诉编译器"这个值会被硬件偷偷改掉"
 * ============================================================
 * 真实场景：while (REG->SR & BUSY) {} 这种等待。
 * 没有 volatile，编译器会把值缓存在寄存器里，
 * 循环永远看不到硬件更新 -> 死等。
 */
static void lesson_volatile(void)
{
    volatile uint32_t hw_status = 0;  /* 模拟只能由硬件修改的状态寄存器 */
    uint32_t fake_hw = 0;             /* 模拟"硬件"在另一处写这个值 */
    uint32_t spins = 0;

    printf("[3] volatile 演示\n");
    /* 模拟：硬件在第 3 次循环时把状态置 1 */
    while (hw_status == 0 && spins < 10) {
        spins++;
        if (spins == 3) {
            fake_hw = 1;
            hw_status = fake_hw;      /* 真实代码里这里由硬件完成，软件不写 */
        }
    }
    printf("    等待结束：spins=%u, status=%u\n",
           (unsigned)spins, (unsigned)hw_status);
    printf("    要点：访问硬件寄存器/中断共享变量的指针或变量必须加 volatile\n");
}

/* ============================================================
 * 4. 指针 = 寄存器的地址
 * ============================================================
 * MCU 里 0x4002 0000 就是某个外设寄存器的物理地址，
 * 写法是：*(volatile uint32_t *)0x40020000 = 1;
 * PC 上不能访问这个地址，所以这里用一块本地数组模拟。
 */
static void lesson_pointer_reg(void)
{
    uint32_t fake_periph[4] = {0};          /* 模拟 4 个连续寄存器 */
    uint32_t *pCR  = &fake_periph[0];       /* 控制寄存器 */
    uint32_t *pSR  = &fake_periph[1];       /* 状态寄存器 */
    uint32_t *pDR  = &fake_periph[2];       /* 数据寄存器 */

    printf("[4] 用指针访问寄存器\n");
    SET_BIT(*pCR, 0);                       /* 使能 */
    *pDR = 0x1234;                          /* 写数据 */
    *pSR = 0x0001;                          /* 模拟硬件回一个状态位 */
    printf("    CR=0x%04X SR=0x%04X DR=0x%04X\n", *pCR, *pSR, *pDR);
    printf("    pCR=%p  (相邻寄存器地址差 %zu 字节)\n",
           (void *)pCR, (size_t)((char *)pSR - (char *)pCR));
}

/* ============================================================
 * 5. 结构体 + 位域：把一个 32 位寄存器"掰开"看
 * ============================================================ */
typedef struct {
    uint32_t enable   : 1;   /* bit0     */
    uint32_t mode     : 3;   /* bit3:1   */
    uint32_t prescale : 8;   /* bit11:4  */
    uint32_t reserved : 20;  /* bit31:12 */
} TIM_CR_t;

static void lesson_bitfield(void)
{
    TIM_CR_t cr;
    uint32_t raw = 0;

    memset(&cr, 0, sizeof(cr));
    cr.enable   = 1;
    cr.mode     = 2;      /* 二进制 010 */
    cr.prescale = 0x5A;

    /* 位域的内存布局与编译器/字节序有关，所以这里用 memcpy 取原始值验证 */
    memcpy(&raw, &cr, sizeof(raw));

    printf("[5] 结构体位域\n");
    printf("    sizeof(TIM_CR_t) = %zu 字节（位域不会真的省成 1 位）\n", sizeof(TIM_CR_t));
    printf("    enable=%u mode=%u prescale=0x%02X\n",
           (unsigned)cr.enable, (unsigned)cr.mode, (unsigned)cr.prescale);
    printf("    打包后的原始 32 位值 = 0x%08X\n", raw);
    printf("    注意：位域的位序依赖编译器，跨平台通信不要用位域打包协议\n");
}

/* ============================================================
 * 6. 字节序：通信协议里最容易踩的坑
 * ============================================================ */
static int is_little_endian(void)
{
    union {
        uint16_t word;
        uint8_t  byte[2];
    } probe;

    probe.word = 0x0102;
    return probe.byte[0] == 0x02;   /* 低地址存低字节 = 小端 */
}

static void lesson_endian(void)
{
    uint16_t value = 0x1234;
    uint8_t  buf[2];

    memcpy(buf, &value, 2);

    printf("[6] 字节序\n");
    printf("    本机是%s端\n", is_little_endian() ? "小" : "大");
    printf("    0x1234 存成两个字节：buf[0]=0x%02X buf[1]=0x%02X\n", buf[0], buf[1]);
    printf("    所以在和仪表/上位机通信时，多字节数据要显式转字节序\n");
}

/* ============================================================
 * 7. 对齐：为什么结构体 sizeof 不等于成员之和
 * ============================================================ */
typedef struct {
    uint8_t  a;
    uint32_t b;
    uint8_t  c;
} DemoAlign_t;

static void lesson_align(void)
{
    printf("[7] 内存对齐\n");
    printf("    sizeof(DemoAlign_t) = %zu 字节（成员之和只有 6 字节）\n",
           sizeof(DemoAlign_t));
    printf("    偏移：a=%zu b=%zu c=%zu\n",
           offsetof(DemoAlign_t, a),
           offsetof(DemoAlign_t, b),
           offsetof(DemoAlign_t, c));
    printf("    编译器为了访问效率自动补空洞；MCU 上要省 RAM 得手动重排或加 __attribute__((packed))\n");
}

int main(void)
{
    printf("===== 嵌入式 C 第三课：地基 =====\n\n");
    lesson_types();
    printf("\n");
    lesson_bitops();
    printf("\n");
    lesson_volatile();
    printf("\n");
    lesson_pointer_reg();
    printf("\n");
    lesson_bitfield();
    printf("\n");
    lesson_endian();
    printf("\n");
    lesson_align();
    printf("\n===== 完 =====\n");
    return 0;
}
