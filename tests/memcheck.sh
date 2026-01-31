#!/bin/sh
BINARY="./ppc"
LOG_FILE="/tmp/memcheck.log.txt"

# --error-exitcode=1 ensures valgrind returns 1 on any error or leak
VG_CMD="valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 --quiet"

log() {
	echo "[$(date)]: $1"
}

echo "Starting tests..."
echo "No error are allowed."
echo "Check logs at: $LOG_FILE"
echo

if ! command -v valgrind > /dev/null 2>&1; then
	log "Error: valgrind is not found on your system"
	log "Please ensure it installed on your system"
	exit 1
fi

if [ ! -f "$BINARY" ]; then
	log "Error: $BINARY not found."
	exit 1
fi

# Define test cases (multi-line strings)
# Each variable is a separate session ending with EOF (Ctrl+D)
TEST_1="10 EXP 10\n20 PUT 65 1\n30 PUT 66 2\n40 PUT 67 3\n50 PUT 68 4\n60 PUT 69 5\n70 PRINT 1..5\nRUN"

run_valgrind() {
	log "Testing: $1"
	# printf handles \n correctly for multi-line input
	printf "%b" "$2" | $VG_CMD $BINARY >> "$LOG_FILE" 2>&1

	if [ $? -eq 0 ]; then
		log "Test $1 passed."
	else
		log "Test $1 failed."
		log "Check log at $LOG_FILE (if needed again)"
		echo

		echo "On: $(date)" >> $LOG_FILE

		echo "--- LOG START ---"
		cat $LOG_FILE
		echo '--- LOG END ---'

		echo "\n[Failed]"
		exit 1
	fi
}

echo_phases() {
	echo
	echo "--- Phase $1: $2 ---"
}

#reset log
: > $LOG_FILE

echo "--- Phase 1: Basic Init/Exit ---"
run_valgrind "Null Input" ""

echo_phases "1" "Instruction-test"

# Loop through test cases
run_valgrind "Simple Program" "$TEST_1"

log "SUCCESS: all tests was passed with exit-code 0"
echo "\n[SUCCESS]"
