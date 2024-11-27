
run_test() {
	echo "Running test..."
	(cd $1 && ctest --output-on-failure)
}


usage() {
	echo "Usage: $0 <Project-name> [Build-dir]"
	exit 1
}

if [ $# -lt 1 ]; then
	usage
fi

PROJECT=$1
BUILD_DIR=${2:-build}

PATH_BUILD=$BUILD_DIR/$PROJECT

if [ ! -d $PATH_BUILD ]; then
	echo "Build directory not found: $PATH_BUILD"
	exit 1
fi

run_test $PATH_BUILD
