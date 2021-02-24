#!/bin/bash
function extractAndThen { 
	zipinfo -1 ${1} | grep /${2}/.*.so$ > ${2}.text
	sed -i "" "s|lib/${2}/||g" ${2}.text 
#	echo "generate for ${2} done."
}; 

function generateSoNameForAbis { 
	array=(armeabi armeabi-v7a arm64-v8a);
	size=`expr ${#array[@]} - 1`
	for(( i=0;i<${#array[@]};i++))
	do
		extractAndThen  ${1}  ${array[i]};
		if [[ $i -ne 0 ]]; then
			diffTwoFile ${array[i]}  ${array[i-1]};
		fi
		if [[ $i -eq $size ]]; then
			diffTwoFile ${array[i]}  ${array[0]};
		fi
	done;
};

function diffTwoFile { 
	diff ${1}.text  ${2}.text -y -W 100 > compare_${1}_${2}.text
	echo "compare between ${1} and ${2} is in compare_${1}_${2}.text [done]."
};
function run_valid {
	if [[ -z ${1} ]]; then
		echo "Usage: sh diffAbi.sh [apk File]"
		return;
	fi
	if [[ -f ${1} && -r ${1} ]]; then
		generateSoNameForAbis ${1}
	else 
		echo "apk not exists or unreadable."
		echo "Usage: sh diffAbi.sh [apk File]"
	fi
};
run_valid $1

