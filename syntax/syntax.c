/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:13:51 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/28 00:06:25 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax(t_list **head)
{
	t_list	*temp;

	if ((*head)->type == 6 && (*head)->next)
		temp = (*head)->next;
	else if ((*head)->type != 6)
		temp = *head;
	else
		return 0;
	if (!check_begin(temp))
		return ((void)(syntax_error(head)), 0);
	while (temp)
	{
		if (!check_list(temp))
			return ((void)(syntax_error(head)), 0);
		temp = get_right(temp);
	}
	return (1);
}

int	check_begin(t_list *head)
{
	if (head->type >= VAR && head->type <= DQUOTE)
		return (1);
	else
		return (0);
}

void	syntax_error(t_list **head)
{
	printf("syntax Eroor\n");
}

int	check_list(t_list *head)
{
	if (head->type == 9)
		return (check_wp(head));
	else if (head->type >= 1 && head->type <= 4)
		return (check_red(head));
	return (1);
}
int	check_wp(t_list *head)
{
	t_list	*t;

	t = get_right(head);
	if (!t)
		return (0);
	if (t->type == 9)
		return (0);
	return (1);
}

int	check_red(t_list *head)
{
	t_list	*t;

	t = get_right(head);
	if (!t)
		return (0);
	if ((!(t->type >= 5 && t->type <= 8) && (t->type != 0)))
		return (0);
	return (1);
}

t_list	*get_right(t_list *head)
{
	if (head->next && head->next->type == 6)
	{
		if (head->next->next)
			return (head->next->next);
		else
			return (NULL);
	}
	else
		return (head->next);
}

t_list	*get_left(t_list *head)
{
	if (head->prev && head->prev->type == 6)
	{
		if (head->prev->prev)
			return (head->prev->prev);
		else
			return (NULL);
	}
	else
		return (head->prev);
}

