/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:20:14 by zmaziane          #+#    #+#             */
/*   Updated: 2022/06/28 00:51:43 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>

# define VAR 0 // $anas
# define DGREAT 1 // >>
# define DLESS 2 // <<
# define LESS 3 // < 
# define GREAT 4 // >
# define WORD 5 // guuyguyuy
# define WSPACE 6 // "  "
# define SQUOTE 7 // \'
# define DQUOTE 8 // \""
# define PIPE 9 // | 

// # define VAR 0 // $anas
// # define DGREAT 1 // >>
// # define DLESS 2 // <<
// # define LESS 3 // < 
// # define GREAT 4 // >
// # define WORD 5 // guuyguyuy
// # define WSPACE 6 // "  "
// # define SQUOTE 7 // \'
// # define DQUOTE 8 // \""
// # define OPAR 9 // (
// # define WILD 10 // *
// # define TILD 11 // ~
// # define AND 12 // &&
// # define OR 13 // ||
// # define PIPE 14 // | 
// # define CPAR 15 // )


typedef struct s_list
{
	struct s_list	*prev;
	char			*str;
	int				type;
	struct s_list	*next;
}	t_list;

t_list	*new_node(char *str, int flag);
void	add_back(t_list **head, char *str, int flag);
void	affich_node(t_list *head);
void	delete_list(t_list **head, t_list *node);
void    check_token(char *str, t_list **head);
int	check_char(char *str, t_list **head);
int	take_word(char *str, t_list **head);
int	take_space(char *str, t_list **head);
int	take_variable(char *str, t_list **head);
int	take_dquote(char *str, t_list **head);
int	check_closed_dq(char	*str, int i, int last, t_list **head);
int	take_qvar(char *str, t_list **head);
void	*ajoute_elm(char *start, char *end, int flag, t_list **head);
int	take_less(char *str, t_list **head);
int	take_colon(char *str, t_list **head);
void	unclosed_quote(t_list **head);
int	invalid_token(t_list **head, char *str);
int	get_last(char *str);
int	calcul_size(char *start, char *end);
int	check_flg(char *str, int q, t_list **head);
int	check_syntax(t_list **head);
void	delete_quotes(t_list **head);
t_list	*link_nodes(t_list **head, t_list *deleted);
int	ch_char(char *str,t_list **head);
int	take_space(char *str, t_list **head);
int	take_word(char *str, t_list **head);
int	check_begin(t_list *head);
void	syntax_error(t_list **head);
int	check_list(t_list *head);
int	check_wp(t_list *head);
int	check_red(t_list *head);
t_list	*get_right(t_list *head);

#endif
