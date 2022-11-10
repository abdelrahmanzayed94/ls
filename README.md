# ls

This program is a simple implementation of "ls" command with the following features:
* listing one or multiple directories
* Support long format (file type, permissions, num of links, user, group, time, ...) using "-l" option
* Show hidden files using "-a" option
* Show I_node value using "-i" option
* Presentation of sticky bit
* Supporting recursive ls using "-R" option

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
wizo@wizo:~/workarea/FileSystem/ls$ ./myls /tmp / -lia
/tmp:
1179699    drwx------   2     wizo       wizo       4096         Nov  9 11:40   ssh-LAGen1QEb99e 
1179665    drwx------   3     root       root       4096         Nov  9 11:39   systemd-private-ef623cde7d46476b9ce28b5bcaad9258-switcheroo-control.service-D7lwei 
1179658    drwxrwxrwt   2     root       root       4096         Nov  9 11:39   .Test-unix 
1179661    drwx------   3     root       root       4096         Nov  9 11:39   systemd-private-ef623cde7d46476b9ce28b5bcaad9258-systemd-timesyncd.service-hbhZvf 
786434     -rw-------   1     wizo       wizo       0            Nov  9 11:40   config-err-ClKO4b 
1179653    drwxrwxrwt   2     root       root       4096         Nov  9 11:39   VMwareDnD  
1179663    drwx------   3     root       root       4096         Nov  9 11:39   systemd-private-ef623cde7d46476b9ce28b5bcaad9258-ModemManager.service-NUkcdh 
786433     drwxrwxrwt   19    root       root       4096         Nov  9 18:28   .          
1179657    drwxrwxrwt   2     root       root       4096         Nov  9 11:39   .font-unix 
1179685    drwx------   2     wizo       wizo       4096         Nov  9 18:26   Temp-bcb1fdb9-6f40-4500-93bd-61af83b0c613 
1179698    drwx------   2     wizo       wizo       4096         Nov  9 11:40   tracker-extract-files.1000 
1193027    drwx------   3     root       root       4096         Nov  9 11:40   systemd-private-ef623cde7d46476b9ce28b5bcaad9258-colord.service-kz9xhi 
1193031    drwx------   3     root       root       4096         Nov  9 11:40   snap.snap-store 
1179654    drwxrwxrwt   2     root       root       4096         Nov  9 11:40   .X11-unix  
2          drwxr-xr-x   20    root       root       4096         Sep 10 12:56   ..         
1179695    drwx------   3     root       root       4096         Nov  9 11:40   systemd-private-ef623cde7d46476b9ce28b5bcaad9258-upower.service-ZyCfRh 
1179667    drwx------   3     root       root       4096         Nov  9 11:39   systemd-private-ef623cde7d46476b9ce28b5bcaad9258-systemd-logind.service-xhlBZh 
1179655    drwxrwxrwt   2     root       root       4096         Nov  9 11:40   .ICE-unix  
1179659    drwx------   3     root       root       4096         Nov  9 11:39   systemd-private-ef623cde7d46476b9ce28b5bcaad9258-systemd-resolved.service-lIlFuf 
1179656    drwxrwxrwt   2     root       root       4096         Nov  9 11:39   .XIM-unix  

/:
12         -rw-------   1     root       root       2147483648   Sep 10 12:53   swapfile   
16         drwxr-xr-x   2     root       root       4096         Sep 10 14:01   lib64      
5505025    drwxrwxr-x   2     root       root       4096         Sep 10 12:56   cdrom      
18         drwxr-xr-x   2     root       root       20480        Nov  9 11:40   sbin       
2621441    drwxr-xr-x   19    root       root       4140         Nov  9 11:39   dev        
1703937    drwxr-xr-x   14    root       root       4096         Feb 23 10:53   var        
5898241    drwxr-xr-x   33    root       root       900          Nov  9 11:51   run        
15         drwxr-xr-x   2     root       root       4096         Feb 23 10:47   lib32      
5373953    drwxr-xr-x   3     root       root       4096         Sep 10 13:32   opt        
1048577    drwxr-xr-x   2     root       root       4096         Feb 23 10:47   mnt        
2          drwxr-xr-x   20    root       root       4096         Sep 10 12:56   .          
1179649    dr-xr-xr-x   13    root       root       0            Nov  9 11:39   sys        
917505     drwxr-xr-x   14    root       root       4096         Feb 23 10:48   usr        
17         drwxr-xr-x   2     root       root       4096         Feb 23 10:47   libx32     
11         drwx------   2     root       root       16384        Sep 10 12:53   lost+found 
4456449    dr-xr-xr-x   274   root       root       0            Nov  9 11:39   proc       
1835009    drwxr-xr-x   9     root       root       4096         Feb 23 10:54   snap       
1310721    drwxr-xr-x   2     root       root       4096         Feb 23 10:47   srv        
13         drwxr-xr-x   2     root       root       45056        Oct 31 15:56   bin        
786433     drwxrwxrwt   19    root       root       4096         Nov  9 18:28   tmp        
14         drwxr-xr-x   126   root       root       4096         Oct  1 00:08   lib        
2          drwxr-xr-x   20    root       root       4096         Sep 10 12:56   ..         
5767169    drwxr-xr-x   134   root       root       12288        Oct 31 15:56   etc        
5242881    drwxr-xr-x   4     root       root       4096         Oct 31 15:49   boot       
4587521    drwx------   4     root       root       4096         Sep 10 13:09   root       
1572865    drwxr-xr-x   3     root       root       4096         Sep 10 13:11   media      
4718593    drwxr-xr-x   3     root       root       4096         Sep 10 12:57   home
wizo@wizo:~/workarea/FileSystem/ls$ ./myls /home/wizo/workarea/FileSystem -R
/home/wizo/workarea/FileSystem:
fdisk      ls         

/home/wizo/workarea/FileSystem/fdisk:
myhdd      myfdisk.c  myfdisk    

/home/wizo/workarea/FileSystem/ls:
myls.c     myls       

wizo@wizo:~/workarea/FileSystem/ls$ ./myls /home/wizo/workarea/FileSystem -liRa
/home/wizo/workarea/FileSystem:
4733521    drwxrwxr-x   2     wizo       wizo       4096         Nov  7 22:03   fdisk      
4731638    drwxrwxr-x   4     wizo       wizo       4096         Nov  7 22:03   .          
4738279    drwxrwxr-x   2     wizo       wizo       4096         Nov 10 19:26   ls         
4719518    drwxrwxr-x   7     wizo       wizo       4096         Oct 31 14:28   ..         

/home/wizo/workarea/FileSystem/fdisk:
4735952    -rw-rw-r--   1     wizo       wizo       1048576      Oct 31 16:51d  myhdd      
4733521    drwxrwxr-x   2     wizo       wizo       4096         Nov  7 22:03d  .          
4735962    -rw-rw-r--   1     wizo       wizo       3445         Nov  1 17:10d  myfdisk.c  
4731638    drwxrwxr-x   4     wizo       wizo       4096         Nov  7 22:03d  ..         
4719184    -rwxrwxr-x   1     wizo       wizo       17056        Nov  1 17:10d  myfdisk    

/home/wizo/workarea/FileSystem/ls:
4737562    -rw-rw-r--   1     wizo       wizo       6156         Nov 10 19:26d  myls.c     
4738279    drwxrwxr-x   2     wizo       wizo       4096         Nov 10 19:26d  .          
4719300    -rwxrwxr-x   1     wizo       wizo       17928        Nov 10 19:26d  myls       
4731638    drwxrwxr-x   4     wizo       wizo       4096         Nov  7 22:03d  ..    

```
