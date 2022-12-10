#include <stdio.h>
#include <gtk/gtk.h>

int main(int argc,char *argv[])
{
    GtkWidget *window;

    /* 
     * 函数gtk_init()会在每个GTK的应用程序中调用。
     * 该函数设定默认的视频和颜色默认参数，接下来会调用函数
     * gdk_init()该函数初始化要使用的库，设定默认的信号处理
     * 检查传递到程序的命令行参数
     * */
    gtk_init(&argc, &argv);
    
    /* 下面两行创建并显示窗口，默认大小200*200 */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(window);
    
    /* 进入主循环 */
    gtk_main();

    return 0;
}