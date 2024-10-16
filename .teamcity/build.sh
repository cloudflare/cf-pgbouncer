#!/bin/bash -x

set -euo pipefail

# when V is 1, print commands and build progress.
export V=1

DEBIAN_BUILD_VERSION=$(grep -o '^[0-9]*' /etc/debian_version)

# buster has libevent version v2.1-6, bullseye has version v2.1-7, stretch only has 2.0.
export DEPENDS="libevent-2.0-5"
if [[ $DEBIAN_BUILD_VERSION == 10 ]]; then
  export DEPENDS="libevent-2.1-6"
elif [[ $DEBIAN_BUILD_VERSION == 11 ]]; then
  export DEPENDS="libevent-2.1-7"
fi

git submodule init
git submodule update

./autogen.sh
LIBS=-lpthread ./configure --prefix=/usr/local --enable-evdns=no --with-openssl=/opt/boringssl-fips

git config --global user.email "database-team+pgbouncer@cloudflare.com"
git config --global user.name "database-team pgbouncer"

# apply patch for fixes in libusual submodule for use with BoringSSL
git apply ./patches/0001-Some-BoringSSL-fixes-for-libusual.patch
cd ./lib
git add .
git commit -a --allow-empty-message -m ""
# update PgBouncer to track newly updated submodule.
# Don't commit (committing will append commit hash to package version and break high-state).
cd ..
git add ./lib

make clean all
sudo make install
make pgbouncer
