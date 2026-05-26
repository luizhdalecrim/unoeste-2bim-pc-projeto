/*
 * Sistema de Gerenciamento de Academia
 * Projeto Final - Pensamento Computacional
 *
 * Funcionalidades principais:
 * [*] Cadastro (instrutor, aluno e modalidade);
 * [*] Exclusão (instrutor, aluno e modalidade);
 * [*] Lançamento de avaliação física;
 * [*] Relatórios (instrutores, alunos, modalidades e avaliações físicas).
 *
 * Features adicionais:
 * [*] CODIFICACAO UTF-8 (PODE TER PROBLEMAS AO EXIBIR O CODIGO FONTE, MAS E
 * EXIBIDO CORRETAMENTE NA EXECUCAO DO PROGRAMA);
 * [*] Suporte a cores para melhor feedback ao usuário;
 * [*] Terminal e menus limpos;
 *
 * Autor: Luiz Henrique Dainez Alecrim
 */

#include <locale.h>
#include <stdio.h>
#include <string.h>

// BIBLIOTECA NECESSÁRIA PARA DEFINIR O TERMINAL PARA UTF-8
#include <stdlib.h>

// CORES
#define COR_VERMELHO "\033[1;31m"
#define COR_AMARELO "\033[1;33m"
#define COR_VERDE "\033[1;32m"
#define COR_AZUL "\033[1;34m"
#define COR_NORMAL "\033[0m"

#define TF_INST 10
#define TF_MOD 10
#define TF_ALUNO 20
#define TF_AVAL 20

int main() {
  // Configurar terminal para UTF-8
  system("chcp 65001 > nul");

  // Aceitar caracteres do padrão UTF-8 brasileiro
  setlocale(LC_ALL, "pt_BR.UTF-8");

  // Limpar terminal
  printf("\e[1;1H\e[2J");

  // Instrutores
  int vCodInst[TF_INST];
  char vInstrutor[TF_INST][50];
  int TLI = 0;

  // Modalidades
  int vCodMod[TF_MOD];
  char vModalidade[TF_MOD][50];
  float vValorAula[TF_MOD];
  int TLM = 0;

  // Alunos
  char vCPFAluno[TF_ALUNO][15];
  char vNomeAluno[TF_ALUNO][50];
  int vDiaVenc[TF_ALUNO];
  int vCodModAluno[TF_MOD];
  float vValor[TF_ALUNO];
  int TLA = 0;

  // Avaliações físicas
  int vLInst[TF_AVAL];
  char vLAluno[TF_AVAL][15];
  char vLDataAval[TF_AVAL][11];
  int TL = 0;

  // Controle
  int opcMenu, opcSub; // Opções menus
  int i, j, pos; // Índices de uso geral

  // Validação
  int encontrado, valido;
  int codInst, codMod;
  char cpf[15], nome[50], data[11], modalidade[50];
  float valorAula, totalMensalidade;
  int diaVenc, diaHoje;
  char continuar;

  // LOOP PRINCIPAL (MENU)
  opcMenu = 0;
  while (opcMenu != 5) {
    printf("\n\n"
           "---[Sistema de Gestão da Academia]---\n"
           "O que deseja fazer?\n"
           "  [1] Cadastro\n"
           "  [2] Exclusão\n"
           "  [3] Lancamento de Avaliação Física\n"
           "  [4] Relatórios\n"
           "  [5] Finalizar\n"
           "  Opção -> ");
    scanf("%d", &opcMenu);

    // OPÇÃO 1 - SUBMENU CADASTRO
    if (opcMenu == 1) {
      opcSub = 0;
      while (opcSub != 4) {
        printf("\n\n"
               "===[CADASTRO]===\n"
               "  [1] Instrutor\n"
               "  [2] Aluno\n"
               "  [3] Modalidade\n"
               "  [4] Retornar\n"
               "  Opção -> ");
        scanf(" %d", &opcSub);

        // Limpar buffer
        setbuf(stdin, NULL);

        // CADASTRO - INSTRUTOR
        if (opcSub == 1) {

          // Evitar overflow
          if (TLI >= TF_INST) {
            printf(COR_VERMELHO "\n"
                                "[ERRO]: Limite de instrutores atingido. "
                                "Exclua para liberar espaço.\n" COR_NORMAL);
          } else {
            printf("Código do instrutor -> ");

            // Retorna 0 se tudo correr bem; retorna 1 se tiver char onde era
            // pra ser int
            valido = scanf(" %d", &codInst);

            setbuf(stdin, NULL);

            // Validar código
            if (codInst <= 0 || !valido) {
              printf(COR_VERMELHO
                     "[ERRO]: O código inserido é inválido. Insira "
                     "um número inteiro maior que 0.\n" COR_NORMAL);
            } else {

              // Evitar clones
              encontrado = 0;
              for (i = 0; i < TLI; i++) {
                if (vCodInst[i] == codInst) {
                  encontrado = 1;
                  i = TLI; // Sair do loop
                }
              }
              if (encontrado) {
                printf(COR_VERMELHO "[ERRO]: Instrutor com código \"%d\" já "
                                    "cadastrado.\n" COR_NORMAL,
                       codInst);
              } else {
                if (codInst > 0) {
                  printf("Nome do instrutor -> ");

                  // Lê string sem \n
                  scanf(" %[^\n]", nome);

                  setbuf(stdin, NULL);
                  vCodInst[TLI] = codInst;
                  strcpy(vInstrutor[TLI], nome);
                  TLI++;
                  printf(COR_VERDE "[OK]: Instrutor \"%s\" cadastrado com "
                                   "sucesso!\n" COR_NORMAL,
                         nome);
                }
              }
            }
          }

          // CADASTRO - ALUNO
        } else if (opcSub == 2) {
          continuar = 's';

          // Definir cadastro como válido, até que se prove o contrário
          valido = 1;

          if (TLA >= TF_ALUNO) {
            printf(COR_VERMELHO "[ERRO]: Limite de alunos atingido. Exclua "
                                "para liberar espaço.\n" COR_NORMAL);
          } else {
            printf("CPF do aluno (formato 000.000.000-00) -> ");
            valido = scanf(" %[^\n]", cpf);
            setbuf(stdin, NULL);
            encontrado = 0;
            for (i = 0; i < TLA; i++) {
              if (strcmp(vCPFAluno[i], cpf) == 0) {
                encontrado = 1;
                i = TLA;
              }
            }
            if (encontrado) {
              printf(COR_VERMELHO
                     "[ERRO]: Aluno com CPF %s já cadastrado.\n" COR_NORMAL,
                     cpf);
            } else {
              printf("Nome do aluno -> ");
              scanf(" %[^\n]", nome);
              setbuf(stdin, NULL);
              printf("Dia de vencimento da mensalidade (1-31) -> ");
              scanf(" %d", &diaVenc);
              setbuf(stdin, NULL);

              // Cálculo do valor da mensalidade usando modalidades
              totalMensalidade = 0.0;

              if (TLM == 0) {
                printf(COR_AMARELO
                       "[AVISO]: Nenhuma modalidade cadastrada. Valor da "
                       "mensalidade será R$ 0,00.\n" COR_NORMAL
                       "Deseja continuar? [s/N] -> ");
                valido = scanf(" %c", &continuar);
                if (!valido ||
                    (continuar != 'n' && continuar != 'N' && continuar != 's' &&
                     continuar != 'S') ||
                    (continuar == 'n' || continuar == 'N')) {
                  valido = 0; // Cadastro se torna inválido
                  continuar = 'n';
                }
                setbuf(stdin, NULL);
              } else {

                // Será usado para índice (vCodModAluno[j])
                j = 0;

                // O vetor de modalidades do aluno cadastrado deve estar zerado
                for (i = 0; i < TLM; i++)
                  vCodModAluno[i] = 0;

                while (continuar == 's' || continuar == 'S') {
                  printf("\n"
                         "-- Selecione as modalidades do aluno --\n"
                         "Modalidades disponíveis:\n\n");
                  for (i = 0; i < TLM; i++) {
                    printf("Código: %d | Nome: %s | Mensalidade: R$ %.2f\n",
                           vCodMod[i], vModalidade[i], vValorAula[i]);
                  }
                  printf("\n"
                         "Digite o código da modalidade desejada -> ");
                  scanf("%d", &codMod);
                  setbuf(stdin, NULL);

                  // Evitar adição de modalidade duplicada
                  encontrado = 0;
                  for (i = 0; i < TLM; i++) {
                    if (vCodModAluno[i] == codMod) {
                      codMod = -1;
                      printf(COR_VERMELHO
                             "[ERRO]: Modalidade já adicionada para este "
                             "aluno.\n" COR_NORMAL);
                      i = TLM;
                    }
                    if (vCodMod[i] == codMod) {

                      // Salvar código da modalidade
                      vCodModAluno[j] = codMod;
                      j++;
                      totalMensalidade += vValorAula[i];
                      printf(COR_VERDE
                             "[OK]: Modalidade \"%s\" adicionada. Subtotal: R$ "
                             "%.2f\n" COR_NORMAL,
                             vModalidade[i], totalMensalidade);
                      encontrado = 1;
                      i = TLM;
                    }
                  }
                  if (!encontrado && codMod > -1) {
                    printf(COR_VERMELHO "[ERRO]: Modalidade não encontrada. "
                                        "Tente novamente.\n" COR_NORMAL);
                  }
                  printf("Adicionar outra modalidade? [S/n] -> ");
                  scanf(" %c", &continuar);
                  setbuf(stdin, NULL);
                }
              }
              if (!valido && (continuar != 's' && continuar != 'S'))
                printf(COR_AZUL "[AÇÃO]: Cadastro cancelado.\n" COR_NORMAL);
              else {
                strcpy(vCPFAluno[TLA], cpf);
                strcpy(vNomeAluno[TLA], nome);
                vDiaVenc[TLA] = diaVenc;
                vValor[TLA] = totalMensalidade;
                TLA++;
                printf(COR_VERDE
                       "[OK]: Aluno \"%s\" cadastrado. Mensalidade: R$ %.2f | "
                       "Vencimento: dia %d\n" COR_NORMAL,
                       nome, totalMensalidade, diaVenc);
              }
            }
          }

          // CADASTRO - MODALIDADE
        } else if (opcSub == 3) {
          if (TLM >= TF_MOD) {
            printf(COR_VERMELHO "[ERRO]: Limite de modalidades atingido. "
                                "Exclua para liberar espaço.\n" COR_NORMAL);
          } else {
            printf("Código da modalidade -> ");
            scanf("%d", &codMod);
            setbuf(stdin, NULL);
            encontrado = 0;
            for (i = 0; i < TLM; i++) {
              if (vCodMod[i] == codMod) {
                encontrado = 1;
                i = TLM;
              }
            }
            if (encontrado)
              printf(COR_VERMELHO "[ERRO]: Modalidade com código %d já "
                                  "cadastrada.\n" COR_NORMAL,
                     codMod);
            else {
              printf("Descrição da modalidade -> ");
              scanf(" %[^\n]", modalidade);
              setbuf(stdin, NULL);
              printf("Valor da aula (R$ 0,00) -> R$ ");
              scanf("%f", &valorAula);
              setbuf(stdin, NULL);
              vCodMod[TLM] = codMod;
              strcpy(vModalidade[TLM], modalidade);
              vValorAula[TLM] = valorAula;
              TLM++;
              printf(COR_VERDE "[OK]: Modalidade \"%s\" cadastrada com "
                               "sucesso.\n" COR_NORMAL,
                     modalidade);
            }
          }
        } else if (opcSub == 4)
          printf(COR_AZUL "[AÇÃO]: Retornar." COR_NORMAL);
        else if (opcSub != 4)
          printf(COR_VERMELHO
                 "[ERRO]: Opção inválida. Tente novamente.\n" COR_NORMAL);

      } // fim while submenu cadastro

      // OPCAO 2 - SUBMENU DE EXCLUSÃO
    } else if (opcMenu == 2) {
      opcSub = 0;
      while (opcSub != 4) {
        printf("\n\n"
               "===[EXCLUSÃO]===\n"
               "  [1] Instrutor\n"
               "  [2] Aluno\n"
               "  [3] Modalidade\n"
               "  [4] Retornar\n"
               "  Opção -> ");
        scanf("%d", &opcSub);
        setbuf(stdin, NULL);

        // EXCLUSÃO INSTRUTOR
        if (opcSub == 1) {
          printf("Insira o Código do Instrutor que deseja Excluir -> ");
          scanf("%d", &codInst);
          setbuf(stdin, NULL);
          pos = -1;
          for (i = 0; i < TLI; i++) {
            if (vCodInst[i] == codInst) {
              pos = i;
              i = TLI;
            }
          }
          if (pos == -1)
            printf(COR_VERMELHO "[ERRO]: Instrutor com código %d não foi "
                                "encontrado.\n" COR_NORMAL,
                   codInst);
          else {
            continuar = 'n';
            printf(COR_VERDE "[OK]: Instrutor encontrado.\n" COR_NORMAL);
            printf(COR_AMARELO "[AVISO]: Tem certeza que deseja prosseguir? "
                               "[s/N] -> " COR_NORMAL);
            scanf(" %c", &continuar);
            setbuf(stdin, NULL);
            if (continuar == 's' || continuar == 'S') {

              // Ajustar vetor
              for (i = pos; i < (TLI - 1); i++) {
                vCodInst[i] = vCodInst[i + 1];
                strcpy(vInstrutor[i], vInstrutor[i + 1]);
              }
              TLI--;
              printf(COR_VERDE
                     "[OK]: Instrutor removido com sucesso.\n" COR_NORMAL);
            } else
              printf(COR_AZUL "[AÇÃO]: Exclusão cancelada." COR_NORMAL);
          }

          /*
           *  EXCLUSÃO DE ALUNO
           *  (SOMENTE SE: dia atual > dia vencimento)
           */
        } else if (opcSub == 2) {
          printf("Informe o CPF do Aluno que deseja Excluir -> ");
          scanf(" %[^\n]", cpf);
          setbuf(stdin, NULL);
          pos = -1;
          for (i = 0; i < TLA; i++) {
            if (strcmp(vCPFAluno[i], cpf) == 0) {
              pos = i;
              i = TLA;
            }
          }
          if (pos == -1)
            printf(COR_VERMELHO
                   "[ERRO]: Aluno com CPF %s não encontrado.\n" COR_NORMAL,
                   cpf);
          else {
            printf("Informe o dia atual do mês (1-31) -> ");
            scanf("%d", &diaHoje);
            setbuf(stdin, NULL);
            if (diaHoje <= vDiaVenc[pos])
              printf(COR_AMARELO
                     "[AVISO]: O aluno \"%s\" não pôde ser excluido. "
                     "O dia atual (%d) não é superior ao dia do vencimento "
                     "(%d).\n" COR_NORMAL,
                     vNomeAluno[pos], diaHoje, vDiaVenc[pos]);
            else {
              continuar = 'n';
              printf(COR_AMARELO "[AVISO]: Tem certeza que deseja prosseguir? "
                                 "[s/N] -> " COR_NORMAL);
              scanf(" %c", &continuar);
              setbuf(stdin, NULL);
              if (continuar == 's' || continuar == 'S') {
                printf(COR_AZUL
                       "[AÇÃO]: Excluindo aluno \"%s\"...\n" COR_NORMAL,
                       vNomeAluno[pos]);

                // Ajustar vetor aluno
                for (i = pos; i < TLA - 1; i++) {
                  strcpy(vCPFAluno[i], vCPFAluno[i + 1]);
                  strcpy(vNomeAluno[i], vNomeAluno[i + 1]);
                  vDiaVenc[i] = vDiaVenc[i + 1];
                  vValor[i] = vValor[i + 1];
                }
                TLA--;
                printf(COR_VERDE
                       "[OK]: Aluno removido com sucesso.\n" COR_NORMAL);
              } else
                printf(COR_AZUL "[AÇÃO]: Exclusão cancelada." COR_NORMAL);
            }
          }

          // EXCLUSÃO DE MODALIDADE
        } else if (opcSub == 3) {
          printf("Informe o Código da Modalidade a Excluir -> ");
          scanf("%d", &codMod);
          setbuf(stdin, NULL);
          pos = -1;
          for (i = 0; i < TLM; i++) {
            if (vCodMod[i] == codMod) {
              pos = i;
              i = TLM;
            }
          }
          if (pos == -1)
            printf(COR_AMARELO "[AVISO]: Modalidade com código %d não "
                               "encontrada.\n" COR_NORMAL,
                   codMod);
          else {
            continuar = 'n';
            printf(COR_AMARELO "[AVISO]: Tem certeza que deseja prosseguir? "
                               "[s/N] -> " COR_NORMAL);
            scanf(" %c", &continuar);
            setbuf(stdin, NULL);
            if (continuar == 's' || continuar == 'S') {
              for (i = pos; i < TLM - 1; i++) {
                vCodMod[i] = vCodMod[i + 1];
                strcpy(vModalidade[i], vModalidade[i + 1]);
                vValorAula[i] = vValorAula[i + 1];
              }
              TLM--;
              printf(COR_VERDE
                     "[OK]: Modalidade removida com sucesso.\n" COR_NORMAL);
            } else
              printf(COR_AZUL "[AÇÃO]: Exclusão cancelada." COR_NORMAL);
          }
        } else if (opcSub == 4)
          printf(COR_AZUL "[AÇÃO]: Retornar.\n" COR_NORMAL);
        else if (opcSub != 4)
          printf(COR_AMARELO "[AVISO]: Opção inválida.\n" COR_NORMAL);

      } // fim while submenu exclusao

      // OPCAO 3 - LANÇAMENTO DE AVALIAÇÃO FÍSICA
    } else if (opcMenu == 3) {
      if (TL >= TF_AVAL)
        printf(COR_VERMELHO
               "[ERRO]: Limite de avaliações atingido.\n" COR_NORMAL);
      else {
        printf("\n\n"
               "===[LANÇAMENTO DE AVALIAÇÃO FÍSICA]===\n");
        printf("Código do instrutor -> ");
        scanf("%d", &codInst);
        setbuf(stdin, NULL);
        pos = -1;
        for (i = 0; i < TLI; i++) {
          if (vCodInst[i] == codInst) {
            pos = i;
            i = TLI;
          }
        }
        if (pos == -1)
          printf(COR_VERMELHO
                 "[ERRO]: Instrutor com código %d não encontrado. Lançamento "
                 "cancelado.\n" COR_NORMAL,
                 codInst);
        else {
          printf(COR_AZUL "[AÇÃO]: Instrutor encontrado.\n" COR_NORMAL);
          printf("CPF do aluno -> ");
          scanf(" %[^\n]", cpf);
          setbuf(stdin, NULL);
          encontrado = 0;
          for (i = 0; i < TLA; i++) {
            if (strcmp(vCPFAluno[i], cpf) == 0) {
              encontrado = 1;
              i = TLA;
            }
          }
          if (!encontrado) {
            printf(COR_VERMELHO
                   "[ERRO]: Aluno com CPF %s não encontrado. Lançamento "
                   "cancelado.\n" COR_NORMAL,
                   cpf);
          } else {
            printf(COR_AZUL "[AÇÃO]: Aluno encontrado.\n" COR_NORMAL);
            printf("Data da avaliação (DD/MM/AAAA): ");
            scanf(" %[^\n]", data);
            setbuf(stdin, NULL);
            vLInst[TL] = codInst;
            strcpy(vLAluno[TL], cpf);
            strcpy(vLDataAval[TL], data);
            TL++;
            printf(COR_VERDE
                   "[OK]: Avaliação registrada com sucesso.\n" COR_NORMAL);
          }
        }
      }

      // OPÇÃO 4 - SUBMENU DE RELATÓRIOS
    } else if (opcMenu == 4) {
      opcSub = 0;
      while (opcSub != 5) {
        printf("\n\n"
               "===[RELATÓRIOS]===\n"
               "  [1] Lista de instrutores\n"
               "  [2] Lista de alunos\n"
               "  [3] Lista de modalidades\n"
               "  [4] Histórico de avaliações físicas\n"
               "  [5] Retornar\n"
               "  Opção -> ");
        scanf("%d", &opcSub);
        setbuf(stdin, NULL);

        // RELATÓRIO INSTRUTORES (1)
        if (opcSub == 1) {
          printf("\n\n"
                 "+++[RELATÓRIO DE INSTRUTORES]+++\n\n");
          if (TLI == 0) {
            printf("Nenhum instrutor cadastrado.\n");
          } else {
            for (i = 0; i < TLI; i++) {
              printf("Cód.: %d Nome: %s\n", vCodInst[i], vInstrutor[i]);
            }
            printf("\n"
                   "Total: %d instrutor(es)\n",
                   TLI);
          }

          // RELATÓRIO ALUNOS (2)
        } else if (opcSub == 2) {
          printf("\n\n"
                 "+++[RELATÓRIO DE ALUNOS]+++\n\n");
          if (TLA == 0) {
            printf("Nenhum aluno cadastrado.\n");
          } else {
            for (i = 0; i < TLA; i++) {
              printf("CPF: %s Nome: %s Dia: %d | R$ %.2f\n", vCPFAluno[i],
                     vNomeAluno[i], vDiaVenc[i], vValor[i]);
            }
            printf("\n"
                   "Total: %d aluno(s)\n",
                   TLA);
          }

          // RELATÓRIO MODALIDADES (3)
        } else if (opcSub == 3) {
          printf("\n\n"
                 "+++[RELATÓRIO DE MODALIDADES]+++\n\n");
          if (TLM == 0) {
            printf("Nenhuma modalidade cadastrada.\n");
          } else {
            for (i = 0; i < TLM; i++) {
              printf("Cód.: %d Nome: %s Valor/aula: %.2f\n", vCodMod[i],
                     vModalidade[i], vValorAula[i]);
            }
            printf("\n"
                   "Total: %d modalidade(s)\n",
                   TLM);
          }

          // RELATÓRIO DE HISTÓRICO DE AVALIAÇÕES
        } else if (opcSub == 4) {
          printf("\n\n"
                 "+++[HISTÓRICO DE AVALIAÇÕES FÍSICAS]+++\n\n");
          if (TL == 0) {
            printf("Nenhuma avaliação registrada.\n");
          } else {
            for (i = 0; i < TL; i++) {

              // Buscar nome do aluno usando CPF
              char nomeAluno[50] = "(não encontrado)";
              for (j = 0; j < TLA; j++) {
                if (strcmp(vLAluno[i], vCPFAluno[j]) == 0) {
                  strcpy(nomeAluno, vNomeAluno[j]);
                  j = TLA;
                }
              }

              // Buscar nome do instrutor pelo código
              char nomeInst[50] = "(não encontrado)";
              for (j = 0; j < TLI; j++) {
                if (vLInst[i] == vCodInst[j]) {
                  strcpy(nomeInst, vInstrutor[j]);
                  j = TLI;
                }
              }
              printf("Data Avaliação: %s Aluno: %s Nome: %s Instrutor: %s\n",
                     vLDataAval[i], vLAluno[i], nomeAluno, nomeInst);
            }
            printf("\n"
                   "Total: %d avaliação(ões) registrada(s)\n",
                   TL);
          }
        } else if (opcSub == 5) {
          printf(COR_AZUL "[AÇÃO]: Retornar.\n" COR_NORMAL);
        } else if (opcSub != 5) {
          printf(COR_AMARELO "[AVISO]: Opção inválida.\n" COR_NORMAL);
        }

      } // fim while submenu relatórios

    } else if (opcMenu != 5) {
      printf(COR_AMARELO
             "[AVISO]: Opção inválida. Escolha entre 1 e 5.\n" COR_NORMAL);
    }

  } // fim while menu principal

  printf(COR_AZUL "[AÇÃO]: Sistema encerrado.\n\n" COR_NORMAL);

  return 0;
}
