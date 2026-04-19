#! /bin/bash

while getopts c: flag
do
    case "${flag}" in
        c) CONTAINER_NAME=${OPTARG};;
        *) echo "Missing container name, please use flag -c"
    esac
done
cpu_num=$(nproc --all)
if ((cpu_num < 1)); then cpu_num=1;fi

echo "Putting stress on CPU..."
docker exec -it "$CONTAINER_NAME" /bin/bash -c \
"for ((i=0; i<$cpu_num;i++)) do while : ; do : ; done & done; wait"
