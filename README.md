# MiniShell

## Development

### Branching

- `main`: The main branch, which should always be stable.
- `any other branch`: Feature branches for development. These branches can be named according to the feature being developed, e.g., `feature/command-parser`.

- Switching branches;
  ```bash
  git switch -c your-branch-name
  ```
  *-c creates the branch if it doesn't exist already.*

- Stashing changes:
  ```bash
  git stash
  git stash apply
  ```

- Pushing to the remote:
  ```bash
  git push origin your-branch-name
  ```

## Other

### Reusable Samples

#### CMDs and ARGs output

```c
printf("=== Parsed commands ===\n");
current_cmd = shell_input->first_cmd;
while(current_cmd != NULL) {
    printf("  Name: %s,", current_cmd->name);
    printf("  Args:");
    for (int i = 0; current_cmd->args[i]; i++)
    {
        printf(" \"%s\"", current_cmd->args[i]);
    }
    current_cmd = current_cmd->next;
}
printf("\n=======================\n");
```