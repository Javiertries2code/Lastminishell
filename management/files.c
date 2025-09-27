#include "../mini.h"


size_t	file_len(int fd)
{
	ssize_t	b;
	size_t	l;
	char	c;

	b = 1;
	l = 0;
	while (b)
	{
		b = read(fd, &c, 1);
		l++;
	}
	return (l);
}

/* 
	Liberar memoria despues de usar!!!!!!!
*/
char	*file_txt(char *filename)
{
	ssize_t	b;
	size_t	l;
	char	*txt;
	int		fd;

	b = 1;
	l = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	l = file_len(fd);
	close(fd);
	txt = (char *) malloc(l + 1);
	if (!txt)
		return (NULL);
	fd = open(filename, O_RDONLY);
	read(fd, txt, l + 1);
	close(fd);
	txt[l] = 0;
	return (txt);
}
