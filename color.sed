#!/usr/bin/sed -E -f
s/[[:<:]](auto|extern|static|register|volatile|const)[[:>:]]/[32m&[0m/g
s/[[:<:]](void|float|double|char|short|int|long|signed|unsigned|[^\s]+_t)[[:>:]]/[33m&[0m/g
s/[[:<:]](if|else|for|while|do|break|continue|return|goto|switch|case|default)[[:>:]]/[34m[0m[34m&[0m/g
s/[[:<:]](struct|enum|union|typedef)[[:>:]]/[35m&[0m/g
s/#[^ 	]+/[31m&[0m/
s/"[^"]*"/[36m&[0m/g
