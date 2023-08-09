#!/bin/sh

script_path=$(dirname `which $0`)

unamestr=`uname`
if [ "$unamestr" = 'Darwin' ]; then
	hb_x86_py3="/usr/local/bin/python3"
	hb_apple_silicon_py3="/opt/homebrew/bin/python3"

	log_file="/tmp/nrf_sniffer_ble.sh.log"
	if [ ! -z "$VIRTUAL_ENV"]; then
		py3=`which python`
	elif [ -f $hb_x86_py3 ]; then
		py3=$hb_x86_py3
	elif [ -f $hb_apple_silicon_py3 ]; then
		py3=$hb_apple_silicon_py3
	else
		py3=`which python3`
		if [ $? -ne 0 ]; then
			echo "No Python 3 found" >&2
			exit 1
		fi
	fi

	echo "Running script with: <$py3> with PATH: <$PATH>" | tee -a $log_file
else
	py3=`which python3`
fi

exec $py3 $script_path/nrf_sniffer_ble.py "$@"
