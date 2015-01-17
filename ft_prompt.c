/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/14 02:25:46 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/17 00:49:05 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"
#define NIQUE	char **history, char *cmd_saved, char *cmd

static void	ft_prompt2(char **env, int ret, int id_usr)
{
	if (ret == 0)
	{
		ft_putchar(-30);
		ft_putchar(-98);
		ft_putchar(-100);
		ft_putchar(' ');
		ft_putstr("\033[1;30;47m");
	}
	else
	{
		ft_putstr("\x1b[31m");
		ft_putchar(-30);
		ft_putchar(-98);
		ft_putchar(-100);
		ft_putchar(' ');
		ft_putstr("\033[1;31;47m");
	}
	if (id_usr != -1 && ft_strequ(ft_get_dirname(), &env[id_usr][5]))
		ft_putstr("~");
	else
		ft_putstr(ft_get_dirname());
	ft_putstr("\033[0;37;40m ");
}

static void	ft_increm(int *i, int nb, char c)
{
	if (c == 'A')
	{
		(*i)--;
		if (*i < 0)
			*i = 0;
	}
	if (c == 'B')
	{
		(*i)++;
		if (*i > nb)
			*i = nb;
	}
}

static char	*ft_increm2(char c, NIQUE, int *i, int nb)
{
	if (c == 'A' || c == 'B')
	{
		if (c == 'A')
		{
			while (*i > 0
				&& (!ft_strnequ(cmd_saved, history[*i], ft_strlen(cmd_saved))
				|| ft_onlyesp(history[*i]) || ft_strequ(cmd, history[*i])))
				(*i)--;
		}
		else
		{
			while (*i < nb
				&& (!ft_strnequ(cmd_saved, history[*i], ft_strlen(cmd_saved))
				|| ft_onlyesp(history[*i]) || ft_strequ(cmd, history[*i])))
				(*i)++;
		}
		if (history[*i] && ft_strnequ(cmd_saved, history[*i],
					ft_strlen(cmd_saved)))
			cmd = ft_strdup(history[*i]);
		else
			cmd = ft_strdup(cmd_saved);
	}
	ft_putstr(cmd);
	return (cmd);
}

static char	*ft_gnlr(char *path_h, char *cmd, char *cmd_saved)
{
	int			nb;
	char		c[2];
	char		cac;
	int			i;
	char		**history;

	nb = 0;
	history = ft_make_history(&nb, &i, path_h);
	while (read(0, &cac, 1) != 0 && cac != '\n')
	{
		if (cac == '\033')
		{
			read(0, c, 1);
			read(0, c, 1);
			ft_increm(&i, nb, *c);
			ft_nclear(ft_strlen(cmd));
			cmd = ft_increm2(*c, history, cmd_saved, cmd, &i, nb);
		}
		else
		{
			cmd = ft_join_or_del(cmd, c, cac);
			cmd_saved = ft_strdup(cmd);
		}
	}
	return (cmd);
}

char		*ft_prompt(char **env, int ret)
{
	char			*cmd;
	char			*cmd_saved;
	int				id_usr;
	int				fd;
	char			*path_h;

	path_h = ft_strdup(".ft_minishell1_history");
	if (ft_get_id_var(env, "HOME") != -1)
		path_h = ft_strjoin(&env[ft_get_id_var(env, "HOME")][5],
				"/.ft_minishell1_history");
	id_usr = ft_get_id_var(env, "USER");
	ft_prompt2(env, ret, id_usr);
	cmd = ft_strnew(1);
	cmd_saved = ft_strnew(1);
	cmd = ft_gnlr(path_h, cmd, cmd_saved);
	ft_putchar('\n');
	fd = open(path_h, O_WRONLY | O_APPEND);
	free(path_h);
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
	close(fd);
	return (cmd);
}
