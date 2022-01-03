/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:05:06 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:05:47 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	export_display(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter)
	{
		if (ft_strcmp(iter->name, "_") != 0)
		{
			if (iter->value != NULL)
				printf("declare -x %s=\"%s\"\n", iter->name, iter->value);
			else
				printf("declare -x %s\n", iter->name);
		}
		iter = iter->next;
	}
}

int	builtin_export(t_env **env, char **args)
{
	size_t	i;

	i = 1;
	if (!args[1])
		export_display(*env);
	else
	{
		while (args[i])
		{
			if (ft_strcmp(args[i], "+=") == 0)
				printf("export: `+=': not a valid identifier\n");
			else if (env_element_exits(*env, args[i]) == FALSE)
				env_add_element(env, args[i]);
			else
				env_replace_element(env, args[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
