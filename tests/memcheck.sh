#!/bin/sh
BINARY="./ppc"
LOG_FILE="/tmp/memcheck.ppc.log"

# --error-exitcode=1 ensures valgrind returns 1 on any error or leak
VG_CMD="valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 --quiet"
TEST=1 # test number
STATUS=0 # exit-code

log() {
	echo "[$(date)]: $1"
}

echo "Starting tests..."
echo "Check logs at: $LOG_FILE"

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
TEST_1="10 mov 0, 72\n20 mov 1, 101\n30 mov 2, 108\n40 mov 3, 108\n50 mov 4, 111\n60 mov 5, 33\n70 print 0..5\nrun"

#Reset log
: > $LOG_FILE

run_valgrind() {
	echo "--- LOG START ---" >> $LOG_FILE
	log "Test: $1"
	# printf handles \n correctly for multi-line input
	printf "%b" "$2" | $VG_CMD $BINARY >> "$LOG_FILE" 2>&1
	STATUS=$?

	if [ $STATUS -eq 0 ]; then
		log "Test $TEST ($1) passed."
	else
		log "logs stored at $LOG_FILE"
		echo

		cat $LOG_FILE
		echo '--- LOG END ---'

		log "Test $TEST failed with status $STATUS"
	fi

	echo "" >> $LOG_FILE
	echo "[test: \"$1\" $TEST]" >> $LOG_FILE
	echo "'''" >> $LOG_FILE
	echo "$2" >> $LOG_FILE
	echo "'''" >> $LOG_FILE
	echo "[On: $(date)]" >> $LOG_FILE
	echo "[Status: $STATUS]" >> $LOG_FILE
	echo "--- LOG END ---" >> $LOG_FILE
	echo "" >> $LOG_FILE
	TEST=$((TEST+1))

	if [ $STATUS -ne 0 ]; then
		exit 1
	fi
}

echo_phases() {
	echo
	echo "--- Phase $1: $2 ---"
}

echo_phases "1" "Program-test"

# Loop through test cases
run_valgrind "No input; fast exit" ""
run_valgrind "Printing \"Hello!\" test" "$TEST_1"

log "all tests passed with status $STATUS"
