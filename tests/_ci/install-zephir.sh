#!/usr/bin/env bash
#
# This file is part of the Phalcon.
#
# (c) Phalcon Team <team@phalconphp.com>
#
# For the full copyright and license information, please view the LICENSE
# file that was distributed with this source code.

PROJECT_ROOT=$(readlink -enq "$(dirname $0)/../../")
ZEPHIRDIR=${PROJECT_ROOT}/vendor/phalcon/zephir

if [ ! -d "${ZEPHIRDIR}" ]; then
	echo -e "The ${ZEPHIRDIR} directory does not exists. First run 'composer install'"
	exit 1
fi

cd ${ZEPHIRDIR}

sed "s#%ZEPHIRDIR%#$ZEPHIRDIR#g" bin/zephir > bin/zephir-cmd
chmod 755 bin/zephir-cmd

mkdir -p ${HOME}/bin

cp ./bin/zephir-cmd ${HOME}/bin/zephir
rm ./bin/zephir-cmd

cd ${PROJECT_ROOT}

zephir version