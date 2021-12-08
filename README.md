# A solution for the Assistance Bots project

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/cc11443d2d3e47b593ee2b59c05bb1d8)](https://app.codacy.com/gh/cbuchart/tecnun_assistance_bots?utm_source=github.com&utm_medium=referral&utm_content=cbuchart/tecnun_assistance_bots&utm_campaign=Badge_Grade_Settings)

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
