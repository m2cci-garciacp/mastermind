# run client several times
set -e # exit if error

fname="data_lvl7"

#  forced into range
test=("0" "4" "5" "6" "55" "20000" "-1" "" "\n" "\t" "1111111111111111111111111111111111111111111111","a" "asdfszsdgdgfz" )

# every try: essaies one word value and then there is 7 to wrap up.
for x in "${test[@]}";
do
    newfname="./data/${fname}_${x}.dat";
    echo "${x}" > $newfname
    cat "./scripts/${fname}.dat" >> $newfname
done


#  surprise
# every try: essaies one word value and then there is 7 to wrap up.
for x in $(seq 0 255);
do
    newfname="./data/${fname}_${x}.dat";
    echo "${x}" > $newfname
    cat "./scripts/${fname}.dat" >> $newfname
done



