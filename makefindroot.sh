#!/bin/sh

ORIG=gslfindroot
# ORIG=gslmultiroot
FUNCTION_NAME=$1

cat ${ORIG}_func_skel.c | sed s/func_skel/${FUNCTION_NAME}/g > gslfindroot_${FUNCTION_NAME}.c
cat ${ORIG}_func_skel.h | sed s/func_skel/${FUNCTION_NAME}/g > gslfindroot_${FUNCTION_NAME}.h


