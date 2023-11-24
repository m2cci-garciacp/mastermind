# run client several times
set -e # exit if error

for lvl in $(seq 5 7);
do
for i in $(seq 1 100);
do
    echo ================
    echo level $lvl : $i
    echo ================
    ./../../client < "./data/data_lvl${lvl}.dat"

done
done
