/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:10:29 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:10:34 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	is_dir(char *path)
{
	struct stat		path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

static char	*set_path(char *command, char *all_bin)
{
	char	*tmp;
	int		size;

	size = ft_strlen(command) + ft_strlen(all_bin) + 1;
	tmp = (char *)malloc(size + 1);
	ft_strlcpy(tmp, all_bin, ft_strlen(all_bin) + 1);
	ft_strlcat(tmp, "/", ft_strlen(tmp) + 2);
	ft_strlcat(tmp, command, ft_strlen(tmp) + ft_strlen(command) + 1);
	return (tmp);
}

static char	**bring_all_paths(t_env *env)
{
	char	*bin;

	bin = env_find(env, "PATH");
	if (!bin)
		return (NULL);
	return (ft_split(bin, ':'));
}

int	ft_execve(t_command *node, t_env **env)
{
	char	**all_bin;
	char	*path;
	char	**cc;
	int		i;

	cc = env_from_t_env_to_2d_array(*env);
	all_bin = bring_all_paths(*env);
	if (is_dir(node->command[0]))
		return (NOT_FILE);
	i = 0;
	if (is_null_or_empty(node->command[0]) != TRUE)
	{
		execve(node->command[0], node->command, cc);
		if (all_bin != NULL)
		{
			while (all_bin[i] != NULL)
			{
				path = set_path(node->command[0], all_bin[i]);
				execve(path, node->command, cc);
				free(path);
				i++;
			}
		}
	}
	return (EXIT_FAILURE);
}
