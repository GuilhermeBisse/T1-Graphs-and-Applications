# T1-Graphs-and-Applications
Trabalho 1 da matéria "Grafos e Aplicações", na qual estou atualmente participando.

<u>Para esse trabalho, algumas instruções tivereram que ser seguidas:</u>

Operações que devem ser implementadas:

a) Leitura de arquivo .txt contendo um grafo:
O arquivo deve ter o seguinte formato:

1a linha:
<num_vertices> <num_arestas ou arcos> <tipo> <valorado>

Linhas seguintes
Para cada aresta ou arco {vi, vj}, incluir uma linha no formato:
<vi> <vj> [<peso>]

Observações:
• <tipo>: Indica o tipo do grafo. Use G para grafos não dirigidos e D para grafos dirigidos.
• <valorado>: Use 1 para grafos valorados e 0 para grafos não valorados.
• <peso>: Este campo é opcional e só estará presente em grafos ponderados.
• Arestas ou arcos paralelos podem aparecer mais de uma vez no arquivo.

b) Criação de grafos ou dígrafos pelo usuário:
Permitir que o usuário:
• Defina o tipo do grafo, se é valorado ou não, e a quantidade de vértices.
• Insira quantas arestas ou arcos desejar.
• Salve o grafo em um arquivo .txt seguindo o formato definido na seção (a).

c) Geração da matriz de adjacências:
• Gerar a matriz de adjacências para o grafo.
• Permitir salvar a matriz em um arquivo .txt com o formato:
<a_11> <a_12> <a_13> ... <a_1N>
<a_21> <a_22> <a_23> ... <a_2N>
...
<a_N1> <a_N2> <a_N3> ... <a_NN>

d) Cálculo do grau de cada vértice:
Calcular e exibir o grau de cada vértice do grafo.

e) Encontrar uma árvore geradora mínima:
Implementar um algoritmo para encontrar a árvore geradora mínima.

f) Cálculo de caminho mais curto:
Implementar o algoritmo de Dijkstra para encontrar o caminho mais curto.

g) Busca em largura:
Implementar a busca em largura.

h) Busca em profundidade:
Implementar a busca em profundidade.
