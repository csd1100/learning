# Basics

## Information

- Distributed version control
- git is acyclic graph
- commit is node in the graph
- use `man git-<op>` to get help

## Initial Setup

- There are global and local configuration
- Config keys are in format `<section>.<key>`
- `--global` makes config global
- `user.email` and `user.name` are used in creating commits
- To add local config use `git config --add <key> "<value>"`
- To add global config use `git config --add --global <key> "<value>"`
- To get config use `git config --get <key>`

## Misc

- Terms:
  - repos - repository / project folder
  - commit - entire repo at given time instant
  - index - staging area
  - squash - take N commits and turning it to 1 commit
  - working tree - data that is tracked by git
