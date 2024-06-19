**TASK. State machine**

Let's implement the following logic using FSM pattern.

Our console program should prompt user for the commands("sad", "fun", "silly", "dangerous") to switch the active song e.g. print corresponding line to the console.
We have the following strings to represent songs from our playlist:
- "Intro"
- "Starman"
- "Show must go on"
- "Let it be"
- "But in the end, it doesn't even matter"

Switches between songs are determined by the rules:
- program starts with playing "Intro"
- if we are playing "Intro" and we got a command "dangerous" then song should be switched to "Let it be"
- if we are playing "Intro" and we got a command "fun" then song should be switched to "Starman"
- if we are playing "Intro" and we got a command "sad" then song should be switched to "But in the end, it doesn't even matter"
- if we are playing "Starman" and we got a command "silly" then song should be switched to "Intro"
- if we are playing "Starman" and we got a command "dangerous" then song should be switched to "Show must go on"
- if we are playing "Starman" and we got a command "fun" then song should be switched to "But in the end, it doesn't even matter"
- if we are playing "Show must go on" and we got a command "sad" then song should be switched to "Let it be"
- if we are playing "Show must go on" and we got a command "fun" then song should be switched to "Starman"
- if we are playing "Let it be" and we got a command "dangerous" then song should be switched to "Intro"
- if we are playing "Let it be" and we got a command "silly" then song should be switched to "Show must go on"
- switch to the song "But in the end, it doesn't even matter" causes program termination.
- all other combinations of active song and command just cause replay of the current song.
