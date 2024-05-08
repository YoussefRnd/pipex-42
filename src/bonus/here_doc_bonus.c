/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:36:19 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/08 18:48:53 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

bool	is_here_doc(char **args)
{
	if (!ft_strncmp(args[1], "here_doc", 8))
		return (true);
	return (false);
}

void	here_doc(t_pipe *p)
{
	int		fd;
	char	*buffer;

	fd = open("/tmp/.here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		ft_putstr_fd("heredoc> ", 1);
		buffer = get_next_line(0);
		if (ft_strncmp(buffer, p->args[2], ft_strlen(buffer) - 1) == 0)
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
	p->input_fd = open("/tmp/.here_doc", O_WRONLY, 0777);
	if (p->input_fd == -1)
	{
		unlink("/tmp/.here_doc");
		perror("Error reopening file");
		exit(EXIT_FAILURE);
	}
	// unlink("/tmp/.here_doc");
}
