####################
# Makefile
# Author: Cole Sigmon
# Date: April 11, 2023
#
# COSC 3750, Homework 7
#
# This is a make file for wytalk.
# Implemented with a clean method.
# ##################

CC = gcc
CFLAGS = -Wall -ggdb
RM = /bin/rm -f

.PHONY: wytalkC clean

wytalk: wytalkC.c socketfun.c
	${CC} ${CFLAGS} wytalkC.c socketfun.c -o wytalkC

clean:
	${RM} wytalkC
