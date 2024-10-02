# minishell
minishell is a project that aims to create a basic shell, similar to bash. It provides a command-line interface where users can execute commands. This project deepens understanding of process creation, file descriptors, signal handling, and command parsing in Unix-like environments.

## Installation
To use this program:
  1. Clone the repository:
     ```bash
     git clone https://github.com/clemllovio/minishell.git
     ```
  2. Navigate to the project directory and compile
## Usage
After compiling, you'll have a `minishell` executable. Run it as follows:
```
./minishell
```
This will start the shell, and you'll see a prompt where you can enter commands:
```
doublechoc>
```

## Features

• Displays a prompt when waiting for a new command

• Working history (up and down arrows)

• Handles single and double quotes

• Implements redirections: `<`, `>`, `<<`, `>>`
• Implements pipes (`|`)

• Handles environment variables (`$` followed by characters)

• Handles `$?` which expands to the exit status of the most recently executed foreground pipeline

• Handles `ctrl-C`, `ctrl-D` and `ctrl-\` which behave like in bash


#### Implements the following builtins:
• `echo` with option `-n`
  
• `cd` with only a relative or absolute path
  
• `pwd` with no options
  
• `export` with no options
  
• `unset` with no options
  
• `env` with no options or arguments
  
• `exit` with no options

## Examples
Here are some example commands you can try in minishell:
```
doublechoc> ls -l
doublechoc> echo "Hello, World!"
douclechoc> cd /path/to/directory
douclechoc> cat file.txt | grep "pattern"
douclechoc> export MY_VAR=value
douclechoc> echo $MY_VAR
```
## Credits
This project was developed by Clémence Llovio and Lisa Ciullo as part of the curriculum at 42 School.
