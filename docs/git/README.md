# Git

## Creating a repository

Here i'll list the steps needed when you want to create a repository share on github for others to see or contribute to or even for yourself to have access from more than 1 machine

1. Go to your Dashboard in GitHub and click on the green `New` button

![Step 1](../../media/git/create-new-repo-1.png)

2. Add yoursefl as the owner, add a repository name and optionally a short description of what this repo is about

![Step 2](../../media/git/create-new-repo-2.png)

3. Follow the steps provided by GitHub.

![Step 3](../../media/git/create-new-repo-3.png)

I usualy prefer to have already created a folder and added some content to it so I could go ahead with the second set of instructions. Make sure to run these commands form the project folder. I use the integrated terminal in VSCode (CTRL+`)

---

```bash
git init
```

This initializes git localy in your prject. In essence you can use Git without sharing your project on GitHub. Initializing git in your project would let you use version control localy.

---

```bash
git remote add origin <repository_url>
```

This command will link your local project to the remote repositoy in Github.

---

```bash
git add .
```

This will add ALL everything you have in your project to the staging area. Some developers prefer to do som of the git commands using the source control tab in VSCode. There you have a + button nect to every change or nect to "Changes" you can add all changed files simultaniously.

---

```bash
git commit -m "Initial commit"
```

This command creates a local commit and creates a message for it. Now you are ready to push your commits to the remote branch.

---

```bash
git push
```

Running this command now will give you an error beacause even though we have linked the local project to the remote repository we still haven't linked our master branch to a remote branch.

Anytime you create a branch localy, make some edits on it you would need to link it with a remote branch first and then you can use `git push` or `git pull` or whatever without specifying the remote branch.

---

```bash
git push --set-upstream origin <branch>
```

This is the command that will create that initial link between your local and remote branch

## Cloning a repository

git clone <repository> <folder_name>

## Git Essentials

Essential git commands and best practices for team development:

<table>
<table>
  <tbody>
    <tr>
      <th colspan="2" style="text-align:center; font-size:1.1em;">Branch Management</th>
    </tr>
    <tr>
      <td style="width:40%;"><b>git branch</b></td>
      <td>List all branches in the repository</td>
    </tr>
    <tr>
      <td><b>git checkout</b> someBranch</td>
      <td>Switch to the specified branch and update the working directory</td>
    </tr>
    <tr>
      <td><b>git checkout -b</b> newBranch</td>
      <td>Creates a new branch from the current branch and switches to it</td>
    </tr>
    <tr>
      <td><b>git checkout -b</b> newBranch fromBranch</td>
      <td>Creates a new branch from the specified branch and switches to it</td>
    </tr>
    <tr>
      <th colspan="2" style="text-align:center; font-size:1.1em;">Syncing and Updating</th>
    </tr>
    <tr>
      <td style="width:40%;"><b>git fetch</b></td>
      <td>Fetch changes from the remote branch</td>
    </tr>
    <tr>
      <td><b>git pull</b></td>
      <td>Fetch changes from the remote branch and merge them into the current branch</td>
    </tr>
    <tr>
      <td><b>git pull --rebase</b></td>
      <td>Fetch and rebase your local commits on top of the remote branch.</td>
    </tr>
    <tr>
      <td><b>git rebase -i origin/master</b></td>
      <td></td>
    </tr>
    <tr>
      <td><b>git rebase origin/master</b></td>
      <td></td>
    </tr>
    <tr>
      <td><b>git push -f</b></td>
      <td></td>
    </tr>
    <tr>
      <td><b>git push --force-with-lease</b></td>
      <td></td>
    </tr>
    <tr>
      <td><b>git reset --soft HEAD~1</b></td>
      <td>Unstage the last commit while preserving changes in the working directory</td>
    </tr>
    <tr>
      <th colspan="2" style="text-align:center; font-size:1.1em;">Stashing uncommitted changes</th>
    </tr>
    <tr>
      <td style="width:40%;"><b>git stash</b></td>
      <td>Save changes in a dirty working directory away</td>
    </tr>
    <tr>
      <td><b>git stash pop</b></td>
      <td>Apply the changes stashed away and remove them from the stash</td>
    </tr>
  </tbody>
</table>
</table>
