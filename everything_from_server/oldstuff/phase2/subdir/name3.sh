#! /bin/bash
# Interactive reading of a variable
#Display variable input

COUNT=$1
USEME=0
echo Count var is $COUNT

while [ $USEME -lt $COUNT ]
do
  echo Enter Your Name:
  read name
  echo Your Name is: $name
  USEME=$((USEME+1))
done
