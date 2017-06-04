#Group 1
#Names: Shaddy Zayour, Alex Adamcik, Travis Allan, Dustin Roberts

echo "***IF CONNECTION IS REFUSED RERUN SCRIPT***"
sleep 1
echo "This occurs because the randomly generated port is currently occupied"
sleep 3
echo "Compiling..."

gcc -o server server.c
gcc -o client client.c
gcc -o client1 client.c

FLOOR=20000
RANGE=65535

port=0   #initialize
while [ "$port" -le $FLOOR ]
do
  port=$RANDOM
  let "port %= $RANGE"
done
echo Attempting to connect to $port
echo "Running Server and first Client"
./server $port & ./client localhost $port

echo "Running second Client"
./client1 localhost $port
