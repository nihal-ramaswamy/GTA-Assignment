#! /bin/sh

for folder in boruvka chinese_postman fleury max_match_bipartite reverse_delete tarjan welsh_powell
do
    echo "running " $folder
    echo "------------------------------------------------"
    cd $folder
    make
    make clean
    cd ..
    echo "------------------------------------------------"
done
