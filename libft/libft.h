#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

size_t	ft_strlen(const char *s);
size_t	ft_strslen(char **strs);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrimchr(const char *str, char c);
char	*ft_strupdate(char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_freestrs(char **arr);
int		ft_open(char *path, int flags);
int		ft_print_error(char *message, int print_error, char *path, int err);
void	ft_freestrarrs(char ***arr);
void	ft_print_pipe(int len);

#endif
