/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsautron <bsautron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:22:51 by bsautron          #+#    #+#             */
/*   Updated: 2015/01/03 02:34:11 by bsautron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL1
# define FT_MINISHELL1

# include <sys/stat.h>
# include <dirent.h>
# include "libft.h"
# include "get_next_line.h"

char	*ft_prompt(char **env, int ret);
char	**ft_getpath(char **env);
char	*ft_getdir(char *path);
char	*ft_getpath_pwd(char *path);
int		ft_env(char **env, char *after);
int		ft_cmd(char **env);
int		ft_cd(char ***env, char *path);
char	ft_onlyesp(char *str);
char	*ft_pwd(void);
int		ft_get_id_var(char **env, char *var);
int		ft_setenv(char ***env, char *xport);
int		ft_unsetenv(char ***env, char *xport);
int		ft_cmd_is_in_path(char *cmd, char *path);
char	*ft_getcmd(char *cmd);
char	**ft_strsplit_white_space(char const *s);
char	*ft_fuckit(char *s);
int		ft_exec(char *bin, char *cmd, char **env);
int		ft_nb_env(char **env);
char	*ft_strtrim_new(char const *s);

#endif
