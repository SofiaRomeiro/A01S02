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
    gcc -ansi -pedantic -Werror -Wall -Wextra <new-name-optional> <file-1-name> <file-2-name>

> - Must always include main.c in 'file-name' !!

Pre-Processamento (executa diretivas iniciadas por #):
>
    gcc -E <file-name>

Assembly:
>
    gcc -S <file-name>

Tempo de execucao:
>
    time <file-name>

Ler um inteiro:
>
    scanf("%d", &x)
>
    scanf("%d%d", &x, &y)   ---> dois inteiros 

> - Must include '&' before the variable name

WARN:
>
    ** nao existe para potencia, apenas multiplica ponteiros

Numeros:
>
    %d --> inteiro; %f --> float; 

Incrementar + 1/ - 1:
> 
    ++<var> (antes); <var>-- (depois)

> - operador antes da var executa a operação antes do programa correr, e vice versa 

Ler proximo caracter da text stream:
>
    getchar()

Escrever o caracter ASCII correspondente ao numero passado:
>
    putchar(c) 

>
    Costante E0F --> End of File

> - NOTA: nao meter ';' na linha do for, meter na linha seguinte




