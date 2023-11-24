set -e
# create data
mkdir -p data
./scripts/makeData.sh
# run tests
./scripts/automator.sh result.txt

echo "Probablement sans erreurs d'input de difficulte (format fault)"
echo ""