# Sincronização do Metrô

## Descrição do projeto

O Sincronização do Metrô é um projeto desenvolvido em C que tem como objetivo controlar a sincronização entre carros de metrô e passageiros utilizando threads.

Cada carro e cada passageiro são representados por threads independentes. O sistema utiliza mecanismos de sincronização para organizar o embarque dos passageiros, garantindo que eles só possam embarcar quando houver um carro na estação e assentos disponíveis.

Quando um carro chega à estação, a função `station_load_car()` informa a quantidade de assentos disponíveis e aguarda até que o embarque seja satisfatório. Isso acontece quando todos os passageiros que estavam esperando embarcam ou quando o carro fica cheio.

Os passageiros utilizam a função `station_wait_for_car()` para aguardar a chegada de um carro com assentos disponíveis. Após embarcarem, chamam `station_on_board()` para informar ao sistema que o embarque foi concluído.

A sincronização é realizada utilizando mutexes e variáveis de condição da biblioteca POSIX Threads (`pthread`). Dessa forma, as threads podem aguardar os eventos necessários sem utilizar busy-wait.

O projeto foi desenvolvido em C para ambiente Linux, utilizando o Ubuntu por meio do WSL.

## Estrutura dos arquivos

O projeto está organizado da seguinte forma:

- `sync_car.c` — contém a implementação das funções de inicialização da estação e sincronização entre carros e passageiros.
- `sync_car.h` — contém a definição da estrutura `station` e as declarações das funções utilizadas pelo projeto.
- `sync_car-runner.c` — arquivo de testes fornecido pelo professor, utilizado para verificar o funcionamento da sincronização.
- `Makefile` — utilizado para compilar o programa e remover o executável gerado.
- `README.md` — documentação do projeto.

## Como compilar

Para compilar o projeto, basta executar o comando:

```bash
make
```

O comando gera o executável:

```text
sync_car
```

Para remover o executável compilado, utilize:

```bash
make clean
```

## Como executar

Após compilar o projeto, execute:

```bash
./sync_car
```

O programa executa os testes de sincronização definidos no arquivo `sync_car-runner.c`.

Quando os testes são concluídos com sucesso, a mensagem apresentada é:

```text
Looks good!
```

## Funcionamento da sincronização

### Inicialização da estação

A função `station_init()` inicializa o mutex, as variáveis de condição e os contadores utilizados no controle do embarque.

### Chegada e embarque dos passageiros

A função `station_wait_for_car()` registra a chegada de um passageiro à estação. Caso não exista um carro presente ou não haja assentos disponíveis, o passageiro aguarda por meio de `pthread_cond_wait()`.

Quando um carro está disponível e existem assentos livres, o passageiro é autorizado a prosseguir.

### Chegada do carro

A função `station_load_car()` recebe a quantidade de assentos disponíveis no carro. A função libera as vagas de acordo com a quantidade de passageiros contabilizados como esperando e aguarda a confirmação dos embarques necessários.

Após a conclusão do embarque esperado, as vagas são encerradas e o carro deixa de ser considerado presente na estação.

### Confirmação do embarque

A função `station_on_board()` registra que um passageiro embarcou, incrementando o contador correspondente e sinalizando a variável de condição utilizada para acordar o carro.

## Mecanismos de sincronização

O projeto utiliza os seguintes mecanismos da biblioteca `pthread`:

- `pthread_mutex_init()` — inicializa o mutex da estação.
- `pthread_mutex_lock()` — protege o acesso compartilhado aos dados da estação.
- `pthread_mutex_unlock()` — libera o mutex após a operação protegida.
- `pthread_cond_init()` — inicializa as variáveis de condição.
- `pthread_cond_wait()` — permite que uma thread aguarde uma condição sem utilizar busy-wait.
- `pthread_cond_signal()` — sinaliza uma thread que aguarda uma variável de condição.
- `pthread_cond_broadcast()` — sinaliza todas as threads que aguardam uma variável de condição.

A estrutura `station` utiliza apenas um mutex para proteger os dados compartilhados. As variáveis de condição permitem coordenar a disponibilidade do carro, das vagas e a confirmação dos embarques.

## Testes realizados

Durante o desenvolvimento, o programa foi compilado e executado utilizando o runner fornecido pelo professor.

Foram realizados testes para verificar:

- O comportamento quando o carro chega sem assentos disponíveis.
- O embarque de passageiros quando há vagas disponíveis.
- O embarque quando há mais vagas do que passageiros restantes.
- A espera do carro pela confirmação dos embarques.
- A sincronização entre as threads de passageiros e carro.

Também foram feitas dez execuções consecutivas em dois lotes, totalizando vinte execuções bem-sucedidas.

Esses resultados demonstram que os testes realizados foram concluídos com sucesso, embora não constituam uma prova formal da ausência de todas as condições de corrida.

## Sistema operacional utilizado

O projeto foi desenvolvido e testado no seguinte ambiente:

- **Sistema operacional:** Ubuntu Linux via WSL.
- **Linguagem:** C.
- **Compilador:** GCC.
- **Biblioteca de threads:** `pthread`.
- **Ferramenta de compilação:** Make.