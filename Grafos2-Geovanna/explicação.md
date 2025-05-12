# Grafos Parte 2

## MST + 1

Problema no AtCoder: [https://atcoder.jp/contests/abc235/tasks/abc235_e](https://atcoder.jp/contests/abc235/tasks/abc235_e)

Submissão: [https://atcoder.jp/contests/abc235/submissions/65699612](https://atcoder.jp/contests/abc235/submissions/65699612)

### Explicação da solução: 
Como a questão exige o processamento de QQ consultas, respondê-las de forma online (isto é, à medida que são recebidas) torna-se inviável, pois isso implicaria em uma complexidade de O(Q⋅Nlog⁡N)O(Q⋅NlogN).

Dessa forma, adota-se uma abordagem offline utilizando o algoritmo de Kruskal. Cada consulta é incorporada ao vetor de arestas com um identificador próprio; as arestas iniciais (aquelas fornecidas previamente) são marcadas com identificador igual a −1−1.

O algoritmo de Kruskal é então executado da seguinte forma: todas as arestas (inclusive as consultas) são ordenadas por peso, e a cada iteração a aresta é considerada para união apenas se os dois vértices ainda não pertencem ao mesmo componente.

Para as arestas correspondentes às consultas (id≠−1id=−1), se os vértices AA e BB ainda não pertencem ao mesmo componente conexo, registra-se a resposta da consulta como "Yes", sem realizar o merge desses componentes na estrutura DSU. Caso contrário, a resposta padrão é "No".

Com essa abordagem, a complexidade total do algoritmo torna-se O((Q+N)⋅log⁡α(N))O((Q+N)⋅logα(N)), onde αα é a função inversa de Ackermann, proveniente da operação find da DSU com compressão de caminho. Como α(N)α(N) cresce extremamente devagar, essa complexidade é considerada praticamente linear na prática.

## 1D Bucket Tool

Problema no AtCoder: [https://atcoder.jp/contests/abc380/tasks/abc380_e](https://atcoder.jp/contests/abc380/tasks/abc380_e)

Submissão: [https://atcoder.jp/contests/abc380/submissions/65703444](https://atcoder.jp/contests/abc380/submissions/65703444)

### Explicação da solução: 
A solução proposta baseia-se na utilização de dois vetores auxiliares e uma estrutura de união e busca (DSU) para o gerenciamento eficiente dos blocos por cor.

O primeiro vetor, denominado cnt, armazena a contagem total de blocos para cada cor. O segundo vetor, ps, está associado à estrutura parent e guarda a cor atual de um conjunto de blocos cujo representante (pai) é LL, sendo CC a cor desse conjunto.

A DSU é empregada para unir o bloco LL com seus vizinhos L−1L−1 e L+SL+S, desde que a cor de L−1L−1 ou L+SL+S coincida com a nova cor atribuída a LL. Essa verificação evita a fusão de blocos de cores distintas.

Após a realização de cada operação do tipo 1 (pintura de bloco), o vetor ps é atualizado no representante do conjunto resultante da operação de find. Em operações do tipo 2 (consulta), imprime-se o valor atual de cnt para uma determinada cor CC, o qual é previamente atualizado no início de cada operação do tipo 1, com base no bloco que foi pintado.

## Flip Edge

Problema no AtCoder: [https://atcoder.jp/contests/abc395/tasks/abc395_e](https://atcoder.jp/contests/abc395/tasks/abc395_e)

Submissão: [https://atcoder.jp/contests/abc395/submissions/65704215](https://atcoder.jp/contests/abc395/submissions/65704215)

### Explicação da solução: 
Nesta questão, o objetivo é determinar o menor caminho entre vértices em um grafo, considerando dois tipos distintos de operações: percorrer arestas normalmente e r everter todas as direções das arestas do grafo, mediante um custo adicional fixo XX.

Para lidar com essa dinâmica, utiliza-se uma abordagem modificada de Dijkstra, mantendo duas versões da distância mínima para cada vértice:

* dist[u][0]dist[u][0]: menor distância até o vértice uu quando o grafo está em seu estado original (não revertido);

* dist[u][1]dist[u][1]: menor distância até o vértice uu quando o grafo está no estado revertido.

O algoritmo segue as regras de: para transições entre os estados (ou seja, de estado 0 para 1 ou de 1 para 0), adiciona-se o custo fixo XX à prioridade na fila (heap); Para movimentações dentro do mesmo estado (isto é, continuar percorrendo arestas no estado atual), adiciona-se o custo da aresta correspondente normalmente.

Essa variação do algoritmo de Dijkstra garante a correta consideração dos dois contextos de execução (original e revertido). A complexidade total da solução é O(N+Mlog⁡M)O(N+MlogM), onde NN é o número de vértices e MM o número de arestas.

