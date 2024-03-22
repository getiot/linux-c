#include <stdio.h>

#define Mon            1
#define Tues           2
#define Wed            3
#define Thur           4
#define Fri            5
#define Sat            6
#define Sun            0

#define January_days   31
#define February_days  28
#define March_days     31
#define April_days     30
#define May_days       31
#define June_days      30
#define July_days      31
#define August_days    31
#define September_days 30
#define October_days   31
#define November_days  30
#define December_days  31

#define first1month    (January_days)
#define first2month    (first1month + February_days)
#define first3month    (first2month + March_days)
#define first4month    (first3month + April_days)
#define first5month    (first4month + May_days)
#define first6month    (first5month + June_days)
#define first7month    (first6month + July_days)
#define first8month    (first7month + August_days)
#define first9month    (first8month + September_days)
#define first10month   (first9month + October_days)
#define first11month   (first10month + November_days)

char *month_names_en[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char *month_names_zh[] = {"一月", "二月", "三月", "四月", "五月", "六月", "七月", "八月", "九月", "十月", "十一月", "十二月"};

int known_weekday = Tues;
int known_year = 1901;
int konwn_month = 1;
int known_day = 1;
  
int day_count(int month)
{
    switch(month)
    {
    case 1: return 0; break;
    case 2: return first1month; break;
    case 3: return first2month; break;
    case 4: return first3month; break;
    case 5: return first4month; break;
    case 6: return first5month; break;
    case 7: return first6month; break;
    case 8: return first7month; break;
    case 9: return first8month; break;
    case 10: return first9month; break;
    case 11: return first10month; break;
    case 12: return first11month; break;
    }
}


char *get_month_name(int month)
{
    if (month < 1 || month > 12) {
        return "";
    }

#ifdef PRINT_IN_CHINESE
    return month_names_zh[month-1];
#else
    return month_names_en[month-1];
#endif
}
  
/*按格式打印某年某月名称*/
void first_line_print(int month, int year)
{
#ifdef PRINT_IN_CHINESE
    printf("%15d年 %s \n", year, get_month_name(month));
#else
    printf("%17s %d \n", get_month_name(month), year);
#endif
}
  
/*按格式打印星期名称*/
void week_print()
{
#ifdef PRINT_IN_CHINESE
    printf(" %-6s%-6s%-6s%-6s%-6s%-6s%-6s\n","日", "一", "二", "三", "四", "五", "六");
#else
    printf("%-5s%-5s%-5s%-5s%-5s%-5s%-5s\n","Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat.");
#endif
}
  
/*计算该年该月份与已知日子之间的距离天数*/
int date_distance_count(int month, int year)
{
    int leap_year_count = 0;
    int i;
    int distance;
     
    if (year > known_year)
    {
        for (i=known_year; i<year; i++)
        {
            if(((i%4 == 0) && (i%100 != 0) ) || (i%400 == 0))
            {
                leap_year_count++;
            }
        }
         
        if (month > 2)
        {
            if(((year%4 == 0) && (year%100 != 0) ) || (year%400 == 0))
            {
                leap_year_count++;
            }
        }
    }
    else
        if (year == known_year)
        {
            if (month > 2)
            {
                leap_year_count = 1;
            }
        }
         
         
        distance = (year - known_year)*365 + leap_year_count + day_count(month);
         
        return distance;
}
  
/*确定该月份第一天是星期几*/
int makesure_firstday_weekday(int month, int year)
{
    int date_distance = 0;
    int weekday;
     
    date_distance = date_distance_count(month, year);
    weekday = (known_weekday + date_distance)%7;
     
    return weekday;
}
  
/*依次打印出该月份的日子*/
void print_in_turn(int month, int firstday, int year)
{
    int i = 1;
    int weekday;
     
    switch(firstday)
    {
    case Sun:
        break;
    case Mon:
        printf("%-5s","");
        break;
    case Tues:
        printf("%-10s","");
        break;
    case Wed:
        printf("%-15s","");
        break;
    case Thur:
        printf("%-20s","");
        break;
    case Fri:
        printf("%-25s","");
        break;
    case Sat:
        printf("%-30s","");
        break;
    }
     
    switch(month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        {
            for(i=0; i<31; i++)
            {
                weekday = (firstday + i) % 7;
                printf("%3d  ", i+1);
                 
                if(weekday == Sat)
                {
                    printf("\n");
                }
            }
            break;
        }
    case 2:
        {
            if(((year%4 == 0) && (year%100 != 0) ) || (year%400 == 0)) /*闰年*/
            {
                for(i=0; i<29; i++)
                {
                    weekday = (firstday + i) % 7;
                    printf("%3d  ", i+1);
                     
                    if(weekday == Sat)
                    {
                        printf("\n");
                    }
                }
                break;
            }
            else /*平年*/
            {
                for(i=0; i<28; i++)
                {
                    weekday = (firstday + i) % 7;
                    printf("%3d  ", i+1);
                     
                    if(weekday == Sat)
                    {
                        printf("\n");
                    }
                }
                break;
            }
             
        }
    case 4:
    case 6:
    case 9:
    case 11:
        {
            for(i=0; i<30; i++)
            {
                weekday = (firstday + i) % 7;/*计算该天是星期几*/
                printf("%3d  ", i+1);
                 
                if(weekday == Sat)
                {
                    printf("\n");/*如果是星期六，则换行*/
                }
            }
            break;
        }
    }
}
  
void date_print(int month, int year)
{
    int firstday;
     
    firstday = makesure_firstday_weekday(month, year);
    print_in_turn(month, firstday, year);
    printf("\n");
}
  
void main_month(int month, int year)
{
    first_line_print(month, year);
    week_print();
    date_print(month, year);
    printf("\n\n");
}
  
void main_calendar(int year)
{
    int i;
    for(i=1; i<=12; i++)
    {
        main_month(i, year);
    }
}
  
int main()
{
    int year;
    printf("请输入年份：year = ");
    scanf("%d",&year);
    printf("\n");
     
    while(year < 1902)
    {
        printf("请输入大于1901的年份\n");
         
        printf("请输入年份：year = ");
        scanf("%d",&year);
        printf("\n");
    }
     
    main_calendar(year);
    return 0;
}