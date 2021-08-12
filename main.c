#include "get_next_line.h"

// void	safe_free2(char **st)
// {
// 	free(*st);
// 	*st = NULL;
// }

int	main(void)
{
	char	*line = 0;
	int		n;
	int		fd;

	n = 0;
	fd = open("test.txt", O_RDONLY);
	while (n > -1)
	{
		n = get_next_line(fd, &line);
		printf("|%d  %s\n", n, line);
		free(line);
		if (n == 0)
		{
			printf("[[[[[[[[[end]]]]]]]]]\n\n");
			break ;
		}
	}

	n = 0;
	fd = open("test.txt", O_RDONLY);
	while (n > -1)
	{
		n = get_next_line(fd, &line);
		printf("|%d  %s\n", n, line);
		free(line);
		if (n == 0)
		{
			printf("[[[[[[[[[end]]]]]]]]]\n\n");
			break ;
		}
	}
	// system("leaks a.out");
}
