#!/bin/sh

docker compose run --entrypoint "make build-x86_64" --rm StasisOS
