#!/bin/bash
#
# read text from file. and compare it.


# read all text in file
ALL_TXT=`cat read_text.sh`
echo $ALL_TXT
echo ""

# read bottom 1 line
BOTTOM_TXT=`tail -n 1 read_text.sh`
echo "BOTTOM: $BOTTOM_TXT"

# read top 1 lines
HEAD_TXT=`head -n 1 read_text.sh`
echo "HEAD: $HEAD_TXT"

# rm return code
HEAD_TXT_NR=`echo $HEAD_TXT | tr -d '\r' | tr -d '\n'`
BOTTOM_TXT_NR=`echo $BOTTOM_TXT | tr -d '\r' | tr -d '\n'`

if [ $HEAD_TXT = "#!/bin/bash" ]; then
  echo "head: match"
else
  echo "head: not match"
fi

if [ $BOTTOM_TXT = "fi" ]; then
  echo "bottom: match"
else
  echo "bottom: not match"
fi

# remove return code:  tr -d '\r'
if [ $HEAD_TXT = "#!/bin/bash" ]; then
  echo "head: match"
else
  echo "head: not match"
fi
if [ $BOTTOM_TXT_NR = "fi" ]; then
  echo "bottom: match"
else
  echo "bottom: not match"
fi
