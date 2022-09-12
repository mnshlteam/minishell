/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 15:34:48 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/12 18:48:51 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_replace_quotes(char **input)
{
	char	*str;

	if (**input != '\'' && **input != '\"')
		return (*input);
	str = ft_substr(*input, 1, ft_strlen(*input) - 2);
	free(*input);
	return (str);
}

char	*ms_parse_quotes(char *str)
{
	int		quote[2];
	int		i;
	char	*s1;
	char	*s2;

	quote[0] = 0;
	i = 0;
	while (str[i])
	{
		quote[1] = ms_quote_status(str[i], quote[0]);
		if (quote[0] != quote[1] && i)
		{
			if (quote[1] < quote[0])
				i++;
			s1 = ft_substr(str, 0, i);
			s2 = ft_substr(str, i, ft_strlen(str) - i);
			s1 = ms_strjoin_free(ms_replace_quotes(&s1), \
				ms_parse_quotes(s2));
			free(s2);
			return (s1);
		}
		quote[0] = quote[1];
		i++;
	}
	return (ft_strdup(str));
}
