modules=(
    "tiny-regex-c/re.c"
    "main.c"
    "lexem.c"
    "syntax.c"
    "interpreter.c"
)

output="./build/main"

gcc -Wall -pedantic "${modules[@]}" -o "$output" -lm

if [ "$1" = "run" ]; 
then
    "$output"
fi