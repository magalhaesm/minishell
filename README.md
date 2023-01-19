<p align="center">
    <img src="https://game.42sp.org.br/static/assets/achievements/minishelln.png">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/OS-Linux-blue" alt="OS">
    <img src="https://img.shields.io/badge/Language-C%20%7C%20C%2B%2B-blue.svg" alt="Language">
    <img src="https://img.shields.io/badge/Grade-125%2F100-brightgreen.svg" alt="Grade">
    <img src="https://img.shields.io/badge/Status-Completed-brightgreen.svg" alt="Status">
</p>

## Introduction

The 8th project of 42 cursus syllabus asks students to implement a simplified shell. It's about minishell, as beautiful as a shell.

As the project's subject states, the existence of shells is linked to the very existence of IT. At the time, al developers agreed that _communicating with a computer using aligned 1/0 swiches was seriously irritating_. It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somehat close to the human language.

## How to compile and run the project

#### 1) Copy this repository to your local workstation

```html
git@github.com:magalhaesm/minishell.git
```

#### 2) Install the required libraries to run the functions from readline library

```html
sudo apt-get install libreadline6 libreadline6-dev
```

#### 3) Compile the project with Makefile

```html
make
```

#### 4) Launch the executable file

```html
./minishell
```

If you want to run the executable program automatically with valgrind flags to check for leaks, just write `make checks` and press enter.

## Implemented builtins

| Builtin | Command description |
|:------|:------|
| `echo` with `-n` | Displays a line of text to the standard output |
| `cd` | Changes the working directory of the current shell execution environment |
| `pwd` | Prints the full filename of the current working directory |
| `export name[=word]` | Sets the export attribute for variables |
| `unset` | Unsets values and attributes of variables and functions |
| `env` | Sets each name to value in the enviroment and run command |
| `exit` | Causes the shell to exit with exit status specified |

## About how we implemented the project

There two main files at projects's root directory:

- `include`: contains all the necessary headers for the project
- `grammar`: the implemented grammar
- `libft`: our own C library with some helpful auxiliary functions, such as ft_strlen
- `tests`: contains unit tests created with [Criterion](https://github.com/Snaipe/Criterion) testing framework to evaluate functions in `src`
- `src`: contains the whole project implementation
  - `builtins`: implements the required builtins by the project's subject
  - `exec`: consists of functions that executes user's input
  - `expansion`: implements shell expansors, such as quote marks and wildcards
  - `helpers`: contains utils function used on the project as a whole
  - `parser`: consists of functions that implement the minishell's grammar and create a tree of a given input by the user
  - `scanner`: implements a scanner to create tokens of a given input by the user
  - `signals`: consists of functions that handle user events, such as `ctrl-C`, `ctrl-D` and `ctrl-\`
  - `table`: implements a hash table to store enviroment variables

## References