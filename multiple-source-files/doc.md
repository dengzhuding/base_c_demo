# GCC 简易使用说明

## compile - 编译阶段生成目标文件(.o)，再链接

### 1. 生成一个可执行文件
  ```
  gcc -Wall main.c hello_fn.c -o newhello  
  .\newhello.exe
  ```

### 2. 先生成目标文件，再链接
  ```
  gcc -Wall -c .\main.c
  gcc -Wall -c .\hello_fn.c
  gcc main.o hello_fn.o -o hello2
  .\hello2.exe
  ```


### 3. 修改源文件,重新链接
  修改文件后重新生成目标文件(.o)
  注意：
  **只修改main.c,仅仅需要重新编译main.c创建新的main.o**
  **如果修改了hello_fn.c,就需要重新编译hello_fn.c创建新的hello_fn.o**
  ```
  gcc -Wall -c .\main.c  
  gcc main.o hello_fn.o -o hello3  
  .\hello3.exe
  ```


## [A simple makefile](https://www.linuxtopia.org/online_books/an_introduction_to_gcc/gccintro_16.html)

Make 从 makefile 中读取项目的描述（默认情况下，在当前目录中称为“Makefile”）  
makefile 根据目标（例如可执行文件）及其依赖项（例如目标文件和源文件）指定一组编译规则，格式如下：
```
target: dependencies
        command
```
**Note that the command lines in a makefile must be indented with a single TAB character, not spaces**


**use:**
1. Makefile文件，有默认规则(隐式规则inimplicit rules)以简化 makefile 的构造(如main.o由main.c而来等)
```
CC=gcc
CFLAGS=-Wall

main: main.o hello_fn.o
clean:
    rm -f main main.o hello_fn.o
```

2. 键入make ->会生成可执行文件main
