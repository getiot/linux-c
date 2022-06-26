/* 服务端代码 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dbus/dbus.h>

void listen_signal()
{
    DBusMessage * msg;
    DBusMessageIter arg;
    DBusConnection * connection;
    DBusError err;
    int ret;
    char * sigvalue;

    /* 步骤1:建立与D-Bus后台的连接 */
    dbus_error_init(&err);

    connection = dbus_bus_get(DBUS_BUS_SESSION, &err);

    if(dbus_error_is_set(&err)) {
        fprintf(stderr,"ConnectionError %s\n",err.message);
        dbus_error_free(&err);
    }
    if(connection == NULL) {
        return;
    }

    /* 步骤2:给连接名分配一个可记忆名字 getiot.singal.dest 作为 Bus name */
    /* 这个步骤不是必须的，但推荐这样处理 */
    ret =dbus_bus_request_name(connection, "getiot.singal.dest", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);

    if(dbus_error_is_set(&err)){
        fprintf(stderr,"Name Error%s\n",err.message);
        dbus_error_free(&err);
    }
    if(ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
        return;

    /* 步骤3:通知 D-Bus daemon，希望监听来自接口 getiot.signal.Type 的信号 */
    dbus_bus_add_match(connection, "type='signal',interface='getiot.signal.Type'", &err);

    /* 实际需要发送东西给 daemon 来通知希望监听的内容，所以需要 flush */
    dbus_connection_flush(connection);

    if(dbus_error_is_set(&err)) {
        fprintf(stderr, "Match Error%s\n", err.message);
        dbus_error_free(&err);
    }

    /* 步骤4:在循环中监听，每隔开1秒，就去试图自己的连接中获取这个信号 */
    /* 这里给出的是中连接中获取任何消息的方式，所以获取后去检查一下这个消息是否我们期望的信号，并获取内容 */
    /* 我们也可以通过这个方式来获取 method call 消息 */
    while(1) {
        dbus_connection_read_write(connection, 0);
        msg = dbus_connection_pop_message (connection);
        if(msg == NULL) {
            sleep(1);
            continue;
        }

        if(dbus_message_is_signal(msg,"getiot.signal.Type","Test")) {
            if(!dbus_message_iter_init(msg, &arg)) {
                fprintf(stderr,"MessageHas no Param");
            }
            else if(dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_STRING) {
                fprintf(stderr,"Param isnot string");
            }
            else {
                dbus_message_iter_get_basic(&arg, &sigvalue);
            }
            printf("Recetive Singal Value : %s\n", sigvalue);
        }
        dbus_message_unref(msg);
    } /* End of while */

}
int main(void)
{
    printf("------Start Listen_signal!-------\n");
    listen_signal();
    return 0;
}