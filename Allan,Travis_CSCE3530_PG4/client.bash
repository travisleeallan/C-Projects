#Run this bash script to compile the program

echo "Compiling the client"
gcc -o simCli simClient.c

echo "Initializing client"
./simCli < data.txt

echo "Program Complete"


