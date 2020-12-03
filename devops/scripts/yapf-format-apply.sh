#!/bin/bash

set -e

#
# This is running a yapf format test
# by doing a filtering step and then analysing
# the result of applying yapf format
#

echo ""
echo ""
echo "------------ Applying YAPF formatting for python ---------------"

# Retrieve list of files that were changed in source branch
# with respect to master (target branch)
tb="origin/master"

# Get all modified files with respect to master
filelist=`git diff ${tb}... --name-status | awk '{if($1 == "M") print $2}' | grep ".*\.py$" || continue`

if [[ -z $filelist ]]; then
  echo "||YAPF||: No modified files to check yapf format. Hence, Exiting yapf-format stage"
  exit 0;
else
  echo "Files modified:"
  echo ${filelist}
fi

# check list of files
for f in $filelist; do
  echo "||YAPF||: CHECKING MATCHING FILE ${f}"
  # apply the yapf formatting script
  yapf -i "${f}"
done

# check if something was modified
notcorrectlist=`git status | grep modified | awk '{ $1=""; print}' | grep ".*\.py$" || continue`
# if nothing changed ok
if [[ -z $notcorrectlist ]]; then
  # send a negative message to gitlab
  echo "||YAPF||: Excellent. **VERY GOOD FORMATTING!** "
  git reset HEAD --hard
  echo "------------ YAPF formatting stage finished!! -----------------"
  exit 0;
else
  echo "||YAPF||: Modified files are not yapf Formatted. Please apply yapf formatting!!!"
  echo "||YAPF||: The following python files have formatting problems:";
  for f in $notcorrectlist; do
      echo $f
  done
fi


echo "$1"
# cleanup changes in git
if [ $1 = True ]; then
  git reset HEAD --hard
fi

echo "------------ YAPF formatting stage finished!! -----------------"

exit 1
