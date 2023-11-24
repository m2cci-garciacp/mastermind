set -e
# compile
gcc -Wall -o ./scripts/makeData ./scripts/makeData.c
# create data
mkdir -p data
./scripts/makeData
# run tests
./scripts/automator.sh

echo "Probablement sans erreurs d'input de sequence (segmentation fault)"
echo ""