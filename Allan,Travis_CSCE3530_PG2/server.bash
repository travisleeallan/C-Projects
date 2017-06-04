#Run this bash script to compile the program

echo "Compiling the proxy server"
gcc -o simServ simServer.c

echo "Initializing server"
./simServ

echo "Program Complete"


