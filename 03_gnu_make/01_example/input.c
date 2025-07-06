// input.c - 输入处理实现
#include <stdio.h>
#include "input.h"

// 获取玩家移动
int getPlayerMove(int* row, int* col) {
    printf("请输入坐标 (行 列): ");
    if (scanf("%d %d", row, col) != 2) {
        printf("输入无效，请重新输入！\n");
        while (getchar() != '\n'); // 清空输入缓冲区
        return 0;
    }
    return 1;
}
