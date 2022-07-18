#include <stdio.h>

void stopPlayer();
void pausePlayer();
void resumePlayer();
void startPlayer();

//按键的动作类型
typedef enum
{
    EV_STOP,
    EV_PLAY_PAUSE
} EventCode;

// MP3的状态
enum
{
    ST_IDLE,
    ST_PLAY,
    ST_PAUSE
};

// MP3当前状态
char state;

// MP3状态初始化
void init()
{
    state = ST_IDLE;
}

//状态机处理MP3的过程变化
void onEvent(EventCode ec)
{
    switch (state)
    {
    case ST_IDLE:
        if (EV_PLAY_PAUSE == ec)
            startPlayer();
        break;
    case ST_PLAY:
        if (EV_STOP == ec)
            stopPlayer();
        else if (EV_PLAY_PAUSE == ec)
            pausePlayer();
        break;
    case ST_PAUSE:
        if (EV_STOP == ec)
            stopPlayer();
        else if (EV_PLAY_PAUSE == ec)
            resumePlayer();
        break;
    default:
        break;
    }
}

void stopPlayer()
{
    state = ST_IDLE;
    printf("停止播放音乐\n");
}

void pausePlayer()
{
    state = ST_PAUSE;
    printf("暂停播放音乐\n");
}

void resumePlayer()
{
    state = ST_PLAY;
    printf("恢复播放音乐\n");
}

void startPlayer()
{
    state = ST_PLAY;
    printf("开始播放音乐\n");
}
//主程序实现MP3的播放控制
void main()
{
    init();
    onEvent(EV_PLAY_PAUSE); //播放
    onEvent(EV_PLAY_PAUSE); //暂停
    onEvent(EV_PLAY_PAUSE); //继续播放
    onEvent(EV_STOP);       //停止
}
