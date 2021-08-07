#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define ERROR -1
# define FAULT 0
# define SUCCESS 1

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

int		error_free(char **buf);
int		all_error_free(char **s1, char **s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);

#endif