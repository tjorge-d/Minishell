# :shell: Minishell
**Minishell** is the first **42** project that proposes to work as a **team** to implement a **command-line interface** similar to **bash** that is able to **execute commands**, make **redirections**, create **pipelines**, handle **Unix signals** and manage **environment variables** using **C**.

## :key: Key Components

### Parser
The **parser** receives a user command and transforms it into a **syntax tree** constituted by **tokens**, taking into consideration **quotes**, **redirections** and **pipes**. Then sends the tree to the executor or **handles errors** in case of an invalid prompt and properly feed-backs the user.

### Executor
After receiving a **syntax tree**, iterates it to construct a **data structure** with all the information needed to execute a **command**. While iterating, if a **pipe** ( **|** ) is found, a new **process** is created and a **pipeline** links the new command’s **input** with the **output** of the previous one. Before executing each command, if any **redirections** (**<**, **>**, **<<**, **>>**) are present, the data is **redirected** to/from a specified file using **file descriptors**.

![Screenshot from 2025-05-14 11-23-06 (1)](https://github.com/user-attachments/assets/a26cc7bf-3506-41de-a5e1-a638ea47f430)
<sup>Simple command to show the biggest file inside the current folder.</sup>

## :books: What did I learn?
An effort was made to **collaborate** as a **team** and to make **technical documentation** (**CI/CD**) using **Git**.
Since the project is about recreating **bash**, a lot of **shell commands** where executed and the functioning of the **UNIX** system was studied, understanding and implementing **Inter-process communication** (**IPC**) and **POSIX API** (**file descriptors**, **signals**, **pipes**, **redirections**, **process control**).
