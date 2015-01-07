#include "ft_minishell1.h"

char	*ft_strtrim_new(char const *s)
{
	int		i;
	char	*tmp;

	tmp = (char *)s;
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
	}
	return (ft_strdup(&tmp[i]));
}
