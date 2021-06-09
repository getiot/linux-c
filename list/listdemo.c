/*
 *  Description : linux应用层编程之内核链表list的使用
 *  Date        ：20180610
 *  Author      ：mason
 *  Mail        : mrsonko@126.com
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "listdemo.h"

#define log(fmt, arg...) printf(""fmt,##arg)

void main() {
    int quit = 0;
    int flag = 0;
    int opt, key;
    struct list_head msg_head, *pos, *n;
    struct msg msg1, msg2, *pmsg;

    //链表初始化
    INIT_LIST_HEAD(&msg_head);

    log("*********************\n\n"
        "input options:\n"
        "1: insert\n"           //插入
        "2: serach\n"           //查询
        "3: search all \n"      //查询所有
        "4: modify\n"           //修改
        "5: delete\n"           //删除
        "6: delete all\n"       //删除全部
        "0: quit\n"
        "\n*********************\n");
    while(!quit) {
        log("\ninput options: ");
        scanf("%d",  &opt);
        switch(opt){
        
            //插入链表，相同结点可重复插入，也可以在加入前比较判断防止插入重复
            case 1:
                pmsg = calloc(1, sizeof(struct msg));
                if(!pmsg){
                    log("insert fail \n");
                    break;
                }
                log("input msgid : ");
                scanf("%d", &pmsg->msgid);
                log("input msg info:");
                getchar();
                gets(pmsg->msginfo);
                log("[Your have input : msgid : %d, msginfo : %s ]\n", pmsg->msgid, pmsg->msginfo);
                list_add_tail(&pmsg->list, &msg_head);  //插入尾部，list_add()插入首部
                break;

             //查询
             case 2:
             flag = 0 ;
             log("input msg id:");
             scanf("%d", &key);   

             //遍历查询
             list_for_each_entry(pmsg, &msg_head, list) {
                if(pmsg->msgid == key){ 
                    log("[msgid: %d, msginfo: %s ]\n", key, pmsg->msginfo);
                    flag = 1;
                    break;
                }
             }
             if(!flag)  
                log("%d not found! \n", key);
             break;             

             //查询所有
             case 3:
                 log("\n***** msg start *****\n\n");
                 list_for_each_entry(pmsg, &msg_head, list){
                     log("[msgid: %d, msginfo: %s ]\n", key, pmsg->msginfo);
                 }
                 log("\n***** msg end   *****\n");
                break;

             //修改
             case 4:
                  flag = 0;
                  log("input msg id:");
                  scanf("%d", &key);   
                  //修改
                  list_for_each_entry(pmsg, &msg_head, list) {
                     if(pmsg->msgid == key){ 
                         log("[msgid: %d, msginfo: %s ]\n", key, pmsg->msginfo);
                         log("input msg you want to set:");        
                         memset(pmsg->msginfo, 0, sizeof(pmsg->msginfo));
                         getchar();
                         gets(pmsg->msginfo);
                         flag = 1;
                     }
                  }
                  if(!flag){
                      log("msgid : %d not fount !\n", key);
                  }
                  flag = 0;
                  break;

             //删除     
             case 5:
                  flag = 0;
                  log("input msg id:");
                  scanf("%d", &key);  
                  //遍历链表并且执行删除操作需要使用这个接口 _safe
                  list_for_each_safe(pos, n, &msg_head){
                      pmsg = list_entry(pos, struct msg, list);
                      if(pmsg->msgid == key){
                          log("[delete msg, msgid:%d, msginfo:%s]\n", pmsg->msgid, pmsg->msginfo);
                          list_del(pos);
                          free(pmsg);
                          flag = 1;
                      }
                  }
                  if(!flag)
                     log("msgid : %d not found!\n", key);
                  flag = 0;
                  break;

             //删除所有
             case 6:
                  list_for_each_safe(pos, n, &msg_head){
                      pmsg = list_entry(pos, struct msg, list);
                      log("[delete msg, msgid:%d, msginfo:%s]\n", pmsg->msgid, pmsg->msginfo);
                      list_del(pos);
                      free(pmsg);
                  }
                  break;  
                  
             default:
                  //退出前释放资源
                  list_for_each_safe(pos, n, &msg_head){
                      pmsg = list_entry(pos, struct msg, list);
                      list_del(pos);
                      free(pmsg);
                  }
                  
                  quit = 1;
                break;
        }
    }
    return ;
}
