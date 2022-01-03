/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:05:14 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:05:41 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(t_env *env)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		tmp = env_find(env, "PWD");
	printf("%s\n", tmp);
	return (EXIT_SUCCESS);
}
