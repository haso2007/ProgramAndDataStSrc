 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 int main(int argc, char *argv[])
 {
 srand(time(NULL));
 printf("rand() = %d \n", rand());
 return 0;
 }
