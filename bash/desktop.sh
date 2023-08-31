#!/bin/bash

desktop_path="$1" # Parametre olarak masaüstü yolunu al

if [ -z "$desktop_path" ]; then
    echo "Kullanım: $0 <masaüstü_yolu>"
    exit 1
fi

if [ -d "$desktop_path" ]; then
    for entry in "$desktop_path"/*; do
        echo "$(basename "$entry")"
    done
else
    echo "Masaüstü bulunamadı veya bir dizin değil."
fi