# LSH 
In order to understand how basic systems work, I decided to program my own shell in C. 

## Example
![lsh running in a terminal](docs/demo.png)

## What it can do
Right now, there are a handful of commands that it can run. Just about everything that you can run in your normal terminal can be run here.

- cd
- ls
- help
- etc

Commands of any length work. For the longest time I couldn't figure out how to have a line longer than 1024 characters. 

## Build and run
Before anything, you need to make sure that you have a C compiler on your computer. (Right now this is only working on MacOS, so keep that in mind.)

1. git clone https://github.com/levimackay/lsh.git
2. cd lsh
3. cc -Wall -Wextra -o lsh main.c
4. ./lsh

## How it works
So basically, my shell runs in a loop. It shows the `lsh>` prompt, waits for the user to enter something, and then does it again until they type `exit` or press Ctrl-D.

For reading input, I used `getline()` because it automatically adjusts the buffer size. That way, I don't have to worry about someone typing a command that's too long. After that, I use `strtok()` to split the input into separate words based on spaces, tabs, or newlines. Those words get stored in `args`, with `NULL` at the end.

I also have three built-in commands: `exit`, `cd`, and `help`. These run directly in the shell instead of creating another process. This is especially important for `cd` because if I ran it in a child process, it would only change that process's directory, not the actual shell's directory.

For everything else, I use `fork()` to create a child process. It returns 0 in the child and the child's PID in the parent. The child uses `execvp()` to find and run the command using PATH. Meanwhile, the parent uses `waitpid()` to wait until the command finishes before showing the prompt again.

For errors, I used `perror()` so the user can actually see what went wrong, like if they typed a command that doesn't exist or tried to go to a folder that isn't there. If a command fails in the child process, the child exits so it doesn't accidentally keep running as another shell.

Lastly, for memory management, I free the buffer created by `getline()` when the shell exits. I also tested everything with AddressSanitizer, and it didn't find any memory errors.

## Limits
- Right now, you aren't able to use |, <, >, &&, ;
- Quotes can't group words
- There is no $HOME or ~
- MacOS only so far (hoping to have windows and linux compatible soon)

## What's next?
- Pipes and redirects
- Real Parser
- Ctrl C only stops the program not the whole shell
- --trace mode that shows fork, exec, and wait live

## Credit
The base loop (read a line, split it, fork and exec) follows Stephen Brennan's tutorial, [Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/). The cd and help built-ins, getline, the word cap and everything on the roadmap are my own additions.
