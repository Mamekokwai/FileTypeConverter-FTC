#include "animation.h"

void loading_animation1()
{
    printf("\n▲▼▲LOARDING SYSTEM INFO▼▲▼");

    // fflush(stdout);

    for (int i = 0; i < 10; i++)
    {
        Sleep(20); // 300毫秒
        printf(".");
        fflush(stdout);
    }

    fflush(stdout);
    Sleep(100);
    printf("▲DONE▼");

    // // 系统检查动画
    // const char *systems[] = {
    //     "NEURAL INTERFACE", "WEAPONS SYSTEMS", "NAVIGATION",
    //     "LIFE SUPPORT", "COMMUNICATIONS", "SENSOR ARRAY"};
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("[%02d%%] INITIALIZING %-18s", i * 15, systems[i]);
    //     fflush(stdout);

    //     // 模拟系统检查的闪烁效果
    //     for (int j = 0; j < 3; j++)
    //     {
    //         Sleep(30);
    //         printf("▓");
    //         fflush(stdout);
    //     }

    //     printf(" [ONLINE]\n");
    //     Sleep(50);
    // }
    // printf("\n▲ SYSTEM STATUS: PURE ▲\n");
}