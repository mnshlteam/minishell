/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:13:08 by hyejo             #+#    #+#             */
/*   Updated: 2022/09/05 17:00:00 by hyejo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parse 함수에서 echo를 만나면 ms_echo 함수를 호출한다.
// parse 함수가 입력받은 문자열을 ft_split() 함수를 이용해
// 공백을 기준으로 나누고 나눈 문자열을 ms_echo가 입력으로 받아 출력한다.

#include "minishell.h"

void	ms_echo(char **strs)
{
	char	**words;
	char	**tmp;

	while (*strs)
	{
		if (**strs == '$')
		{
			words = ft_split(*strs, '$');
			tmp = words;
			while (*tmp)
			{
				printf("%s", ms_getenv(*tmp));
				free(*tmp);
				tmp++;
			}
			free(words);
		}
		else
			printf("%s", *strs);
		if (*(strs + 1))
			printf(" ");
		strs++;
	}
	printf("\n");
}
