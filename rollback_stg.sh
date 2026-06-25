#!/bin/bash
git checkout stg
git fetch origin stg
git reset --hard origin/stg
git clean -fd
echo "Ветка stg возвращена к последней ревизии."

