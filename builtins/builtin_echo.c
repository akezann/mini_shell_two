/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:04:07 by akezanna          #+#    #+#             */
/*   Updated: 2022/01/03 15:06:21 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static size_t	check_n(char **args)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (args[++j])
	{
		i = 0;
		if (args[j][i] == '-')
		{
			i++;
			while (args[j][i] != '\0')
			{
				if (args[j][i] != 'n')
					return (j);
				i++;
			}
		}
		else
			return (j);
	}
	return (j);
}

int	is_null_or_empty(char *str)
{
	if (str == NULL || str[0] == '\0')
		return (TRUE);
	return (FALSE);
}

int	builtin_echo(char **args)
{
	size_t	i;

	i = check_n(args);
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (is_null_or_empty(args[i]) != TRUE && args[i + 1])
			write(1, " ", 1);
		i++;
	}
	i = check_n(args);
	if (i == 1)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
