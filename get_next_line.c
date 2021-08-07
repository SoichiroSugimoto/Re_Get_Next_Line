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

int	free_join(char **dst, char **src1, char **src2)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(*src1))
		*src1 = "";
	tmp = *dst;
	*dst = ft_strjoin(*src1, *src2);
	// error_free(&tmp);
	// all_error_free(src1, src2);
	if (dst == NULL)
		return (ERROR);
	else
		return (SUCCESS);
}

int	cpy_line(char ***line, char **save, char **buf)
{
	int		i;
	int		len;
	char	*emp;
	char	*tmp;

	i = 1;
	emp = "";
	len = find_newline_code(*save) + 1;
	if (find_newline_code(*save) == -2)
	{
		// printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		len = ft_strlen(*save) + 1;
		if (ft_strlen(*save) == 0)
			len = 0;
		i = 0;
	}
	**line = (char *)malloc(sizeof(char) * len);
	if (**line == NULL)
		return (all_error_free(buf, save));
	// printf("+++++++++++++++++++++++++len:    %d++++++++++++++++++++++++++++++++\n", len);
	ft_strlcpy(**line, *save, len);/////
	tmp = *save;
	*save = ft_strjoin(*(save) + len, emp);
	if (*save == NULL)
		return (all_error_free(buf, save));
	// printf("        emp: %zu\n", ft_strlen(emp));//////////////////
	error_free(&tmp);
	return (i);
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		*buf;
	int			i;
	size_t		size;

	size = 1;
	i = 0;
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line || BUFFER_SIZE <= 0 || fd < 0 || buf == NULL)
		return (ERROR);
	while (find_newline_code(save) < 0 && size > 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if ((int)size == -1)
			return (all_error_free(&buf, &save));
		buf[size] = '\0';
		i = free_join(&save, &save, &buf);
		if (i == -1)
			return (all_error_free(&buf, &save));
	}
	error_free(&buf);
	// printf("<<<<<save>>>>>: %s\n", save);
	return (cpy_line(&line, &save, &buf));
}
