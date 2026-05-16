  #include <stdio.h> 
  #include <stdbool.h> 

int main(int argc, char const *argv[])
{
    printf("%d\n",0123==123); //return 0 because 0123 is an octal
    printf("%d\n",0x07b==123); //return 1 because 0x07b is an hexadécimal
    return 0;
}
