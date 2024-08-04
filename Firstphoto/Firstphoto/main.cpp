#include <graphics.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <chrono>
#include <thread>
#pragma comment(lib,"winmm.lib")

// 全局变量来控制音乐播放状态和进度
bool isPlaying = false;
int musicDuration = 0;
int currentPos = 0;

// 函数声明
void drawButton(int x, int y, bool isPlaying);
void drawProgressBar(int x, int y, int width, int height, int currentPos, int totalDuration);
void updateMusicProgress();

int main(void) {
    // 初始化图形窗口
    initgraph(828, 736, 1);

    // 加载背景图片
    IMAGE bg;
    loadimage(&bg, "bg.jpg");

    // 按钮位置和大小
    int buttonX = 700, buttonY = 600;
    int buttonRadius = 25;  // 按钮半径

    // 进度条位置和大小
    int progressBarX = 100, progressBarY = 650;
    int progressBarWidth = 600, progressBarHeight = 20;

    // 获取音乐总时长
    mciSendString("open music.mp3 alias mymusic", 0, 0, 0);
    char durationStr[128];
    mciSendString("status mymusic length", durationStr, sizeof(durationStr), 0);
    musicDuration = atoi(durationStr); // 将音乐时长转换为整数

    // 主循环
    while (true) {
        // 绘制背景
        putimage(0, 0, &bg);

        // 绘制播放/暂停按钮
        drawButton(buttonX, buttonY, isPlaying);

        // 绘制进度条
        drawProgressBar(progressBarX, progressBarY, progressBarWidth, progressBarHeight, currentPos, musicDuration);

        // 检查鼠标点击
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                int dx = msg.x - (buttonX + buttonRadius);
                int dy = msg.y - (buttonY + buttonRadius);
                if (dx * dx + dy * dy <= buttonRadius * buttonRadius) {
                    // 点击按钮区域
                    isPlaying = !isPlaying;
                    if (isPlaying) {
                        mciSendString("play mymusic repeat", 0, 0, 0);
                    }
                    else {
                        mciSendString("pause mymusic", 0, 0, 0);
                    }
                }
            }
        }

        // 更新音乐进度
        if (isPlaying) {
            char posStr[128];
            mciSendString("status mymusic position", posStr, sizeof(posStr), 0);
            currentPos = atoi(posStr); // 将当前位置转换为整数
        }

        // 刷新屏幕
        Sleep(10);
    }

    // 关闭音乐
    mciSendString("close mymusic", 0, 0, 0);
    closegraph();

    return 0;
}

// 绘制播放/暂停按钮函数
void drawButton(int x, int y, bool isPlaying) {
    int radius = 25;
    setfillcolor(isPlaying ? GREEN : RED);
    fillcircle(x + radius, y + radius, radius);
    settextcolor(WHITE);
    settextstyle(20, 0, "Arial");
    outtextxy(x + 10, y + 10, isPlaying ? "暂停" : "开始");
}

// 绘制进度条函数
void drawProgressBar(int x, int y, int width, int height, int currentPos, int totalDuration) {
    setfillcolor(LIGHTGRAY);
    solidrectangle(x, y, x + width, y + height);
    setfillcolor(BLUE);
    solidrectangle(x, y, x + (int)(width * ((float)currentPos / totalDuration)), y + height);
}
