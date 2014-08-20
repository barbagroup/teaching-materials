Collaborating with Git
======================

Chris and Natalia both clone the repository:

```shell
git clone https://github.com/anushkrish/cocktail-recipes.git
```

Chris
-----

Chris thinks 2.5 oz is for amateurs. So he makes the following change,

```markdown
* 3.0 oz Alto del Carmen Pisco
```

commits,

```shell
> git add PiscoSour.md
> git commit -m "The-the-re-re!"
```

and pushes his changes to the remote repository.

```shell
> git push
```

Natalia
-------

Natalia is more practical:

```markdown
* 1 tbsp sugar
* 1/2 lemon
```
```shell
> git add PiscoSour.md
> git commit -m "Some practical changes."
```
```shell
> git push
To https://github.com/anushkrish/cocktail-recipes.git
 ! [rejected]        master -> master (non-fast-forward)
error: failed to push some refs to 'https://github.com/anushkrish/cocktail-recipes.git'
To prevent you from losing history, non-fast-forward updates were rejected
Merge the remote changes (e.g. 'git pull') before pushing again.  See the
'Note about fast-forwards' section of 'git push --help' for details.
```

Git detects the diverged timelines of Natalia's local branch `master` and the 
remote branch `origin/master`, and decides that it cannot push Natalia's 
changes.

Natalia checks her logs:

```
> git log master --oneline
ddae6d2 Some practical changes.
bb874b7 First commit. Pisco Sour recipe.
```

```
> git log origin/master --oneline
bb874b7 First commit. Pisco Sour recipe.
```

Presumably, the history of `origin/master` is unchanged since she first cloned 
the repository. She would like to make it match her local branch by pushing her 
changes, but Git tells her that the remote branch currently has a different 
history from the one she is trying to push. To see what changes have occurred 
to the remote branch, she first needs to update her local copy of 
`origin/master` by fetching all the changes from the remote repository.

```
> git fetch origin
```

Check the log and status again:
```
> git log origin/master
a0c2052 The-the-re-re!
bb874b7 First commit. Pisco Sour recipe.
> git status
# On branch master
# Your branch and 'origin/master' have diverged,
# and have 1 and 1 different commit(s) each, respectively.
#
nothing to commit (working directory clean)
```

The problem now becomes obvious. The local history she is trying to push has 
"Some practical changes." immediately following the first commit. But the 
remote branch already has the change "The-the-re-re!" immediately following the 
first commit.

Never forget: The remote history is more sacred than the local history. This is 
because it is what is visible to all collaborators. Another user may have 
cloned the remote and made changes to it. If you change the remote history 
later, then the history that the other person built upon is lost.

What should Natalia do? She should first update her local history to match the 
remote history, then commit her new changes, and then push the new commits to 
the remote repository. The first step is done using `git merge`:

```
> git merge origin/master
Auto-merging PiscoSour.md
CONFLICT (content): Merge conflict in PiscoSour.md
Automatic merge failed; fix conflicts and then commit the result.
```

Here, she tries to merge the remote branch with her local branch and 
encounters conflicts (as expected). Git is usually clever about merges. If 
different users edited different parts of the same file, it can merge the two 
versions of the file by itself. But if each user edited the same lines and 
committed their changes, then Git cannot decide by itself what the correct 
version should be. The user needs to manually choose.

```
> git status
# On branch master
# Your branch and 'origin/master' have diverged,
# and have 1 and 1 different commit(s) each, respectively.
#
# Unmerged paths:
#   (use "git add/rm <file>..." as appropriate to mark resolution)
#
#	both modified:      PiscoSour.md
#
no changes added to commit (use "git add" and/or "git commit -a")
```

Edit PiscoSour.md. Remove the extra characters that Git inserts to indicate  
which parts of the file are in conflict.

Natalia changes

```markdown
<<<<<<< .merge_file_LQBQZj
* 2.5 oz Pisco
* 1 tbsp sugar
* 1/2 lemon
=======
* 3.0 oz Alto del Carmen Pisco
* 0.5 oz simple syrup
* 0.75 oz fresh lemon juice
>>>>>>> .merge_file_l1T1fk
```

to

```markdown
* 3.0 oz Alto del Carmen Pisco
* 1 tbsp sugar
* 1/2 lemon
```

She decides to retain the larger quantity of Chris' favourite Pisco, and also 
her more practical modifications to the recipe.

```
> git add PiscoSour.md
> git commit -m "Merged changes."
> git log --oneline
14221b5 Merged changes.
ddae6d2 Some practical changes.
a0c2052 The-the-re-re.
bb874b7 First commit. Pisco Sour recipe.
```

Now her local history consists of the remote history plus her changes. This can 
be pushed to the remote repository as a "fast-forward update".

```
> git push
```

Natalia then realises that she forgot to change the instructions to match her 
new ingredients. She edits PiscoSour.md and commits the change:

```
In cocktail shaker filled with ice, combine egg white, Pisco, sugar, and
squeeze lemon. Cover, shake vigorously for 15 seconds, and strain into
six-ounce cocktail glass.
```
```
> git add PiscoSour.md
> git commit -m "Edit instructions."
```

and she decides to push the changes. But wait! Look both ways before crossing 
the road. Has somebody else pushed changes to the remote since the last time 
you pushed? Always check first.
```
> git fetch origin
```
No output. Which means no changes are fetched. It's safe to push.
```
> git push
```

Back to Chris
-------------
Chris is perfectly happy with his recipe. But he's slowly getting bored of it. 
He wants to see if anybody else had any new ideas which he might like. So he 
decides to fetch changes from the remote repository
```
> git fetch origin
remote: Counting objects: 9, done.
remote: Compressing objects: 100% (4/4), done.
remote: Total 9 (delta 3), reused 8 (delta 2)
Unpacking objects: 100% (9/9), done.
From https://github.com/anushkrish/cocktail-recipes
   a0c2052..22947b0  master     -> origin/master
```
and merge them into his local repository
```
> git merge origin/master
Updating a0c2052..22947b0
Fast-forward
 PiscoSour.md |   10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)
```

The merge proceeds smoothly. There was no divergence between the remote branch 
and Chris' local branch. The remote history was only a continuation of the 
local history, and all the additional changes could be "fast-forward" merged. 
This makes Chris happy. He kicks back, relaxes and takes a long refreshing sip 
of Pisco Sour.
