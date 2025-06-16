#!/usr/bin/env bash

is_save=0
function Is_Save_Data_2File()
{
    read -N 1 -p "Do you want to save the data in to a file? (y/n)"$'\n' -s is_save  

    if [[ "$is_save" == y ]] || [[ "$is_save" == Y ]]; then
    is_save=1
    else
    is_save=0
    fi    
}