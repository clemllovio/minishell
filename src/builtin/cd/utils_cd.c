/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:39:52 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:26:17 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message_cd(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4)
		g_exit_status = 1;
	if (type == 0)
	{
		g_exit_status = 2;
		ft_putstr_fd("Invalid option, subject : cd with no options\n", 2);
	}
	else if (type == 1)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (type == 2)
		ft_putstr_fd("subject: cd with only a relative or absolute path\n", 2);
	else if (type == 3)
		ft_putstr_fd("subject: cd with only a relative or absolute path\n", 2);
	else if (type == 4)
		ft_putstr_fd("chdir: error retrieving current directory \n", 2);
}

size_t	get_nb_arguments(char **cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (FAILURE);
	while (cmd[i] != NULL)
		i++;
	return (i);
}

char	*find_old_path(char *actual_path, t_env **lst)
{
	t_env	*copy;
	char	*old_path;

	old_path = NULL;
	copy = *lst;
	while (copy != NULL)
	{
		if (ft_strcmp(copy->name, "PWD") == 0)
		{
			if (copy->value[0] != '\0')
			{
				old_path = ft_strdup(copy->value);
				if (!old_path)
					return (NULL);
				return (old_path);
			}
		}
		copy = copy->next;
	}
	old_path = ft_strdup(actual_path);
	if (!old_path)
		return (NULL);
	return (old_path);
}

void	clear_actualise_pwd(char *actual_path, char *old_path)
{
	if (actual_path)
		free(actual_path);
	if (old_path)
		free(old_path);
}
