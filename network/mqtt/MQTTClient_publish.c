/*
 * A publish example for paho.mqtt.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"

#define ADDRESS     "tcp://localhost:1883" //更改此处地址
#define CLIENTID    "ubuntu" //更改此处客户端ID
#define TOPIC       "test"  //更改发送的话题
#define PAYLOAD     "Hello, GetIoT.tech!" //更改信息内容
#define QOS         1
#define TIMEOUT     10000L

int main(int argc, char* argv[])
{
    //声明一个MQTTClient
    MQTTClient client;
    char *username = "rudy";      //添加的用户名
    char *password = "p@ssw0rd";  //添加的密码
    int rc;

    //初始化MQTT Client选项
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    //#define MQTTClient_message_initializer { {'M', 'Q', 'T', 'M'}, 0, 0, NULL, 0, 0, 0, 0 }
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    //声明消息token
    MQTTClient_deliveryToken token;

    //使用参数创建一个client，并将其赋值给之前声明的client
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = username; //将用户名写入连接选项中
    conn_opts.password = password;//将密码写入连接选项中

    //使用MQTTClient_connect将client连接到服务器，使用指定的连接选项。成功则返回MQTTCLIENT_SUCCESS
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic '%s' for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);

    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    
    return rc;
}
