#include "get_next_line.h"

int	find_newline_code(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ERROR);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	if (str[i] == '\0')
		return (-2);
	return (ERROR);
}

int	free_join(char **dst, char **src, int n)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(*dst))
		*dst = "";
	if (!(*src))
		*src = "";
	tmp = *dst;
	*dst = ft_strjoin(*dst, *src);
	if (n != 0)
		error_free(&tmp);
	if (dst == NULL)
		return (ERROR);
	else
		return (SUCCESS);
}

int	len_cpy_line(char *save)
{
	int	len;

	len = find_newline_code(save) + 1;
	if (len > (int)ft_strlen(save))
		len = (int)ft_strlen(save);
	if (find_newline_code(save) == -2)
		len = ft_strlen(save) + 1;
	if (find_newline_code(save) == -2 && ft_strlen(save) == 0)
		len = 0;
	return (len);
}

int	cpy_line(char ***line, char **save)
{
	int		i;
	int		l1;
	int		l2;
	char	*tmp;

	i = 1;
	l1 = len_cpy_line(*save);
	l2 = len_cpy_line(*save);
	if (l2 == 0)
		l2 = 1;
	if (find_newline_code(*save) == -2)
		i = 0;
	**line = (char *)malloc(sizeof(char) * l2);
	if (**line == NULL)
		return (error_free(save));
	ft_strlcpy(**line, *save, l2);
	tmp = *save;
	if (find_newline_code(*save) == -2)
		l1 = ft_strlen(*save);
	*save = ft_strjoin(*(save) + l1, "");
	if (*save == NULL)
		return (ERROR);
	error_free(&tmp);
	return (i);
}

int	get_next_line(int fd, char **line)
{
	static char		*save;
	static int		n;
	char			*buf;
	int				i;
	size_t			size;

	size = 1;
	i = 0;
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line || BUFFER_SIZE <= 0 || fd < 0 || buf == NULL)
		return (error_free(&buf));
	while (find_newline_code(save) < 0 && size > 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if ((int)size == -1)
			return (error_free(&buf));
		buf[size] = '\0';
		i = free_join(&save, &buf, n);
		if (i == -1)
			return (error_free(&save));
		n++;
	}
	if (n != 0)
		error_free(&buf);
	return (cpy_line(&line, &save));
}
