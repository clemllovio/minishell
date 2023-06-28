# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execution.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 09:55:39 by lciullo           #+#    #+#              #
#    Updated: 2023/06/28 10:58:57 by cllovio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	src/execution/execution.c 										\
		src/execution/struct.c											\
		src/execution/files/infiles.c									\
		src/execution/files/outfiles.c									\
		src/execution/files/heredoc.c									\
		src/execution/files/heredoc_utils.c								\
		src/execution/files/heredoc_child_process.c						\
		src/execution/no_pipe/one_builtin_exec.c						\
		src/execution/with_pipe/loop_list.c								\
		src/execution/with_pipe/launch_exec.c							\
		src/execution/with_pipe/begin_exec.c							\
		src/execution/with_pipe/paths/check_access.c					\
		src/execution/with_pipe/paths/is_executable.c					\
		src/execution/with_pipe/paths/get_cmd_with_path.c				\
		src/execution/with_pipe/execute_token.c							\
		src/execution/with_pipe/dup_files.c 							\
		src/execution/clear_exec/close_files.c 							\
		src/execution/clear_exec/close_heredoc.c						\
		src/execution/clear_exec/clear_cmds.c							\
		src/execution/clear_exec/clear_heredoc.c						\
		src/execution/clear_exec/clear_files.c							\
		src/execution/clear_exec/clear_one_builtin_exec.c				\
		src/builtin/builtin.c 											\
		src/builtin/echo.c												\
		src/builtin/cd/cd.c												\
		src/builtin/cd/utils_cd.c										\
		src/builtin/env/env.c											\
		src/builtin/env/create_env_array.c								\
		src/builtin/env/create_env_list.c								\
		src/builtin/pwd.c												\
		src/builtin/exit.c 												\
		src/builtin/unset.c												\
		src/builtin/export/export.c										\
		src/builtin/export/check_is_valid.c								\
		src/builtin/export/print_export.c								\
		src/builtin/export/export_utils.c								\
		src/builtin/export/parse_export.c								\
		src/builtin/export/name_with_equal.c							\
		src/builtin/export/check_name_by_name.c							\
		src/builtin/export/clear_export.c