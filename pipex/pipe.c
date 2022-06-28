/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:28:16 by abigeddi          #+#    #+#             */
/*   Updated: 2022/06/28 09:28:19 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int	ft_pipe(t_data *data, char **env)
{
	if (pipe(data->fd) == -1)
		return (ft_putstr_fd("error whith opening the pipe", 1), exit(1), 0);
	data->pid = fork();
	if (data->pid < 0)
		perror("Fork");
	if (data->pid == 0)
	{
		dup2(data->fd[1], 1);
		dup2(data->input, 0);
		close(data->fd[0]);
		close(data->fd[1]);
		if (data->input > 0)
			execve(data->s1[0], data->s1, env);
	}
	else
	{
		dup2(data->fd[0], 0);
		dup2(data->output, 1);
		close(data->fd[0]);
		close(data->fd[1]);
		execve(data->s2[0], data->s2, env);
	}
	close(data->input);
	return (close(data->output), waitpid(data->pid, NULL, 0), 0);
}
