obj = main.o ExpressionManager.o # the nature of the variable of makefile is C-like macro. 

main : $(obj)  
	cc -std=c++17 -o main $(obj)  

# GNU的make可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个 .o 文件后都写上同更新执行文件类似的命令。
# 进一步地，我们可以把依赖文件相同的目标文件放在一起，make也会自动推导
# 这叫隐晦规则，优点是精简，缺点是关系凌乱不利于后续维护
$(obj) : ExpressionManager.h

# 不成文的规矩是——“clean从来都是放在文件的最后”。
# .PHONY 表示 clean 是一个“伪目标“
.PHONY : clean
clean : 
	cat main.cpp 
# 而在 rm 命令前面加了一个小减号的意思就是，也许某些文件出现问题，但不要管，继续做后面的事。
	-rm main $(obj)

# 如果你的Makefile需要一口气生成若干个可执行文件，但你只想简单地敲一个make完事，
# 并且，所有的目标文件都写在一个Makefile中，那么你可以使用“伪目标”这个特性：
# all : prog1 prog2 prog3
# .PHONY : all

# prog1 : prog1.o utils.o
#     cc -o prog1 prog1.o utils.o

# prog2 : prog2.o
#     cc -o prog2 prog2.o

# prog3 : prog3.o sort.o utils.o
#     cc -o prog3 prog3.o sort.o utils.o

# (因为Makefile中的第一个目标会被作为其默认目标
# 这里如果不写.PHONY，其实make也会自动推导。但是显示写出是好习惯


# 传统写法
 
# 执行文件edit和中间目标文件（ *.o ）都是目标文件

# 第一个目标文件将被视为执行文件。执行文件是我们的终极目标文件。
# 执行文件的依赖文件则是中间目标文件。
# 执行文件的更新方式
# edit : main.o ExpressionManager.o
# 	cc -std=c++17 -o edit main.o ExpressionManager.o

# 依赖文件（prerequisites）就是冒号后面的那些 .c 文件和 .h 文件
# 中间文件的更新方式
# main.o : main.cpp ExpressionManager.h
# 	cc -std=c++17 -o main.cpp

# ExpressionManager.o : ExpressionManager.cpp ExpressionManager.h
# 	cc -std=c++17 -o ExpressionManager.cpp

# 删除中间文件 
# clean不是文件，只是一个动作。冒号后面是空的。
#  要执行其后的命令，就要在make命令后明显地指出这个label的名字。这样的方法非常有用，我们
# 可以在一个makefile中定义不用的编译或是和编译无关的命令，比如程序的打包，程序的备份，等等。
# clean :
# 	rm edit main.o ExpressionManager.o

# 在Makefile使用 include 关键字可以把别的Makefile包含进来
# 在 include 前面可以有一些空字符，但是绝不能是 Tab 键开始
# include 的语法是：

# include <filename1> <filename2> ...

# 如果你想让make不理那些无法读取的文件，而继续执行，你可以在include前加一个减号“-”。如：

# -include <filename>


# make支持三个通配符： * ， ? 和 ~