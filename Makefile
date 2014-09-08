#/*
 #* =========================================================================
 #*
 #*        Filename: Makefile
 #*
 #*        Version:  1.0
 #*        Created:  2014-08-09 01:59:56
 #*        Description:  生成可执行文件 makefile模板
 #*
 #*        Author:  walter(朱瑜玮) (walter@taomee.com)
 #*        Company:  TaoMee.Inc, ShangHai.
 #=========================================================================

CC = g++
WORKDIR = .
SRCDIR = $(WORKDIR)/src
INCLUDEDIR = $(WORKDIR)/include
OBJDIR = $(WORKDIR)/obj
BINDIR = $(WORKDIR)/bin
CFLAGS = -g -Wall -Wreorder -std=c++0x -I$(INCLUDEDIR)
LFLAGs = -lpthread
TARGET = $(BINDIR)/testthread

#找到所有的.cpp
SRCS = $(wildcard $(SRCDIR)/*.cpp)
#找到所有的.h
HEADERS = $(wildcard $(INCLUDEIR)/*.h)
#生成.o文件至obj/下,nodir是出去文件的路径名
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRCS)))

all : $(TARGET)

#$@表示目标文件
$(TARGET) : $(OBJS) 
	$(CC) $(OBJS)  -o $@ $(LFLAGs)

#$<表示第一个依赖文件, 即$(OBJDIR)/%.o，泛指生成某个.o文件
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -rf $(OBJS)

.PHONY: all clean clean_all  
