# run client several times
set -e # exit if error

for x in `find ./data/data_lvl7_* -maxdepth 1 -type f`; do
    echo the file name is $x
    
    for i in $(seq 1 10);
    do
        echo ================ > $1
        echo  fname $x : $i > $1
        echo ================ > $1
        ./../../client < $x > $1

        tail -n 10 $1

    done

done

