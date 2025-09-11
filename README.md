# Tiny Shell — mysh 🐚⚡  
Custom Unix-like Shell with Built-ins, Aliases, Pipes, and Redirection  

![Language](https://img.shields.io/badge/language-C-blue.svg) 
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg) 
![Build](https://img.shields.io/badge/build-Makefile-orange.svg)  

---

✨ **Overview**  
This project implements a lightweight shell (`mysh`) in C.  
It started as an Operating Systems assignment and was extended into a practical developer tool.  

It demonstrates mastery of:  
- **Process control** (fork, execvp, wait)  
- **System calls** (I/O, file descriptors)  
- **User experience** (history, aliases, configs)  

🛠️ **Workflow**  
- Prompt: `user@host:cwd$mysh>` dynamic display  
- Loop: read → parse → execute → re-prompt  
- Built-ins: `cd`, `pwd`, `exit`, `export`, `alias`, `unalias`, `which`  
- Config: loads `~/.myshrc` (aliases, exports, etc.)  
- Environment: support for `export VAR=value`  
- History & editing: via GNU Readline (`↑ ↓`, `Ctrl+R`)  
- External commands: launched via `fork + execvp + wait`  
- Pipes & redirection: `|`, `<`, `>`, `>>` across multiple stages  
- Errors: descriptive messages (e.g., *No such directory*)  

📁 **Repository Layout**  
```bash
src/       # main source (mysh.c + helpers)
docs/      # design notes, demo screenshots
tests/     # sample scripts and test cases
Makefile   # build rules (gcc + readline)
README.md  # this overview
```

🚦 **Demo**

Build and run:

```bash
make
./mysh
```

Example session:

```bash
Copy code
mysh> alias ll="ls -la"
mysh> export PATH=$PATH:/usr/local/bin
mysh> cat file.txt | grep "hello" > out.txt
mysh> which python
/usr/bin/python
```

🔍 **Features**

- Process Control: fork/exec/wait
- Built-ins: cd, pwd, exit, export, alias, unalias, which
- Configurable startup (~/.myshrc)
- Aliases & env vars
- Command history & navigation (Readline)
- Pipes and redirection

📜 **License**

MIT (see [LICENSE](LICENSE))

---
