/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:31:48 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/08 19:42:06 by yboumlak         ###   ########.fr       */
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
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	cmd_args[0] = cmd_path;
	dprintf(2,"current_input_fd: %d | prev_fd: %d | in_fd: %d | out_fd: %d | pipe_fd0: %d | pipe_fd1: %d\n", p->input_fd, p->prev_fd, p->in_fd, p->out_fd, p->pipe_fd[0], p->pipe_fd[1]);
	if ((p->idx == 2 && !p->is_here_doc) || (p->idx == 3 && p->is_here_doc))
	{
		dup2(p->input_fd, STDIN_FILENO);
		dprintf(2, "input_fd used\n");
	}
	else {
		dup2(p->prev_fd, STDIN_FILENO);
		dprintf(2, "prev_fd used\n");

	}
	if (p->idx != p->argc - 2)
	{
		dup2(p->pipe_fd[1], STDOUT_FILENO);
		dprintf(2, "pipe_fd1 used\n");
		close(p->pipe_fd[1]);
	}
	else {
		dup2(p->out_fd, STDOUT_FILENO);
		dprintf(2, "out_fd used\n");
	}
	close(p->pipe_fd[0]);
	execve(cmd_path, cmd_args, p->envp);
}

void	parent_proc(t_pipe *p)
{
	close(p->pipe_fd[1]);
	if (p->prev_fd != -1 && !p->is_here_doc)
		close(p->prev_fd);
	p->prev_fd = p->pipe_fd[0];
	if (p->idx == p->argc - 2)
		close(p->prev_fd);
}

void	execute_pipe(t_pipe *p)
{
	pid_t	pid;
	int		status;

	p->input_fd = p->in_fd;
	p->prev_fd = -1;
	while (p->idx <= p->argc - 2 - p->is_here_doc)
	{
		p->cmd = p->args[p->idx];
		pipe(p->pipe_fd);
		if (p->is_here_doc && p->idx == 3)
			here_doc(p);
		pid = fork();
		if (pid == 0)
			child_proc(p);
		else if (pid > 0)
			parent_proc(p);
		else
		{
			perror("Fork");
			exit(EXIT_FAILURE);
		}
		p->idx++;
	}
	while (waitpid(0, &status, 0) > 0)
		;
}
