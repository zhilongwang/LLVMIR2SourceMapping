# LLVM IR to Source Mapping

This llvm pass demonstrate how to map llvm IR to source code.

#### Compile

```
# Install Dependency, llvm-6.0 clang-6.0 is prefered.
sudo apt-get install llvm clang 

# Compile LLVM Pass
mkdir build
cd build
cmake ..
make 
```


#### Usage

```
# Compile a Target Programs
cd testcase
clang -Xclang -load -Xclang ../build/libLLVMIR2SourceMapping.so -o target target.c
```


