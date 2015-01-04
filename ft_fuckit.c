/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fuckit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 01:27:35 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 01:41:37 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char                *ft_fuckit(char *s)
{
	char            *new;
	int             i;
	int             j;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(s));
	while (s[i])
	{
		if (s[i] <= ' ' && new[j - 1] != ' ')
		{
			new[j] = ' ';
			i++;
			j++;
		}
		else if (s[i] <= ' ')
			i++;
		else
		{
			new[j] = s[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}
