/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:45:02 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/28 09:21:34 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    token(char *str, t_list **head)
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


int	check_char(char *str, t_list **root)
{
	else if (*str == '$')
		return (take_var(str, root));
	else if (*str == 60 || *str == 62)
		return (take_less_more(str, root));
	else if (*str == '|')
		return (take_wp(str, root));
	else if (*str == '\'' || *str == '\"')
		return (take_colon(str, root));
	else if ((*str >= 9 && *str <= 13) || (*str == 32))
		return (take_space(str, root));
	else
		return (take_word(str, root));
	return (0);
}

int	take_word(char *str, t_list **root)
{
	int		j;
	char	*comp;
	int		i;

	i = -1;
	comp = "&|\'\"$*<>~ \t\r\f\v\n()";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (ajoute_elm(str, str + i, WORD, root), i);
	}
	return (ajoute_elm(str, str + i, WORD, root), i);
}

int	take_space(char *str, t_list **root)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	ajoute_elm(str, str + i, WSPACE, root);
	return (i);
}

int	take_var(char *str, t_list **root)
{
	char	*comp;
	int		i;
	int		j;

	i = 0;
	comp = "|\'\"$<> \t\r\f\v\n";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (ajoute_elm(str, str + i, VAR, root), i);
	}
	return (ajoute_elm(str, str + i, VAR, root), i);
}

int	take_dquote(char *str, t_list **root)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	ajoute_elm(str, str + 1, DQUOTE, root);
	str++;
	while (str[i] != '\"' && str[i])
	{
		if (str[i] == '$')
		{
			if (i != 0)
			{
				ajoute_elm(str + last, str + i, WORD, root);
				i += take_qvar(str + i, root) - 1;
			}
			else
				i += take_qvar(str, root) - 1;
			last = i;
		}
		i++;
	}
	last = check_closed_dq(root, str, i, last);
	return (last);
}

int	check_closed_dq(t_list **root, char	*str, int i, int last)
{
	if (str [i] == '\"' && last == 0)
	{
		ajoute_elm(str, str + i, WORD, root);
		ajoute_elm(str + i, str + i + 1, DQUOTE, root);
	}
	else if (str [i] == '\"' && last != 0)
	{
		ajoute_elm(str + last + 1, str + i, WORD, root);
		ajoute_elm(str + i, str + i + 1, DQUOTE, root);
	}
	else if (!str[i])
		return (unclosed_quote(root), i + 1);
	return (i + 2);
}

int	take_qvar(char *str, t_list **root)
{
	char	*comp;
	int		i = 0;
	int		j;

	comp = "!@#$+-./, \t\r\f\v\n\"";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (ajoute_elm(str, str + i, VAR, root), i);
	}
	return (i);
}

void	*ajoute_elm(char *start, char *end, int flag, t_list **root)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)malloc(calc_size(start, end));
	if (!str)
		return (NULL);
	while (start != end)
		str[++i] = *(start++);
	str[++i] = 0;
	append_in_end(root, str, flag);
	return (NULL);
}

int	take_less_more(char *str, t_list **root)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (ajoute_elm(str, str + 2, DLESS, root), 2);
		else
			return (ajoute_elm(str, str + 1, LESS, root), 1);
	}
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (ajoute_elm(str, str + 2, DGREAT, root), 2);
		else
			return (ajoute_elm(str, str + 1, GREAT, root), 1);
	}
	return (0);
}

int	take_wp(char *str, t_list **root)
{

	if (*str != *(str + 1))
		return (ajoute_elm(str, str + 1, check_flag(str, 1, root), root), 1);
    else
        return (printf("error", 1));
	return (0);
}

int	take_colon(char *str, t_list **root)
{
	int	i;

	i = 0;
	if (*str == '\"')
		return (take_dquote(str, root));
	ajoute_elm(str, str + 1, SQUOTE, root);
	str++;
	while (str[i] != '\'' && str[i])
		i++;
	if (str[i] == '\'')
	{
		ajoute_elm(str, str + i, WORD, root);
		ajoute_elm(str + i, str + i + 1, SQUOTE, root);
	}
	else if (!str[i])
		return (unclosed_quote(root), (i + 1));
	return (i + 2);
}


void	unclosed_quote(t_list **root)
{
	clr_lst(root, *root);
	printf("unclosed quote\n");
	*root = NULL;
}

int	invalid_token(t_list **root, char *str)
{
	clr_lst(root, *root);
	*root = NULL;
	printf("unexpected token\n");
	return (get_last(str));
}

int	get_last(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	calcul_size(char *start, char *end)
{
	int	i;

	i = 1;
	while (start++ != end)
		i++;
	return (i);
}

int	check_flag(char *str, int q, t_list **root)
{
	if (*str == '|')
			return (PIPE);
	return (0);
}
