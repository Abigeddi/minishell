/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:24:33 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/23 01:34:22 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_node(char *str, int flag)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = flag;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_back(t_list **head, char *str, int flag)
{
	t_list	*tmp;
	t_list	*ptr;

	tmp = new_node(str, flag);
	if (!*head)
		*head = tmp;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = tmp;
		tmp->prev = ptr;
	}
}

void	affich_node(t_list *head)
{
	t_list	*temp;

	temp = head;
	if (!head)
		printf("List is empty\n");
	else
	{
		temp = head;
		while (temp)
		{
			printf("[%d]=>[%s]\n", temp->type, temp->str);
			temp = temp->next;
		}
	}
}


void	delete_list(t_list **head, t_list *node)
{
	if (node == NULL)
		return ;
	delete_list(head, node->next);
	free(node);
}
