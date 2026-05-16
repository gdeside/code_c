#include<stdio.h>
#include<stdlib.h>


int tableof5(){
    static int count =0;
    count+=5;
    return count;
}


int main(int argc, char const *argv[])
{
    printf("%d\n",tableof5());
    printf("%d\n",tableof5());
    printf("%d\n",tableof5());
    printf("%d\n",tableof5());
    printf("%d\n",tableof5());
    printf("%d\n",tableof5());
    printf("%d\n",tableof5());
    return 0;
}
