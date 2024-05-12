# Enigma-Emulator
Hi. In the final year of high school in Denmark every student has to write an in-depth paper about a specific topic. I decided to research and write about the Enigma machine and the importance for the Second World War. While the paper is still being processed I decided to get into coding around a month ago, and so to take advantage of the fact the my knowledge around the inner working of the machine is still quite fresh, this marks my first coding project.

## Briefly about the Enigma machine: 
The Enigma machine was an electrical encrypting device used by Nazi Germany during the Second World War. It's efficiency in encrypting and decrypting strong cryptotexts lies primarily in to fields. 1) The rotor system consisting of 3 scrambler wheels and a reflecter. 2) The plugboard which allows for additional complexity though paired letter substitutions. The creator of the device, Arthur Scherbius, made sure that the initial (user-determined) setting for the Enigma could decrypt a message by using the same settings that were used to encrypt it. (I strongly recommend testing this out.)

## Emulator features
Throughout this project I made it my goal to design the emulator in a way that would resemble a real enigma as closely as possible. This was done actively by researching the specific wirings of each rotor model, exact turnover notchpoints of each scrambler wheel, the reflecter model's specific letter substitutions, etc. All these features have been implimented to allow users to select inbetween the 5 rotor models true to that of those used in german army and air force during the Second World War. 

## Installation
This program uses the CS50 library primarily for user prompting. After having copied over the repository to a local machine make sure to compile the program with the following GCC compiler that includes the CS50 library: `gcc -o enigma enigma.c -lcs50`. Finally run the code:
`./enigma`.


## How to use
In order to encrypt a message with the Enigma emulator, the user will first be prompted to pick the specific rotor ordering 1-5, where the first 1, 2 and 3 represent the ones used in the M1 Enigma model, and 4 and 5 represent the ones used in the Army enigma after 1938. Then the specific rotor position will be determined for each of the 3 rotors. After having initiated the rotor system the user will be prompted for 6 plugboard pairs totalling 12 letters. Finally a specific messages can be entered and encrypted/decrypted. 
  
### Example: encrypt 
  Rotor-order: 1-2-3
  Rotor-positions: A-B-C
  Plugboard: qa-ws-ed-rf-tg-yh
  Input: HELLO
  Output: VAUEY

### Example: decrypt
  Rotor-order: 1-2-3
  Rotor-positions: A-B-C
  Plugboard: qa-ws-ed-rf-tg-yh
  Input: VAUEY
  Output: HELLO
