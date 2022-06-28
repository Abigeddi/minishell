/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:09:21 by abigeddi          #+#    #+#             */
/*   Updated: 2022/06/28 09:31:32 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>

typedef struct s_data
{
	int		fd[2];
	pid_t	pid;
	char	**s1;
	char	**s2;
	int		input;
	int		output;
}	t_data;

char	**ft_split(char const *s, char c);
char	*ft_allocate(char **strs, const char *s, size_t n);
int		word_count(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putchar(char c, int fd);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_pipe(t_data *data, char **env);
char	*search_path(char *str, char **env);
void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif