#!/bin/bash

while getopts c:f: flag
do
    case "${flag}" in
        c) CONTAINER_NAME=${OPTARG};;
        f) LOG_FILE=${OPTARG};;
    esac
done

docker exec -it $CONTAINER_NAME /bin/bash -c "tail -f /logs/$LOG_FILE"
