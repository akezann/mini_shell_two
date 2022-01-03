/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:05:31 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:05:38 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	find_element(t_env *env, char *arg)
{
	while (env)
	{
		if (ft_strcmp(env->name, arg) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

int	builtin_unset(t_env **l_env, char **args)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		if (find_element(*l_env, args[i]) == TRUE)
			env_delete_element_at(l_env, env_find_index(*l_env, args[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}
