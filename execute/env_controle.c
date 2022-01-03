/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:07:33 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:07:47 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_controle.h"

static size_t	count_env_elements(t_env *env)
{
	size_t	i;
	t_env	*iter;

	i = 0;
	iter = env;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}

void	print_t_env(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter)
	{
		if (iter->value != NULL)
			printf("%s=%s\n", iter->name, iter->value);
		iter = iter->next;
	}
}

char	**env_from_t_env_to_2d_array(t_env *env)
{
	char	**res;
	size_t	size;
	t_env	*iter;
	char	*tmp;

	size = count_env_elements(env);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = NULL;
	size = 0;
	iter = env;
	while (iter)
	{
		tmp = ft_strjoin(iter->name, "=");
		res[size] = ft_strjoin(tmp, iter->value);
		size++;
		free(tmp);
		iter = iter->next;
	}
	return (res);
}

char	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(key, env->name) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	free_2d_array(char ***arr)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *arr;
	while (tmp[i] != NULL)
	{
		if (tmp[i])
			free(tmp[i]);
	}
	free(tmp);
}
