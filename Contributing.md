## VSCode Setup
In order to get Intelli-Sense working with bazel, we need to tell vscode where
to look for the libraries we are using.

When using the `ms-vscode.cpptools` extension, we can use a `compile_commands.json`
file to enable this.

To generate the `compile_commands.json` file run
```bash
bazel run @hedron_compile_commands//:refresh_all
```