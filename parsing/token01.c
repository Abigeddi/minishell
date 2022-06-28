/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:06:17 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/28 00:55:04 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	take_variable(char *str, t_list **head)
{
	char	*cmp;
	int		i;
	int		j;
	
	i = 1;
	cmp = "|\'\"$<> \t\r\f\v\n";
	while (str[i])
	{
		j = 0;
		while (cmp[j])
			{
				if (str[i] == cmp[j])
				{
					ajoute_elm(str, str + i, VAR, head);
					return (i);
				}
				j++;
			}
		i++;
	}
	ajoute_elm(str, str + i, VAR, head);
	return (i);
}

int	take_less(char *str, t_list **head)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (ajoute_elm(str, str + 2, DLESS, head), 2);
		else
			return (ajoute_elm(str, str + 1, LESS, head), 1);
	}
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (ajoute_elm(str, str + 2, DGREAT, head), 2);
		else
			return (ajoute_elm(str, str + 1, GREAT, head), 1);
	}
	return (0);
}

int	take_colon(char *str, t_list **head)
{
	int	i;

	i = 0;
	if (*str == '\"')
		return (take_dquote(str, head));
	ajoute_elm(str, str + 1, SQUOTE, head);
	str++;
	while (str[i] != '\'' && str[i])
		i++;
	if (str[i] == '\'')
	{
		ajoute_elm(str, str + i, WORD, head);
		ajoute_elm(str + i, str + i + 1, SQUOTE, head);
	}
	else if (!str[i])
		return (unclosed_quote(head), (i + 1));
	return (i + 2);
}

int	calcul_size(char *start, char *end)
{
	int	i;

	i = 1;
	while (start++ != end)
		i++;
	return (i);
}

void	*ajoute_elm(char *start, char *end, int flag, t_list **head)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(calcul_size(start, end));
	if (!str)
		return (NULL);
	while (start != end)
		str[i++] = *(start++);
	str[i++] = 0;
	add_back(head, str, flag);
	return (NULL);
}
