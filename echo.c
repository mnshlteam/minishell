/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:13:08 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/24 20:11:27 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_echo_n(char *str, int *n)
{
	int	i;

	*n = 0;
	if (*str != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	*n = 1;
	return (1);
}

void	ms_echo(char **strs)
{
	int	n;

	if (ms_echo_n(*strs, &n))
		strs++;
	else
		n = 0;
	while (*strs)
	{
		printf("%s", *strs);
		if (*(strs + 1))
			printf(" ");
		strs++;
	}
	if (n == 0)
		printf("\n");
}
