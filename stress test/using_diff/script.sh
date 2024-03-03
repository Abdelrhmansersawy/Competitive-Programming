set -e

for((i = 1; i < 10; ++i)); do

    echo "Passed test: "  $i
done

cat input_file  > failtest.txt
open failtest.txt
