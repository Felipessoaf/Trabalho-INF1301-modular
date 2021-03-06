#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: JOGO	Jogo de xadrez
*
*  Arquivo gerado:              JOGO.h
*  Letras identificadoras:      JOGO
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: fpf - Felipe Pessoa de Freitas
*			mmq - Matheus de Mello Queiroz
*			pf  - Pedro Ferreira
*			
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     2       mmq   16/nov/2016 corre��o de bugs
*     1       fpf   21/out/2016 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa jogo de xadrez
*     Caso o Rei esteja em uma casa amea�ada e n�o possa se movimentar para qualquer outra casa,
*	  � emitida a mensagem �Cheque Mate�. Caso ele possa se movimentar
*	  para outra casa, � emitida a mensagem �Cheque�.
*	  A partida termina com o Cheque Mate ou a qualquer momento que um dos jogadores digite �FIM�.
*
*
***************************************************************************/

#include "TABULEIRO.H"

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Inteiro que indica se o jogo est� rodando. 0 = PARADO; diferente de 0 = RODANDO  */

int jogoRodando;

/* string com o nome do jogador das pe�as brancas */

char * jogadorB;

/* string com o nome do jogador das pe�as pretas */

char * jogadorP;

/* char que indica o jogador corrente */

char jogCorr;


/***********************************************************************
*
*  $TC Tipo de dados: JOGO Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do jogo
*
***********************************************************************/

typedef enum {

	JOGO_CondRetOK,
	/* Concluiu corretamente */
	
	JOGO_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento do jogo */

	JOGO_CondRetTabuleiroInexistente,
	/* Tabuleiro n�o existe */

	JOGO_CondRetArquivoPecasNaoExiste,
	/* Arquivo de pe�as do tabuleiro n�o existe */

	JOGO_CondRetArquivoPecasForaPadrao,
	/* Arquivo de pe�as do tabuleiro n�o est� no padr�o */

	JOGO_CondRetJogoParado,
	/* O jogo ja terminou ou nao come�ou */

	JOGO_CondRetJogoEmAndamento,
	/* O jogo ja esta rodando */

	JOGO_CondRetMovimentoInvalido,
	/* Movimento Inv�lido */

	JOGO_CondRetJogoNaoPodeIniciar,
	/* Jogo nao pode ser iniciado */

	JOGO_CondRetCheque,
	/* Ocorreu cheque */

	JOGO_CondRetChequeMate,
	/* Ocorreu cheque mate */

	JOGO_CondRetNaoExisteRei
	/* Peca rei nao existe */

} JOGO_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: JOGO  &Mostra tabuleiro
*
*  $ED Descri��o da fun��o
*     Mostra um tabuleiro de xadrez
*
*  $EP Par�metros
*	 pTabuleiro - referencia para o tabuleiro a ser exibido
*
*  $FV Valor retornado
*     JOGO_CondRetOK				   - Executou corretamente
*	  JOGO_CondRetTabuleiroInexistente - Tabuleiro n�o existe
*	  JOGO_CondRetJogoParado		   - Jogo esta parado
*
***********************************************************************/

	JOGO_tpCondRet JOGO_MostraTabuleiro(TAB_tppTabuleiro pTabuleiro);

/***********************************************************************
*
*  $FC Fun��o: JOGO  &Recebe jogada
*
*  $ED Descri��o da fun��o
*     Recebe a jogada de um jogador na partida
*
*  $EP Par�metros
*	 pTabuleiro - referencia para o tabuleiro do jogo
*	 origem		- coordenada origem da jogada
*	 destino	- coordenada destino da jogada
*
*  $FV Valor retornado
*     JOGO_CondRetOK				   - Executou corretamente
*	  JOGO_CondRetTabuleiroInexistente - Tabuleiro n�o existe
*	  JOGO_CondRetJogoParado		   - Jogo esta parado
*	  JOGO_CondRetMovimentoInvalido	   - Movimento Inv�lido
*
***********************************************************************/

	JOGO_tpCondRet JOGO_RecebeJogada(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino);

/***********************************************************************
*
*  $FC Fun��o: JOGO  &Recebe jogadores
*
*  $ED Descri��o da fun��o
*     Recebe os jogadores da partida
*
*  $EP Par�metros
*	 jog1		- nome do jogador1
*	 jog2		- nome do jogador2
*
*  $FV Valor retornado
*     JOGO_CondRetOK				   - Executou corretamente
*	  JOGO_CondRetJogoEmAndamento	   - Jogo em andamento
*	  JOGO_CondRetFaltouMemoria		   - Faltou memoria
*
***********************************************************************/

	JOGO_tpCondRet JOGO_RecebeJogadores(char * jog1, char * jog2);


/***********************************************************************
*
*  $FC Fun��o: JOGO  &Monta tabuleiro
*
*  $ED Descri��o da fun��o
*     Monta um tabuleiro de xadrez a partir de arquivo
*
*  $EP Par�metros
*	 pTabuleiro - referencia para o tabuleiro a ser montado
*
*  $FV Valor retornado
*     JOGO_CondRetOK					 - Executou corretamente
*	  JOGO_CondRetTabuleiroInexistente	 - Tabuleiro n�o existe
*	  JOGO_CondRetArquivoPecasNaoExiste	 - Arquivo de pecas inexistente
*	  JOGO_CondRetArquivoPecasForaPadrao - Arquivo de pecas fora do padrao
*	  JOGO_CondRetJogoEmAndamento		 - Jogo em andamento
*
***********************************************************************/

	JOGO_tpCondRet JOGO_MontaTabuleiro(TAB_tppTabuleiro pTabuleiro, char * nomeArq);

/***********************************************************************
*
*  $FC Fun��o: JOGO  &Inicia jogo
*
*  $ED Descri��o da fun��o
*     Inicia o jogo
*
*  $FV Valor retornado
*     JOGO_CondRetOK					 - Executou corretamente
*	  JOGO_CondRetJogoNaoPodeIniciar	 - Jogo nao pode ser iniciado
*	  JOGO_CondRetJogoEmAndamento		 - Jogo em andamento
*
***********************************************************************/

	JOGO_tpCondRet JOGO_IniciaJogo();
	
/***********************************************************************
*
*  $FC Fun��o: JOGO  &Cheque mate
*
*  $ED Descri��o da fun��o
*     Confere o jogador est� em cheque mate
*
*  $EP Par�metros
*	 pTabuleiro - referencia para o tabuleiro do jogo
*    jogador    - nome do jogador que se deseja obter a informa��o
*
*  $FV Valor retornado
*     JOGO_CondRetOK					 - N�o ocorreu cheque nem cheque mate
*     JOGO_CondRetChequeMate			 - Ocorreu cheque mate
*	  JOGO_CondRetCheque				 - Ocorreu cheque
*	  JOGO_CondRetNaoExisteRei			 - A pe�a rei n�o existe
*     JOGO_CondRetTabuleiroInexistente	 - Tabuleiro n�o existe
*	  JOGO_CondRetJogoParado			 - Jogo esta parado
*
***********************************************************************/

	JOGO_tpCondRet JOGO_ChequeMate( TAB_tppTabuleiro pTabuleiro, char* jogador );

#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: JOGO  Jogo de xadrez **********/

#else
#endif
