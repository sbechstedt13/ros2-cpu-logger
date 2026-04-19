# Ubuntu 22.04 as Base Image
FROM ubuntu:22.04 AS base
ENV DEBIAN_FRONTEND=noninteractive
ENV ROS_VERSION=2
ENV ROS_DISTRO=humble

# TODO: rm hard-coding of version, e.g. external script
COPY ros2-apt-source_1.1.0.jammy_all.deb /tmp/ros2-apt-source.deb

# Add ROS 2 apt repo & setup sources
RUN apt-get update && apt-get upgrade \
    && apt-get install --no-install-recommends -y software-properties-common \
    && add-apt-repository universe \
    && dpkg -i /tmp/ros2-apt-source.deb \
    && rm -f /tmp/ros2-apt-source.deb \
    && apt-get update && apt-get upgrade \
    && apt-get install --no-install-recommends -y \
    ros-humble-ros-base \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/

# Create ws + use cpu logger nodes
FROM base AS ws
WORKDIR /ws/
# Import external package
COPY ./cpu_load/ws/ .
RUN apt-get update && apt-get upgrade \
    && apt-get install -y \
    ros-dev-tools \
    python3-colcon-common-extensions \
    && . /opt/ros/humble/setup.sh \
    && colcon build --packages-select cpu_logger


# Create final docker image
FROM base
COPY --from=ws /ws/install/ /ws/install/
ENTRYPOINT . /ws/install/setup.sh && ros2 run cpu_logger talker
