#include "ft_minishell1.h"

char	*ft_getpath_pwd(char *path)
{
	char	*dst;
	int		i;
	int		j;

	dst = ft_strdup(ft_pwd());
	i = ft_strlen(dst) - 1;
	j = ft_strlen(path) - 1;
	while (i >= 0 && j >= 0)
	{
		dst[i] = '\0';
		i--;
		j--;
	}
	return (dst);
}
