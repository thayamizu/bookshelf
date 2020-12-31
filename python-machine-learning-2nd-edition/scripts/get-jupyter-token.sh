#!/bin/zsh
docker exec docker-jupyter jupyter  notebook list | tail -2 | cut -f 2 -d "=" | cut -b 1-48