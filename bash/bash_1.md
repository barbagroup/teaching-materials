Redirect & Piping
------------------

There are always three default files open, stdin (the keyboard), stdout (the screen), and stderr (error messages output to the screen). These, and any other open files, can be redirected. Redirection simply means capturing output from a file, command, program, script, or even code block within a script and sending it as input to another file, command, program, or script.

A following example will show how redirection works:
*wc* command stands for wordcount, and * is the wildcard character.

```shell
> wc -l *.md
       8 Calendar.md
      11 README.md
       3 Test.md
      91 Topics.md
     113 total
```
Flag "*-l*" only counts the number of lines in the *.md* files. We can use ">" to write/overwrite the output into a file:

```shell
> wc -l *.md > length.txt
```

There is no output on the screen since we redirect the output to *length.txt* file. Then if we want to find the .md file with the minimum lines, we can use *sort* command. *head -1* command gives the first line of a file.

```shell
> sort lengths.txt > sorted_length.txt
> cat sorted_length.txt
       3 Test.md
       8 Calendar.md
      11 README.md
      91 Topics.md
     113 total
> head -1 lengths.txt
       3 Test.md
```

In this method, we created several temporary files which are not necessary, instead we can use pipes to get rid of *length.txt* and *sorted_length.txt* file.

```shell
> wc -l *.md | sort | head -1
       3 Test.md
```

By using "|" as a pipe, we get the same result. A pipe uses the output of the left side as the input of the right side, without creating the temporary files.  

As a supplement, ">>" adds the standard output at the end of an existing file, rather than overwrites the previous file.


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

**Display the Value** -> *set* / *env* / *echo*

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

**Change PATH Variable** -> *export*

```shell
> export PATH=$PATH:/Users/tingyu66/git/barbagroup/teaching-materials/bash
```

If we want to make the change permenantly, we need to edit the user's *.bash_profile* file in the user's home directory.



Alias
-------------------
 *alias* is a command which enables a replacement of a string by another string. 
 
 **Create & Remove an Alias** -> *alias* & *unalias*
 
 syntax: alias **[name]**='[*a command or string*]', for example:
 
 ```shell
 > alias ll='ls -l'
 > ll
 -rw-r--r--@ 1 tingyu66  staff   137B Sep  2 15:06 bash_1.md
 ```
 *alias* command without any argument shows all the aliases that have been defined.
 If we want to remove the alias, we can use *unalias*:
 
 ```shell
 > unalias ll
 ```
 
 The script above only works on current work session, in order to make an alias permenant and global, we can add it into */etc/bashrc*.
 
 
 


