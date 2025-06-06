#1/bin/bash

filepath=$1
filecontent=$2

if [ $# -lt 2 ]; then
    echo "ERROR: Must enter 2 arguments (file path and text)"
    exit 1
fi

# Extract the directory part from the full file path
dirpath=$(dirname ${filepath})

mkdir -p ${dirpath}
     
echo ${filecontent} > ${filepath}