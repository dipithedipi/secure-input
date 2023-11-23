#!/bin/bash

# gcc -o test_number ../lib/input.c test_number.c -Ilib

# Funzione per eseguire il test
run_test() {
    local test_number="$1"
    local prompt="$2"
    local retryOnInvalid="$3"
    local expected="$4"
    local bufferSize="$5"
    local input="$6"
    local retryInput="$7"

    echo -e "Test $test_number:\n"

    # Esegui il programma e cattura l'output
    local program_output=$(echo -e "$input" | ./test_number 2>&1)  # Sostituisci "compiled" con il nome del tuo eseguibile
    local program_return=$?

    echo -e "[-] Output programma:"
    echo -e "$program_output"
    echo -e "\n[-] Risultato test:"

    # Controlla il risultato restituito dal programma
    if [ "$program_return" -eq "$expected" ]; then
        echo -e "- Input dato: $input"
        echo -e "- Expected: $expected"
        echo -e "- Recived: $program_return"
        echo -e "- Program result: Pass\n"
        ((passed_tests++))
    else
        echo -e "- Input dato: $input"
        echo -e "- Expected: $expected"
        echo -e "- Recived: $program_return"
        echo -e "- Program result: Fail\n"
        ((failed_tests++))
    fi

    echo -e "--------------------------------------\n"
}

# Inizializza contatori
passed_tests=0
failed_tests=0

# Esegui i test
run_test 1 "Inserisci un numero intero" true 0 10 "42\n"
run_test 2 "Inserisci un numero intero" true 0 20 "1234567890123456789\n"
run_test 3 "Inserisci un numero intero" false 0 5 "abc\n"
run_test 4 "Inserisci un numero intero" false 0 5 "12abc\n"
run_test 5 "Inserisci un numero intero" true 0 10 "-99\n"
run_test 6 "Inserisci un numero intero" false 0 5 " 42 \n"
run_test 7 "Inserisci un numero intero" true 0 3 "0\n"
run_test 8 "Inserisci un numero intero" false 0 3 "  0 \n"
run_test 9 "Inserisci un numero intero" false 0 3 " 123 \n"
run_test 10 "Inserisci un numero intero" true 0 5 "-456\n"
run_test 11 "Inserisci un numero intero" false 0 5 "789\n"
run_test 12 "Inserisci un numero intero" false 0 5 "789xyz\n"
run_test 13 "Inserisci un numero intero" true 0 30 "999999999999999999\n"
run_test 14 "Inserisci un numero intero" false 0 5 "\n"
run_test 15 "Inserisci un numero intero" true 0 10 "   42 \n"
run_test 16 "Inserisci un numero intero" false 0 5 "12.34\n"
run_test 17 "Inserisci un numero intero" true 0 15 "987654321\n"
run_test 18 "Inserisci un numero intero" false 0 5 "  \n"
run_test 19 "Inserisci un numero intero" false 0 5 "abc123\n"
run_test 20 "Inserisci un numero intero" false 0 5 "3.14\n"
run_test 21 "Inserisci un numero intero" false 0 5 "a\n"

# Stampare il risultato totale
echo -e "Risultato totale:"
echo -e "Test passati: $passed_tests"
echo -e "Test falliti: $failed_tests"
