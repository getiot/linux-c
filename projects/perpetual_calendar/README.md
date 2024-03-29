# 万年历程序

万年历（Perpetual Calendar）是可以使用很多年的日历，通常设计成可以计算未来某一日期在星期中的日子。

本项目使用纯 C 语言，接收一个年份作为输入，然后打印出该年份各个月的日历。

编译：

```bash
$ make
```

默认为英文输出，如果需要中文输出，可以在编译时添加 `PRINT_IN_CHINESE` 宏定义：

```bash
$ make CFLAGS=-DPRINT_IN_CHINESE
```

或者直接修改 Makefile 文件。

运行：

```bash
$ ./calendar 
请输入年份：year = 2024

           2024年 一月 
 日   一   二   三   四   五   六   
       1    2    3    4    5    6  
  7    8    9   10   11   12   13  
 14   15   16   17   18   19   20  
 21   22   23   24   25   26   27  
 28   29   30   31  


           2024年 二月 
 日   一   二   三   四   五   六   
                      1    2    3  
  4    5    6    7    8    9   10  
 11   12   13   14   15   16   17  
 18   19   20   21   22   23   24  
 25   26   27   28   29  


           2024年 三月 
 日   一   二   三   四   五   六   
                           1    2  
  3    4    5    6    7    8    9  
 10   11   12   13   14   15   16  
 17   18   19   20   21   22   23  
 24   25   26   27   28   29   30  
 31  


           2024年 四月 
 日   一   二   三   四   五   六   
       1    2    3    4    5    6  
  7    8    9   10   11   12   13  
 14   15   16   17   18   19   20  
 21   22   23   24   25   26   27  
 28   29   30  


           2024年 五月 
 日   一   二   三   四   五   六   
                 1    2    3    4  
  5    6    7    8    9   10   11  
 12   13   14   15   16   17   18  
 19   20   21   22   23   24   25  
 26   27   28   29   30   31  


           2024年 六月 
 日   一   二   三   四   五   六   
                                1  
  2    3    4    5    6    7    8  
  9   10   11   12   13   14   15  
 16   17   18   19   20   21   22  
 23   24   25   26   27   28   29  
 30  


           2024年 七月 
 日   一   二   三   四   五   六   
       1    2    3    4    5    6  
  7    8    9   10   11   12   13  
 14   15   16   17   18   19   20  
 21   22   23   24   25   26   27  
 28   29   30   31  


           2024年 八月 
 日   一   二   三   四   五   六   
                      1    2    3  
  4    5    6    7    8    9   10  
 11   12   13   14   15   16   17  
 18   19   20   21   22   23   24  
 25   26   27   28   29   30   31  



           2024年 九月 
 日   一   二   三   四   五   六   
  1    2    3    4    5    6    7  
  8    9   10   11   12   13   14  
 15   16   17   18   19   20   21  
 22   23   24   25   26   27   28  
 29   30  


           2024年 十月 
 日   一   二   三   四   五   六   
            1    2    3    4    5  
  6    7    8    9   10   11   12  
 13   14   15   16   17   18   19  
 20   21   22   23   24   25   26  
 27   28   29   30   31  


           2024年 十一月 
 日   一   二   三   四   五   六   
                           1    2  
  3    4    5    6    7    8    9  
 10   11   12   13   14   15   16  
 17   18   19   20   21   22   23  
 24   25   26   27   28   29   30  



           2024年 十二月 
 日   一   二   三   四   五   六   
  1    2    3    4    5    6    7  
  8    9   10   11   12   13   14  
 15   16   17   18   19   20   21  
 22   23   24   25   26   27   28  
 29   30   31  


```
