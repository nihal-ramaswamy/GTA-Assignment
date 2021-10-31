# GTA Assignment 1

```
@author: Nihal Ramaswamy (PES1UG19CS297)
```

## Directory
There are a total of seven algorithms implemented:
1.  [boruvka](./boruvka)
2.  [chinese postman](./chinese_postman)
3.  [fleury](./fleury)
4.  [maximum matching bipartite](./max_match_bipartite)
5.  [reverse delete](./reverse_delete)
6.  [tarjan](./tarjan)
7.  [welsh_powell](./welsh_powell)
The above said algorithms are placed in their dedicated folders.
The [include](./include) folder contains the implementation of the following
1.  [Disjoint Set Union](./include/dsu.hpp)
2.  [Edge Class](./include/edge.hpp)
3.  [Graph Class](./include/graph.hpp)
4.  [Miscellaneous](./include/misc.hpp)
The above algorithms inherits the `Graph` class and implements functions necessary for it.


## Directory Structure
![Directory Structure](./directory_structure.png)

## Running the Project
There are two ways of running this project.

### Method 1:
Run the file using the bash script.
```bash
chmod a+rx run.sh
./run.sh
```
The [run.sh](./run.sh) file goes to each of the folders containing the implemented algorithm and runs the dedicated `Makefile`.

### Method 2:
Individually the `Makefile`s for each of the folders containing the algorithms.
```bash
cd <FOLDER>
make
```
To remove the generated files
```bash
make clean
```

## Inputs and Outputs
Inputs are provided via chaning the the default `stdin` and outputs are provided via chaning the default `stdin`.
When running the `Makefile`, it runs the following:
```bash
./${FILE} < input.txt > output.txt
```
Here the `<` changes the the `stdin` from default to `input.txt` which is present in each of the folder.
The `>` changes the the `stdout` from default to `output.txt` which is present in each of the folder.

### Format of input
The first line of the input file contains two integers `N` and `M`, representing the number of nodes in the graph and the number of edges.
The next `M` lines contains three integers `u`, `v` and `w`, representing a bidirectional edge between nodes `u` and `v` with a weight `w`.

### Format of output
Format of the output is explained in the individual directories for the algorithms.

