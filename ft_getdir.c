#include "ft_minishell1.h"

char	*ft_getdir(char *path)
{
	char	*dst;
	int		i;

	i = ft_strlen(path) - 1;
	dst = ft_strdup(path);
	while (i >= 0 && path[i] != '/')
		i--;
	dst[i] = '\0';
	return (dst);
}
