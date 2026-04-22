#!/bin/bash

# LOG_FILE currently hardcoded in cpu_util_publisher.cpp
# can be found in ROS2 Workspace cpu_load
# TODO: Take user input for Logfile
while getopts c: flag
do
    case "${flag}" in
        c) CONTAINER_NAME=${OPTARG};;
        #f) LOG_FILE=${OPTARG};;
    esac
done

docker exec -it $CONTAINER_NAME /bin/bash -c "tail -f /logs/cpu_load.log"
