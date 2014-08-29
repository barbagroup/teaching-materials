##The situation
As per emails of 8.29.14 the following issue came up:

2 of 3 notebooks on numerical-mooc branch `phugoid_solution` were ready to be published.  The third notebook was not.  

To remedy this, I created a new branch called `phugoid_2`, then deleted all files not pertaining to notebooks 1 and 2.  I committed these changes, then merged them via pull request into `solutions`.  Then I merged them from `solutions` -> `master`

##The issue
Notebook 3 (and other files) still exists on branch `phugoid_solution`, but the only difference between `phugoid_solution` and `master` is a single commit -- the commit which deletes all of those files.  

Trying to merge from `phugoid_solution` to `master` results in 

```Bash
git merge --no-ff phugoid_solution
Already up-to-date.
```

Because the only differences between the branches are files that `master` has been told to effectively ignore.

##Solution
On `phugoid_solution`, make an edit to the "deleted" file and commit it.  Attempting to merge `phugoid_solution` -> `master` now will result in:

```Bash
git merge --no-ff phugoid_solution
CONFLICT (modify/delete): <notebook name> deleted in HEAD and modified in phugoid_solution.  Version phugoid_solution of <notebook name> left in tree.
Automatic merge failed; fix conflicts and then commit the result.
```
then

```Bash
git status

On branch master
Your branch is ahead of 'origin/master' by 1 commit.
  (use "git push" to publish your local commits)
  You have unmerged paths.
    (fix conflicts and run "git commit")

    Unmerged paths:
      (use "git add/rm <file>..." as appropriate to mark resolution)

        deleted by us:   next.git.lesson

        no changes added to commit (use "git add" and/or "git commit -a")
```

Now, simply re-add the "deleted" file and commit it to complete the merge and restore the file.

```Bash
git add next.git.lesson 

git status
On branch master
Your branch is ahead of 'origin/master' by 1 commit.
  (use "git push" to publish your local commits)
  All conflicts fixed but you are still merging.
    (use "git commit" to conclude merge)

    Changes to be committed:

        new file:   next.git.lesson
```

