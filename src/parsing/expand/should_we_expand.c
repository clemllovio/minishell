/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_we_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:42:28 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 23:36:52 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_data(t_list *temp, t_env *env, int *status_expand);
static int	process_expanded_data(t_list *temp);
static char	*join_tab(char **tab);

int	should_we_expand(t_list **list, t_env *env)
{
	t_list	*temp;
	int		status_expand;

	temp = (*list);
	status_expand = 0;
	while (temp)
	{
		if (temp->type != HERE_DOC)
		{
			if (expand_data(temp, env, &status_expand) == FAILURE)
				return (ft_lstclear(list, free), FAILURE);
			if (status_expand == 1 && (temp->data[1] != NULL \
			|| temp->data[0][0] != '\0'))
			{
				if (process_expanded_data(temp) == FAILURE)
					return (ft_lstclear(list, free), FAILURE);
				status_expand = 0;
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

static int	expand_data(t_list *temp, t_env *env, int *status_expand)
{
	char	**temp_tab;

	temp_tab = temp->data;
	temp->data = is_there_a_dollar(temp->data, env, status_expand);
	if (!(temp->data))
	{
		temp->data = temp_tab;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	process_expanded_data(t_list *temp)
{
	char	*tab_in_line;
	char	**temp_tab;

	change_tab(temp->data, 0);
	temp_tab = temp->data;
	tab_in_line = join_tab(temp->data);
	if (!(tab_in_line))
	{
		temp->data = temp_tab;
		return (FAILURE);
	}
	temp_tab = temp->data;
	temp->data = ft_split_parsing(tab_in_line);
	free(tab_in_line);
	if (!(temp->data))
	{
		temp->data = temp_tab;
		return (FAILURE);
	}
	free_array(temp_tab);
	change_tab(temp->data, 1);
	return (SUCCESS);
}

static char	*join_tab(char **tab)
{
	int		i;
	char	*new_s;
	char	*temp;

	new_s = calloc(1, 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		temp = new_s;
		new_s = ft_strjoin_parsing(new_s, tab[i]);
		if (!new_s)
			return (free(temp), NULL);
		temp = new_s;
		new_s = ft_strjoin_parsing(new_s, " ");
		if (!new_s)
			return (free(temp), NULL);
		i++;
	}
	return (new_s);
}
