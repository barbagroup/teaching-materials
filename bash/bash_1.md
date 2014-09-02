File Permission
----------------------
**Permission Groups**

+ u-owner
+ g-group
+ a-all users

**Permission Types**

+ r-read
+ w-write
+ e-execute

**Viewing the Permissions** -> *ls -l*

List files in long format: [*file_type*][*permission*][*#hard_link*][*owner*][*group*][*size*][*date*][*file_name*]

```shell
> ls -l
-rw-r--r--@ 1 tingyu66  staff   137B Sep  2 15:06 bash_1.md
```
**Set & Change Permissions** -> *chmod*

```shell
> chmod a+rw bash_1.md
> ls -l
-rw-rw-rw-@ 1 tingyu66  staff   137B Sep  2 15:06 bash_1.md
```

also, we can use octonary reference to set permission, for example: rw- = 4+2+0 = 6

```shell
> chmod 666 bash_1.md
> ls -l
-rw-rw-rw-@ 1 tingyu66  staff   137B Sep  2 15:06 bash_1.md
```
**Change Ownership** -> *chown*

```shell
> chown guest:nogroup bash_1.md
> ls -l
-rw-r--r--@ 1 guest  nogroup   137B Sep  2 15:06 bash_1.md
```

PATH
---------------
PATH is an *environmental variable* that tells the shell which directories to search for executable files.
The value of PATH is a series of absolute paths separated by colon. 

**Manipulate Shell Variables & Functions** -> *set*

```shell
> set
BASH=/bin/bash
...
PATH=/Users/tingyu66/anaconda/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/usr/texbin
...
USER=tingyu66
...
```

, or just display the PATH using *echo*

```shell
> echo $PATH
PATH=/Users/tingyu66/anaconda/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/usr/texbin
```

