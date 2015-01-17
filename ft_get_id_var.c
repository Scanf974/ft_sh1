/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_id_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 05:59:19 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/15 23:25:32 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_get_id_var(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], var, ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}
