#!/bin/sh

if [ $# -ne 1 ]; then
	echo "Usage: ${0##*/} user@host" >&2
	exit 1
fi

PUBKEY=$(cat)

ssh -i ~/.ssh/mars_key -o PasswordAuthentication=no -o PreferredAuthentications=publickey "$1" "echo '$PUBKEY' >> ~/.ssh/authorized_keys"

if [ $? -ne 0 ]; then
	echo "Error: failed to add key" >&2
	exit 1
fi

echo "key added successfully"
