#!/bin/bash
red=`tput setaf 1`
green=`tput setaf 2`
blue=`tput setaf 4`
white=`tput sgr0`

Success=0
Total=5

#Variables#

executable=./zappy_ai

#VALID ARGS#
$executable -n teamName -p 123
ret=$?
if [ $ret -eq 0 ]
then
    echo "${green}Success test for valid arguments${white}"
    Success=$((Success+1))
else
    echo "${red}Invalid test for valid arguments${white}"
fi

#VALID ARGS 2#
$executable -p 123 -n teamName -h localhost
ret=$?
if [ $ret -eq 0 ]
then
    echo "${green}Success test for valid arguments 2${white}"
    Success=$((Success+1))
else
    echo "${red}Invalid test for valid arguments 2${white}"
fi

#INVALID ARGUMENTS#
$executable -p invalidArgs -n teamName -h localhost
ret=$?
if [ $ret -eq 2 ]
then
    echo "${green}Success test for invalid arguments${white}"
    Success=$((Success+1))
else
    echo "${red}Invalid test for invalid arguments${white}"
fi

#TOO MUCH ARGUMENTS#
$executable -p 123 -n teamName -h localhost -tooMuch arguments
ret=$?
if [ $ret -eq 2 ]
then
    echo "${green}Success test for too much arguments${white}"
    Success=$((Success+1))
else
    echo "${red}Invalid test for too much arguments${white}"
fi

#TOO FEW ARGUMENTS#
$executable -p 123
ret=$?
if [ $ret -eq 2 ]
then
    echo "${green}Success test for too few arguments${white}"
    Success=$((Success+1))
else
    echo "${red}Invalid test for too few arguments${white}"
fi

echo "${green}Success : $Success${white}"
echo "${blue}Total : $Total${white}"