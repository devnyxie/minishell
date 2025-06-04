/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:08:35 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/04 15:59:22 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_cmd_path(char *path, char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break ;
		tmp = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!tmp)
			break ;
		if (access(tmp, X_OK) == 0)
		{
			free_2d(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

// Recursively launch each command in the pipeline.
// 'prev_fd' is the read end of the previous pipe (or -1 for the first command).
int start_process(t_cmd *cmd, int prev_fd, t_shell *shell)
{
    int pipefd[2] = { -1, -1 };
    int pid;

    if (!cmd->next && ft_strcmp(cmd->name, "exit") == 0)
        exit(0);
    // If there’s a next command, create a new pipe for this pair.
    if (cmd->next)
        if (pipe(pipefd) < 0)
            perror("pipe"), exit(1);

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // -------- CHILD --------
        // 1) If there was a previous pipe, dup its read end onto stdin.
        if (prev_fd != -1) {
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);
        }

        // 2) If there’s a next command, dup this pipe’s write end onto stdout.
        if (cmd->next) {
            close(pipefd[0]);          // close unused read end
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
        }

        // 3) Now we’re in the right process and the fds are hooked up.
        //    Check if it’s a builtin:
        for (int i = 0; shell->builtins[i].name; i++) {
            if (ft_strcmp(cmd->name, shell->builtins[i].name) == 0) {
                shell->builtins[i].fn(cmd->args);
                // exit(0);
            }
        }

        // 4) Otherwise it’s an external: resolve path, then execve.
        char *path = search_cmd_path(shell->path, cmd->name);
        if (path) {
            execve(path, cmd->args, shell->envp);
            perror("execve");
        } else {
            fprintf(stderr, "%s: command not found\n", cmd->name);
        }
        exit(1);
    }

    // -------- PARENT --------
    // 1) Close any fds we don’t need:
    if (prev_fd != -1)
        close(prev_fd);
    if (cmd->next) {
        close(pipefd[1]);  // parent only needs the read end for the next child
    }

    // 2) Recurse/loop to launch next command, passing this pipe’s read end.
    if (cmd->next) {
        start_process(cmd->next, pipefd[0], shell);
    }

    // 3) Wait for this child to finish.
    waitpid(pid, NULL, 0);
    return 0;
}


// gets parsed input from shell->parsed_input and starts the commands
void	lexer(t_shell *shell, t_cmd *cmd)
{
	start_process(cmd, -1, shell);
}