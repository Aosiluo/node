#include <stdio.h>

#define L2B_32(data) (1 == is_little_endian() ? (( (data & 0xff000000) >>24) |   \
                                                  ((data & 0x00ff0000) >>8)  |   \
                                                  ((data & 0x0000ff00) <<8)  |   \
                                                  ((data & 0x000000ff) <<24) )   \
                                                : data )


int is_little_endian(coid) {
    int data = 9;
    char* b = (char*)&data;
    printf("zhizhen %d\n", b);
    if (1 == *(char*)&data)
    {
        return 1;
    }
    else {
        return 0;
    }
                 
}

int main()
{
    int a;
    a = is_little_endian();
    printf("a:%d\n", a);
}
