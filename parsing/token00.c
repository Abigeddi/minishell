/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:25:33 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/28 00:52:19 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    check_token(char *str, t_list **head)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i += check_char(str + i, head);
	}
	if (*head)
	{
		check_syntax(head);
		delete_quotes(head);
	}
}
t_list	*link_nodes(t_list **head, t_list *deleted)
{
	t_list	*tmp;

	if (!deleted->prev)
	{
		*head = deleted->next;
		(*head)->prev = NULL;
		return (*head);
	}
	else if (!deleted->next)
	{
		tmp = deleted->prev;
		deleted->prev->next = NULL;
		return (tmp);
	}
	tmp = deleted->prev;
	deleted->next->prev = tmp;
	tmp->next = deleted->next;
	return (tmp);
}

void	delete_quotes(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == 7 || tmp->type == 8)
			tmp = link_nodes(head, tmp);
		tmp = tmp->next;
	}
}
int	check_char(char *str, t_list **head)
{
	if (*str == '$')
		return (take_variable(str, head));
	else if (*str == 60 || *str == 62)
		return (take_less(str, head));
	else if (*str == '|')
		return (ajoute_elm(str, str + 1, PIPE, head), 1);
	else if (*str == '\'' || *str == '\"')
		return (take_colon(str, head));
	else if ((*str >= 9 && *str <= 13) || (*str == 32))
		return (take_space(str, head));
	else
		return (take_word(str, head));
	return (0);
}

int	take_space(char *str, t_list **head)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	ajoute_elm(str, str + i, WSPACE, head);
	return (i);
}
int	take_word(char *str, t_list **head)
{
	int		j;
	char	*comp;
	int		i;

	i = 0;
	comp = "|\'\"$*<> \t\r\f\v\n";
	while (str[i])
	{
		j = 0;
		while (comp[j])
		{
			if (str[i] == comp[j])
			{
				ajoute_elm(str, str + i, WORD, head);
				return (i);
			}
			j++;
		}
		i++;
	}
	ajoute_elm(str, str + i, WORD, head);
	return (i);
}
