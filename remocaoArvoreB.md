Algoritmo Remover(arvore, chave){
	pagina, posicao = buscaArvoreB(arvore, chave);
	se(pagina == null){
		retorne;
	}
	se(pagina == arvore.raiz E pagina[pos].esq == null E pagina[pos].dir == null){
		se(pagina.qtd == 1){
			liberar(pagina);
		}
		senao{
			liberar(pagina[pos]);
		}
	}
	senao{
		Substituir(pagina, posicao);
	}
}

Algoritmo Substituir(pagina, posicao){
	aux = pagina;
	se(aux[posicao].esq != null){
		aux = aux[posicao].esq;
	}
	enquanto(aux[aux.qtd-1].dir != null){
		aux = aux[aux.qtd-1].dir
	}
	pagina[posicao] = aux[aux.qtd-1];
	liberar(aux[aux.qtd-1]);
	aux.qtd--;
	
	consertaEstrutura(aux);
}

Algoritmo consertaEstrutura(pagina){
	se(pagina == null){
		retorne;
	}
	se(pagina.qtd < d){
		int pos_pai = buscaPosNoPai(pagina, chave);
		Pagina pai = pagina.pai;
		Pagina irma;
		se(pai[pos_pai-1].esq != null){
			irma = pai.esq;
		}
		senao se(pai[pos_pai+1].esq != null){
			irma = pai.dir;
		}
		se(pagina.qtd + irma.qtd < 2d){
			Concatenacao(pagina, irma);
		}
		senao{
			Redistribuicao(pagina, irma);
		}
}

Algoritmo Concatenaçao(pagina, irma){
	Pagina Pai = pagina.pai;
	se(pai[pos_pai] < pagina[pagina.qtd-1]){
		ajustaPosicaoEPonteiro(pagina, pai, pos_pai);
		pagina[0].pont_esq = irma[irma.qtd-1].pont_dir;
		pai[pos_pai-1].pont_dir = pai[pos_pai].pont_dir;
	}
	senao{
		ajustaPosicaoEPonteiro(pagina, pai, pos_pai);
		pagina[0].pont_dir = irma[irma.qtd-1].pont_esq;
	}
	liberar(pai[pos_pai]);
	pai.qtd--;
	para(int i = irma.qtd-1; i >= 0; i--){
		ajustaPosicaoEPonteiro(pagina, irma, i);
	}
	liberar(irma);
	consertaEstrutura(pai);
}

Algoritmo Redistribuicao(pagina, irma){
	int metade = piso((pagina.qtd + irma.qtd)/2);
	Pagina pai = pagina.pai;
	int excedente = irma.qtd - metade;
	para(int i = irma.qtd-1; i >= irma.qtd-excedente-1; i--){
		se(i == excedente - 1){
			ajustaPosicaoEPonteiro(pagina, pai, pos);
			pai[pos_pai] = irma[irma.qtd-1];
			liberar(irma[irma.qtd-1]);
			irma.qtd--;
			break;
		}
		ajustaPosicaoEPonteiro(pagina, irma, i);
		liberar(irma[i]);
		irma.qtd--;
	}
	liberar(irma[i]);
	irma.qtd--;
	consertaEstrutura(irma);
}

Algoritmo ajustaPosicaoEPonteiro(pag1, pag2, pos){
	se(pag1 == null){
		retorne;
	}
	pag1[pag1.qtd] = pag2[pos];
	pag1.qtd++;
	para(int j = pag1.qtd-2; j >= 0; j--){
			se(pag1[j] > pag1[j+1]){
				pag1[j+1] = pag1[j];
				pag1[j+1].pont_dir = pag1[j].pont_dir;
				pag1[j] = pag2[pos];
				se(j == 0){
					pag1[j].pont_esq = pag2[pos].pont_esq;
				}
			}
			senao{
				pag1[j].pont_esq = pag1[j-1].pont_dir;
				break;
			}
		}
}

Algoritmo buscaPosNoPai(pagina, chave){
	para(int i = 0; i < pagina.pai[pagina.pai.qtd-1]; i++){
		se(chave < pagina.pai[i]){
			retorne i;
		}
	}
}