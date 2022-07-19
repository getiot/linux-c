#include <stdio.h>

/***********************************************
1、定义状态接口，以MP3的状态接口为例，每种状态下都可能发生
两种按键动作。
************************************************/

typedef struct State
{
    void (*stop)();
    void (*playOrPause)();
} State;

/***********************************************
2、定义系统当前状态指针，保存系统的当前状态
************************************************/

State *pCurrentState;

/***********************************************
3、定义具体状态，根据状态迁移图来实现具体功能和状态切换。
************************************************/

void ignore();
void startPlay();
void stopPlay();
void pausePlay();
void resumePlay();

//空闲状态时，stop键操作无效，play/pause会开始播放音乐
State IDLE = {
    ignore,
    startPlay
};

//播放状态时，stop键会停止播放音乐，play/pause会暂停播放音乐
State PLAY = {
    stopPlay,
    pausePlay
};

//暂停状态时，stop键会停止播放音乐，play/pause会恢复播放音乐
State PAUSE = {
    stopPlay,
    resumePlay
};

void ignore()
{
    //空函数，不进行操作
}

void startPlay()
{
    //实现具体功能
    printf("开始播放音乐\n");
    //进入播放状态
    pCurrentState = &PLAY;
}

void stopPlay()
{
    //实现具体功能
    printf("停止播放音乐\n");
    //进入空闲状态
    pCurrentState = &IDLE;
}

void pausePlay()
{
    //实现具体功能
    printf("暂停播放音乐\n");
    //进入暂停状态
    pCurrentState = &PAUSE;
}

void resumePlay()
{
    //实现具体功能
    printf("恢复播放音乐\n");
    //进入播放状态
    pCurrentState = &PLAY;
}

/***********************************************
4、定义主程序上下文操作接口，主程序只关心当前状态，不关心状态之间
是怎么变化的。
************************************************/

void onStop();
void onPlayOrPause();

State context = {
    onStop,
    onPlayOrPause
};

void onStop(State *pThis)
{
    pCurrentState->stop(pThis);
}

void onPlayOrPause(State *pThis)
{
    pCurrentState->playOrPause(pThis);
}

/***********************************************
5、初始化系统当前状态指针，其实就是指定系统的起始状态
************************************************/

void init()
{
    pCurrentState = &IDLE;
}

/***********************************************
6、主程序通过上下文操作接口来控制系统当前状态的变化
************************************************/
void main()
{
    init();
    context.playOrPause(); //播放
    context.playOrPause(); //暂停
    context.playOrPause(); //播放
    context.stop();        //停止
}