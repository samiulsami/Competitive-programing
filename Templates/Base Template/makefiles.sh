#!/bin/bash
#Shell script to create copies of Template
#Pass at most 2 arguments: Name of template file, and number of copies to create
#Example: bash makefiles.sh Template.cpp 5
cnt=10
template="../Template.cpp"
if ! [ -z "$1" ]
  then
	template="../$1"
fi

if ! [ -z "$2" ]
  then
	cnt=$2
fi

if (( cnt > 26 )); then
	cnt=26
fi

newfoldername="Solutions"
mkdir $newfoldername
cd $newfoldername

for((i=0; i<cnt; i++))
	do	
		A=$(printf \\$(printf '%03o' $((i+65))))
		cat $template > "$A.cpp"
		start "$A.cpp"
		sleep 0.03
done

