# minishell - 42 (with @Leanak)

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
