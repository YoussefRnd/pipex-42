/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:31:48 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/09 19:13:39 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	child_proc(t_pipe *p)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = split_cmd(p->cmd);
	cmd_path = is_path_valid(cmd_args[0], p->envp);
	if (cmd_path == NULL)
		error("Command not found");
	cmd_args[0] = cmd_path;
	if ((p->idx == 2 && !p->is_here_doc) || (p->idx == 3 && p->is_here_doc))
		dup2(p->input_fd, STDIN_FILENO);
	else
		dup2(p->prev_fd, STDIN_FILENO);
	if (p->idx != p->argc - 2)
	{
		dup2(p->pipe_fd[1], STDOUT_FILENO);
		close(p->pipe_fd[1]);
	}
	else
		dup2(p->out_fd, STDOUT_FILENO);
	close(p->pipe_fd[0]);
	execve(cmd_path, cmd_args, p->envp);
}

void	parent_proc(t_pipe *p)
{
	close(p->pipe_fd[1]);
	if (p->prev_fd != -1)
		close(p->prev_fd);
	p->prev_fd = p->pipe_fd[0];
	if (p->idx == p->argc - 2)
		close(p->prev_fd);
}

void	execute_pipe(t_pipe *p)
{
	pid_t	pid;
	int		status;

	if (p->is_here_doc && p->idx == 3)
		here_doc(p);
	p->input_fd = p->in_fd;
	p->prev_fd = -1;
	while (p->idx <= p->argc - 2)
	{
		p->cmd = p->args[p->idx];
		pipe(p->pipe_fd);
		pid = fork();
		if (pid == 0)
			child_proc(p);
		else if (pid > 0)
			parent_proc(p);
		else
			error("Fork");
		p->idx++;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
}
