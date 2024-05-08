/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:38:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/08 12:32:59 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/Libft/libft.h"
# include "../src/bonus/get_next_line_bonus.h"
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		idx;
	int		argc;
	char	**args;
	int		pipe_fd[2];
	int		prev_fd;
	int		in_fd;
	int		out_fd;
	char	*cmd;
	char	**envp;
	int		input_fd;
	bool	is_here_doc;
}			t_pipe;

char		*is_path_valid(char *cmd, char **env_vars);

char		**split_cmd(char *s);

void		execute_pipe(t_pipe *p);

void		here_doc(t_pipe *p);

bool		is_here_doc(char **cmd_args);

#endif