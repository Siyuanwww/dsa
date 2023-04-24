for (( i=1; ; i++)) {
    ./gen > in
    ./std < in > ans
    ./main < in > out
    diff ans out > /dev/null
    if [ $? -ne 0 ]; then
        echo Error occurrence!
        exit
    fi
    echo Test case $i: Accepted
}