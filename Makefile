SGDK_VERSION=2.11
UID=$(shell id -u)
GID=$(shell id -g)
DOCKER_IMAGE=registry.gitlab.com/doragasu/docker-sgdk:v${SGDK_VERSION}

.PHONY: compile
compile:
	docker run -it --rm --user ${UID}:${GID} -v "${PWD}":/workdir -w /workdir ${DOCKER_IMAGE}

shell:
	docker run -it --rm -v "${PWD}":/workdir -w /workdir --entrypoint=/bin/bash ${DOCKER_IMAGE}

clean:
	rm -rf out/* build/* src/boot/*

format:
	clang-format -i src/*.c inc/*.h
