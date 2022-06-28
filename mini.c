/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:31:22 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/27 21:28:10 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	char	*str;
	t_list	*head;

	head = NULL;
	while (1)
	{
		str = readline("Minishell@adza:");
		if (str)
			check_token(str, &head);
		delete_list(&head, head);
		head = NULL;
	}
}
