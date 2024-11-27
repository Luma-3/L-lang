BUILD_DIR="${1:-build}"

LUMC_DIR="LumC"

if [ ! -d "$BUILD_DIR" ]; then
	echo "Error: build directory '$BUILD_DIR' does not exist"
	exit 1
fi

TEST_DIR=$(find "$BUILD_DIR" -name "CTestTestfile.cmake" -exec dirname {} \;)


if [ -z "$TEST_DIR" ]; then
	echo "Error: Could not find test directory in '$BUILD_DIR'"
	exit 1
fi

echo "Running tests in '$TEST_DIR'"

for test in $TEST_DIR; do
	echo "Running test in '$test'"
	(cd "$test" && ctest --output-on-failure)
done