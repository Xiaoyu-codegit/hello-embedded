#include <stdio.h>

int main(int argc, char const *argv[])
{
    fopen("io.txt","r");
    perror("This question err!");
    return 0;
}
