#Run this bash script to compile the program

echo "Compiling the proxy client"
gcc -o simCli simClient.c

echo "Initializing client"
./simCli

echo "Program Complete"


