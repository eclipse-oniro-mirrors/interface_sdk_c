#!/bin/bash
# Copyright (c) Huawei Technologies Co., Ltd. 2020-2030. All rights reserved.
set -e

while getopts "o:i:t:h" arg
do
    case "${arg}" in
        "o")
            OUT_DIR=${OPTARG}
            ;;
        "i")
            SOURCE_DIR=${OPTARG}
            ;;
        "t")
            TARGET_ARCH=${OPTARG}
            ;;
        "h")
            echo "help"
            ;;
        ?)
            echo "unkonw argument"
            exit 1
            ;;
    esac
done

if [ ! -d "${OUT_DIR}" ];then
    mkdir -p ${OUT_DIR}
fi

if [ ! -d "${OUT_DIR}/sys" ];then
    mkdir -p ${OUT_DIR}/sys
fi

cp -rp ${SOURCE_DIR}/fortify/  ${OUT_DIR}
cp ${SOURCE_DIR}/sys/select.h  ${OUT_DIR}/sys/
cp ${SOURCE_DIR}/sys/stat.h    ${OUT_DIR}/sys/
cp ${SOURCE_DIR}/sys/time.h    ${OUT_DIR}/sys/
cp ${SOURCE_DIR}/alloca.h      ${OUT_DIR}
cp ${SOURCE_DIR}/ctype.h       ${OUT_DIR}
cp ${SOURCE_DIR}/fcntl.h       ${OUT_DIR}
cp ${SOURCE_DIR}/features.h    ${OUT_DIR}
cp ${SOURCE_DIR}/math.h        ${OUT_DIR}
cp ${SOURCE_DIR}/pthread.h     ${OUT_DIR}
cp ${SOURCE_DIR}/sched.h       ${OUT_DIR}
cp ${SOURCE_DIR}/signal.h      ${OUT_DIR}

cp ${SOURCE_DIR}/stdarg.h      ${OUT_DIR}
cp ${SOURCE_DIR}/stddef.h      ${OUT_DIR}
cp ${SOURCE_DIR}/stdint.h      ${OUT_DIR}
cp ${SOURCE_DIR}/stdio.h       ${OUT_DIR}
cp ${SOURCE_DIR}/stdlib.h      ${OUT_DIR}
cp ${SOURCE_DIR}/string.h      ${OUT_DIR}
cp ${SOURCE_DIR}/strings.h     ${OUT_DIR}
cp ${SOURCE_DIR}/time.h        ${OUT_DIR}
cp ${SOURCE_DIR}/unistd.h      ${OUT_DIR}

case "$(uname -s)" in
    Darwin*|FreeBSD*|OpenBSD*|NetBSD*)
        sed -E -i '' '/PTHREAD_[A-Z]+_INITIALIZER/d' ${OUT_DIR}/pthread.h ;;
    Linux*|CYGWIN*|MINGW*|MSYS*|SunOS*|AIX*|HP-UX*)
        sed -E -i '/PTHREAD_[A-Z]+_INITIALIZER/d' ${OUT_DIR}/pthread.h ;;
    *)
        echo "Unsupported OS: $(uname -s)" >&2
        exit 1
        ;;
esac