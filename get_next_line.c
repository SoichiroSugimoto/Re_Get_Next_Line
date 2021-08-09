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
	if (find_newline_code(save) == -2)
		len = ft_strlen(save) + 1;
	return (len);
}

int	cpy_line(char ***line, char **save, char **buf, int n)
{
	int		i;
	int		len;
	char	*tmp;

	i = 1;
	len = len_cpy_line(*save);
	if (find_newline_code(*save) == -2)
		i = 0;
	**line = (char *)malloc(sizeof(char) * len);
	if (**line == NULL)
		return (all_error_free(buf, save));
	ft_strlcpy(**line, *save, len);
	tmp = *save;
	if (find_newline_code(*save) != -2)
	{
		*save = ft_strjoin(*(save) + len, "");
		if (*save == NULL)
			return (error_free(buf));
	}
	if (n != 0)
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
			return (all_error_free(&buf, &save));
		n++;
	}
	error_free(&buf);
	return (cpy_line(&line, &save, &buf, n));
}
