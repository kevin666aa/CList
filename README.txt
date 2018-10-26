README

included:
All source files (.cpp, .h)
this README
Makefile

Proj1 ECS60

I have to say that although this one doesn't need us to write much code, but it is still quite challenging, especially to start with. My main structure is link list, which I used shared_ptr to connect each node. 

It took me three whole days to finish. There were times when I sit there coding, I just want to smash my Mac and poke into my own eyes. Luckily I went through. 

I passed all five of the cases. There are no true memory leak in my program, tested with valgrind. But I do have still reachable leak dectected by valgrind. I check on https://stackoverflow.com/questions/3840582/still-reachable-leak-detected-by-valgrind , which says that this is fine, so I just consider it done. (I don't know how to do it either)

I learned a lot from the project. I now know that PIMPL is a pain in the ass, but it is secure. I have deeper understand of shared_ptr and link list. I was going to try weak_ptr but I was too exhausted. 

That's all.

Reference: 
	For link list, I went through some definitions on the internet, and I actually looked into the example of linklist in my ECS40 class. Link: https://drive.google.com/drive/u/1/folders/1dY01eJLI9tMe8X074OZc8BZW9akBn0yq
	For the operators, I looked into one of the homework I did in ECS40, which is myvector. (Can't put in here)
	For this README.txt, I looked into a example file. Link: https://courses.cs.washington.edu/courses/cse326/02wi/homework/hw5/README-2.txt


Yiran Wu (Kevin) Aug.12 2018