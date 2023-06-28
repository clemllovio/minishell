/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:10:47 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 21:04:01 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	store_heredoc_in_list(char **delimiter, t_exec *data);
static int	manage_main_process_heredoc(t_exec *data, char **delimiter);
static	int	manage_heredoc(char **delimiter, t_exec *data, \
								t_env **lst, t_list *list);

int	loop_for_heredoc(t_list *list, t_exec *data, t_data *parsing, t_env **lst)
{
	t_list	*copy;
	int		close_before_last;

	copy = list;
	close_before_last = 0;
	(void)parsing;
	while (copy != NULL)
	{
		if (copy->type == HERE_DOC)
		{
			data->quote_here_doc = copy->quote_here_doc;
			g_exit_status = manage_heredoc(&copy->data[0], data, lst, list);
			if (g_exit_status == 130)
				return (g_exit_status);
		}
		close_before_last++;
		copy = copy->next;
	}
	return (g_exit_status);
}

static	int	manage_heredoc(char **delimiter, t_exec *data, \
			t_env **lst, t_list *list)
{
	if (pipe(data->tmp_fd_heredoc) == FAILURE)
	{
		pipe_heredoc_issue(data);
		return (FAILURE);
	}
	data->pid_heredoc = fork();
	if (data->pid_heredoc == FAILURE)
	{
		fork_issue_heredoc(data, data->tmp_fd_heredoc);
		return (FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (data->pid_heredoc == 0)
		loop_in_child_heredoc(data, *delimiter, lst, list);
	else
		g_exit_status = manage_main_process_heredoc(data, delimiter);
	return (g_exit_status);
}

static int	manage_main_process_heredoc(t_exec *data, char **delimiter)
{
	int	status;

	status = 0;
	if (waitpid(data->pid_heredoc, &status, WUNTRACED) == FAILURE)
		g_exit_status = WEXITSTATUS(status);
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (store_heredoc_in_list(delimiter, data) == FAILURE)
	{
		g_exit_status = 0;
		return (g_exit_status);
	}
	add_to_tab_heredoc(data->fd_heredoc, data->tmp_fd_heredoc[0]);
	return (g_exit_status);
}

static int	store_heredoc_in_list(char **delimiter, t_exec *data)
{
	ft_close(data->tmp_fd_heredoc[1]);
	free(*delimiter);
	*delimiter = ft_itoa(data->tmp_fd_heredoc[0]);
	if (!*delimiter)
	{
		itoa_heredoc_issue(data, data->tmp_fd_heredoc);
		return (FAILURE);
	}
	return (SUCCESS);
}
