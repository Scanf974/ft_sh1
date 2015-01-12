#include "ft_minishell1.h"

char	*ft_strtrim_new(char const *s)
{
	int		i;
	char	*tmp;
	char	*dst;

	tmp = (char *)s;
	dst = NULL;
	i = 0;
	if (tmp)
	{
		i = ft_strlen(s) - 1;
		while (i >= 0 && tmp[i] <= ' ')
		{
			tmp[i] = '\0';
			i--;
		}
		i = 0;
		while (tmp[i] && tmp[i] <= ' ')
			i++;
		dst = ft_strdup(&tmp[i]);
	}
	return (dst);
}
