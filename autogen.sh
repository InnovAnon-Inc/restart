#! /bin/sh
set -exo nounset

autoreconf --install

if [ $# -eq 0 ] ; then exit 0
else
	test "x$1" == xmake
	./configure
	make
	make install
fi
