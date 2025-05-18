/* Código gerado pelo compilador EasyLang */
#include <stdio.h>

int main() {
int a = 5;
int x = 2;
printf("%d\n", a);
printf("%d\n", x);
printf("[DEBUG] Entering debug block\n");
int z = 0;
printf("Line 1: remember z as %d\n", z);
printf("Line 2: z = %d, z > (-1) = %d\n", z, z > (-1));
while (z > (-1)) {
    z =   (-1);
  int b = a + x;
  printf("%d\n", b);
    a = b * 3;
  printf("%d\n", a);
}
printf("[DEBUG] Exiting debug block\n");
printf("%d\n", a + x);
    return 0;
}
