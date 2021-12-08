# A solution for the Assistance Bots project

## Statement

Read the complete statement [here](https://github.com/cbuchart/operating_systems_lectures/blob/master/src/AssistanceBots/README.md).

## Compilation

The solution requires a compiler supporting C++17.

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

It will compile two executables: `tecnun_notes_app_basic` and `tecnun_notes_app_pubsub`. The second one implements the optional publisher/subscriber solution.

Add `-DFIND_DATES_USING_REGEX=ON` to use a date search based on regular expressions. This search is slower but illustrates the use of the `regex` module.

## Execution

Commands and notes are introduced through the standard input. You can find several input sets (along with their corresponding expected outputs) in the `samples` directory.

For example:

```bash
./tecnun_notes_app_basic < ../samples/input_1.txt
```
