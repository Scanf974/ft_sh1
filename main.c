/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:21:58 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 02:22:41 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		main(int argc, char **argv, char **env)
{
	char			**saint_env;
	int				fd = STDOUT_FILENO;
	struct termios	term_attributes;

	(void)argc;
	(void)argv;
	ft_putendl("                         @EEEEEEEEEEEEESSEQ.");
	ft_putendl("                         EEEEEEEEEEEEEEEEE3L");
	ft_putendl("                        JEEEEEEEEEEEEEEEEEE[");
	ft_putendl("                        {EEEEEEEEEEEEEEEEEE1");
	ft_putendl("                        @EEEEEEEEEEEEEEEEEEQ.");
	ft_putendl("                  `*G@EEEEEEEEEEEEEEEEEEEEEEEEEEP*");
	ft_putendl("                        J1:::z:=c.;.=::z::JL");
	ft_putendl("                       E3@sSSSSS@sz@SSSSSb@Ed.");
	ft_putendl("                       \\3E$EEEEEEF3EEEEEEZQE[");
	ft_putendl("                        V$?5GGGRF::?5GGGP5$Q.:");
	ft_putendl("                        '$c..:.z:::::..:.:$F");
	ft_putendl("                          E)::;;Z2H5L;.;:3.");
	ft_putendl("                          J1J3E5E5EE51t[!F");
	ft_putendl("                           \"[L:::::.:::yF");
	ft_putendl("                             *c::::::;*");
	ft_putendl("                               `^**^`");
	saint_env = (char **)malloc(sizeof(char *) * 2);
	//ft_disable_sig();

	if (!isatty(fd))
		return(1);
	else
	{
		if (tcgetattr(fd, &term_attributes) != 0)
		{
			perror("tcgetattr error");
			return(EXIT_FAILURE);
		}
		term_attributes.c_lflag = term_attributes.c_lflag & ~ICANON;
		term_attributes.c_lflag = term_attributes.c_lflag & ~ECHO;
		term_attributes.c_cc[VMIN] = 1;
		term_attributes.c_cc[VTIME] = 0;
		if (tcsetattr(fd, TCSADRAIN, &term_attributes) == -1)
		{
			perror("tcsetattr");
			return (1);
		}

	}

	if (ft_nb_env(env))
	{
		ft_setenv(&env, "OLDPWD= ");
		ft_cmd(env);
	}
	else
	{
		ft_setenv(&saint_env, "PWD=/Volumes/Data/nfs/zfs-student-3/users/2014/bsautron/Semestre01/ft_sh1");
		ft_setenv(&saint_env, "USER=bsautron");
		ft_setenv(&saint_env, "PATH=/bin:/usr/bin");
		ft_cmd(saint_env);
	}
	term_attributes.c_lflag = term_attributes.c_lflag | ICANON;
	term_attributes.c_lflag = term_attributes.c_lflag | ECHO;
	if (tcsetattr(fd, TCSADRAIN, &term_attributes) == -1)
	{
		perror("tcsetattr");
		return (1);
	}

	return (0);
}
