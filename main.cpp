#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#include "TAD.h"
#include "Bootstrap.h"

char menuPrincipal(void) //ok
{
	application();
	consolePrintf("topo", "rosa", 0, "TRABALHO CONTROLE DE ALUNOS");
    consolePrintf("subMenu", "verde", 0, "Selecione um item:");
    consolePrintf("esquerda", "branco", 0, "[A] - Alunos");
    consolePrintf("esquerda", "branco", 1, "[B] - Disciplinas");
    consolePrintf("esquerda", "branco", 2, "[C] - Relatorios");
    consolePrintf("esquerda", "vermelho", 3, "[S] - Salvar Mudanacas");
    consolePrintf("esquerda", "branco", 4, "[ESC] - Sair");
	return toupper(getch());
}

char menuAlunos(void) //ok
{
	application();
	consolePrintf("topo", "azul", 0, "ALUNOS");
    consolePrintf("subMenu", "verde", 0, "Selecione um item:");
    consolePrintf("esquerda", "branco", 0, "[A] Recuperar dados");
    consolePrintf("esquerda", "branco", 1, "(automatico ORDENADO)");
    consolePrintf("esquerda", "branco", 3, "[B] Inserir alunos");
    consolePrintf("esquerda", "branco", 4, "(manual ORDENADO)");
    consolePrintf("esquerda", "branco", 6, "[C] Excl. alu. e notas");
    consolePrintf("esquerda", "branco", 7, "[D] Pesquisar aluno");
    consolePrintf("esquerda", "branco", 8, "[E] Alterar dados alu.");
    consolePrintf("esquerda", "branco", 10, "[0] Voltar");
	return toupper(getch());
}

char menuDisciplina(void) //ok
{
	application();
	consolePrintf("topo", "azul", 0, "DISCIPLINA");
    consolePrintf("subMenu", "verde", 0, "Selecione um item:");
    consolePrintf("esquerda", "branco", 0, "[A] Inse. notas auto.");
    consolePrintf("esquerda", "branco", 1, "(NO FINAL)");
    consolePrintf("esquerda", "branco", 3, "[B] Inse. notas manual");
    consolePrintf("esquerda", "branco", 4, "(NO FINAL)");
    consolePrintf("esquerda", "branco", 6, "[C] Alterar notas");
    consolePrintf("esquerda", "branco", 7, "[D] Excluir notas");
    consolePrintf("esquerda", "branco", 9, "[0] Voltar");
	return toupper(getche());
}

char menuRelatorios(void)
{
	
	application();
	consolePrintf("topo", "azul", 0, "RELATORIOS");
    consolePrintf("subMenu", "verde", 0, "Selecione um item:");
    consolePrintf("esquerda", "branco", 0, "[A] Rel. alunos");
    consolePrintf("esquerda", "branco", 1, "(RECURSIVO)");
    consolePrintf("esquerda", "branco", 2, "[B] Rel. discplina");
    consolePrintf("esquerda", "branco", 3, "[C] Rel. reprova mat.");
    consolePrintf("esquerda", "branco", 4, "[D] Rel. alunos nas");
    consolePrintf("esquerda", "branco", 5, "suas disciplinas");
    consolePrintf("esquerda", "branco", 10, "[0] Voltar");

	return toupper(getch());
}

int main(void){
	
	application();
	char op;
	char nomeAluno[max];
	
	TpDisciplina *listaDisc = NULL;
	TpPont *listaAlunos = NULL;
	TpDescritor desc; //criando e inicializando o descritor a lista dinamica de alunos
	inicializarDesc(desc);
	
	//COLOCAR AS STRUCT E LISTAS
	
	do{
		op = menuPrincipal();
		system("cls");
		switch(op) //ALUNO OU DISCIPLINA
		{
			
			case 'A':
				op = menuAlunos();
				system("cls");
				switch(op) //ok
				{
					case 'A': 
						printf("### INSERIR ALUNOS AUTOMATICO E ORDENADO ###\n");
						recuperarDados(desc);
//						dadosFalsos(desc);
						
						//criarArqBinarioAlunos();
						break;
					
					case 'B':
						printf("### INSERIR ALUNOS MANUALMENTE E ORDENADO ###\n");
						
						listaAlunos = inserirAlunosOrd(listaAlunos,desc);
						
						break;
						
					case 'C':
						printf("### EXCLUIR ALUNOS E SUAS NOTAS ###\n");
						
						excluirAluno(desc);
						
						break;
						
					case 'D':
						printf("### PESQUISAR ALUNO ###\n");
						TpPont *aluno;
						TpDisciplina *aux;
						char nome[max];
						if(desc.qtde == 0)
							printf("\nNenhum dados cadastrado!\n");
						else
						{
							printf("\nNome do aluno que deseja buscas:");
							gets(nome);
							aluno=buscarAluno(nome,desc);
							if(aluno!=NULL)
							{
								printf("Nome: %s\n",aluno->dadosAluno.nome);
								printf("Curso: %s\n",aluno->dadosAluno.curso);
								printf("Nascimento: %d/%d/%d\n",aluno->dadosAluno.dataNasc.dd,aluno->dadosAluno.dataNasc.mm,aluno->dadosAluno.dataNasc.aaaa);
								printf("Endereco: %s - ",aluno->dadosAluno.endereco.rua);
								printf("Cidade: %s - ",aluno->dadosAluno.endereco.cidade);
								printf("UF: %s\n",aluno->dadosAluno.endereco.uf);
								if(aluno->disciplinas != NULL)
								{
									printf("### DISCIPLINAS ###\n");
									printf("\n* === * === * === * === *\n");
									aux=aluno->disciplinas;
										while( aux!=NULL)
									{
										
										printf("Diciplina: %s\n", aux->nomeDisc);
										printf("Nota 1: %.1f\n", aux->nota1);
										printf("Nota 2: %.1f\n", aux->nota2);
										printf("Frequencia: %d\n", aux->freq);
										aux=aux->prox;
										printf("\n* === * === * === * === *\n");	
									}
								}
								else
								{
									system("cls");
									printf("**  Aluno SEM notas!!  **");					
								}
							}
						}
						
						break;
						
					case 'E':
						printf("### ALTERAR DADOS DO ALUNO ###\n");
						char nom[max];
						TpPont *auxx;
						if(desc.qtde == 0)
							printf("\nNenhum dados cadastrado!\n");
						else
						{
							printf("\nNome do aluno que deseja alterar:");
							gets(nom);
							auxx=buscarAluno(nom,desc);
							if(auxx!=NULL)
								alterarDadoAluno(auxx);
						}
						
						break;
						
					default:
						printf("\nVoltando...\n");
						
						break;
				}
				break;
			case 'B':
				op = menuDisciplina();
				system("cls");
				switch(op) //ok
				{
					case 'A':
						printf("### INSERIR NOTAS AUTOMATICO ###\n");

						
						//criarArqBinarioDisciplinas();
						
						system("cls");

						break;
						
					case 'B':
						printf("### INSERIR NOTAS MANUALMENTE ###\n");
						char nomeAluno[max];
						TpPont *auxAlu;
						printf("\nNome do aluno:  ");
						fflush(stdin);
						gets(nomeAluno);
						auxAlu=buscarAluno(nomeAluno,desc);
						if(auxAlu != NULL)
						{
							inserirDiscFinal(auxAlu);
						}						
						
						break;
						
					case 'C':
						printf("### ALTERAR DADOS DAS NOTAS ###\n");
						TpPont *alunoAux;
						char nomeDeAux[max];
						if(desc.qtde == 0)
							printf("\nNenhum dados cadastrado!\n");
						else
						{
							printf("Nome do Aluno que deseja altera: ");
							gets(nomeDeAux);
							alunoAux=buscarAluno(nomeDeAux,desc);
							if(alunoAux!=NULL)
							{
								alterarNotas(alunoAux);
							}
						}
						
						break;
						
					case 'D':
						printf("### EXCLUIR NOTAS ###\n");
						
						listaAlunos = excluirDiscplina(desc);

						break;
						
					default:
						printf("\nVoltando...\n");
						
						break;
				}
				break;
			case 'C':
				op = menuRelatorios();
				system("cls");
				switch(op)
				{
					case 'A':
						printf("### RELATORIO DE ALUNO RECURSIVO ###\n");
						
						if(desc.inicio == 0)
							printf("\nNenhum dados cadastrado!\n");
						else
						{
							relatorioAlunosRecur(desc);
						
							printf("\nRelatorio de aluno recursivo finalizado!\n");
						}
						
						break;
						
					case 'B':
						printf("### RELATORIO DISCIPLINA ###\n");
						
						if(desc.inicio == 0)
							printf("\nNenhum dados cadastrado!\n");
						else
						{
							relatorioDisciplinas(desc);	
						}
						
						break;
						
					case 'C':
						printf("### RELATORIO REPROVAS NA MATERIA ###\n");
						
						if(desc.inicio == 0)
							printf("\nNenhum dados cadastrado!\n");
						else
						{
							relatorioReprovas(desc);
						}
						
						break;
						
					case 'D':
						printf("### RELATORIO DE ALUNOS COM SUAS RESPECTIVAS DISCIPLINAS ###\n");
						
						if(desc.inicio == 0)
							printf("\nNenhum dados cadastrado!\n");
						else
						{
							relatorioAlunosDiciplinas(desc);
						}
						
						break;
						
					default: 
						printf("\nVoltando...\n");
						
						break;
				}
				break;
			case 27:
				printf("\nPrograma encerrado!\n");
				
				break;
			case 'S':
				salvarDados(desc);
				break;
			default:
				printf("\nNao tem essa opcao!\n");
						
				break;
			
		}
		getch();
		system("cls");
	}while(op != 27);
	
	return 0;
}
