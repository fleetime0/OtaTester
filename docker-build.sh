#!/bin/bash
set -e

rm -rf build

IMAGE_NAME=ubuntu-build-docker
SERVICE_NAME=ubuntu-build

docker build -t $IMAGE_NAME .

export UID_=$(id -u)
export GID_=$(id -g)

docker compose run --rm $SERVICE_NAME

docker rmi $IMAGE_NAME
