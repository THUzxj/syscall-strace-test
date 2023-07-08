#~/bin/bash

TRACE_DIR="./traces/unix_domain_socket"
STRACE_FLAGS="-yy -Y -f"

set -x
mkdir -p $TRACE_DIR
sudo rm /tmp/socket /tmp/socket.origin

strace $STRACE_FLAGS -o $TRACE_DIR/server.log ./bin/unix_domain_socket/server &

sleep 0.5

sudo mv /tmp/socket /tmp/socket.origin
sudo socat -t100 -x -v UNIX-LISTEN:/tmp/socket,mode=777,reuseaddr,fork UNIX-CONNECT:/tmp/socket.origin 2> $TRACE_DIR/socat.log &

sleep 0.5

strace $STRACE_FLAGS -o $TRACE_DIR/client.log ./bin/unix_domain_socket/client

sudo rm /tmp/socket /tmp/socket.origin

pkill -9 server

sudo pkill -9 socat
