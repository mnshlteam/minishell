/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:43:49 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/23 15:30:09 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_quote_after_dollar(char **cmd)
{
	int	i;
	int	quote;

	i = 0;
	quote = ms_quote_status(**cmd, 0);
	if (quote)
	{
		while (quote)
			quote = ms_quote_status((*cmd)[++i], quote);
		return (i);
	}
	return (0);
}

static char	*ms_replace_dollar(char **cmd)
{
	char	*tmp;
	char	*str;
	int		i;

	(*cmd)++;
	i = ms_quote_after_dollar(cmd);
	if (i > 0)
		return (NULL);
	else if (**cmd == '?')
	{
		(*cmd)++;
		return (ft_itoa(g_config.exit_status));
	}
	while (ft_isalnum((*cmd)[i]) || (*cmd)[i] == '_')
		i++;
	tmp = ft_substr(*cmd, 0, i);
	*cmd += i;
	if (!ft_strlen(tmp))
		str = ft_strdup("$");
	else
		str = ft_strdup(ms_getenv(tmp));
	free(tmp);
	return (str);
}

static char	*ms_parse_dollar_str(char *cmd, int quote)
{
	char	*str;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	if (*cmd == '$')
		return (ms_strjoin_free(ms_replace_dollar(&cmd), \
			ms_parse_dollar_str(cmd, quote)));
	while (cmd[i])
	{
		quote = ms_quote_status(cmd[i], quote);
		if (cmd[i] == '$' && quote != 1)
		{
			str = ft_substr(cmd, 0, i);
			cmd += i;
			return (ms_strjoin_free(str, ms_parse_dollar_str(cmd, quote)));
		}
		i++;
	}
	return (ft_strdup(cmd));
}

void	ms_parse_dollar(t_cmd *cmd)
{
	char	*str;

	str = ms_parse_dollar_str(cmd->str, 0);
	free(cmd->str);
	cmd->str = str;
}
