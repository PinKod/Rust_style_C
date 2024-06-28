#!/bin/bash

FILE_PATH="last_file_tested.txt"

# Check if the file exists
if [ ! -f "$FILE_PATH" ]; then
    touch "$FILE_PATH"
fi


echo "Tests:"

# Check if the required number of arguments is passed

var1=""

while true
do
  read var1
  if [[ -z "$var1" ]] ; then
    read -r line < "$FILE_PATH"
    if [[ -z "$line" ]] ; then
      continue
    else
      var1=$line
      break
    fi
  else
    rm "$FILE_PATH"
    touch "$FILE_PATH"
    echo "$var1" > "$FILE_PATH"
    break
  fi
done
# Check if the username is empty



SEARCH_PATTERN=$var1

#echo $var1
# Find the file in the current directory and all subdirectories
FILE=$(find . -type f -name "$SEARCH_PATTERN" | head -n 1)
#echo $FILE
# Check if the file was found
if [ -f "$FILE" ]; then
#echo "Found file: $FILE"
        counter=1
        while true
        do
            # Compile the C file
            #echo "Compiling $FILE... test $counter flag: -Dtest"$counter""
            TEMP_FILE=$(mktemp)
            gcc -Wall  -Wextra -std=c11 -Werror -Dtest"$counter" -g -o output $FILE 2>$TEMP_FILE
            # shellcheck disable=SC2143
            #if [[ $(grep -q "symbol\(s\) not found for architecture x86_64" "$TEMP_FILE") ]]; then
            if grep -q "symbol(s) not found for architecture x86_64" $TEMP_FILE; then
                #echo "Compilation failed due to linker error."
                # Remove the temporary file
                rm $TEMP_FILE
                # Exit the script with an error status
                exit 0
            else
                if grep -q "error" $TEMP_FILE ; then
                  echo
                  echo "Test $counter compilation failed with error:"
                  echo
                  cat $TEMP_FILE
                  rm $TEMP_FILE
                  exit 0
                fi
                # Remove the temporary file
                rm $TEMP_FILE
            fi
            if [ $? -eq 0 ]; then
                #echo "Compilation successful."
                # Run the compiled program
                echo "Test $counter"
                echo
                ./output
                echo "Test $counter passed"
                echo
                rm output
                else
                    echo "Test: $counter"
                    echo "Compilation failed."
                    exit 1
                fi

            # Increment the counter
            ((counter++))
        done

else
    echo "File not found."
    exit 1
fi
