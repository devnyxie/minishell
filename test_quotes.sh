#!/bin/bash

echo "Testing Bash-style double quote parsing and evaluation..."

# Test 1: Basic double quotes
echo 'Test 1 - Basic quotes:'
echo 'echo "hello world"' | ./minishell
echo

# Test 2: Variable expansion inside quotes
echo 'Test 2 - Variable expansion inside quotes:'
echo 'echo "User: $USER, Home: $HOME"' | ./minishell
echo

# Test 3: Escaped characters inside quotes
echo 'Test 3 - Escaped characters:'
echo 'echo "He said: \"hello\""' | ./minishell
echo

# Test 4: Escaped dollar sign
echo 'Test 4 - Escaped dollar sign:'
echo 'echo "Literal: \$USER = $USER"' | ./minishell
echo

# Test 5: Space preservation
echo 'Test 5 - Space preservation:'
echo 'echo "hello    world    with    spaces"' | ./minishell
echo

# Test 6: Braced variables
echo 'Test 6 - Braced variables:'
echo 'echo "User: ${USER}, Shell: ${SHELL}"' | ./minishell
echo

# Test 7: Undefined variables
echo 'Test 7 - Undefined variables:'
echo 'echo "Undefined: $UNDEFINED_VAR end"' | ./minishell
echo

# Test 8: Empty quotes
echo 'Test 8 - Empty quotes:'
echo 'echo ""' | ./minishell
echo

# Test 9: Mixed arguments
echo 'Test 9 - Mixed quoted/unquoted:'
echo 'echo hello "world with spaces" more' | ./minishell
echo

# Test 10: Unquoted variables
echo 'Test 10 - Unquoted variables:'
echo 'echo $USER' | ./minishell
echo

# Test 11: Mixed variables
echo 'Test 11 - Mixed variables:'
echo 'echo $USER "is the user" $HOME' | ./minishell
echo

# Test 12: With pipes
echo 'Test 12 - With pipes:'
echo 'echo "hello world" | cat' | ./minishell
echo

echo "All tests completed!"
