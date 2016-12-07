# Connecting an Authorea article to a Github branch

Here is the situation:

I would like to write a proposal collaboratively using Authorea.
I would also like to have supplementary materials (extra figures, code, and data) available on Github to strengthen/justify the ideas exposed in my proposal.
In addition, it would be great to have the proposal available and version controlled on Github.
Thus I need to synchronize the Github repository to the Authorea article.
Ideally, it would be awesome if I avoid cluttering the Authorea folder with the supplementary materials.

Here is a possible solution:

1- Create a local git repository `myproposal` that contains some supplementary materials (e.g., a `README.md`, a Python script `script.py`, and some data `data.txt`):
```
mkdir myproposal
cd myproposal
git init
vim README.md
git add README.md
git commit -m 'Add a README'
touch data.txt
vim script.py
git add data.txt
git add script.py
git commit -m 'Add a Python script that reads the data'
```

2- Create a Github repository named `myproposal` and push you local changes to it:
```
git remote add origin git@github.com:mesnardo/myproposal.git
git push -u origin master
```

3- Log in on Authorea and create a new article (button `New Article`).
Choose a title, make it public (or private), and set the format to `Markdown`.
Click on `Submit`.

You are now facing your Authorea article.
On the top-right corner, click on the three vertical dots, then `Settings`.
Click on `Setup Github integration`.

To avoid cluttering Authorea with the supplementary materials, we want the article to be linked to another branch than the default `master`.
To do that, we are going to do the Github integration manually.

From here, I am just following what Authorea is telling me to do to manually integrate Github.

Click on `Generate ssh key pair`.

Copy the key and deploy it on the Github repository (go to `Settings`->`Deploy keys`).

Allow write access, so you can push to this repository (Deploy keys always have pull access).

On Authorea, paste the SSH url on the Github repository, which is `git@github.com:mesnardo/myproposal.git`.

From Authorea, copy the webhook url (it looks something like `https://www.authorea.com/article_git_access_bridges/web_hook/xxxx`).

On the Github repository, go to `Settings->Webhooks->Add webhook` and paste the url.

Back to Authorea; set the Default branch to be `authorea` and the conflict-branch to be `authorea-conflict`. (Whenever Authorea fails to push to the Github branch `authorea`, it will pushes to `authorea-conflict`; your task will be then to resolve the conflict and merge `authorea-conflict` into `authorea`.)

Click `Submit`.

In the next window, click on the link `go to Git functions`.

Now, click on `Push`.

At that point, you should have a new branch called `authorea` on your Github repository that contains the article (several Markdown files, a `bibliography` folder, and a `figures` folder).

As you can see, this branch does not contain the supplementary materials (`README.md`, `script.py`, and `data.txt`).

4- Now, you can pull the branch `authorea` on your local repository:
```
git remote update origin
git checkout -b authorea origin/authorea
```

The Github branch `authorea` is now synchronized to the Authorea article.
Every time you modify and commit something on Authorea, it will appear on Github (from there, you can pull locally the commits locally if needed).
Every time you commit on your local repository and push it to Github, Authorea will automatically pull the changes.

Once I am done writing my proposal (or whenever I want), I can merge the branch `authorea` into `master`.