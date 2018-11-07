# mister-sss
Sword Slash Shoot Stab Strike? Some violent three letter acronym.

----------FOR DEVELOPERS:
All of the source code is contained inside the "src" folder. Resources such as pictures and sounds are contained inside the "res" folder. The executables are compiled and saved inside the "bin" folder. This folder should only have the following files, (along with some hidden files):
"README.txt"
"LICENSE.txt"
"ASSIGN.txt"
"makefile"
"src/"
"bin/"
"res/"

Within the "src" folder, there is another folder named "tst". This folder contains random cpp files used to test the already made classes along the way. For example, I could have a "rectangleTest.cpp" file, simply to make sure the Rectangle class does everything that I want it to do before production.

As far as the "bin" folder is concerned, since there are multiple operating systems working on this project, within the "bin" folder there is a "linux" folder and a "windows" folder for the respective binaries.

The "ASSIGN.txt" file contains the workflow of the project. The developers may post assignments for other developers in this file. The assignments may be made another way by the developers directly communicating with each other, in this case, the "ASSIGN.txt" file is simply kept for documentation, who has done what.

COMMENTS:

If Johnathan is in accordance, I propose that the official comment standard is just to have good comments. This means a comment in header files, above methods/functions, and withing methods/functions. Make the world a better place and don't litter, but also please share your comments.

GIT:

Git review:

"git status" - Check the status of your git stuff. If you are confused, type this, maybe it will help.

"git rm" - removes a file from git for you.
"git add" - adds a file to git for you.
"git add *" - adds all the files created or changed to git for you.
"git commit" - needed before a push or a pull.
"git push" - pushes your changes onto the server.
"git pull" - obtains changes from the server to you.

note: After our first working version of mister-sss, or version 1.0, we will need to tag that push in the release section on github.

----------FOR EVERYONE:
This game is really fun. To play it, just make sure you have SDL2 and opengl installed on your system and get ready to play an original game in C++! If you need to compile this and you are running Linux, simply cd into this directory and enter "make" in the terminal. The resulting program will show up in the "bin/" folder.
