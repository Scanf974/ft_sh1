/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 04:18:51 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/17 08:59:02 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static void	ft_print_env(char **env)
{
	int		i;

	i = 0;
	while (env[i] && (*env)[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

static int	ft_nique(char **tab, int i)
{
	if (tab[i][1] != 'i')
	{
		ft_putendl_fd("env: illegal option ON VERRA", 2);
		return (-1);
	}
	return (0);
}

int			ft_env(char ***env, char *after, char **path, int rt)
{
	int		i;
	char	**tab;
	char	**nl;

	i = 0;
	nl = *env;
	if (!(*env))
		return (-1);
	tab = ft_strsplit_white_space(after);
	if (tab[0])
	{
		while (tab[i] && tab[i][0] == '-')
		{
			nl = NULL;
			if (ft_nique(tab, i) == -1)
				return (-1);
			i++;
		}
		if (tab[i])
			return (ft_what(ft_strstr(after, tab[i]), &nl, path, rt));
	}
	if (ft_nb_env(tab) < 2)
		ft_print_env(*env);
	return (0);
}
