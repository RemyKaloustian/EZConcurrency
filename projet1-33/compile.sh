###########################
#  Compilation program    #
# author : @CésarCollé    #
###########################

if [ "$1" = "debug" ]; then
  make clean
  make ARG=-DDEBUG
elif [ "$1" = "plot" ]; then
  make clean
  make ARG=-DPLOT
else
  make clean
  make
fi
