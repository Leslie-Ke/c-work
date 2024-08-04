#include <graphics.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <chrono>
#include <thread>
#pragma comment(lib,"winmm.lib")

// ȫ�ֱ������������ֲ���״̬�ͽ���
bool isPlaying = false;
int musicDuration = 0;
int currentPos = 0;

// ��������
void drawButton(int x, int y, bool isPlaying);
void drawProgressBar(int x, int y, int width, int height, int currentPos, int totalDuration);
void updateMusicProgress();

int main(void) {
    // ��ʼ��ͼ�δ���
    initgraph(828, 736, 1);

    // ���ر���ͼƬ
    IMAGE bg;
    loadimage(&bg, "bg.jpg");

    // ��ťλ�úʹ�С
    int buttonX = 700, buttonY = 600;
    int buttonRadius = 25;  // ��ť�뾶

    // ������λ�úʹ�С
    int progressBarX = 100, progressBarY = 650;
    int progressBarWidth = 600, progressBarHeight = 20;

    // ��ȡ������ʱ��
    mciSendString("open music.mp3 alias mymusic", 0, 0, 0);
    char durationStr[128];
    mciSendString("status mymusic length", durationStr, sizeof(durationStr), 0);
    musicDuration = atoi(durationStr); // ������ʱ��ת��Ϊ����

    // ��ѭ��
    while (true) {
        // ���Ʊ���
        putimage(0, 0, &bg);

        // ���Ʋ���/��ͣ��ť
        drawButton(buttonX, buttonY, isPlaying);

        // ���ƽ�����
        drawProgressBar(progressBarX, progressBarY, progressBarWidth, progressBarHeight, currentPos, musicDuration);

        // ��������
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                int dx = msg.x - (buttonX + buttonRadius);
                int dy = msg.y - (buttonY + buttonRadius);
                if (dx * dx + dy * dy <= buttonRadius * buttonRadius) {
                    // �����ť����
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

        // �������ֽ���
        if (isPlaying) {
            char posStr[128];
            mciSendString("status mymusic position", posStr, sizeof(posStr), 0);
            currentPos = atoi(posStr); // ����ǰλ��ת��Ϊ����
        }

        // ˢ����Ļ
        Sleep(10);
    }

    // �ر�����
    mciSendString("close mymusic", 0, 0, 0);
    closegraph();

    return 0;
}

// ���Ʋ���/��ͣ��ť����
void drawButton(int x, int y, bool isPlaying) {
    int radius = 25;
    setfillcolor(isPlaying ? GREEN : RED);
    fillcircle(x + radius, y + radius, radius);
    settextcolor(WHITE);
    settextstyle(20, 0, "Arial");
    outtextxy(x + 10, y + 10, isPlaying ? "��ͣ" : "��ʼ");
}

// ���ƽ���������
void drawProgressBar(int x, int y, int width, int height, int currentPos, int totalDuration) {
    setfillcolor(LIGHTGRAY);
    solidrectangle(x, y, x + width, y + height);
    setfillcolor(BLUE);
    solidrectangle(x, y, x + (int)(width * ((float)currentPos / totalDuration)), y + height);
}
