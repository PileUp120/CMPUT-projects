#!/bin/bash
sed -e 's/10/ A/g' | sed 'y/0123456789A/░▪┛┓┗┏┣┫┻┳╋/' |  sed -e 's/ //g' | \
sed -e 's/░▪▪/░━━/g' | sed -e 's/▪░/┃░/g' | \
sed -e 's/░▪/░┃/g' | sed -e 's/▪/━/g'

