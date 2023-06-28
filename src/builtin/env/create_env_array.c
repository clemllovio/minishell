/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:51:19 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/24 13:11:50 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_array_env(char **env, size_t row)
{
	size_t	i;

	i = 0;
	while (i < row + 1)
	{
		free(env[i]);
		i++;
	}
	free(env);
	return ;
}

static size_t	get_nb_row(t_env *lst)
{
	size_t	nb_row;

	nb_row = 0;
	if (!lst)
		return (FAILURE);
	while (lst != NULL)
	{
		if (lst->equal == TRUE)
			nb_row++;
		lst = lst->next;
	}
	return (nb_row);
}

static	char	*join_name_with_value(char *name, char *value)
{
	char	*start;
	char	*tmp_name;
	char	*result;

	tmp_name = ft_strdup(name);
	if (!tmp_name)
		return (perror("Malloc failed in join name with value"), NULL);
	start = ft_strjoin(tmp_name, "=");
	if (!start)
	{
		perror("Malloc failed in join name with value");
		return (free(tmp_name), NULL);
	}
	result = ft_strjoin(start, value);
	if (!result)
	{
		perror("Malloc failed in join name with value");
		return (free(start), free(tmp_name), NULL);
	}
	return (free(start), free(tmp_name), result);
}

static char	**make_array(t_env *lst, char **env)
{
	size_t	row;

	row = 0;
	while (lst != NULL)
	{
		if (lst->equal == TRUE)
		{
			env[row] = join_name_with_value(lst->name, lst->value);
			if (!env[row])
			{
				perror("Malloc failed in join name with value return function");
				free_array_env(env, row);
				return (NULL);
			}
			row++;
		}
		lst = lst->next;
	}
	env[row] = NULL;
	return (env);
}

char	**fill_env(t_env *lst)
{
	char	**env;
	size_t	nb_row;

	if (!lst)
		return (NULL);
	env = NULL;
	nb_row = get_nb_row(lst);
	if (nb_row == 0)
		return (NULL);
	env = malloc(sizeof(char *) * (nb_row + 1));
	if (!env)
		return (NULL);
	env = make_array(lst, env);
	if (!env)
		return (NULL);
	return (env);
}
