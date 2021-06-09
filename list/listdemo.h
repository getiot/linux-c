#ifndef _LISTDEMO_H
#define _LISTDEMO_H

//通过结构体成员指针获取结构体指针位置
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})


//链表结构体
struct list_head {
	struct list_head *next, *prev;
};

//链表初始化
static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

#ifndef CONFIG_DEBUG_LIST
static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}
#else
extern void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next);
#endif


//添加至链表首部
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

//添加到链表尾部
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

//判断链表是否为空
/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
 /* if empty return 1,else 0 */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}


//删除操作
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

//获取链表的数据指针
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)
	
//遍历链表
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

//遍历过程中如果对链表有删除操作需要使用这个接口
#define list_for_each_safe(pos, n, head) \
        for (pos = (head)->next, n = pos->next; pos != (head); \
            pos = n, n = pos->next)
            

//遍历链表元素
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))
	     
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))
	     
//取第一个元素
#define list_first_entry(ptr, type, member) \
        list_entry((ptr)->next, type, member)

//自定义消息结构体
struct msg {
    int msgid;
    char msginfo[50];
    struct list_head list;
};

#endif
