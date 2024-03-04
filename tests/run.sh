#!/bin/sh

testdir=$(dirname $0)
interpreter=${2:-"lua5.4"}
export LUA_CPATH="$testdir/../?.so;;"
export LUA_PATH="$testdir/?.lua;;"

tests="core"

dotest=${1:-$tests}

for t in $tests; do
	echo Running $t
	$interpreter $testdir/$t.lua
done
