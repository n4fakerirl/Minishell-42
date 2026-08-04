# minishell - 42 (with @Leanak) | [FRENCH VERSION] _english below_

## 📚 Description

`minishell` est un projet de l'école 42 qui consiste à recréer un **shell minimaliste** en C.  
L’objectif est de comprendre le fonctionnement interne d’un terminal Unix : parsing, exécution des commandes, redirections, pipes, variables d’environnement, et gestion des signaux.

---

## 📦 Objectifs

* Reproduire le comportement d’un shell Bash simplifié
* Implémenter la gestion :
  - Des **commandes internes** (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
  - Des **redirections** (`>`, `>>`, `<`, `<<`)
  - Des **pipes** (`|`)
  - Des **variables d’environnement**
  - Des **signaux** (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
* Créer un parsing robuste gérant les **quotes**, **expansions** et **heredocs**
* Gérer les erreurs et les codes de sortie comme dans Bash

---

## 🧠 Fonctionnement général

* Le programme lit une commande depuis l’entrée standard (prompt)
* Il effectue un **parsing** complet pour séparer les commandes, arguments, redirections, etc.
* Les **builtins** sont exécutées directement dans le shell
* Les autres commandes sont exécutées via des **processus enfants** avec `fork()` et `execve()`
* Le shell reste actif jusqu’à réception de la commande `exit` ou d’un signal de fermeture

---

## 💡 Exemple d’utilisation

```bash
$> ./minishell
minishell> echo Hello World
Hello World
minishell> ls | grep src > result.txt
minishell> cat << EOF
> This is a heredoc
> EOF
minishell> exit
```

---

## ⚙️ Compilation

| Commande      | Description                                 |
| ------------- | ------------------------------------------- |
| `make`        | Compile `minishell`                         |
| `make clean`  | Supprime les fichiers objets (`.o`)         |
| `make fclean` | Supprime les fichiers objets et exécutables |
| `make re`     | Nettoie puis recompile entièrement          |

---

## 🖼️ Note du projet

<p align="center"> <img width="199" height="169" alt="image" src="https://github.com/user-attachments/assets/b6f9595b-33dd-44a8-9c01-d6514a0a5e92" /> </p>

---

## 🫐 Auteurs

* Léa (lenakach) && Océane (ocviller)
* Piscine de Mars 2025
* Projet réalisé à 42 Paris, 2025

---

# minishell - 42 (with @Leanak) | [ENGLISH VERSION]

## 📚 Description

`minishell` is a project from the 42 curriculum that consists of recreating a **minimal Unix shell** in C.
The goal is to understand how a Unix terminal works internally by implementing command parsing, execution, redirections, pipes, environment variables, and signal handling.

---

## 📦 Objectives

* Reproduce the behavior of a simplified Bash shell
* Implement support for:

  * **Built-in commands** (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
  * **Redirections** (`>`, `>>`, `<`, `<<`)
  * **Pipes** (`|`)
  * **Environment variables**
  * **Signals** (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
* Build a robust parser capable of handling **quotes**, **environment variable expansion**, and **heredocs**
* Handle errors and exit statuses similarly to Bash

---

## 🧠 How It Works

* The program reads commands from the standard input through an interactive prompt
* It performs complete **parsing** to identify commands, arguments, pipes, and redirections
* **Built-in commands** are executed directly within the shell
* External commands are executed in **child processes** using `fork()` and `execve()`
* The shell remains active until the `exit` command is executed or it receives a termination signal

---

## 💡 Example

```bash id="svcmn4"
$> ./minishell
minishell> echo Hello World
Hello World
minishell> ls | grep src > result.txt
minishell> cat << EOF
> This is a heredoc
> EOF
minishell> exit
```

---

## ⚙️ Compilation

| Command       | Description                          |
| ------------- | ------------------------------------ |
| `make`        | Compiles `minishell`                 |
| `make clean`  | Removes object files (`.o`)          |
| `make fclean` | Removes object files and executables |
| `make re`     | Cleans and recompiles the project    |

---

## 🖼️ Project Grade

<p align="center">
  <img width="199" height="169" alt="image" src="https://github.com/user-attachments/assets/b6f9595b-33dd-44a8-9c01-d6514a0a5e92" />
</p>

---

## 🫐 Authors

* Léa (lenakach) & Océane (ocviller)
* March 2025 Piscine
* Project completed at 42 Paris in 2025
