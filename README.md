# [advent of code](https://adventofcode.com/)

## organization
each day has a folder
- `main.cpp` is the program that computes the solution for both parts
- `main` is its compiled binary
- `input.txt` is the input i got from the website

## usage
run these commands from the project root.

```
./compile.bash <dayfolder>
```
- uses clang to compile the `main.cpp` file in that day's folder. 
the resulting binary is in a file called `main`.

```
./run.bash <dayfolder>
```
- runs the `main` binary inside that day's folder.