Using `git` for version control
===============================

*Version control* is a method to keep track of changes that we introduce to a 
set of files or documents that we use. This is especially useful when writing 
code because most code is written and improved through incremental changes. 
Version control allows us to compare newer versions of code with older 
versions, and investigate when certain changes were made that may have caused 
the code to malfunction. `git` is a one such version control software, which 
was created by Linus Torvalds to help with writing the Linux kernel.

Version control systems store files in a directory known as a repository. Apart 
from the files, a repository also contains information about the history of 
each file, and all the edits that were made. In this tutorial, we will learn 
how to create a `git` repository, add files to it, make changes to those files, 
and record the history of those changes.

Creating a `git` repository
---------------------------

We first start with some new code in a folder. Create a folder and add a Python 
script to it:

```shell
> mkdir -p ~/git/new_repo
> cd ~/git/new_repo
> vim HelloWorld.py
```

Add the following text to the script:

```python
print "Hello world!"
```

Exit the text editor. Now we have a folder called `new_repo` with the script 
`HelloWorld.py` in it. We want to convert this folder into a `git` repository. 
This is done easily:

```shell
> git init
```

This command creates the hidden directory `.git` inside `new_repo`, which 
stores all the information required for the `git` repository. We can check the 
status of this repository using the command:

```shell
> git status
```

which gives the following output:

    # On branch master
    #
    # Initial commit
    #
    # Untracked files:
    #   (use "git add <file>..." to include in what will be committed)
    #
    #	HelloWorld.py
    nothing added to commit but untracked files present (use "git add" to track)

To interpret the above, we need to introduce some terminology:

* The history of the repository is stored along a timeline known as a *branch*.
* At any point of time, the user can choose to save a snapshot of all the files 
in the repository. Each snapshot is referred to as a *commit*. The act of 
saving a snapshot is referred to as *committing changes*.

As you can see, the above message is pretty informative and helpful. This is 
generally true with most of the output that `git` gives. The `git status` 
command tells us that we are on the branch named *master*, which is the default 
name given when we create a new repository. "Initial commit" means that we are 
yet to commit any changes to this repository. Creating a repository from a 
folder does not automatically save a snapshot of the files that were already 
present in it. The command also lists the files in the repository that are 
currently not being tracked, i.e. they have not been saved in any snapshot, and 
their histories are not being tracked by the version control software. In our 
case, this list consists of the lone file `HelloWorld.py`.

The output also tells us what we must do to commit our changes: `(use "git add 
<file>..." to include in what will be committed)`. So let's do that, and check
the status again:

```shell
> git add HelloWorld.py
> git status
# On branch master
#
# Initial commit
#
# Changes to be committed:
#   (use "git rm --cached <file>..." to unstage)
#
#   new file:   HelloWorld.py
#
```

Note that this still does not commit the changes. The `git add` command adds 
the file to what is known as the *staging area*. This is where all the changes 
to the files that are ready to be committed are stored. All files in the staging 
area are listed under "Changes to be committed:". We can see that 
`HelloWorld.py` has been added to this list. Suppose we decided that we 
actually do not want to commit this file, `git` also tells us how to remove it
from the staging area: `(use "git rm --cached <file>..." to unstage)`. But we 
don't want to do that right now.

We want to save a snapshot of the repository as it is right now, we means we 
need to use the following command:

```shell
> git commit
```

This opens up a text editor where you can type in some information regarding 
the commit. For example, we could add the message "First commit to the new 
repository. Added the file HelloWorld.py". For short messages, this can be done 
in one go using the `-m` command line flag:

```shell
> git commit -m "First commit. Add HelloWorld.py"
```

Follow guidelines on [this page]
(http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html) 
when writing commit messages. Try to make the messages detailed and easy to 
understand so that they help the developer in the future.

Congratulations! You have commited your first change to the repository. 

Check the status of the repository again:

```shell
> git status
# On branch master
nothing to commit (working directory clean)
```

Now, suppose you decide to make some changes to the file. Instead of printing 
"Hello world!", you want to display "Greetings Earth! We come in peace." You 
make the appropriate changes to the file:

```python
print "Greetings Earth! We come in peace."
```

and check the status of the repository:

```shell
> git status
# On branch master
# Changes not staged for commit:
#   (use "git add <file>..." to update what will be committed)
#   (use "git checkout -- <file>..." to discard changes in working directory)
#
#	modified:   HelloWorld.py
#
no changes added to commit (use "git add" and/or "git commit -a")
```

You'll see that the name of the branch is still mentioned, but the text 
"Initial commit" is absent. You have a list of files that have been changed 
since the last commit, along with some tips on what you can do with them.

Another useful command that you will find yourself using very often is `git 
diff`. This gives a list of all the changes in all the files since the last 
commit:

```shell
> git diff
diff --git a/HelloWorld.py b/HelloWorld.py
index ed708ec..ce3f2ef 100644
--- a/HelloWorld.py
+++ b/HelloWorld.py
@@ -1 +1 @@
-print "Hello world!"
+print "Greetings Earth! We come in peace."
```

All the lines starting with `-` are those that have been removed, and the lines 
beginning with `+` are the ones that have been added. In our case, we can see 
that `print "Hello world!"` has been removed and `print "Greetings Earth! We 
come in peace."` has been added to the file.

We will again need to stage the changed files using `git add` before we can 
commit the changes:

```shell
> git add HelloWorld.py
> git status
# On branch master
# Changes to be committed:
#   (use "git reset HEAD <file>..." to unstage)
#
#	modified:   HelloWorld.py
#
```

At this point, suppose we made any further changes to `HelloWorld.py` and then 
called `git commit`, *only the changes that were staged* will be committed. 
This is the purpose of the staging area. Once you have fixed all the changes 
that you want to commit at the next snapshot, you can stage the file and 
continue editing it without worrying about the new changes.

The output tells you that the file `HelloWorld.py` has been "modified" since 
the last commit. You'll also notice that a different command is now being 
suggested to unstage your changes: `(use "git reset HEAD <file>..." to 
unstage)` The exact meaning of this command will be explained at a later point.

Commit the changes:

```shell
> git commit -m "Edit the message to sound more friendly."
> git status
# On branch master
nothing to commit (working directory clean)
```

We have now saved snapshots of the repository at two different points. We can 
look at a list of all commits using the `git log` command:

```shell
> git log
commit e9d7cbab2205d00d5ef574fcae8ff75701529565
Author: Anush Krishnan <k.anush@...>
Date:   Tue Aug 19 16:36:08 2014 -0400

    Edit the message to sound more friendly.

commit 16bb3d3b5af5e485e4713a3fdefcff7ae88ce7df
Author: Anush Krishnan <k.anush@...>
Date:   Tue Aug 19 15:45:12 2014 -0400

    First commit. Add HelloWorld.py.
```

`git log` lists all the commits in a reverse-chronological order. The first 
line for each commit contains a long string of alphanumeric characters, which 
is the *hash*, or a unique identifier for that commit. Whenever we need to 
refer to a specific commit in the future, we use the hash of that commit. The 
author, date and time of the commit are also listed, along with the commit 
message.

Uploading your repository to Github
-----------------------------------