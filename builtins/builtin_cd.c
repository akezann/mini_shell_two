/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:03:57 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:05:52 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*set_path(t_env **env, char *line)
{
	char	*res;

	if (!line)
		res = env_find(*env, "HOME");
	else
		res = ft_strdup(line);
	return (res);
}

static char	*set_env_var(char *value, char *key)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

static void	insert(t_env **env, char *arg)
{
	if (env_element_exits(*env, arg) == FALSE)
		env_add_element(env, arg);
	else
		env_replace_element(env, arg);
}

static void	set_pwd(t_env **env, char *old_pwd, char *line)
{
	char	*pwd;
	char	*p;
	char	*op;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		pwd = ft_strjoin(old_pwd, ft_strjoin("/", line));
	p = set_env_var(pwd, "PWD");
	op = set_env_var(old_pwd, "OLDPWD");
	insert(env, p);
	insert(env, op);
	free(op);
	free(p);
	free(pwd);
}

int	builtin_cd(t_env **env, char *line)
{
	int		res;
	char	*path;
	char	*pwd;

	path = set_path(env, line);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		pwd = env_find(*env, "PWD");
	res = chdir(path);
	if (res == -1)
	{
		printf("cd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	else
		set_pwd(env, pwd, line);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		printf("cd: error retrieving current directory: getcwd:\
		cannot access parent directories:  %s\n", strerror(errno));
	free(path);
	if (res == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
