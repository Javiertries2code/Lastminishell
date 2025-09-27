#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

void ft_striteri(char *s, void (*f)(unsigned int,
char*))
{

   
    unsigned int i;

    i = 0;

    while (s[i])
    {
        f(i, &s[i]);
    i++;
    }
}


 void f(unsigned int i, char *c)
  {
         char ch;

    ch = 'j';

    printf("yy%c\n", *c);

    if (i && *c != ' ')

        c[0] = ch;

    printf("zz%c\n", *c);
 }

int main(void)
{

 char str1[] = "hola cara bola"; 
 printf("before\n%s\n", str1);
 ft_striteri(str1, (*f));
 printf("after\n%s\n", str1);
     return (0); }