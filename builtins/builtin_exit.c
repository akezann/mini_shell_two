/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:04:47 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:04:51 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	count_args(char **args)
{
	int		res;

	res = 0;
	while (args[res])
		res++;
	return (res);
}

static int	is_numeric(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/*
** @breif	: exits with passed argument
** @param	: args: list of arguments passed
** @return	: exit status
*/

int	builtin_exit(char **args)
{
	printf("exit\n");
	if (count_args(args) < 2)
		exit (0);
	else if (is_numeric(args[1]))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		exit (255);
	}
	else if (count_args(args) > 2)
		printf("exit: too many arguments\n");
	else
		exit (ft_atoi(args[1]));
	return (EXIT_FAILURE);
}
