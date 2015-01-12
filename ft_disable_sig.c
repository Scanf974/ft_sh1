#include "ft_minishell1.h"

void	ft_disable_sig(void)
{
	int		i;

	i = 1;
	while (i <= 31)
	{
		signal(i, SIG_IGN);
		i++;
	}
}
