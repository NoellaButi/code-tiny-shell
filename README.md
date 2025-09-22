# Tiny Shell — mysh 🐚⚡  
Custom Unix-like Shell with Built-ins, Aliases, Pipes, and Redirection  

![Language](https://img.shields.io/badge/language-C-blue.svg) 
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg) 
![Build](https://img.shields.io/badge/build-Makefile-orange.svg)  
![CI](https://github.com/NoellaButi/code-tiny-shell/actions/workflows/ci.yml/badge.svg?branch=main)

---

## ✨ Overview
This project implements a lightweight shell (`mysh`) in C.  
It started as an Operating Systems assignment and was extended into a practical developer tool.  

It demonstrates:
- **Process control** (`fork`, `execvp`, `wait`)  
- **System calls** (I/O, file descriptors)  
- **User experience** (history, aliases, configs)  

---

## 🔍 Features
- Dynamic prompt: `user@host:cwd$mysh>`  
- Built-ins: `cd`, `pwd`, `exit`, `export`, `alias`, `unalias`, `which`  
- Configurable startup (`~/.myshrc`)  
- Aliases & environment variable support  
- Command history & search (GNU Readline: ↑ ↓, `Ctrl+R`)  
- Pipes & redirection (`|`, `<`, `>`, `>>`)  
- Error handling with descriptive messages  

---

## 🚦 Quickstart

Build and run:
```bash
make
./mysh
```

Example session:
```bash
mysh> alias ll="ls -la"
mysh> export PATH=$PATH:/usr/local/bin
mysh> cat file.txt | grep "hello" > out.txt
mysh> which python
/usr/bin/python
```

## 📁 Repository Layout
```bash
code-tiny-shell/
├─ src/         # source code (mysh.c + helpers)
├─ tests/       # sample scripts and test cases
├─ docs/        # design notes, demo screenshots
├─ Makefile     # build rules (gcc + readline)
└─ README.md
```

## 📊 Demo
![Demo](docs/demo.png)

## 🔮 Roadmap
- Add tab-completion for commands
- Add background process support (&)
- Add colored prompt themes

## 📜 License
MIT (see LICENSE)

---

