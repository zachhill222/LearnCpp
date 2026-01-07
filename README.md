Most examples can be compiled with
```console
user@host: ~/dir/$ g++ -o main <filename>.cpp
```
and then run with
```console
user@host: ~/dir/$ ./main
```
or (if you have valgrind for example)
```console
user@host: ~/dir/$ valgrind ./main
```
to verify that there are no memory leaks. It may be useful to change some of the examples to see how memory leaks can happen.
