# Basics

## Information

- Distributed version control
- git is acyclic graph
- commit is node in the graph
- commit stores pointers to entire project at that point not just diffs
- use `man git-<op>` to get help
- SHAs are 40 chars and have (0-9a-f)
- `git cat-file -p <sha>` can be used to get contents of commit

## Config

- There are global and local configuration
- Configuration keys are in format `<section>.<key>`
- `--global` makes config global
- `user.email` and `user.name` are used in creating commits
- To add local config use `git config --add <key> "<value>"`; if run twice it
  adds twice and last added value will be used
- To add global config use `git config --add --global <key> "<value>"`
- To get config use `git config --get <key>`
- To get config use `git config --get-regexp <value>` to get values using regexp
- To remove a key use `git config --unset <key>` but
  if key has multiple values use `--unset-all`
- To remove a section use `git --remove-section`

## Merge

- Merge commit is made at the "merge base" where the branches diverge.
- If merge base is at HEAD of the target branch the merge is done with Fast Forward
  strategy.
- `git merge <source-branch>`
- In merge we add commits from `source-branch` on top of `current-branch`.
- So `HEAD` when we are doing conflict resolution will be `current-branch`.

## Rebase

### NOTE: NEVER REBASE ON PUBLIC BRANCHES BECAUSE IT CHANGES THE HISTORY

- Rebase rewrites history
- The basic steps of rebase is the following:
  1. execute `git rebase <targetbranch>`. I will refer to the current branch as
     `<currentbranch>` later on
  1. checkout the latest commit on `<targetbranch>`
  1. play one commit at a time from `<currentbranch>`
  1. once finished will update `<currentbranch>` to the current commit sha
- In rebase branch on which we are rebasing i.e. `targetbranch` is checked out first
  and then git replays our `currentbranch`'s changes on top of it.
- When we are resolving the conflict in the rebase, we are adding
  `currentbranch`'s changes on top of `targetbranch`,
  `HEAD` will be at `targetbranch` commit.
- So when we have long-lived feature branches and there is a conflict in branches
  every time we `rebase` we will need to resolve the same conflict again and again.
- Because, `rebase` checks `targetbranch` out then plays `currentbranch`'s commits
  one at a time. i.e. Every we `rebase`, git will checkout `main` then it will play
  feature branch's commit. So conflict will occur every time, since we will apply
  same commit on top of `main` every time we `rebase`.
- The solution to above problem is `rerere`.

### Interactive rebase

- Interactive Rebase can be done using `-i` flag to `rebase` command.
- This provides a way for us to choose what to do when replaying our commits.
- The menu is provided to us in our editor with commented explanation on how it
  can be used. And we update uncommented lines with what we want to do.
- Squashing commits can be done by using interactive `rebase`

## Rerere

- Reuse recorded resolution
- We can enable it in git config. `git config --add rerere.enabled true`
- It has one caveat though, if we resolve conflict wrongly and that resolution
  is recorded it will use that wrong resolution until we remove the recording.

## Reflog

- `reflog` has all the history of git operations including all the `reset --hard`s
  an `branch -D`s so you can use reflog to retrieve deleted data.
- `reflog` is updated locally and it is not present on remote.

## Misc

- Terms:
  - repos - repository / project folder
  - commit - entire repo at given time instant
  - index - staging area
  - squash - take N commits and turning it to 1 commit
  - working tree - data that is tracked by git
  - tree - is directory
  - blob - is file
