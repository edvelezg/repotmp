#!/bin/bash
	set -x
      OPTIONS="Compile Clean Quit"
      select opt in $OPTIONS; do
          if [ "$opt" = "Quit" ]; then
           echo done
           exit
          elif [ "$opt" = "Compile" ]; then
           	g++ -c mylib.cpp
			ar ru libmylib.a mylib.o
       	  elif [ "$opt" = "Clean" ]; then
            rm -f *.o *.a
          else
           clear
           echo bad option
          fi
      done
