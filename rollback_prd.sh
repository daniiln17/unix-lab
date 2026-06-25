#!/bin/bash
git checkout prd
git fetch origin prd
git reset --hard origin/prd
git clean -fd
echo "Ветка prd возвращена к последней ревизии."
