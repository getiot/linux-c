/*
 *  Description : Linux kernel linked list example
 *  Date        : 20210610
 *  Author      : RudyLo
 *  Mail        : luhuadong@163.com
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listdemo.h"

#define log(fmt, arg...) printf("" fmt, ##arg)

//自定义消息结构体
struct msg
{
    int msgid;
    char msginfo[50];
    struct list_head list;
};

void main()
{
    bool is_running = true;
    struct list_head msg_head, *pos, *n;
    struct msg *pmsg;

    //链表初始化
    INIT_LIST_HEAD(&msg_head);

    log("*********************\n\n"
        "input options:\n"
        " 1) insert\n"      //插入
        " 2) serach\n"      //查询
        " 3) search all \n" //查询所有
        " 4) modify\n"      //修改
        " 5) delete\n"      //删除
        " 6) delete all\n"  //删除全部
        " 0) quit\n"
        "\n*********************\n");

    while (is_running)
    {
        char opt = 0;
        log("\ninput options: ");
        scanf("%c", &opt);
        getchar();
        switch (opt)
        {
        //插入链表，相同结点可重复插入，也可以在加入前比较判断防止插入重复
        case '1':
            pmsg = calloc(1, sizeof(struct msg));
            if (!pmsg)
            {
                log("insert fail \n");
                break;
            }
            log("input msgid: ");
            scanf("%d", &pmsg->msgid);
            getchar();
            log("input msg info: ");
            fgets(pmsg->msginfo, sizeof(pmsg->msginfo), stdin);
            if (pmsg->msginfo[strlen(pmsg->msginfo)-1] == '\n')
                pmsg->msginfo[strlen(pmsg->msginfo)-1] = '\0';
            log("[Your have input : msgid : %d, msginfo : %s ]\n", pmsg->msgid, pmsg->msginfo);
            list_add_tail(&pmsg->list, &msg_head); //插入尾部，list_add()插入首部
            break;

        //查询
        case '2':
        {
            bool flag = false;
            int key = 0;
            log("input msg id: ");
            scanf("%d", &key);
            getchar();

            list_for_each_entry(pmsg, &msg_head, list)
            {
                if (pmsg->msgid == key)
                {
                    log("[msgid: %d, msginfo: %s]\n", key, pmsg->msginfo);
                    flag = true;
                    break;
                }
            }
            if (!flag)
                log("%d not found! \n", key);
        }
            break;

        //查询所有
        case '3':
            log("\n------ ALL node ------\n\n");
            list_for_each_entry(pmsg, &msg_head, list)
            {
                log("[msgid: %d, msginfo: %s]\n", pmsg->msgid, pmsg->msginfo);
            }
            break;

        //修改
        case '4':
        {
            bool flag = false;
            int key = 0;
            log("input msg id: ");
            scanf("%d", &key);
            getchar();
            //修改
            list_for_each_entry(pmsg, &msg_head, list)
            {
                if (pmsg->msgid == key)
                {
                    log("[msgid: %d, msginfo: %s]\n", key, pmsg->msginfo);
                    log("input msg you want to set: ");
                    memset(pmsg->msginfo, 0, sizeof(pmsg->msginfo));
                    //getchar();
                    fgets(pmsg->msginfo, sizeof(pmsg->msginfo), stdin);
                    if (pmsg->msginfo[strlen(pmsg->msginfo)-1] == '\n')
                        pmsg->msginfo[strlen(pmsg->msginfo)-1] = '\0';
                    flag = true;
                }
            }
            if (!flag)
            {
                log("msgid : %d not fount!\n", key);
            }
        }
            break;

        //删除
        case '5':
        {
            bool flag = false;
            int key = 0;
            log("input msg id: ");
            scanf("%d", &key);
            getchar();
            //遍历链表并且执行删除操作需要使用这个接口 _safe
            list_for_each_safe(pos, n, &msg_head)
            {
                pmsg = list_entry(pos, struct msg, list);
                if (pmsg->msgid == key)
                {
                    log("[delete msg, msgid: %d, msginfo: %s]\n", pmsg->msgid, pmsg->msginfo);
                    list_del(pos);
                    free(pmsg);
                    flag = true;
                }
            }
            if (!flag)
                log("msgid : %d not found!\n", key);
        }
            break;

        //删除所有
        case '6':
            list_for_each_safe(pos, n, &msg_head)
            {
                pmsg = list_entry(pos, struct msg, list);
                log("[delete msg, msgid:%d, msginfo:%s]\n", pmsg->msgid, pmsg->msginfo);
                list_del(pos);
                free(pmsg);
            }
            break;

        case '0':
        case 'q':
            //退出前释放资源
            list_for_each_safe(pos, n, &msg_head)
            {
                pmsg = list_entry(pos, struct msg, list);
                list_del(pos);
                free(pmsg);
            }

            is_running = false;
            break;

        default:
            log("Error: invalid option!\n");
            break;
        }
    }
    return;
}
