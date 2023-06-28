/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_a_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:42:22 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 23:34:18 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_tilde(char **tab, int i);
static int	launch_expand(t_env *env, char **tab, int i, int *status_expand);

char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '$' || tab[i][j] == '~')
			{
				if (handle_tilde(tab, i) == FAILURE)
					return (NULL);
				if (launch_expand(env, tab, i, status_expand) == FAILURE)
					return (NULL);
				break ;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

static int	handle_tilde(char **tab, int i)
{
	char	*temp;

	if (tab[i][0] == '~' && (tab[i][1] == '\0'))
	{	
		temp = tab[i];
		tab[i] = ft_strdup("$HOME");
		if (!tab[i])
		{
			tab[i] = temp;
			return (FAILURE);
		}
		free(temp);
	}
	else if (tab[i][0] == '~' && tab[i][1] == '/')
	{
		temp = tab[i];
		tab[i] = ft_strjoin_expand("$HOME", tab[i], 1, ft_strlen(tab[i]));
		if (!tab[i])
		{
			tab[i] = temp;
			return (FAILURE);
		}
		free(temp);
	}
	return (SUCCESS);
}

static int	launch_expand(t_env *env, char **tab, int i, int *status_expand)
{
	char		*temp;
	t_expand	utils;

	if (!env)
		return (FAILURE);
	init_struct_expand(tab[i], env, &utils);
	if (!utils.new_line)
		return (FAILURE);
	temp = tab[i];
	tab[i] = expand(&utils, 0, 0, 0);
	if (!(tab[i]))
	{
		tab[i] = temp;
		return (FAILURE);
	}
	free(temp);
	*status_expand = 1;
	return (SUCCESS);
}
