/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 04:18:51 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 00:33:24 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_env(char **env, char *after)
{
	int		i;

	i = 0;
	if (!env)
		return (-1);
	if (ft_onlyesp(after))
	{
		while (env[i])
		{
			ft_putendl(env[i]);
			i++;
		}
	}
	return (0);
}
