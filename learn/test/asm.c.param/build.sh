gcc -c a.S -o a.S.o -I.
gcc -c a.c -o a.o -I.
gcc a.o a.S.o -o a.bin -I.
./a.bin

