# A01S02

## C

Deteta erros no codigo:
>
    -ansi

Rejeita todas as extensoes pribidas:
>
    -pedantic 

> - 'Warning' avisa mas compila, 'Error' nao compila !

Transformar warnings em erros:  
>
    -Werror

Emite todos os warnings acerca de possiveis erros:
>
    -Wall -Wextra 

Comandos completos para compilar:
>
    gcc -ansi -pedantic -Werror -Wall -Wextra -o <file-name>

Ver conteudo do ficheiro no cmd:
>
    cat <file-name>

Compilar varios ficheiros:
>
    gcc -ansi -pedantic -Werror -Wall -Wextra <file-1-name> <file-2-name>

> - Must always include main.c in 'file-name' !!

Pre-Processamento (executa diretivas iniciadas por #):
>
    gcc -E <file-name>

Assembly:
>
    gcc -S <file-name>
