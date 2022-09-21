/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:24:45 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/21 20:46:48 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_export_error(char *str)
{
	int		i;

	if (*str == '=')
	{
		ms_print_error("export: `", str, "': not a valid identifier\n", 0);
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		else if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ms_print_error("export: `", str, "': not a valid identifier\n", 0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ms_unset_error(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ms_print_error("unset: `", str, "': not a valid identifier\n", 0);
			return (1);
		}
		i++;
	}
	return (0);
}
