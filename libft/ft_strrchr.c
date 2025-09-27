#include<string.h>
char *ft_strchr(char *s, int c)
{
int i;
int lenght;

lenght = 0;
while (s[lenght] || s[lenght - 1])
	{
		lenght++;
	}

i = lenght -1;

while (s[i] && i >= 0)
	{

		if (c == s[i])
			return  &s[i];
		else

	i--;

	}

return (&s[lenght]);
}


// int main()
// {
// 	char ch = 'x';
// 	printf("%c\n", *ft_strchr("hobla carabola", ch));
// 		printf("%c\n", *(ft_strchr("hola carabola", ch)+1));


// }
