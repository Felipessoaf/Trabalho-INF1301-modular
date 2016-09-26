/***************************************************************************
*  $MCI M�dulo de implementa��o: TAB  Tabuleiro do Xadrez
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  -------------------------------------------Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW 
*
*  -------------------------------------------Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       avs   25/set/2016 in�cio da implementa��o das pe�as
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#include "LISTA.H"
#undef TABULEIRO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de pe�as
*
*
***********************************************************************/

	typedef struct tagPeca{
		
		char nome[4];
			/* Nome da pe�a */

		char cor;
			/* Cor da pe�a, podendo ser b (branco) ou p (preto) */

		LIS_tppLista pAndar;
				/* Ponteiro da Lista contendo os movimentos da pe�a de andar */

		LIS_tppLista pComer;
				/* Ponteiro da Lista contendo os movimentos da pe�a de comer */

	} tpPeca;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de movimentos da pecas
*
*
***********************************************************************/

	typedef struct tagMovimentoPeca{

		int coordenadas[4];
			/* Vetor de inteiros que representa as coordenadas Oeste = 0, 
			Norte = 1, Leste =2 e Sul = 3 */

		int max;
			/* Numero maximo de vezes que esse movimento pode ser repetido em uma jogada */

		int min;
			/* Numero minimo de vezes que esse movimento pode ser repetido em uma jogada */

	} tpMovimentoPeca;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

	static tpPeca LerArquivoPecas()