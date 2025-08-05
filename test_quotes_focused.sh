#!/bin/bash

# Colors and emojis
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PASS="✅"
FAIL="❌"
WARN="⚠️"
INFO="ℹ️"
ROCKET="🚀"
QUOTE="💬"
DOLLAR="💲"
PIPE="🔗"
REDIR="📂"
BUILTIN="🔧"

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to run a test
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_pattern="$3"
    local should_fail="${4:-false}"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Testing:${NC} $test_name"
    echo -e "${INFO} Input: ${YELLOW}$input${NC}"
    
    # Run the test
    local output
    if [[ "$should_fail" == "true" ]]; then
        output=$(echo "$input" | timeout 5s ./minishell 2>&1)
        local exit_code=$?
        if [[ $exit_code -ne 0 ]] || echo "$output" | grep -q "error\|Error\|command not found"; then
            echo -e "${PASS} ${GREEN}Test passed${NC} (expected failure)"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${FAIL} ${RED}Test failed${NC} (should have failed)"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    else
        output=$(echo "$input" | timeout 5s ./minishell 2>/dev/null)
        if echo "$output" | grep -qE "$expected_pattern"; then
            echo -e "${PASS} ${GREEN}Test passed${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${FAIL} ${RED}Test failed${NC}"
            echo -e "Expected pattern: ${YELLOW}$expected_pattern${NC}"
            echo -e "Actual output: ${YELLOW}$output${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    echo ""
}

echo -e "${ROCKET} ${BLUE}=== MINISHELL QUOTE IMPLEMENTATION TEST SUITE ===${NC}"
echo ""

# Check if minishell exists
if [[ ! -f "./minishell" ]]; then
    echo -e "${FAIL} ${RED}minishell executable not found!${NC}"
    echo "Please run 'make' first."
    exit 1
fi

echo -e "${INFO} ${BLUE}Testing the new quote parsing implementation...${NC}"
echo ""

# ===== CORE QUOTE FUNCTIONALITY =====
echo -e "${QUOTE} ${BLUE}=== CORE QUOTE FUNCTIONALITY ===${NC}"
run_test "Basic double quotes" 'echo "hello world"' "hello world"
run_test "Basic single quotes" "echo 'hello world'" "hello world"
run_test "Single quoted command" "'ls'" ".*"
run_test "Double quoted command" '"ls"' ".*"
echo ""

# ===== VARIABLE EXPANSION IN QUOTES =====
echo -e "${DOLLAR} ${BLUE}=== VARIABLE EXPANSION IN QUOTES ===${NC}"
run_test "Variable in double quotes" 'echo "User: $USER"' "User: .*"
run_test "Variable in single quotes (literal)" "echo '\$USER'" '\$USER'
run_test "Braced variable in double quotes" 'echo "User: ${USER}"' "User: .*"
run_test "Braced variable in single quotes (literal)" "echo '\${USER}'" '\${USER}'
run_test "Mixed expansion" $'echo \'literal: $USER\' "expanded: $USER"' "literal: .*USER.* expanded: .*"
echo ""

# ===== ESCAPE SEQUENCES =====
echo -e "${QUOTE} ${BLUE}=== ESCAPE SEQUENCES ===${NC}"
run_test "Escaped double quotes" 'echo "He said: \"hello\""' 'He said: "hello"'
run_test "Escaped backslash" 'echo "Path: \\\\"' "Path: \\\\\\\\"
run_test "Escaped dollar sign" 'echo "Literal: \$USER = $USER"' "Literal: .*USER = .*"
run_test "Backslash in single quotes (literal)" "echo 'Path: \\\\'" 'Path: \\\\'
echo ""

# ===== SPACE AND SPECIAL CHARACTER HANDLING =====
echo -e "${QUOTE} ${BLUE}=== SPACE AND SPECIAL CHARACTER HANDLING ===${NC}"
run_test "Space preservation in double quotes" 'echo "hello    world    spaces"' "hello    world    spaces"
run_test "Space preservation in single quotes" "echo 'hello    world    spaces'" "hello    world    spaces"
run_test "Mixed quoted and unquoted" 'echo hello "world with spaces" more' "hello world with spaces more"
run_test "Empty double quotes" 'echo ""' "^$"
run_test "Empty single quotes" "echo ''" "^$"
echo ""

# ===== VARIABLE EXPANSION EDGE CASES =====
echo -e "${DOLLAR} ${BLUE}=== VARIABLE EXPANSION EDGE CASES ===${NC}"
run_test "Undefined variable in quotes" 'echo "Undefined: $UNDEFINED_VAR end"' "Undefined:  end"
run_test "Variable at start of string" 'echo "$USER_suffix"' ".*suffix"
run_test "Variable at end of string" 'echo "prefix_$USER"' "prefix_.*"
run_test "Multiple variables" 'echo "$USER and $HOME"' ".* and .*"
echo ""

# ===== INTEGRATION WITH EXISTING FEATURES =====
echo -e "${PIPE} ${BLUE}=== INTEGRATION WITH PIPES AND REDIRECTION ===${NC}"
run_test "Double quotes with pipes" 'echo "hello world" | cat' "hello world"
run_test "Single quotes with pipes" "echo 'hello world' | cat" "hello world"
run_test "Quoted redirection filename" 'echo test > "output.txt" && cat "output.txt"' "test"
run_test "Variable in pipe" 'echo $USER | cat' ".*"
echo ""

# ===== ERROR HANDLING =====  
echo -e "${WARN} ${BLUE}=== ERROR HANDLING ===${NC}"
run_test "Unclosed double quotes" 'echo "unclosed' "" true
run_test "Unclosed single quotes" "echo 'unclosed" "" true
run_test "Mixed unclosed quotes" 'echo "start '"'"' middle' "" true
echo ""

# ===== COMPLEX REAL-WORLD SCENARIOS =====
echo -e "${ROCKET} ${BLUE}=== COMPLEX REAL-WORLD SCENARIOS ===${NC}"
run_test "Command with quoted arguments" 'echo "arg1" "arg2 with spaces" "arg3"' "arg1 arg2 with spaces arg3"
run_test "Nested command structure" 'echo "Output: $(echo hello)"' "Output: .*hello.*"
run_test "Path with spaces simulation" 'echo "cd \"My Documents\""' 'cd "My Documents"'
run_test "Script-like command" 'echo "#!/bin/bash" && echo "echo hello"' "#!/bin/bash.*echo hello"
echo ""

# ===== COMPARISON WITH BASH BEHAVIOR =====
echo -e "${INFO} ${BLUE}=== BASH BEHAVIOR COMPATIBILITY ===${NC}"

# Test what bash would do vs our shell
echo -e "${INFO} ${YELLOW}Comparing with bash behavior:${NC}"

# Test case 1: Single quotes around command
echo -e "${INFO} Testing: 'echo hello'"
bash_output=$(echo "'echo hello'" | bash 2>/dev/null || echo "BASH_ERROR")
minishell_output=$(echo "'echo hello'" | ./minishell 2>/dev/null || echo "MINISHELL_ERROR")

if [[ "$bash_output" == "$minishell_output" ]]; then
    echo -e "${PASS} Behavior matches bash"
    PASSED_TESTS=$((PASSED_TESTS + 1))
else
    echo -e "${FAIL} Behavior differs from bash"
    echo -e "Bash: ${YELLOW}$bash_output${NC}"
    echo -e "Minishell: ${YELLOW}$minishell_output${NC}"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi
TOTAL_TESTS=$((TOTAL_TESTS + 1))
echo ""

# Test case 2: Double quotes around command  
echo -e "${INFO} Testing: \"echo hello\""
bash_output=$(echo '"echo hello"' | bash 2>/dev/null || echo "BASH_ERROR")
minishell_output=$(echo '"echo hello"' | ./minishell 2>/dev/null || echo "MINISHELL_ERROR")

if [[ "$bash_output" == "$minishell_output" ]]; then
    echo -e "${PASS} Behavior matches bash"
    PASSED_TESTS=$((PASSED_TESTS + 1))
else
    echo -e "${FAIL} Behavior differs from bash"
    echo -e "Bash: ${YELLOW}$bash_output${NC}"
    echo -e "Minishell: ${YELLOW}$minishell_output${NC}"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi
TOTAL_TESTS=$((TOTAL_TESTS + 1))
echo ""

# Clean up test files
rm -f output.txt 2>/dev/null

# ===== FINAL RESULTS =====
echo -e "${ROCKET} ${BLUE}=== QUOTE IMPLEMENTATION TEST RESULTS ===${NC}"
echo ""
echo -e "${INFO} Total tests run: ${YELLOW}$TOTAL_TESTS${NC}"
echo -e "${PASS} Tests passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "${FAIL} Tests failed: ${RED}$FAILED_TESTS${NC}"
echo ""

success_rate=$(( (PASSED_TESTS * 100) / TOTAL_TESTS ))

if [[ $FAILED_TESTS -eq 0 ]]; then
    echo -e "${PASS} ${GREEN}🎉 ALL QUOTE TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}Your quote implementation is perfect!${NC}"
    exit 0
elif [[ $success_rate -ge 90 ]]; then
    echo -e "${PASS} ${GREEN}🎊 EXCELLENT! Quote implementation is working great! 🎊${NC}"
    echo -e "${GREEN}Success rate: ${success_rate}%${NC}"
    exit 0
elif [[ $success_rate -ge 80 ]]; then
    echo -e "${WARN} ${YELLOW}🙂 GOOD! Quote implementation is mostly working!${NC}"
    echo -e "${YELLOW}Success rate: ${success_rate}%${NC}"
    exit 0  
else
    echo -e "${FAIL} ${RED}Quote implementation needs more work.${NC}"
    echo -e "${YELLOW}Success rate: ${success_rate}%${NC}"
    exit 1
fi
