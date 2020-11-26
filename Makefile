########################################################################
#                                                                      #
# Copyright(C) 2020 - LBS - (Single person developer.)                 #
# Tue Mar 24 11:27:47 CET 2020                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# Script description:                                                  #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
########################################################################

ROOTCFLAGS  = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS    = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS   = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)

CXX  = g++
CXX += -I./

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated -lpushVectorInRoot
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += $(ROOTLDFLAGS)
CXXFLAGS += $(LIB_push_vector_in_root)

.PHONY: all printmakeinfo clean 

#----------------------------------------------------#

all: push plot

printmakeinfo:
	$(info CXX                 = "$(CXX)")
	$(info CXXFLAGS            = "$(CXXFLAGS)")

push: push.cc
	$(CXX) -o $@ $< $(CXXFLAGS)

plot: plot.cc
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -f *~
	rm -f .*~
	rm -f push
	rm -f plot
