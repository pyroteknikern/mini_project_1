# Project: Morse coder-decoder (Part 1)

In this programming assignment, create a Morse code (https://en.wikipedia.org/wiki/Morse_code) coder-decoder program in the C programming language. The program should be capable of encoding text into Morse code and decoding Morse code into text. This project is open-ended, meaning, to get a pass grade you need to implement minimum requirements, anything more you do is a bonus, you will learn more and get better.

The data structure you use is a memory data structure - Arrays

## Your task
### Minimum requirements
1. Your app should support the following commands.
  - `help`, - shows the list of commands and what they do.
  - `code input text`, - code the input text in Morse code
  - `decode input text`, - decode the entered Morse code.
   - `search`, shows Morse code for the specified symbol
  - `show`, Shows a table with Morse code
  - `case_sensitive`- enable case-sensitive processing.
- `case_insensitive` - enable case-insensitive processing.

2. Implement an input loop control to show the pt.1 above as a menu and ask user to enter a command
3. Each command will have its own function.
4. Each function should have a doc string/comment, that explains what the function does
5. The program handles errors gracefully, providing clear error messages.
6. Debugging in a local IDE
7. Unified naming conventions
8. The code is well-organized. Each function solves some small, manageable task. 
9. Ensure that the program handles invalid inputs gracefully. For encoding, only accept letters and numbers. For decoding, only accept valid Morse code characters (dots, dashes, and spaces).

### Sky is the limit
Free to add more commands.
Example
- Complicate the coding, add a cipher
(ex https://en.wikipedia.org/wiki/Caesar_cipher )

## struct dictionary:
Provide a dictionary as a struct that defines Morse code for the 26 lowercase letters of the English alphabet and the numbers 0-9. The Morse code representations should include dots (.) for short signals and dashes (-) for long signals, separated by spaces.

It will have the following fields:
- Dictionary ID
- size
- Array of letters of the English alphabet and the numbers 0-9.
- Array of Morse code representations 

## struct coder-decoder:
It will have the following fields
- Dictionary
- Current dictionary ID
- A flag or field to indicate whether the program should be case-sensitive or not when decoding.

1. Encoding Function:
Implement a function that takes a text input (a string) and encodes it into Morse code according to the provided Morse code definitions. The encoding should maintain spaces between words.

2. Decoding Function:
Implement a function that takes a Morse code input (a string) and decodes it into English text according to the provided Morse code definitions. Assume that Morse code characters are separated by spaces, and words are separated by double spaces
