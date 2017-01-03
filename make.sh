# Makes object files and an executable program out of .c files and .h files.

# Usage: Copy this file into the directory containing the .c and .h files and
# run. Only one executable should be desired from all the files in the
# directory; in other words, there should only be one main method in total.


# The name of the executable
EXECUTABLE="main"


echo Welcome! Please ignore rm command errors, but fix compiler and linker
echo warnings and errors.
ls
echo

echo Removing old executable...
rm $EXECUTABLE
ls
echo

echo Removing old object files...
rm *.o
ls
echo

echo Compiling .h files...
for f in *.h;
	do gcc -g -Wall -std=gnu11 -c -o "${f%.h}.o" "$f";
done;
ls
echo

echo Removing new object files...
rm *.o
ls
echo

echo Compiling .c files...
for f in *.c;
	do gcc -g -Wall -std=gnu11 -c -o "${f%.c}.o" "$f";
done;
ls
echo

echo Linking into executable...
gcc -g -Wall -std=gnu11 -o $EXECUTABLE *.o
ls
echo
echo Done! :D
