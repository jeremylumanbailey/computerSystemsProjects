#! /bin/bash
# Interactive reading of a variable
#Display variable input
if [ "$1" == "" ]
then
  echo "Enter Your Name:"
  read name
  echo Your Name is: $name

else

 echo Your Name is: $1
fi
