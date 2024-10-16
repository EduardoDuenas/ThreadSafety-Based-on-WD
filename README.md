# ThreadSafety-Based-on-WD
TFG de uma prova de conceito de um mecanismo de "exclusão mutua" sem uso de mutex baseado em WatchDog

Resumo do TFG
Esse trabalho consiste no desenvolvimento, análise e resultado da implantação de uma função de permanência num Sistema Operacional. A ideia do projeto é um sistema que permite uma tarefa executar durante um período determinado no processador sem ser substituída por outra tarefa em uma troca de contexto. O objetivo é fazer possível que uma tarefa de baixa prioridade seja executada sem ser substituída por uma de maior prioridade e sem diminuir a robustez do sistema, garantindo segurança contra race condition nas seções críticas.
