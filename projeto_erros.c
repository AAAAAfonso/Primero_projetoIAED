/* 
*Ficheiro:  porojeto_erros.c 
*Autor: Afonso Freitas
*Descricao: este ficheiro contem funções que identificam os erros dos comandos
*/
#include "projeto_header.h"


extern int total_activities;
extern int total_users;
extern int total_tasks;

/*esta função verifica a existência de uma atividade numa array de atividades*/
int no_act_error(Activity array_act[],char act_temp[]){
    int i;
    for (i = INDEX_0_ACTV;i < total_activities;++i){
        if(strcmp(array_act[i].desc_act,act_temp) == 0)
            return VALID;
    }
    printf(NO_ACTIVITY);
    return ERROR;
}

/*
*esta função verifica a existência de possíveis erros no 
*comando correspondente à letra "t"
*/
int errors_command_t(Task array_tarefas[], char aux_disc[], int duration){
    int i;
    /*verifica se ainda é possível introduzir uma nova Tarefa*/
    if (total_tasks == MAX_ID){ 
        printf(MANY_TASKS);
        return ERROR;
    }
    /*verifica se a descrição introduzida é repetida*/
    for (i = INDEX_0_TASK; i < total_tasks ;++i){
        if(!strcmp(array_tarefas[i].description,aux_disc)){
            printf(DUPLICATE_DESCRIPTION);
            return ERROR;
        }
    }
    if(duration <= 0){ /*verifica se a duracao introduzida é positiva*/
        printf(INVALID_DURATION);
        return ERROR;
    }
    return VALID;
}


/*esta função verifica a existência de possíveis erros no 
comando correspondente à letra "u"*/
int errors_command_u(User array_users[],char aux_util[]){
    int i;
    /*verifica se o utilizador introduzido ja existe na array*/
    for( i = INDEX_0_USER ; i < total_users; ++i){
        if(!strcmp(array_users[i].username,aux_util)){
            printf(DUPLICATE_USER);
            return ERROR;
        }
    }
    /*verifica se é possível introduzir um novo utilizador*/
	if(total_users == MAX_USERS){
        printf(MANY_USERS);
        return ERROR;
    }
    return VALID;
}
/*
*esta função verifica a existência de possíveis erros no 
*comando correspondente à letra "m"
*/
int errors_command_m(Activity array_act[], User array_users[],
Task array_tarefas[],char act_temp[],char user_temp[],int id_temp){

    int i;
    /*verifica se a tarefa introduzida existe*/
    if(id_temp >= total_tasks || id_temp < 0){
        printf(NO_TASK);
        return ERROR;
    }
    /*verifica se a atividade a ser atribuida não é a inicial*/
    if(!strcmp(TO_DO_STR,act_temp)){
        /*verifica se a atividade a ser atribuida nao é ela propria*/
        if(strcmp(TO_DO_STR,array_tarefas[id_temp].activ_p[0].desc_act)){
            printf(TASK_STARTED);
            return ERROR;
        }
    }
    /*verifica se o utilizador introduzido existe*/
    for (i = INDEX_0_USER;i < total_users;++i){
        if(strcmp(array_users[i].username,user_temp) == 0)
            return no_act_error(array_act,act_temp);
    }
    printf(NO_USER);
    return ERROR;
}

/*
*esta função verifica a existência de possíveis erros no 
*comando correspondente à letra "a"
*/
int errors_command_a(Activity array_act[],char act_temp[]){

    int i;
    /*verifica se já existe a atividade na array*/
    for ( i = INDEX_0_ACTV; i < total_activities; ++i){
        if(strcmp(array_act[i].desc_act,act_temp) == 0){
            printf(DUPLICATE_ACTIVITY);
            return ERROR;
        }
    }
    /*verifica se todos os caracters são maiusculos*/
    for( i = 0; act_temp[i] != '\0'; ++i){
        if(LOWERCASE(act_temp[i])){
            printf(INVALID_DESCRIPTION);
            return ERROR;
        }
    }
    /*verifica se ainda é possível introduzir uma nova atividade*/
    if(total_activities == MAX_ACTIVITIES){
        printf(MANY_ACTIVITIES);
        return ERROR;
    }
    else return VALID;
}