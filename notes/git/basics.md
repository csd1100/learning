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

## Rebase

### NEVER REBASE on PUBLIC BRANCHES. i.e. never change public branch history

- Rebase rewrites history
- The basic steps of rebase is the following:
  1. execute `git rebase <targetbranch>`. I will refer to the current branch as
     `<currentbranch>` later on
  1. checkout the latest commit on `<targetbranch>`
  1. play one commit at a time from `<currentbranch>`
  1. once finished will update `<currentbranch>` to the current commit sha

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
