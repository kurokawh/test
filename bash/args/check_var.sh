#!/bin/sh

NP_ENV=$1
FILTER=$2
DB_NAME=$3
LOG_ID=$4

echo "1: NP_ENV: $NP_ENV"
echo "2: FILTER: $FILTER"
echo "3: DB_NAME: $DB_NAME"
echo "4: LOG_ID: $LOG_ID"
if [ $NP_ENV = "1" ] ; then
	echo "NP_ENV is set to: $NP_ENV"
else 
	echo "NP_ENV is not 1"
fi

if [ -n "$FILTER" ] ; then
	echo "FILTER is set to: $FILTER"
else 
	echo "FILTER is not set"
fi

# NG
if [ $DB_NAME = "" ] ; then
	echo "DB_NAME is set to: $DB_NAME"
else 
	echo "DB_NAME is not set"
fi


if [ $LOG_ID -lt 10 ] ; then
	FILTER_DIR="d000$LOG_ID"
elif [ $LOG_ID -lt 100 ] ; then
	FILTER_DIR="d00$LOG_ID"
else
	FILTER_DIR="d0$LOG_ID"
fi

echo "command: csv2db ${DB_PATH}\\${DB_NAME} -s d${LOG_ID} -r ${FILTER_DIR}/${FILTER}*"
