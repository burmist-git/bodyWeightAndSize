#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2020 - LBS - (Single person developer.)                 #
# Tue Mar 24 11:56:17 CET 2020                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

LC_TIME=en_US.UTF-8
LANG=en_US.UTF-8

source /home/burmist/root_v6.14.00/root-6.14.00-install/bin/thisroot.sh

function push_sh {
    vecparID=0
    $sourceHome/push 0 $outRootFile $vecparID 2 $1 $2
}

function plot_sh {
    $sourceHome/plot 0 $inRootFile $vecNamesFile
}

function ldd_info_sh {
    echo "Info --> ldd push"
    ldd push
    echo "Info --> ldd plot"
    ldd plot
}

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -push   : example of the push "
    echo " [1]         : weight "
    echo " [2]         : size "
    echo " [0] -plot   : example of the plot "
    echo " [0] -ldd    : print ldd info "
    echo " [0] -h      : print help"
}

sourceHome=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
dataFolder=$sourceHome'/data/'
outRootFile=$dataFolder'bodyWeightAndSize.root'
inRootFile=$outRootFile
vecNamesFile=$sourceHome'/vectorOfinDataValuesNames.dat'

mkdir -p $dataFolder

if [ $# -eq 0 ]; then    
    printHelp
else
    if [ "$1" = "-push" ]; then
	if [ $# -eq 3 ]; then
	    mass=$2
	    size=$3
	    push_sh $mass $size
	else
            printHelp
        fi
    elif [ "$1" = "-plot" ]; then
	plot_sh
    elif [ "$1" = "-ldd" ]; then
	ldd_info_sh
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi
#espeak "I have done"
