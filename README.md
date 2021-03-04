# A01S02

## C

Deteta erros no codigo:
>
    -ansi

Rejeita todas as extensoes pribidas:
>
    -pedantic 

'Warning' avisa mas compila, 'Error' nao compila !

Transformar warnings em erros:  
>
    -Werror

Emite todos os warnings acerca de possiveis erros:
>
    -Wall -Wextra 

Comandos completos para compilar:
>
    gcc -ansi -pedantic -Werror -Wall -Wextra -o <file-name>