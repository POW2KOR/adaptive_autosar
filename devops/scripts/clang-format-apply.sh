#!/bin/bash

set -e

#
# This is running a clang-format test
# by doing a filtering step and then analysing
# the result of applying clang-format
#

echo ""
echo ""
echo "------------ Applying CLANG formatting ---------------"

# Retrieve list of files that were changed in source branch
# with respect to master (target branch)
tb="origin/master"

# Get all modified files with respect to master
filelist=`git diff ${tb}... --name-status |  awk '{if($1 == "M") print $2}' | egrep "\.h$|\.hpp$|\.cc$|\.CPP$|\.C$|\.cpp$|\.c$|\.cxx$" || continue`

if [[ -z $filelist ]]; then
  echo "||CLANG||: No modified files to check clang format. Hence, Exiting clang-format stage"
  exit 0;
else
  echo "||CLANG||: Files modified:"
  echo ${filelist}
fi

# check list of files
for f in $filelist; do
  echo "||CLANG||: CHECKING MATCHING FILE ${f}"
  # apply the clang-format script
  clang-format --style=file -i "${f}"
done

# check if something was modified
notcorrectlist=`git status | grep modified | awk '{ $1=""; print}' | egrep "\.h$|\.hpp$|\.cc$|\.CPP$|\.C$|\.cpp$|\.c$|\.cxx$" || continue`
# if nothing changed ok
if [[ -z $notcorrectlist ]]; then
  echo "||CLANG||: Excellent. **VERY GOOD FORMATTING!** "
  git reset HEAD --hard
  echo "----------- Clang formatting stage finished!! ------------"
  exit 0;
else
  echo "||CLANG||: Modified files are not Clang-Formatted. Please apply clang-format!!!"
  echo "||CLANG||: The following files have clang-format problems:";
  for f in $notcorrectlist; do
      echo $f
  done
fi

# cleanup changes in git
if [ $1 = True ]; then
  git reset HEAD --hard
fi

echo "----------- Clang formatting finished!! ------------"
exit 1
