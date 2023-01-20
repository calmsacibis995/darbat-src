#!/bin/sh

# First argument is the file to source stuff from
config=$1
shift 

if [ $1 = "-v" ]; then
    VERBOSE=1
    shift
else
    VERBOSE=0
fi;

# Command to run
op=$@
IFS='
'
TLA=${TLA:-`which baz`}
TLA=${TLA:-`which tla`}
# ${TLA:?"Can't find baz or tla"}

echo "Package: Root"
$TLA "$@"

for i in `$TLA cat-config $config`; do
    dir=`echo $i | cut -f1`
    src=`echo $i | cut -f2`
    if [ -d $dir ]; then
	echo "Package: $dir ($src)"

	# If it's 'update' or 'changes' we need to do benno magic
	if [ $1 = "update" -o $1 = "changes" ]; then
	    # Check version
	    (   IFS=/;
		set $src;
		IFS=' ';
		archive=$1
		category=$2
		src=$archive/$category
		CUR=`(cd $dir; $TLA tree-version)`
		set `echo $category | sed 's/--/ /g'`
		if [ -z $3 ]; then
		    LATEST=$archive/`$TLA versions -r $src | head -1`
		else
		    LATEST=$archive/$category;
		fi;
		if [ $CUR != $LATEST ]; then
		    if [ $BAZ_ALWAYS_UPDATE ]; then
			(cd $dir; baz switch $LATEST);
		    else
			echo "WARNING: different! Current:" $CUR "Latest:" $LATEST
			echo " This probably means a version has jumped. In which you case will want to "
			echo " update to the latest version. "
			echo
			echo " Using baz: (cd $dir; baz switch $LATEST) "
			echo
			echo " Using tla: Remove the directory and rerun tla_config.sh"
		    fi;
		fi;
	    );
	fi;

	# Execute the actual code
	if [ $VERBOSE -eq "1" ]; then
	    (cd $dir; $TLA "$@");
	else
	    (cd $dir; $TLA "$@" | grep -v "^\*" )
	fi;    
    else
	echo "Directory doesnt exist!" $dir, $src;
	$TLA get $src $dir;
    fi;
done
