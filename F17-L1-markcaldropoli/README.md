# Lab1

- Reverting in repositories
- Loops and microbenchmarking
- Introduction to Debugging

## Reverting mistakes

One of the best features of repositories is that they allow us to go back in time to recover from mistakes. This is called _reverting_. Let's find out how it works.

After last lab, you should remember how to remove a tracked file from your repository using `git-rm`. Let's (accidentally) remove an important file from our repository:

```shell
$ git rm .important
$ git commit -m "Remove an important file"
$ git push
```

Observe that it has been not only removed from our file system (hint: try using `ls -a` to list all files, even hidden files) ... but that it's been removed from the repository as a tracked file (hint: refresh your browser). Now, how do we get it back? For that, we need to revert.

First, we need to figure out the commit to which we want to revert. There are two ways to do that.

### Using github.com
Go to the main page of your repository. Above the file listings, and below the title of your repository, you should see text with a clock icon that says _commit(s)_ along with the number of commits you've made. Click on that to go to the listing of commits in your repository. Here we can do three things:

- By clicking on the clipboard next to the seven digit "magic number" identifying that commit, we copy the full SHA hash value identifying the commit.
- By clicking on the "magic number" itself, we can see the changes that commit made.
- By clicking on the `<>`, we can travel in time to see the full repository at that moment, including all code that wasn't affected by the commit.

One of those commits will have your message "Remove an important file". We want to go back in time to just before that. Which commit is that? Once you've found it, get its SHA hash.

### Using the terminal

`git-log` will list all commits made to this repository.

```shell
$ git log
```

You'll see an output that have entries that look something like this:

```shell
commit 865692c03839462cf3abce8069b97870f3cd8e47
Author: Matthew Cole <matthews email address>
Date:   Wed Aug 30 21:16:46 2017 -0400

    Initial commit
```
The digits after the word "commit" are the SHA hash (and the first seven digits of that are the "magic number"). Find the commit just before our mistake and copy its SHA hash.

### Okay, but how do we actually revert?

Use the `git-revert` command to undo our mistake! Fill in `<sha>` with your SHA hash

```shell
git revert <sha>
git commit -m "Reverting from removing an important file!"
git push
```
Finally observe that our important file is back in the repository and being tracked. **_Phew!_**

Now that we've recovered from our mistake, here are two web pages that you may find useful for learning about other features of `git-revert` in the future:

- [How to revert Git repository to a previous commit?](https://stackoverflow.com/a/4114122/5537617)
- [git-revert](https://git-scm.com/docs/git-revert)

---

## Lab 1

The instructions to complete this lab are in [instructions.pdf](instructions.pdf).
Pay close attention to the deliverables for each section.
**Be careful to not cut and paste from the PDF document directly!**
If you do not complete the lab by the end of your class, you have until the end of the day (11:59pm) to complete the work and submit it to MyCourses.
