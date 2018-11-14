# OS Project 2: Synchronization

An introduction to multi-threaded code in C. Uses the `pthread` library to run 4 additional threads that communicate via queues.

1. Reader parses input into individual words and sends the strings to Munch1
1. Munch1 converts each lowercase character into its uppercase complement and sends the string to Munch2
1. Munch2 converts each space into an `*` (asterisk) and sends the string to Writer
1. Writer outputs the string to `stdout`.
1. At the end, Main outputs statistics about the queues.
