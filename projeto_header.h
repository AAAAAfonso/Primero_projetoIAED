/* 
*Ficheiro:  porojeto_erros.c 
*Autor: Afonso Freitas
*descrição: este ficheiro é o header do prjeto e apresenta os "defines" a serem
*usadas, a declaração de algumas funções e a criação de structs a serem usadas
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*o número correspondente à maquina de estado*/
#define COMMAND 0
#define END 1
#define IGNORE 2
#define VALID 3
#define ERROR 2
/*o numero máximo de valores guardados numa array de um dado tipo*/
#define MAX_ID 10000
#define MAX_USERS 50
#define MAX_ACTIVITIES 10
/*macros que identificam o tipo de caracter*/
#define BLANK_CHARACTER(c) (c == ' ' || c == '\t')
#define NEWLINE(c) c == '\n'
#define NO_NEWLINE(c) c != '\n'
#define LOWERCASE(c) c >= 'a' && c <= 'z'
/*quantidade inicial de estruturas num dado array*/
#define INICIAL_ACTIVITIES 3
#define INICIAL_TASKS 0
#define INICIAL_USERS 0
#define TEMPO_INICIAL 0
/*primeiro índice de uma array de um dado tipo estrutura*/
#define INDEX_0_ACTV 0
#define INDEX_0_TASK 0
#define INDEX_0_USER 0
/*índice representativo numa array de atividades*/
#define TO_DO INDEX_0_ACTV
#define IN_PROGRESS INDEX_0_ACTV + 1
#define DONE INDEX_0_ACTV + 2
/*quantidade maxima de caracteres de uma dada descrição*/
#define STR_ATIVIDADE 21
#define STR_USER 21
#define STR_TASK 51
/*nome de strings pre-definidas*/
#define TO_DO_STR "TO DO"
#define IN_PROGRESS_STR "IN PROGRESS"
#define DONE_STR "DONE"
#define INVALID_TIME "invalid time\n"
#define INVALID_DURATION "invalid duration\n"
#define INVALID_DESCRIPTION "invalid description\n"
#define NO_ACTIVITY "no such activity\n"
#define NO_TASK "no such task\n"
#define NO_USER "no such user\n"
#define MANY_TASKS "too many tasks\n"
#define MANY_USERS "too many users\n"
#define MANY_ACTIVITIES "too many activities\n"
#define TASK_STARTED "task already started\n"
#define DUPLICATE_DESCRIPTION "duplicate description\n"
#define DUPLICATE_ACTIVITY "duplicate activity\n"
#define DUPLICATE_USER "user already exists\n"
/*identificadores de uma determinada descrição*/
#define READ_DESC_TASK " %50[^\n]"
#define READ_USER " %20s"
#define READ_ACTIVITY " %20[^\n]"
/*comparação do tempo de início de duas tarefas*/
#define LESS_INICIAL_TIME(task1,task2) task1.inicial < task2.inicial 

/*definição da estrutura "Activity" */
typedef struct {
    char desc_act[STR_ATIVIDADE]; /*breve descrição da tarefa*/ 
} Activity;

/*definição da estrutura "User" */
typedef struct {
    char username[STR_USER]; /*nome do utilizador*/ 
} User;

/*definição da estrutura "Task" */
typedef struct {
    int id_task; /*representa o id de uma tarefa */ 
    char description[STR_TASK]; /*breve descrição da tarefa*/ 
    int duration; /*duração da tarefa*/ 
    int inicial; /*tempo em que começou a atividade*/ 
    Activity activ_p[1];  /*atividade a qual a tarefa pertence*/ 
    User user_p[1]; /*utilizador a qual a tarefa pertence*/ 
}Task;

int no_act_error(Activity array_activities[],char act_temp[]);

int errors_command_t(Task array_tarefas[], char aux_disc[], int duration);

int errors_command_u(User array_users[],char aux_util[]);

int errors_command_a(Activity array_activities[],char act_temp[]);

int errors_command_m(Activity array_activities[], User array_users[],
Task array_tarefas[],char act_temp[],char user_temp[],int id_temp);