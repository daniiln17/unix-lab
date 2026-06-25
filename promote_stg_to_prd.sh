#!/bin/bash
git checkout stg
git pull origin stg 2>/dev/null
git checkout prd
git pull origin prd 2>/dev/null
git merge stg -m "Merge stg into prd"
TAG_NAME="stg-prd-$(date +%Y%m%d-%H%M%S)"
git tag $TAG_NAME
echo "Перенос завершен. Тег: $TAG_NAME"

