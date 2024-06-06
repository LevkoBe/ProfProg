**TASK. Another singleton**

We need to have an interactive program that asks user for his 5 favorite words. After that the program should run 5 threads for every word. Each thread should sleep for a second and then it should print a message(<pre-word> word <post-word>) based on the program configuration stored in a configuration file with content
a-k <pre-word> <post-word>
l-o <pre-word> <post-word>
p-z <pre-word> <post-word>
Therefore pre-word and post-word for the current thread should be chosen based on the first letter of the favorite word passed to the thread.
Your task is to use Singleton pattern to have on-demand load of configuration and usage of this configuration in different threads.
