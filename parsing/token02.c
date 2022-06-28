/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:44:42 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/27 21:28:45 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	take_dquote(char *str, t_list **head)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	ajoute_elm(str, str + 1, DQUOTE, head);
	str++;
	while (str[i] != '\"' && str[i])
	{
		if (str[i] == '$')
		{
			if (i != 0)
			{
				ajoute_elm(str + last, str + i, WORD, head);
				i += take_qvar(str + i, head) - 1;
			}
			else
				i += take_qvar(str, head) - 1;
			last = i;
		}
		i++;
	}
	last = check_closed_dq(str, i, last, head);
	return (last);
}

int	take_qvar(char *str, t_list **head)
{
	char	*comp;
	int		i;
	int		j;

	i = 1;
	comp = "!@#$+-./, \t\r\f\v\n\"";
	while (str[i++])
	{
		j = 0;
		while (comp[j++])
			if (str[i] == comp[j])
				return (ajoute_elm(str, str + i, VAR, head), i);
	}
	return (i);
}

int	check_closed_dq(char	*str, int i, int last, t_list **head)
{
	if (str [i] == '\"' && last == 0)
	{
		ajoute_elm(str, str + i, WORD, head);
		ajoute_elm(str + i, str + i + 1, DQUOTE, head);
	}
	else if (str [i] == '\"' && last != 0)
	{
		ajoute_elm(str + last + 1, str + i, WORD, head);
		ajoute_elm(str + i, str + i + 1, DQUOTE, head);
	}
	else if (!str[i])
		return (unclosed_quote(head), i + 1);
	return (i + 2);
}

void	unclosed_quote(t_list **head)
{
	delete_list(head, *head);
	printf("unclosed quote\n");
	*head = NULL;
}
