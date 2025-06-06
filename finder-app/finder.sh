#1/bin/bash

filesdir=$1
searchstr=$2

if [ $# -lt 2 ]; then
    echo "ERROR: Must enter 2 arguments (directory and search string)"
    exit 1
fi

if [ ! -d "$filesdir" ]; then
    echo "ERROR: ${filesdir} is not a directory"
    exit 1
fi

# find produces one line per file
# wc -l counts number of lines
# piping this to wc -l will give the total number of files
num_files=$(find ${filesdir} -type f | wc -l)

# 2>/dev/null redirects stderr to an ignored destination
# to show only matching lines and supress errors
num_matching_lines=$(grep -r ${searchstr} ${filesdir} 2>/dev/null | wc -l)

echo "The number of files are ${num_files} and the number of matching lines are ${num_matching_lines}"