/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:13:08 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/21 18:13:33 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parse 함수에서 echo를 만나면 ms_echo 함수를 호출한다.
// parse 함수가 입력받은 문자열을 ft_split() 함수를 이용해
// 공백을 기준으로 나누고 나눈 문자열을 ms_echo가 입력으로 받아 출력한다.

#include "minishell.h"

void	ms_echo(char **strs)
{
	int	n;

	if (ft_strncmp(*strs, "-n", 3) == 0)
	{
		n = 1;
		strs++;
	}
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
