set -e
cd "`dirname "$0"`"

if [ -f ULIS/Tools/Scripts/Linux/Generate_Ubuntu.sh ]; then
    sh ULIS/Tools/Scripts/Linux/Generate_Ubuntu.sh
fi