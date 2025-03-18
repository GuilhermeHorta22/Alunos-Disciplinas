// Estruturas de dados iniciais
#define max 50
struct TpData
{
	int dd,mm,aaaa;
};

struct TpEndereco
{
	char rua[max];
	char cidade[max];
	char uf[max];
};

struct TpAluno
{
	char nome[max], curso[max];
	TpData dataNasc;
	TpEndereco endereco;
};

struct TpDisciplina
{
	char nomeDisc[max];
	float nota1, nota2;
    int freq;
    TpDisciplina *prox; // já tranforma em um lista simples;
};

struct tpDadosDisc
{
	float nota1, nota2;
    int freq;
};

struct TpPont 
{
	TpAluno dadosAluno;
	TpPont *ant,*prox;
	TpDisciplina *disciplinas;
};

struct TpDescritor
{
	int qtde;
	TpPont *inicio, *fim; //descritor que vaia apontar para lista de alunos
};
// já faz a strcut de dados ser a propria estrutura de dados simplismente encadeada
// pode fazer assim tmb ou do outro jeito decide ai vericode

void inicializarDesc(TpDescritor &desc)
{
	desc.qtde = 0;
	desc.inicio = NULL;
	desc.fim = NULL;
}

TpPont *novoAluno(TpAluno nAluno)
{
	TpPont *novo = new TpPont;
	
	novo->dadosAluno = nAluno;
	novo->prox = novo->ant = NULL;
	novo->disciplinas = NULL;
	
	return novo;
}
// quando for colocar um novo aluno, devemos perguntar se já quer adicionar a disciplina
// passamos ela (disciplina) como NULL e se já for add, nos adicionamos se não já esta como NULL por padrão

TpDisciplina *novaDisciplina(char nome[max], float n1, float n2, int frequencia)
{
	TpDisciplina *nova= new TpDisciplina;
	
	strcpy(nova->nomeDisc,nome);
	nova->nota1 = n1;
	nova->nota2 = n2;
	nova->freq = frequencia;
	nova->prox = NULL;
	
	return nova;
}

//função teste que exibe os dados do arquivo binario
void exibeDadosArqAlunos(void)
{
	TpAluno aluno[max];
	int i=0;
	
	FILE *ptrAlunos = fopen("dadosAlunos.dat","rb");
	
	if(ptrAlunos == NULL)
		printf("\nErro na abertura do arquivo de alunos!\n");
	else
	{
		fread(&aluno[i],sizeof(TpAluno),1,ptrAlunos);
		while(!feof(ptrAlunos))
		{
			printf("\nNome: %s",aluno[i].nome);
			printf("\nCurso: %s",aluno[i].curso);
			printf("\nData nascimento: %d/%d/%d",aluno[i].dataNasc.dd, aluno[i].dataNasc.mm, aluno[i].dataNasc.aaaa);
			printf("\nEndereco: %s",aluno[i].endereco.rua);
			printf("\nCidade: %s",aluno[i].endereco.cidade);
			printf("\nEstado: %s\n",aluno[i].endereco.uf);
			
			fread(&aluno[i],sizeof(TpAluno),1,ptrAlunos);
			i++;
		}
		printf("\n\nRelatorio finalizado!!!\n");
		fclose(ptrAlunos);
		getch();
	}
}

void exibeDadosArqDisc(void)
{
	tpDadosDisc disc[max];
	int i=0;
	
	FILE *ptrDisc = fopen("dadosDisciplina.dat","rb");
	
	if(ptrDisc == NULL)
		printf("\nErro na abertura do arquivo de disciplina!\n");
	else
	{
		fread(&disc[i],sizeof(tpDadosDisc),1,ptrDisc);
		while(!feof(ptrDisc))
		{
			printf("\nNota 1: %.1f",disc[i].nota1);
			printf("\nNota 1: %.1f",disc[i].nota2);
			printf("\nFrenquencia 1: %d\n",disc[i].freq);
			
			fread(&disc[i],sizeof(tpDadosDisc),1,ptrDisc);
			i++;
		}
		printf("\n\nRelatorio finalizado!!!\n");
		fclose(ptrDisc);
		getch();
	}
}

TpPont *inserirDiscFinal(TpPont *aluno)
{
	TpDisciplina *nc, *aux;
	char nomeDisc[max], nomeAluno[max];
	float n1, n2;
	int freq, pos;
	char op;
	
	printf("\nDeseja inserir uma disciplina (S - sim | N - nao): ");
	op = toupper(getche());
	
	while(op == 'S')
	{
		printf("\nDigite o nome da disciplina: ");
		fflush(stdin);
		gets(nomeDisc);
		printf("\nDigite a nota 1: ");
		scanf("%f",&n1);
		printf("\nDigite a nota 2: ");
		scanf("%f",&n2);
		
		printf("\nDigite a frequencia: ");
		scanf("%d",&freq);
			
		nc = novaDisciplina(nomeDisc,n1,n2,freq);
		
		if(aluno->disciplinas == NULL) //SE ESTIVAR VAZIA
			aluno->disciplinas = nc;
		else //INSERINDO NO FINAL
		{
			aux = aluno->disciplinas;
			while(aux->prox != NULL)
			{
				aux = aux->prox;	
			}
			aux->prox = nc;
		}
		
		printf("\nDeseja inserir uma nota (S - sim | N - nao): ");
		op = toupper(getche());
	}
	
	return aluno;
}

//função que insere os alunos dentro da alocação dinamica
TpPont *inserirAlunosOrd(TpPont *listaAlunos, TpDescritor &desc)
{
	TpPont *nc, *atual;
	TpAluno aluno;
	int pos;
	char nomeAluno[max];
	printf("\nDigite o nome do aluno (0 - SAIR): ");
	fflush(stdin);
	gets(nomeAluno);
	while(nomeAluno[0] != 48)
	{
		//COLETANDO OS DADOS
		strcpy(aluno.nome,nomeAluno);
		
		printf("\nDigite o nome do curso: ");
		fflush(stdin);
		gets(aluno.curso);
		
		printf("\nDigite sua data de nascimento");
		printf("\nDia: ");
		scanf("%d",&aluno.dataNasc.dd);
		printf("\nMes: ");
		scanf("%d",&aluno.dataNasc.mm);
		printf("\nAno: ");
		scanf("%d",&aluno.dataNasc.aaaa);
		
		printf("\nDigite o seu endereco: ");
		fflush(stdin);
		gets(aluno.endereco.rua);
		printf("\nDigite o nome da sua cidade: ");
		fflush(stdin);
		gets(aluno.endereco.cidade);
		printf("\nDigite a UF do seu estado: ");
		fflush(stdin);
		gets(aluno.endereco.uf);
		
		//CRIANDO A NOVA CAIXA E COMEÇANDO A MANIPULÇÃO DA LISTA E DO DESCRITOR
		nc = novoAluno(aluno);
		inserirDiscFinal(nc);
		
		desc.qtde++;

		if(desc.inicio == NULL) //VAZIO
		{
			listaAlunos = nc;
			desc.inicio = nc;
			desc.fim = nc;
		}
		else
		{
			if(stricmp(aluno.nome,desc.inicio->dadosAluno.nome) <= 0) //INSERIR NO INICIO
			{
				nc->prox = desc.inicio;
				desc.inicio->ant = nc;
				listaAlunos = nc;
				desc.inicio = nc;
			}
			else
			{
				if(stricmp(aluno.nome,desc.fim->dadosAluno.nome) >= 0) //INSERIR NO FINAL
				{
					nc->ant = desc.fim;
					desc.fim->prox = nc;
					desc.fim = nc;
				}
				else //INSERIR NO MEIO
				{
					atual = desc.inicio;
					while(stricmp(aluno.nome,atual->dadosAluno.nome) > 0)
						atual = atual->prox;
						
					nc->prox = atual;
					nc->ant = atual->ant;
					atual->ant->prox = nc;
					atual->ant = nc;
				}
			}
		}
		printf("\nDigite o nome do aluno (0 - SAIR): ");
		fflush(stdin);
		gets(nomeAluno);
	}
	printf("\nInserir alunos ordenado finalizado!\n");
	
	return listaAlunos;
}

void relatorioAlunosRecur(TpDescritor desc)
{
	if(desc.inicio != NULL)
	{
		printf("\nNome: %s",desc.inicio->dadosAluno.nome);
		printf("\nCurso: %s",desc.inicio->dadosAluno.curso);
		printf("\nData nascimento: %d/%d/%d",desc.inicio->dadosAluno.dataNasc.dd, desc.inicio->dadosAluno.dataNasc.mm, desc.inicio->dadosAluno.dataNasc.aaaa);
		printf("\nEndereco: %s",desc.inicio->dadosAluno.endereco.rua);
		printf("\nCidade: %s",desc.inicio->dadosAluno.endereco.cidade);
		printf("\nEstado: %s\n",desc.inicio->dadosAluno.endereco.uf);
		
		desc.inicio = desc.inicio->prox;
		relatorioAlunosRecur(desc); //chamando a função de novo em uma nova posição
	}
}

TpPont *buscarAluno(char nome[max],TpDescritor desc)
{
	TpPont *aux=NULL;
	
	if(desc.qtde==0)
	{
		printf("Sem Alunos para busca!!");
		return NULL;
	}
	else
	{
		if(stricmp(desc.inicio->dadosAluno.nome,nome)==0)
		{
			return desc.inicio;
		}
		else
		{
			if(stricmp(desc.fim->dadosAluno.nome,nome)==0)
			{
				return desc.fim;
			}
			else
			{
				// vamos buscar no meio da lista
				aux=desc.inicio->prox;
				while(aux!=NULL && stricmp(aux->dadosAluno.nome,nome)!=0)
				{
					aux=aux->prox;
				}
				if(stricmp(aux->dadosAluno.nome,nome)==0)
				{
					return aux;
				}
				else
				{
					printf("Aluno nao localizado!!!");
					return NULL;
				}
				
			}
		}
	}
		
}

TpPont *alterarDadoAluno(TpPont *aluno)
{
	int op,oop=1;
	char nCurso[max];
	TpEndereco nEnde;
	TpData nData;
	printf("Aluno: %s\n",aluno->dadosAluno.nome);
	
	while(oop != 'N')
	{
		printf("Escolha qual alterar\n1 - Curso\n2 - Data de Nascimento\n3 - Endereco\n");
		scanf("%d",&op);
	
		if(op==1)
		{
			printf("Curso Atual: %s\n",aluno->dadosAluno.curso);
			printf("Novo Curso: ");
			fflush(stdin);
			gets(nCurso);
			strcpy(aluno->dadosAluno.curso,nCurso);
			
		}
		if(op==2)
		{
			printf("Nascimento: %d/%d/%d\n",aluno->dadosAluno.dataNasc.dd,aluno->dadosAluno.dataNasc.mm,aluno->dadosAluno.dataNasc.aaaa);
			printf("Nova data: \n");
			printf("\nDia: ");
			scanf("%d",&nData.dd);
			printf("\nMes: ");
			scanf("%d",&nData.mm);
			printf("\nAno: ");
			scanf("%d",&nData.aaaa);
			aluno->dadosAluno.dataNasc=nData;
		}
		if(op==3)
		{
			printf("Endereco Atual: ");
			printf("Rua: %s - ",aluno->dadosAluno.endereco.rua);
			printf("Cidade: %s - ",aluno->dadosAluno.endereco.cidade);
			printf("Estado - UF: %s\n",aluno->dadosAluno.endereco.uf);
			
			printf("Novo Endereco: \n");
			printf("\nRua: ");
			fflush(stdin);
			gets(nEnde.rua);
			printf("\nCidade: ");
			fflush(stdin);
			gets(nEnde.cidade);
			printf("\nEstado - UF: ");
			fflush(stdin);
			gets(nEnde.uf);
			
			aluno->dadosAluno.endereco=nEnde;
	
		}
		
		
		printf("Nova Altereacao: s - Sim | n - Nao\n");
		oop=toupper(getche());	
	}
	printf("\nAlterar dado do aluno finalizado!\n");
	
	return aluno;
}

TpPont *alterarNotas(TpPont *aluno)
{
	float nN1,nN2,nF;
	int op;
	char nomeDisc[max],oop,opD,nNome[max];
	TpDisciplina *aux,*auxE;
	auxE=aluno->disciplinas;
	while(auxE != NULL)
	{
		printf("Diciplina: %s\n",auxE->nomeDisc);
		auxE=auxE->prox;
	}
	while(opD!='N')
	{
		printf("\nNome da Disciplina que deseja mudar: ");
		gets(nomeDisc);
		aux=aluno->disciplinas;
		if(aux!=NULL)
		{
			// aqui eu busco a disciplina quando achar sai
			while(aux!=NULL && stricmp(aux->nomeDisc,nomeDisc)!=0)
			{
				aux=aux->prox;
			}
			// verifico se realmente é essa disciplina
			
			if(stricmp(aux->nomeDisc,nomeDisc)==0)
			{
				// loop para mudar mais de uma info da disciplina
				while(oop!='N')
				{
					printf("Escolha qual alterar\n1 - Nome\n2 - Nota 1\n3 - Nota 2\n4 - Frequencia\n");
					scanf("%d",&op);
					if(op==1)
					{
						printf("\nNome Atal: %s",aux->nomeDisc);
						fflush(stdin);
						printf("\nNovo Nome: ");
						gets(nNome);
						strcpy(aux->nomeDisc,nNome);
					}
					if(op==2)
					{
						printf("\nNota 1 Atul: %f",aux->nota1);
						printf("\nNovo Nota: ");
						scanf("%f",&aux->nota1);
					}
					if(op==3)
					{
						printf("\nNota 2 Atul: %f",aux->nota2);
						printf("\nNovo Nota: ");
						scanf("%f",&aux->nota2);
					}
					if(op==4)
					{
						printf("\nFrequencia atual: %d",aux->freq);
						printf("\nNova frenquencia: ");
						scanf("%d",&aux->freq);
					}
					
					printf("\nAlterar outro dados de %s: s - Sim | n - Nao\n",aux->nomeDisc);
					oop=toupper(getche());	
				}
			}
			else
			{
				printf("** Disciplina NAO localizado **");
			}
		}
		printf("\nAlterar OUTRA disciplina: s - Sim | n - Nao\n");
		opD=toupper(getche());	
	}
	
	return aluno;
}

TpPont *excluirDiscplina(TpDescritor desc) //OK
{
	TpPont *aux;
	TpDisciplina *auxDisc, *atualDisc, *antDisc,*auxE;
	char nomeDisc[max], nomeAluno[max], op;
	
	if(desc.qtde == 0)
		printf("\nNenhum dados cadastrado ainda!\n");
	else
	{
		printf("\nDe qual aluno voce deseja excluir a nota? ");
		fflush(stdin);
		gets(nomeAluno);
		
		aux = buscarAluno(nomeAluno,desc);
		if(aux != NULL) //ACHOU O ALUNO
		{
			auxE=aux->disciplinas;
			while(auxE != NULL)
			{	
				printf("Diciplina: %s\n",auxE->nomeDisc);
				auxE=auxE->prox;
			}
			printf("\nDe qual disciplina voce deseja excluir? ");
			fflush(stdin);
			gets(nomeDisc);
			
			atualDisc = aux->disciplinas;
			
			if(stricmp(nomeDisc,aux->disciplinas->nomeDisc) == 0) //SE CASO FOR A PRIMEIRA DISCIPLINA
			{
				printf("\nDADOS DA DISCIPLINA:");
				printf("\nNome: %s",aux->disciplinas->nomeDisc);
				printf("\nNota 1: %.1f",aux->disciplinas->nota1);
				printf("\nNota 2: %.1f",aux->disciplinas->nota2);
				printf("\nFrequencia: %d",aux->disciplinas->freq);
					
				printf("\nVoce autoriza a exclusao (S - sim | N - nao)? ");
				op = toupper(getche());
				if(op == 'S')
				{
					auxDisc = aux->disciplinas;
					aux->disciplinas = aux->disciplinas->prox;
					delete(auxDisc);
						
					printf("\nDisciplina excluida com sucesso!!!\n");
				}
				else
				if(op == 'N')
					printf("\nVoce nao autorizou essa exclusao!!!\n");
				else
					printf("\nEssa opcao nao existe!\n");
			}
			else
			{
				antDisc = atualDisc;
				atualDisc = atualDisc->prox;
				while(atualDisc->prox != NULL && stricmp(nomeDisc,atualDisc->nomeDisc) != 0)
				{
					antDisc = atualDisc;
					atualDisc = atualDisc->prox;
				}
					
					
				if(stricmp(nomeDisc,atualDisc->nomeDisc) == 0)
				{
					printf("\nDADOS DA DISCIPLINA:");
					printf("\nNome: %s",atualDisc->nomeDisc);
					printf("\nNota 1: %.1f",atualDisc->nota1);
					printf("\nNota 2: %.1f\n",atualDisc->nota2);
					printf("\nFrequencia: %d",atualDisc->freq);
					
					printf("\nVoce autoriza a exclusao (S - sim | N - nao)? ");
					op = toupper(getche());
					if(op == 'S')
					{
						auxDisc = atualDisc;
						antDisc->prox = atualDisc->prox;
						delete(auxDisc);
						
						printf("\nDisciplina excluida com sucesso!!!\n");
					}
					else
					if(op == 'N')
						printf("\nVoce nao autorizou essa exclusao!!!\n");
					else
						printf("\nEssa opcao nao existe!\n");
				}
				else
					printf("\nNao existe essa disciplina");
			}
		}
		printf("\nFinalizado a exclusao de disciplina!");
	}
	
	
	return aux;
}

void relatorioDisciplinas(TpDescritor desc) //OK
{
	char nomeDisc[max];
	int status = 0;
	TpPont *aux;
	TpDisciplina *auxDisc;
	aux = desc.inicio;

	if(aux == NULL)
		printf("\nNao tem alunos cadastrado!\n");
	else
	{	
		printf("\nDigite o nome da disciplina: ");
		fflush(stdin);
		gets(nomeDisc);
		
		printf("\nNome da disciplina: %s",nomeDisc);
		
		while(aux != NULL)
		{
			auxDisc = aux->disciplinas;
			while(auxDisc != NULL)
			{
				if(stricmp(nomeDisc,auxDisc->nomeDisc) == 0)
				{
					printf("\nNome do aluno: %s",aux->dadosAluno.nome);
					printf("\nNota 1: %.1f",auxDisc->nota1);
					printf("\nNota 2: %.1f",auxDisc->nota2);
					printf("\nFrequencia: %d\n",auxDisc->freq);
					status = 1; //indica que achou pelo menos uma vez a disciplina
				}
				auxDisc = auxDisc->prox;
			}
			aux = aux->prox;
		}
		if(status == 0)
			printf("\nA disciplina nao esta cadastrada!\n");
		printf("\nRelatorio de disciplinas finalizado!\n");
	}
}

void relatorioAlunosDiciplinas(TpDescritor desc) //OK
{
	TpPont *aux;
	TpDisciplina *auxDisc;
	aux = desc.inicio;
	
	
	if(desc.inicio == NULL)
		printf("\nNao tem alunos cadastrado!\n");
	else
	{
		while(aux != NULL)
		{
			printf("\n\n### DADOS DO ALUNO ###");
			printf("\nNome: %s",aux->dadosAluno.nome);
			printf("\nCurso: %s",aux->dadosAluno.curso);
			printf("\nData nascimento: %d/%d/%d",aux->dadosAluno.dataNasc.dd, aux->dadosAluno.dataNasc.mm, aux->dadosAluno.dataNasc.aaaa);
			printf("\nEndereco: %s",aux->dadosAluno.endereco.rua);
			printf("\nCidade: %s",aux->dadosAluno.endereco.cidade);
			printf("\nEstado: %s",aux->dadosAluno.endereco.uf);
			
			auxDisc = aux->disciplinas;
			while(auxDisc != NULL) //ELE NÃO QUER ENTRAR NESSE IF!!!!
			{
				printf("\n*** DADOS DA DISCIPLINA ***");
				printf("\nNome: %s",auxDisc->nomeDisc);
				printf("\nNota 1: %.1f",auxDisc->nota1);
				printf("\nNota 2: %.1f",auxDisc->nota2);
				printf("\nFrequencia: %d",auxDisc->freq);
				auxDisc = auxDisc->prox;
			}
			aux = aux->prox;
		}
		printf("\nRelatorio de disciplina por aluno finalizado!\n");
	}
}

void exibeAlunosEdisc(TpPont *aux) //função teste
{
	TpDisciplina *auxDisc;
	printf("\n\n### DADOS DO ALUNO ###");
	printf("\nNome: %s",aux->dadosAluno.nome);
	printf("\nCurso: %s",aux->dadosAluno.curso);
	printf("\nData nascimento: %d/%d/%d",aux->dadosAluno.dataNasc.dd, aux->dadosAluno.dataNasc.mm, aux->dadosAluno.dataNasc.aaaa);
	printf("\nEndereco: %s",aux->dadosAluno.endereco.rua);
	printf("\nCidade: %s",aux->dadosAluno.endereco.cidade);
	printf("\nEstado: %s",aux->dadosAluno.endereco.uf);
					
	auxDisc = aux->disciplinas;
	if(auxDisc != NULL) //se caso ele tiver disciplinas cadastrada
	{
		while(auxDisc != NULL) //mostrando todas as disciplinas do aluno
		{
			printf("\n*** DADOS DA DISCIPLINA ***");
			printf("\nNome: %s",auxDisc->nomeDisc);
			printf("\nNota 1: %.1f",auxDisc->nota1);
			printf("\nNota 2: %.1f",auxDisc->nota2);
			printf("\nFrequencia: %d",auxDisc->freq);
			auxDisc = auxDisc->prox;
		}
	}
	else
		printf("\nO aluno nao possui disciplinas cadastrada!\n");
}

void excluirAluno(TpDescritor &desc)
{
	TpPont *aux;
	TpDisciplina *auxDisc;
	char nomeAluno[max], op;
	
	if(desc.qtde == 0)
		printf("\nNenhum dados cadastrado ainda!\n");
	else
	{
		printf("\nDigite o nome do aluno para excluir: ");
		fflush(stdin);
		gets(nomeAluno);
		
		//verificação que possivelmente contorne o erro de excluir quando tem apenas 1 aluno
		if(desc.inicio == desc.fim)
		{
			aux = desc.inicio;
			auxDisc = aux->disciplinas;
			
			exibeAlunosEdisc(aux); //função que exibe o aluno e suas disciplinas (PARA SIMPLIFICAR)
					
			printf("\nVoce autoriza a exclusao (S - sim | N - nao)? ");
			op = toupper(getche());
			if(op == 'S')
			{
				inicializarDesc(desc);
				delete(aux);
				if(auxDisc != NULL) //esse aluno tem disciplinas cadastrada
					delete(auxDisc);
				
				printf("\nExclusao feita com sucesso!\n");
			}
			else
			if(op == 'N')
				printf("\nVoce nao autorizou a exclusao!\n");
			else
				printf("\nNao tem essa opcao!\n");
		}
		else
		{
			if(stricmp(nomeAluno,desc.inicio->dadosAluno.nome) == 0) //primeiro aluno
			{
				aux = desc.inicio;
				auxDisc = aux->disciplinas;
				
				exibeAlunosEdisc(aux); //função que exibe o aluno e suas disciplinas (PARA SIMPLIFICAR)
						
				printf("\nVoce autoriza a exclusao (S - sim | N - nao)? ");
				op = toupper(getche());
				if(op == 'S')
				{
					desc.inicio = desc.inicio->prox;
					desc.inicio->ant = NULL; //para não ficar com lixo no anterior
					delete(aux);
					if(auxDisc != NULL) //esse aluno tem disciplinas cadastrada
						delete(auxDisc);
						
					desc.qtde--;
					
					printf("\nExclusao feita com sucesso!\n");
				}
				else
				if(op == 'N')
					printf("\nVoce nao autorizou a exclusao!\n");
				else
					printf("\nNao tem essa opcao!\n");
			}
			else
			{
				if(stricmp(nomeAluno,desc.fim->dadosAluno.nome) == 0) //ultimo aluno
				{
					aux = desc.fim;
					auxDisc = aux->disciplinas;
					
					exibeAlunosEdisc(aux); //função que exibe o aluno e suas disciplinas (PARA SIMPLIFICAR)
							
					printf("\nVoce autoriza a exclusao (S - sim | N - nao)? ");
					op = toupper(getche());
					if(op == 'S')
					{
						desc.fim = desc.fim->ant;
						desc.fim->prox = NULL; //para não ficar com lixo no proximo
						delete(aux);
						if(auxDisc != NULL) //esse aluno tem disciplinas cadastrada
							delete(auxDisc);
						
						desc.qtde--;
						
						printf("\nExclusao feita com sucesso!\n");
					}
					else
					if(op == 'N')
						printf("\nVoce nao autorizou a exclusao!\n");
					else
						printf("\nNao tem essa opcao!\n");
				}
				else //no meio
				{
					aux = buscarAluno(nomeAluno,desc);
				
					if(aux != NULL) //ACHOU O ALUNO
					{
						exibeAlunosEdisc(aux); //função que exibe o aluno e suas disciplinas (PARA SIMPLIFICAR)
							
						printf("\nVoce autoriza a exclusao (S - sim | N - nao)? ");
						op = toupper(getche());
						if(op == 'S')
						{
							aux->prox->ant = aux->ant;
							aux->ant->prox = aux->prox;
							delete(aux);
							if(auxDisc != NULL) //esse aluno tem disciplinas cadastrada
								delete(auxDisc);
								
							desc.qtde--;
								
							printf("\nExclusao feita com sucesso!\n");
						}
						else
						if(op == 'N')
							printf("\nVoce nao autorizou a exclusao!\n");
						else
							printf("\nNao tem essa opcao!\n");
					}
				}
			}
		}
		
		printf("\nExclusao de alunos finalizada!\n");
	}
}

void relatorioReprovas(TpDescritor desc)
{
	TpPont *aux;
	TpDisciplina *auxDisc;
	float media;
	int status; //não tem reprovas
	
	aux = desc.inicio; //vai receber uma unica vez
	
	//W para toda vez que executar essa função recriar os arquivo com os novos alunos
	FILE *ptrTxt = fopen("reprovas.txt","w");
	
	if(ptrTxt == NULL)
		printf("\nErro na abertura do arquivo texto!\n");
	else
	{
		while(aux != NULL)
		{
			status=0;
			auxDisc = aux->disciplinas; //toda vez que for para um novo aluno tem que ver as disciplinas
			fprintf(ptrTxt,"\nNome do aluno: %s\n",aux->dadosAluno.nome);
			if(auxDisc == NULL)//o aluno não tem disciplinas
			{
				fprintf(ptrTxt,"O aluno nao tem nenhuma disciplina cadastrada!\n");
			}
			else //aluno tem disciplinas
			{
				while(auxDisc != NULL)
				{	
					media = (auxDisc->nota1 + auxDisc->nota2) / 2; //media do aluno
					if(media < 6)
					{
						fprintf(ptrTxt,"Materia reprovada: %s\n",auxDisc->nomeDisc);
						fprintf(ptrTxt,"Media: %.1f\n",media);
						status = 1; //indica que o aluno tem reprova
					}
					auxDisc = auxDisc->prox;
				}
				if(status == 0) //o aluno não tem nenhuma reprova
				{
					fprintf(ptrTxt,"Nao ha reprovas!\n");
				}
			}
			aux = aux->prox;
		}
		fclose(ptrTxt);
	}
	printf("\nRelatorio de reprovas no arquivo texto finalizado!\n");
}

void dadosFalsos(TpDescritor &desc)
{
    // Criando alunos fictícios
    TpAluno alunos[] = {
        {"Guilherme", "Sistemas de Informacao", {15, 9, 2003}, {"Rua Sao Pedro", "Presidente Bernardes", "SP"}},
        {"Andre", "Educacao Fisica", {21, 8, 2000}, {"Rua Sao Luis", "Presidente Epitacio", "SP"}},
        {"Ruan", "Ciencia da Computacao", {14, 12, 2004}, {"Rua Sao Joao", "Presidente Venceslau", "SP"}},
        {"Pedro", "Gastronomia", {3, 3, 2003}, {"Rua Sao Jose", "Alvares Machado", "SP"}},
        {"Andressa", "Fisioterapia", {12, 6, 2004}, {"Rua Sao Miguel", "Presidente Prudente", "SP"}}
    };

    // Criando disciplinas fictícias
    TpDisciplina *disciplinas[] = {
        novaDisciplina("Matematica", 8.0, 9.5, 20),
        novaDisciplina("Historia", 7.2, 6.0, 15),
        novaDisciplina("Biologia", 5.5, 7.3, 18),
        novaDisciplina("Fisica", 6.0, 8.0, 12),
        novaDisciplina("Quimica", 7.5, 6.5, 10)
    };

    // Inserindo alunos e associando disciplinas
    for(int i = 0; i < 5; i++)
	{
        TpPont *novo = novoAluno(alunos[i]);
        novo->disciplinas = disciplinas[i];

        // Inserindo na lista de forma ordenada
        if(desc.inicio == NULL)
		{
            desc.inicio = desc.fim = novo;
        }
		else
		{
            if(stricmp(novo->dadosAluno.nome, desc.inicio->dadosAluno.nome) <= 0)
			{
                // Inserir no início
                novo->prox = desc.inicio;
                desc.inicio->ant = novo;
                desc.inicio = novo;
            }
			else
			if(stricmp(novo->dadosAluno.nome, desc.fim->dadosAluno.nome) >= 0)
			{
                // Inserir no final
                novo->ant = desc.fim;
                desc.fim->prox = novo;
                desc.fim = novo;
            }
			else
			{
                // Inserir no meio
                TpPont *atual = desc.inicio;
                while (stricmp(novo->dadosAluno.nome, atual->dadosAluno.nome) > 0)
                    atual = atual->prox;

                novo->prox = atual;
                novo->ant = atual->ant;
                atual->ant->prox = novo;
                atual->ant = novo;
            }
        }
        desc.qtde++;
    }
	gotoxy(15, 7);
    printf("\nDados ficticios inseridos com sucesso!\n");
}

void recuperarDados(TpDescritor &desc)
{
    FILE *ptrArquivo = fopen("dadosAlunosEdisciplinas.dat", "rb");

    if(ptrArquivo == NULL)
	{
        printf("\nErro na abertura do arquivo binário!\n");
        return;
    }

    // Recuperando os dados do arquivo único
    TpAluno aluno;
    while(fread(&aluno, sizeof(TpAluno), 1, ptrArquivo))
	{
        // Cria um novo nó para o aluno
        TpPont *nAluno = novoAluno(aluno);
        desc.qtde++;

        // Insere o aluno na lista de forma ordenada
        if(desc.inicio == NULL)
		{
            desc.inicio = nAluno;
            desc.fim = nAluno;
        }
		else
		{
            TpPont *atual = desc.inicio;
            while(atual != NULL && stricmp(aluno.nome, atual->dadosAluno.nome) > 0)
			{
                atual = atual->prox;
            }

            if(atual == NULL)
			{
                // Inserir no final
                nAluno->ant = desc.fim;
                desc.fim->prox = nAluno;
                desc.fim = nAluno;
            }
			else
			{
                // Inserir no meio ou início
                nAluno->prox = atual;
                nAluno->ant = atual->ant;
                if (atual->ant != NULL)
				{
                    atual->ant->prox = nAluno;
                }
				else
				{
                    desc.inicio = nAluno;
                }
                atual->ant = nAluno;
            }
        }

        // Recupera as disciplinas associadas ao aluno
        int qtdDisciplinas = 0;
        fread(&qtdDisciplinas, sizeof(int), 1, ptrArquivo); // Lê a quantidade de disciplinas do aluno

        for(int i = 0; i < qtdDisciplinas; i++)
		{
            TpDisciplina disciplina;
            fread(&disciplina, sizeof(TpDisciplina), 1, ptrArquivo);

            // Cria e insere a disciplina na lista do aluno
            TpDisciplina *novaDisc = novaDisciplina(disciplina.nomeDisc, disciplina.nota1, disciplina.nota2, disciplina.freq);
            if(nAluno->disciplinas == NULL)
			{
                nAluno->disciplinas = novaDisc;
            }
			else
			{
                TpDisciplina *aux = nAluno->disciplinas;
                while(aux->prox != NULL)
				{
                    aux = aux->prox;
                }
                aux->prox = novaDisc;
            }
        }
    }

    fclose(ptrArquivo);
    printf("\nDados recuperados com sucesso!\n");
}
void salvarDados(TpDescritor &desc)
{
    FILE *ptrArquivo = fopen("dadosAlunosEdisciplinas.dat", "wb");

    if(ptrArquivo == NULL)
	{
        printf("\nErro ao abrir o arquivo binário para salvar os dados!\n");
        return;
    }

    TpPont *atual = desc.inicio;

    // Percorre a lista de alunos
    while(atual != NULL)
	{
        // Escreve os dados do aluno no arquivo
        fwrite(&atual->dadosAluno, sizeof(TpAluno), 1, ptrArquivo);

        // Calcula e escreve a quantidade de disciplinas associadas
        int qtdDisciplinas = 0;
        TpDisciplina *disciplinaAtual = atual->disciplinas;
        while(disciplinaAtual != NULL)
		{
            qtdDisciplinas++;
            disciplinaAtual = disciplinaAtual->prox;
        }
        fwrite(&qtdDisciplinas, sizeof(int), 1, ptrArquivo);

        // Escreve as disciplinas associadas
        disciplinaAtual = atual->disciplinas;
        while(disciplinaAtual != NULL)
		{
            fwrite(disciplinaAtual, sizeof(TpDisciplina), 1, ptrArquivo);
            disciplinaAtual = disciplinaAtual->prox;
        }

        // Avança para o próximo aluno
        atual = atual->prox;
    }

    fclose(ptrArquivo);
    printf("\nDados salvos com sucesso no arquivo binario unico!\n");
}

////função que recupera o arquivo binario com os dados dos alunos
//void recuperarDados(TpDescritor &desc)
//{
//    FILE *ptrAlunos = fopen("dadosAlunos.dat", "rb");
//    FILE *ptrDisciplinas = fopen("dadosDisciplina.dat", "rb");
//    
		// se não é null vai fazer algo
//    if (ptrAlunos == NULL || ptrDisciplinas == NULL) {
//        printf("\nErro na abertura dos arquivos binários!\n");
//    }

//    // Recuperando os dados dos alunos
//    TpAluno aluno;
//    while (fread(&aluno, sizeof(TpAluno), 1, ptrAlunos)) {
//        TpPont *nAluno = novoAluno(aluno);  // Cria um novo nó para o aluno
//        desc.qtde++;
//        // Insere o aluno na lista de forma ordenada
//        if (desc.inicio == NULL) {
//            desc.inicio = nAluno;
//            desc.fim = nAluno;
//        } else {
//            TpPont *atual = desc.inicio;
//            while (atual != NULL && stricmp(aluno.nome, atual->dadosAluno.nome) > 0) {
//                atual = atual->prox;
//            }

//            if (atual == NULL) {
//                // Inserir no final
//                nAluno->ant = desc.fim;
//                desc.fim->prox = nAluno;
//                desc.fim = nAluno;
//            } else {
//                // Inserir no meio ou início
//                nAluno->prox = atual;
//                nAluno->ant = atual->ant;
//                if (atual->ant != NULL) {
//                    atual->ant->prox = nAluno;
//                } else {
//                    desc.inicio = nAluno;
//                }
//                atual->ant = nAluno;
//            }
//        }

//        // Agora recuperamos as disciplinas associadas ao aluno
//        TpDisciplina disciplina;
//        while (fread(&disciplina, sizeof(TpDisciplina), 1, ptrDisciplinas)) {
//            TpDisciplina *novaDisc = novaDisciplina(disciplina.nomeDisc, disciplina.nota1, disciplina.nota2, disciplina.freq);
//			
//			if (nAluno->disciplinas == NULL) {
//                nAluno->disciplinas = novaDisc;
//            } else {
//                TpDisciplina *aux = nAluno->disciplinas;
//                while (aux->prox != NULL) {
//                    aux = aux->prox;
//                }
//                aux->prox = novaDisc;
//            }
//        }
//    }

//    fclose(ptrAlunos);
//    fclose(ptrDisciplinas);
//    printf("\nDados recuperados com sucesso!\n");
//}
////função salva os dados no binario
//void salvarDados(TpDescritor &desc)
//{
//    FILE *ptrAlunos = fopen("dadosAlunos.dat", "wb");
//    FILE *ptrDisciplinas = fopen("dadosDisciplina.dat", "wb");

//    if (ptrAlunos == NULL || ptrDisciplinas == NULL)
//    {
//        printf("\nErro ao abrir os arquivos binários para salvar os dados!\n");
//        return;
//    }

//    TpPont *atual = desc.inicio;

//    // Percorre a lista de alunos
//    while (atual != NULL)
//    {
//        // Escreve os dados do aluno no arquivo binário de alunos
//        fwrite(&atual->dadosAluno, sizeof(TpAluno), 1, ptrAlunos);

//        // Percorre as disciplinas do aluno e escreve no arquivo binário de disciplinas
//        TpDisciplina *disciplinaAtual = atual->disciplinas;
//        while (disciplinaAtual != NULL)
//        {
//            tpDadosDisc dadosDisciplina;
//            dadosDisciplina.nota1 = disciplinaAtual->nota1;
//            dadosDisciplina.nota2 = disciplinaAtual->nota2;
//            dadosDisciplina.freq = disciplinaAtual->freq;

//            fwrite(&dadosDisciplina, sizeof(tpDadosDisc), 1, ptrDisciplinas);
//            disciplinaAtual = disciplinaAtual->prox;
//        }

//        // Avança para o próximo aluno
//        atual = atual->prox;
//    }

//    fclose(ptrAlunos);
//    fclose(ptrDisciplinas);

//    printf("\nDados salvos com sucesso nos arquivos binários!\n");
//}
