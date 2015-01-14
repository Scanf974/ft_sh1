/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 07:58:27 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/14 05:02:37 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static int	ft_nbenv(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static char	**ft_realloc_env(char **env, int id)
{
	int		i;
	int		j;
	int		nb_env;
	char	**new_env;

	i = 0;
	nb_env = ft_nbenv(env);
	new_env = (char **)malloc(sizeof(char *) * (nb_env + 1));
	while (env[i] && i < id)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	j = i;
	i++;
	while (env[i])
	{
		new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	i = 0;
	return (new_env);
}

int			ft_unsetenv(char ***env, char *del)
{
	int		id;
	int		nb_env;

	id = 0;
	nb_env = ft_nbenv(*env);
	if (!ft_strlen(del))
		return (0);
	if (ft_onlyesp(del))
		ft_putendl("unset: not enought arguments");
	del = ft_strtrim_new(del);
	while (*del)
	{
		while (*del <= ' ')
			del++;
		while ((*env)[id] && !ft_strnequ((*env)[id],
					ft_strjoin(del, "="), ft_strlen_esp(del) + 1))
			id++;
		if (id < nb_env)
			*env = ft_realloc_env(*env, id);
		else
			return (-1);
		del += ft_strlen_esp(del);
	}
	return (0);
}
