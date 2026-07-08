#!/bin/bash
set -e

if [ $# -ne 1 ]; then
    echo "Utilisation : ./genere_html.sh nom_de_la_page"
    exit 1
fi

PAGE="$1"

WIKI="$HOME/SCAO.wiki"
SITE="$HOME/SCAO"

echo "=== Mise à jour du wiki ==="
cd "$WIKI"
git pull

echo "=== Préparation du Markdown ==="

TMP="/tmp/$PAGE.md"
cp "$PAGE.md" "$TMP"

# Transformation des URL GitHub en chemins locaux
sed -i 's|https://github.com/AIREL46/SCAO/blob/master/||g' "$TMP"

# Sécurisation des titres Markdown
sed -i 's/^## /\n\n## /g' "$TMP"
sed -i 's/^### /\n\n### /g' "$TMP"

echo "=== Conversion HTML ==="

cd "$SITE"

pandoc \
    "$TMP" \
    --standalone \
    --css=css/scao.css \
    -o "$PAGE.html"

echo
echo "Fichier HTML généré :"
echo "$SITE/$PAGE.html"
echo
echo "Vous pouvez l'ouvrir avec :"
echo "xdg-open $SITE/$PAGE.html"
