/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akezanna <akezanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:20:32 by yait-kad          #+#    #+#             */
/*   Updated: 2022/01/03 15:17:17 by akezanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*treat_quotes(int *index, char *line, char type)
{
	char	*double_quote;
	int		backslash;
	int		j;
	int		i;

	i = *index;
	j = i;
	j++;
	while (line[j] != '\0' && line[j] != type)
	{
		if (line[j] == '\\')
		{
			backslash = check_backslash(line, j);
			if (backslash % 2 != 0)
				j = j + backslash;
			else
				j = j + backslash - 1;
			backslash = 0;
		}
		j++;
	}
	double_quote = ft_substr(line, i, (j - i + 1));
	*index = j;
	return (double_quote);
}

void	quotes(char **token, int *k, char *line, char type)
{
	char	*trt;
	char	*tmp;
	int		i;

	i = *k;
	trt = treat_quotes(&i, line, type);
	tmp = ft_strjoin(*(token), trt);
	free(*(token));
	*(token) = tmp;
	free(trt);
	*k = i;
}

char	*get_word(char *line, int *k)
{
	char	*token;
	int		backslash;
	int		i;

	token = ft_strdup("");
	backslash = 0;
	i = *k;
	while ((line[i] != '\0') && (ft_strchr("|;> <\t", line[i]) == NULL))
	{
		backslash = check_backslash(line, i);
		if (backslash % 2 != 0)
			backslash_impair(line, &token, &i, &backslash);
		else if (line[i] == '"' || line[i] == '\'')
			quotes(&token, &i, line, line[i]);
		else
		{
			if (backslash > 0)
				backslash_exist(line, &token, &i, &backslash);
			else
				backslash_not_exist(line, &token, &i);
		}
		i++;
	}
	*k = i;
	return (token);
}
