# Theory of Algorithms - MD5 Message-Digest Algorithm
###### David Gallagher
## Project Specs
Write a program in the C programming language that calculates the MD5 hash digest of an input.
The algorithm is specified in the [Request For Comments 1321](https://tools.ietf.org/html/rfc1321) document supplied by the Internet Engineering Task Force.

## Instructions for use
For command line interactions on any OS see this [Cheat Sheet](https://gist.github.com/jonlabelle/e8ba94cd29b8f63fd7dd3c4f95c1d210).  
You will need Git [installed locally](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).  

``` 
git clone https://github.com/d-gallagher/TheoryOfAlgorithms.git
cd TheoryOfAlgorithms/Md5
```
Follow the guides below for Windows or Linux environments.
##### Windows
[Walkthrough: Compile a C program on the command line](https://docs.microsoft.com/en-us/cpp/build/walkthrough-compile-a-c-program-on-the-command-line?view=vs-2019).  
Windows development suggestions:  
[Clion](https://www.jetbrains.com/clion/download/#section=windows) Jetbrains c development environment, does a lot of work for you.  
[Visual Studio Code](https://code.visualstudio.com/) a lightweight and prominent cross-platform IDE for development.  
Use [Cmder](https://cmder.net/) instead of cmd prompt on windows. It's a better console/terminal and uses linux commands.  
```
cl main.c 
main "filename"
```
##### Linux
[How to Write and Run a C Program in Linux](https://vitux.com/how-to-write-and-run-a-c-program-in-linux/).  
[Visual Studio Code](https://code.visualstudio.com/) a lightweight and prominent cross-platform IDE for development.  
[VIM](https://www.linux.com/training-tutorials/vim-101-beginners-guide-vim/) is more challenging to learn but provides a 
lot of functionality and is worth learning if you will be terminal bound for certain projects.  
```
make main
./main "file name"
```
