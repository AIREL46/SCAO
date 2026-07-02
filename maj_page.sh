#!/bin/bash
set -e

if [ $# -ne 1 ]; then
    echo "Utilisation : ./maj_page.sh nom_de_la_page"
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

perl -0pi -e '
s{
!\[(.*?)\]\((.*?)\)\n+
\[\1\]\(\2\)
}{
![$1]($2)
}gsx;
' "$TMP"

echo "=== Conversion HTML ==="

cd "$SITE"

# Sécurisation des titres Markdown
sed -i 's/^## /\n\n## /g' "$TMP"
sed -i 's/^### /\n\n### /g' "$TMP"

pandoc \
    "$TMP" \
    --standalone \
    --css=css/scao.css \
    -o "$PAGE".html

echo "=== Publication ==="

git add "$PAGE".html
git commit -m "Mise à jour de $PAGE"
git push origin master

echo
echo "Terminé."
echo "https://airel46.github.io/SCAO/$PAGE.html"
