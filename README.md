# ls

This program is a simple implementation of "ls" command with the following features:
* listing one or multiple directories
* Support long format (file type, permissions, num of links, user, group, time, ...) using "-l" option
* Show hidden files using "-a" option
* Show I_node value using "-i" option

command used for compilation:
```
$ gcc myls.c -o myls
```
run example:
```
wizo@wizo:~/workarea/FileSystem/ls$ ./myls
myls.c     myls       
wizo@wizo:~/workarea/FileSystem/ls$ ./myls -a
myls.c     .          myls       ..         
wizo@wizo:~/workarea/FileSystem/ls$ ./myls -i
4738381    myls.c     4719300    myls       
wizo@wizo:~/workarea/FileSystem/ls$ ./myls -ia
4738381    myls.c     4738279    .          4719300    myls       4731638    ..         
wizo@wizo:~/workarea/FileSystem/ls$ ./myls -l
-rw-rw-r--   1     wizo       wizo       5331         Nov  9 18:25   myls.c     
-rwxrwxr-x   1     wizo       wizo       17880        Nov  9 18:25   myls       
wizo@wizo:~/workarea/FileSystem/ls$ ./myls -li
4738381    -rw-rw-r--   1     wizo       wizo       5331         Nov  9 18:25   myls.c     
4719300    -rwxrwxr-x   1     wizo       wizo       17880        Nov  9 18:25   myls       
wizo@wizo:~/workarea/FileSystem/ls$ ./myls -lia
4738381    -rw-rw-r--   1     wizo       wizo       5331         Nov  9 18:25   myls.c     
4738279    drwxrwxr-x   2     wizo       wizo       4096         Nov  9 18:25   .          
4719300    -rwxrwxr-x   1     wizo       wizo       17880        Nov  9 18:25   myls       
4731638    drwxrwxr-x   4     wizo       wizo       4096         Nov  7 22:03   ..         
```
