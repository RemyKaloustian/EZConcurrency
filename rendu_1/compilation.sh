###########################
#  Compilation program    #
# author : @CésarCollé    #
###########################

if [ "$0" = "debug" ]; then
  make clean
  make ARG=-DDEBUG
else
  make clean
  make
fi
