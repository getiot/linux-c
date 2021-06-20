#include <stdio.h>
#include <string.h>

int main()
{
    char dest[30] = "string(a)";
    char src[30]="string\0string";
    int i;
    bcopy(src, dest, 30);      /* src指针放在前面 */
    printf("bcopy(): ");
    for(i=0; i<30; i++)
        printf("%c", dest[i]);
    
    memcpy(dest, src, 30);     /* dest指针放在前面 */
    printf("\nmemcpy(): ");
    for(i=0; i<30; i++)
        printf("%c", dest[i]);
    
    return 0;
}
