/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:10:39 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 21:02:59 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_heredoc_process(t_exec *data);
static int	empty_line_heredoc(t_exec *data, t_env **lst, \
				t_list *list, char *line);
static int	not_empty_heredoc_line(t_exec *data, char *delimiter, \
					char *line, t_env **lst);

void	loop_in_child_heredoc(t_exec *data, char *delimiter, \
		t_env **lst, t_list *list)
{
	char	*line;

	line = NULL;
	init_heredoc_process(data);
	while (g_exit_status == 0)
	{
		init_signals_heredoc();
		line = readline("heredoc> ");
		if (line)
		{
			if (not_empty_heredoc_line(data, delimiter, line, lst) == BREAK)
				break ;
		}
		else
		{
			g_exit_status = empty_line_heredoc(data, lst, list, line);
			exit (g_exit_status);
		}
	}
	clear_heredoc_end(data, lst, list, data->tmp_fd_heredoc);
	exit(g_exit_status);
}

static void	init_heredoc_process(t_exec *data)
{
	close(data->tmp_fd_heredoc[0]);
	close_tab_heredoc(data);
	g_exit_status = 0;
}

static int	not_empty_heredoc_line(t_exec *data, char *delimiter, \
			char *line, t_env **lst)
{
	char		*temp;
	t_expand	utils;

	temp = NULL;
	if (!ft_strcmp(line, delimiter))
		return (BREAK);
	if (ft_strchr(line, '$') != 0 && data->quote_here_doc == 0)
	{
		if (!lst)
			return (free(line), FAILURE);
		temp = line;
		init_struct_expand(line, *lst, &utils);
		if (!utils.new_line)
			return (free(line), FAILURE);
		line = expand(&utils, 0, 0, 1);
		free(temp);
		if (!line)
			return (FAILURE);
	}
	write(data->tmp_fd_heredoc[1], line, ft_strlen(line));
	ft_putstr_fd("\n", data->tmp_fd_heredoc[1]);
	free(line);
	return (SUCCESS);
}

static int	empty_line_heredoc(t_exec *data, t_env **lst, \
			t_list *list, char *line)
{
	if (g_exit_status == 130)
	{
		close_tab_heredoc(data);
		clear_heredoc_end(data, lst, list, data->tmp_fd_heredoc);
		exit (g_exit_status);
	}
	ft_putstr_fd("here-document at line delimited by end-of-file\n", 2);
	free(line);
	g_exit_status = 0;
	clear_heredoc_end(data, lst, list, data->tmp_fd_heredoc);
	return (g_exit_status);
}
