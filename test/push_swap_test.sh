#!/bin/bash

PATH='/Users/thle/Desktop/projects/push_swap'

#test for 3
# $PATH/push_swap 1 2 3
# $PATH/push_swap 1 3 2
# $PATH/push_swap 2 1 3
# $PATH/push_swap 2 3 1
# $PATH/push_swap 3 2 1
# $PATH/push_swap 3 1 2

#test for 5
# $PATH/push_swap 1 2 3 4 5
# $PATH/push_swap 1 2 3 5 4
# $PATH/push_swap 1 2 4 3 5
# $PATH/push_swap 1 2 4 5 3
# $PATH/push_swap 1 2 5 4 3
# $PATH/push_swap 1 2 5 3 4
# $PATH/push_swap 1 3 2 4 5
# $PATH/push_swap 1 3 2 5 4
# $PATH/push_swap 1 3 4 2 5
# $PATH/push_swap 1 3 4 5 2
# $PATH/push_swap 1 3 5 4 2
# $PATH/push_swap 1 3 5 2 4
# $PATH/push_swap 1 4 3 2 5
# $PATH/push_swap 1 4 3 5 2
# $PATH/push_swap 1 4 2 3 5
# $PATH/push_swap 1 4 2 5 3
# $PATH/push_swap 1 4 5 2 3
# $PATH/push_swap 1 4 5 3 2
# $PATH/push_swap 1 5 3 4 2
# $PATH/push_swap 1 5 3 2 4
# $PATH/push_swap 1 5 4 3 2
# $PATH/push_swap 1 5 4 2 3
# $PATH/push_swap 1 5 2 4 3
# $PATH/push_swap 1 5 2 3 4
# $PATH/push_swap 2 1 3 4 5
# $PATH/push_swap 2 1 3 5 4
# $PATH/push_swap 2 1 4 3 5
# $PATH/push_swap 2 1 4 5 3
# $PATH/push_swap 2 1 5 4 3
# $PATH/push_swap 2 1 5 3 4
# $PATH/push_swap 2 3 1 4 5
# $PATH/push_swap 2 3 1 5 4
# $PATH/push_swap 2 3 4 1 5
# $PATH/push_swap 2 3 4 5 1
# $PATH/push_swap 2 3 5 4 1
# $PATH/push_swap 2 3 5 1 4
# $PATH/push_swap 2 4 3 1 5
# $PATH/push_swap 2 4 3 5 1
# $PATH/push_swap 2 4 1 3 5
# $PATH/push_swap 2 4 1 5 3
# $PATH/push_swap 2 4 5 1 3
# $PATH/push_swap 2 4 5 3 1
# $PATH/push_swap 2 5 3 4 1
# $PATH/push_swap 2 5 3 1 4
# $PATH/push_swap 2 5 4 3 1
# $PATH/push_swap 2 5 4 1 3
# $PATH/push_swap 2 5 1 4 3
# $PATH/push_swap 2 5 1 3 4
# $PATH/push_swap 3 2 1 4 5
# $PATH/push_swap 3 2 1 5 4
# $PATH/push_swap 3 2 4 1 5
# $PATH/push_swap 3 2 4 5 1
# $PATH/push_swap 3 2 5 4 1
# $PATH/push_swap 3 2 5 1 4
# $PATH/push_swap 3 1 2 4 5
# $PATH/push_swap 3 1 2 5 4
# $PATH/push_swap 3 1 4 2 5
# $PATH/push_swap 3 1 4 5 2
# $PATH/push_swap 3 1 5 4 2
# $PATH/push_swap 3 1 5 2 4
# $PATH/push_swap 3 4 1 2 5
# $PATH/push_swap 3 4 1 5 2
# $PATH/push_swap 3 4 2 1 5
# $PATH/push_swap 3 4 2 5 1
# $PATH/push_swap 3 4 5 2 1
# $PATH/push_swap 3 4 5 1 2
# $PATH/push_swap 3 5 1 4 2
# $PATH/push_swap 3 5 1 2 4
# $PATH/push_swap 3 5 4 1 2
# $PATH/push_swap 3 5 4 2 1
# $PATH/push_swap 3 5 2 4 1
# $PATH/push_swap 3 5 2 1 4
# $PATH/push_swap 4 2 3 1 5
# $PATH/push_swap 4 2 3 5 1
# $PATH/push_swap 4 2 1 3 5
# $PATH/push_swap 4 2 1 5 3
# $PATH/push_swap 4 2 5 1 3
# $PATH/push_swap 4 2 5 3 1
# $PATH/push_swap 4 3 2 1 5
# $PATH/push_swap 4 3 2 5 1
# $PATH/push_swap 4 3 1 2 5
# $PATH/push_swap 4 3 1 5 2
# $PATH/push_swap 4 3 5 1 2
# $PATH/push_swap 4 3 5 2 1
# $PATH/push_swap 4 1 3 2 5
# $PATH/push_swap 4 1 3 5 2
# $PATH/push_swap 4 1 2 3 5
# $PATH/push_swap 4 1 2 5 3
# $PATH/push_swap 4 1 5 2 3
# $PATH/push_swap 4 1 5 3 2
# $PATH/push_swap 4 5 3 1 2
# $PATH/push_swap 4 5 3 2 1
# $PATH/push_swap 4 5 1 3 2
# $PATH/push_swap 4 5 1 2 3
# $PATH/push_swap 4 5 2 1 3
# $PATH/push_swap 4 5 2 3 1
# $PATH/push_swap 5 2 3 4 1
# $PATH/push_swap 5 2 3 1 4
# $PATH/push_swap 5 2 4 3 1
# $PATH/push_swap 5 2 4 1 3
# $PATH/push_swap 5 2 1 4 3
# $PATH/push_swap 5 2 1 3 4
# $PATH/push_swap 5 3 2 4 1
# $PATH/push_swap 5 3 2 1 4
# $PATH/push_swap 5 3 4 2 1
# $PATH/push_swap 5 3 4 1 2
# $PATH/push_swap 5 3 1 4 2
# $PATH/push_swap 5 3 1 2 4
# $PATH/push_swap 5 4 3 2 1
# $PATH/push_swap 5 4 3 1 2
# $PATH/push_swap 5 4 2 3 1
# $PATH/push_swap 5 4 2 1 3
# $PATH/push_swap 5 4 1 2 3
# $PATH/push_swap 5 4 1 3 2
# $PATH/push_swap 5 1 3 4 2
# $PATH/push_swap 5 1 3 2 4
# $PATH/push_swap 5 1 4 3 2
# $PATH/push_swap 5 1 4 2 3
# $PATH/push_swap 5 1 2 4 3
# $PATH/push_swap 5 1 2 3 4
