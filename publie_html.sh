#!/bin/bash
set -e

if [ $# -ne 1 ]; then
    echo "Utilisation : ./publie_html.sh nom_de_la_page"
    exit 1
fi

PAGE="$1"

SITE="$HOME/SCAO"

cd "$SITE"

echo "=== Vérification ==="

if [ ! -f "$PAGE.html" ]; then
    echo "Erreur : $PAGE.html n'existe pas."
    exit 1
fi

echo "=== Publication ==="

git add "$PAGE.html"

# Ajoute également le CSS si vous l'avez modifié
git add css/scao.css

if git diff --cached --quiet; then
    echo "Aucune modification à publier."
    exit 0
fi

git commit -m "Mise à jour de $PAGE"
git push origin master

echo
echo "Publication terminée."
echo
echo "Votre page sera disponible dans quelques instants :"
echo "https://airel46.github.io/SCAO/$PAGE.html"
