
PROJECT_NAME := my-linux-commands
IMAGE_NAME := ${PROJECT_NAME}-image:`whoami`
CONTAINER_NAME := ${PROJECT_NAME}-`whoami`

image:
	podman build -t ${IMAGE_NAME} \
		--build-arg USER_ID=`id -u` \
		--build-arg GROUP_ID=`id -g` \
		--build-arg USER_NAME=`whoami` \
		--build-arg GROUP_NAME=`whoami` \
		--file Dockerfile .

container: image
	podman run -it --rm \
		--name ${CONTAINER_NAME} \
		--volume $(CURDIR):/home/`whoami` \
		--workdir /home/`whoami` \
		${IMAGE_NAME} \
		/bin/bash


