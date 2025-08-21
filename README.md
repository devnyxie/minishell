# minishell
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

`minishell` is a shell implementation in C, designed to mimic the behavior of a Bash shell. It must be equally compatible with Bash, meaning it should handle commands, pipes, arguments, redirections and all other shell features in a similar way. Of course, with limited access even to the C standard library, and perfectly managed memory.

## Development

### Branching

- `main`: The main branch, which should always be stable.
- `dev`: The development branch, where new features and changes are merged and tested before being pushed to `main`.
- `any other branch`: Feature branches for development. These branches can be named according to the feature being developed, e.g., `feature/command-parser`.

### Testing

#### Valgrind

To test the shell with Valgrind using our suppression file:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind.supp ./minishell
```

The `valgrind.supp` file contains comprehensive suppressions for readline/libedit library leaks that are expected and not actual bugs. This will give you a clean output showing only your actual memory leaks.
If you would like to add more suppressions, add `--gen-suppressions=yes` flag, which will output rules for each leak found. You can then add these rules to the `valgrind.supp` file.
