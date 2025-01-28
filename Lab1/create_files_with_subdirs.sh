#!/bin/bash

PROGRAM_LANG=("Python" "Java" "Javascript" "C++" "C#" "Ruby" "PHP" "Swift" "Go" "R")
MAIN_DIR=$(date '+%Y-%m-%d_%H-%M-%S')
mkdir "$MAIN_DIR"

# Creates directories file101 to file110
for i in {101..110}; do 
    FILE_DIR="file$i"
    mkdir "$MAIN_DIR/$FILE_DIR"
    #Creates each file in each director tuser101 to tuser 110 
    for a in {101..110}; do
        FILE="tuser$a.txt"
        touch "$MAIN_DIR/$FILE_DIR/$FILE"
        
        # Ensure the index for PROGRAM_LANG is a-101 to map correctly to the array
        LANG_INDEX=$((a - 101))

        echo "${PROGRAM_LANG[$LANG_INDEX]}" > "$MAIN_DIR/$FILE_DIR/$FILE"
    done 
done
