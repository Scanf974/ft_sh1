/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 05:51:18 by bsautron          #+#    #+#             */
/*   Updated: 2014/12/26 07:09:32 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char	*ft_pwd(void)
{
	char	dir[1024];

	if (getcwd(dir, sizeof(dir)) != NULL)
		return (ft_strdup(dir));
	return (NULL);
}
