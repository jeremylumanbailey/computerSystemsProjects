#! /bin/bash
# Interactive reading of a variable
#Display variable input


name_please() {
  echo Enter Your Name:
  read name
  echo Your Name is: $name
}

COUNT=$1
USEME=0
echo Count var is $COUNT

while [ $USEME -lt $COUNT ]
do
 name_please
 USEME=$((USEME+1))
done

