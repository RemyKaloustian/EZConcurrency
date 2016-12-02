###########################
#  Compilation program    #
# author : @CésarCollé    #
###########################

#PATH= "$( "$(dirname "$0")"/makefile && pwd)"
# make
# PATH_="$(cd "$(dirname "$0")"&&pwd)"/
# pwd
# cd $PATH_ && make clean
# cd $PATH_ && make


if [ "$1" = "debug" ]; then
  make clean
  make ARG=-DDEBUG
elif [ "$1" = "plot" ]; then
  make clean
  make ARG=-DPLOT
else
  PATH_="$(cd "$(dirname "$0")"&&pwd)"/
  cd $PATH_ && make clean
  cd $PATH_ && make

fi
