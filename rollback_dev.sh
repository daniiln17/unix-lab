#!/bin/bash
git checkout dev
git fetch origin dev
git reset --hard origin/dev
git clean -fd
echo "Ветка dev возвращена к последней ревизии."
