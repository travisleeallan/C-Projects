#Run this bash script to compile the program

echo "Compiling the server"
gcc -o simServ simServer.c

echo "Initializing server"
./simServ

echo "Program Complete"


