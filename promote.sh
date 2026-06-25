#!/bin/bash
# Перенос из dev в stg с меткой времени

git checkout dev
git pull origin dev 2>/dev/null

git checkout stg
git pull origin stg 2>/dev/null

git merge dev -m "Merge dev into stg"

TAG_NAME="stg-$(date +%Y%m%d-%H%M%S)"
git tag $TAG_NAME

echo "Перенос завершен. Тег: $TAG_NAME"
