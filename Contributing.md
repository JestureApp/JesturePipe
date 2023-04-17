# Development Requirements
* [Bazel](https://bazel.build/)
  
# IDE setup
For any IDEs using some form of `clangd` for IntelliSense run
```
bazel run //.vscode:compile_commands
```
to generate a `compile_commands.json` file.

## VSCode
VSCode is the preferred IDE as we have setup some tooling to make working in this
code base easier.

### Tasks
* Build all
* Build all (debug)
* Refresh compile_commands.json

# More
For more information please see the following
* [Gesture](jesturepipe/gesture/README.md)