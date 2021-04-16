/* 
*Ficheiro:  porojeto_main.c 
*Autor: Afonso Freitas
*descrição: este ficheiro contém os comandos do projeto
*/

#include "projeto_header.h"

/*inicialização da variável que indica a o tempo no sistema*/
int time = TEMPO_INICIAL;
/*inicialização da variável que indica a quantidade de Tarefas no sistema*/
int total_tasks = INICIAL_TASKS; 
/*inicialização da variável que indica a quantidade de Utilizadores no sistema*/
int total_users = INICIAL_USERS; 
/*inicialização da variável que indica a quantidade de Atividades no sistema*/
int total_activities = INICIAL_ACTIVITIES;

/*
*função que executa o comando correspondente à letra "q"
*este comando é responsável pelo fim da execução do programa
*/
int command_q(){
    char c;
    c = getchar();
    if (NEWLINE(c) ||c == EOF) /*verificação do fim do comando*/
        return END;
    else 
        return IGNORE;
}

/*
*função que executa o comando correspondente à letra "t"
*este comando é responsável pela introdução de novas tarefas no sistema
*/
int command_t(Activity array_actv[],Task array_tasks[]){

    /*inteiro auxiliar para armazenar o input*/
    int aux_duration;
    /*string auxiliar para armazenar o input*/
    char aux_disc[STR_TASK],c;

    c = getchar();
    if(BLANK_CHARACTER(c)){
        scanf(" %d", &aux_duration); /*leitura de uma possível duração*/
        c = getchar();
        if(BLANK_CHARACTER(c)){ 
            scanf(READ_DESC_TASK ,aux_disc);/*leitura de uma possível descrição*/
            if(errors_command_t(array_tasks,aux_disc,aux_duration) != ERROR){
                /*inicialização de uma nova tarefa*/ 
                strcpy(array_tasks[total_tasks].description,aux_disc);
                array_tasks[total_tasks].duration = aux_duration;
                array_tasks[total_tasks].activ_p[0] = array_actv[TO_DO];
                array_tasks[total_tasks].inicial = 0;
                array_tasks[total_tasks].id_task = total_tasks  + 1;
                printf("task %d\n", array_tasks[total_tasks++].id_task);
            }
        }
    }
    return total_tasks;
}

/*
*esta função ordena alfabeticamente com base na descrição das tarefas uma
*array de estruturas "Task" (é utilizado 1 versão do shell sort)
*/
void sort_alphabetically(Task array_aux[], int max_limit){
    int i,gap = 1;
    for(gap = 1;gap < max_limit;gap = 3*gap + 1);
    for(;gap > 0;gap/=3){   
        for ( i = gap; i < max_limit; i++){   
            Task aux = array_aux[i];
            int j = i;
            while(j >= gap && strcmp(aux.description,array_aux[j-gap].description) < 0){
                array_aux[j] = array_aux[j-gap];
                j -= gap;
            }
            array_aux[j] = aux;
        }
    }
}

/*
*esta função ordena numericamente, por ordem crescente 
*com base no tempo inicial de uma dada array com a estrutura "Task"
*é utilizado 1 versão do insertion sort
*/
void inicial_sort(Task array_aux[], int max_limit){
    int i,j;
    for (i= 1; i <= (max_limit - 1); i++) {
        Task aux = array_aux[i];
        j = i-1;
        while ( j >= INDEX_0_TASK && LESS_INICIAL_TIME(aux, array_aux[j])) {
            array_aux[j + 1] = array_aux[j];
            j--;
        }
        array_aux[j + 1] = aux;
    }
}

/*
*esta função executa o comando correspondente à letra "n"
*este comando é responsável pela alteração do tempo no programa
*/
void command_n(){
    char c;
    int time_aux; /*inteiro auxiliar para armazenar o input*/
    c = getchar();
    if(BLANK_CHARACTER(c)){
        /*verifica se existe no input, um número inteiro positivo,e uma nova linha*/
        if(scanf(" %d%c",&time_aux, &c) != 2 ||time_aux < 0||NO_NEWLINE(c))
            printf(INVALID_TIME);
        else if(NEWLINE(c))
            printf("%d\n",time += time_aux);
    }
}

/*esta função imprime com a respetiva formatação o output do comando "l" */
void command_l_output(Task array_tasks[], int aux_id){
    printf("%d %s #%d %s\n",
    array_tasks[aux_id].id_task,
    array_tasks[aux_id].activ_p[0].desc_act,
    array_tasks[aux_id].duration,
    array_tasks[aux_id].description);
}

/*
*esta função executa o comando correspondente à letra "l"
*este comando é responsável pela numeração e listagem das tarefas
*por ordem alfabetica caso não seja introduzido nenhum id, senão 
*imprime as tarefas pela ordem introduzida no input
*/
void command_l(Task array_tasks[]){
    char c;
    int aux_id; /*armazena um input ou acede uma array*/

    Task array_aux[MAX_ID];
    c = getchar();
    if(NEWLINE(c)){ /*lista alfabeticamente as tarefas*/
        /*a variável "aux_id" representa o id-1*/ 
        for (aux_id = INDEX_0_TASK; aux_id < total_tasks; aux_id++) 
            array_aux[aux_id] = array_tasks[aux_id];
            /*criação de um vetor idêntico ao original*/ 

        sort_alphabetically(array_aux, total_tasks);
        /*a variável "aux_id" já não representa o id-1*/
        for(aux_id = 0; aux_id < total_tasks ; aux_id++)
            command_l_output(array_aux,aux_id);
    }
    else if(BLANK_CHARACTER(c)){ /*assume a listagem de acordo com o input*/
        while(scanf(" %d", &aux_id) == 1){
            if(aux_id <= total_tasks && aux_id > 0)
                command_l_output(array_tasks,--aux_id);
            else
                printf("%d: no such task\n", aux_id);
        }
    }
}


/*
*esta função executa o comando correspondente à letra "u"
*este comando é responsável pela adição de um utilizador no sistema
*ou pela listagem dos utilizadores caso a não adição
*/
int command_u(User array_users[]){

    /*string auxiliar para armazenar o input*/
    char c,aux_user[STR_USER];
    int i;

    c = getchar();
    if( BLANK_CHARACTER(c)){ /*assume a adição de um utilizador no sistema*/
        scanf(READ_USER, aux_user);
        if(errors_command_u(array_users,aux_user) != ERROR ){
            strcpy(array_users[total_users].username,aux_user);
            total_users++;
        }
    }
    else if(NEWLINE(c)){ /*lista todos os utilizadores por ordem de adição*/
        for( i = INDEX_0_USER ; i < total_users; ++i)
            printf("%s\n",array_users[i].username);
    }
    return total_users;
}

/*
*esta função função auxiliar do comando "m"
*atribui uma tarefa a uma nova atividade  
*caso a tarefa saia da atividade incial "TO DO", incializa o tempo inicial
*e se entrar na atividade "DONE", imprime o tempo gasto e o excesso demorado
*/
void command_m_auxfinal(Activity array_actv[],Task array_tasks[],
User array_users[],int id_temp, char act_temp[], char user_temp[]){

    int i,index_user,index_activity;
    int gasto,slack;

    for (i=INDEX_0_ACTV;strcmp(array_actv[i].desc_act,act_temp)!=0;++i);
    index_activity = i; /*encontra o índice da atividade na "array_actv"*/
    for (i=INDEX_0_USER;strcmp(array_users[i].username,user_temp) != 0;++i);
    index_user = i; /*encontra o índice do utilizador na "array_users"*/
    /*verifica se há uma atribuição à mesma atividade*/
    if(strcmp(array_tasks[id_temp].activ_p[0].desc_act,
    array_actv[index_activity].desc_act) != 0){
        /*verifica se sai da atividade incial "TO DO"*/
        if(!strcmp(array_tasks[id_temp].activ_p[0].desc_act,TO_DO_STR))
            array_tasks[id_temp].inicial = time;
        /*atualização do utilizador e atividade da tarefa*/
        array_tasks[id_temp].activ_p[0] = array_actv[index_activity];
        array_tasks[id_temp].user_p[0] = array_users[index_user];
        /*verifica se entrou na atividade "DONE"*/
        if(!strcmp(array_tasks[id_temp].activ_p[0].desc_act,DONE_STR)){
            gasto = time - array_tasks[id_temp].inicial;
            slack = gasto - array_tasks[id_temp].duration;
            printf("duration=%d slack=%d\n", gasto , slack);
        }
    }
}

/*
*executa o comando correspondente à letra "m"
*este comando é responsável pela atribuição de uma atividade
*e utilizador a uma tarefa 
*/
void command_m(Activity array_actv[],Task array_tasks[], User array_users[]){
    
    /*strings auxiliares para armazenar o input*/
    char c,user_temp[STR_USER],act_temp[STR_ATIVIDADE];
    int id_temp;
    
    c = getchar();
    if(BLANK_CHARACTER(c)){
        scanf(" %d", &id_temp); /*leitura de um possível id*/
        c = getchar();
        if(BLANK_CHARACTER(c)){
            scanf(READ_USER, user_temp); /*leitura de um possível "user"*/
            c = getchar();
            if (BLANK_CHARACTER(c)){
                scanf(READ_ACTIVITY, act_temp);/*leitura de uma possível descricao*/
                if(errors_command_m(array_actv,array_users,
                array_tasks,act_temp,user_temp,--id_temp) != ERROR){
                    command_m_auxfinal(array_actv,array_tasks,
                    array_users,id_temp,act_temp,user_temp);
                }
            }   
        }
    }
}
/*
*executa uma função auxiliar do comando "d"
*esta função é responsável pela impressão de tarefas
*por ordem crescente de instante de início e alfabeticamente por descrição,
*se duas ou mais tarefas tiverem o mesmo instante de início
*/
void comando_d_auxi(Task array_tasks[], char act_temp[]){

    int i,j;
    Task array_aux[MAX_ID];

    for ( i = INDEX_0_TASK, j = 0; i < total_tasks; i++){ 
        if(!strcmp(array_tasks[i].activ_p[0].desc_act,act_temp))
            array_aux[j++] = array_tasks[i];
    } /*atribuição a uma array com as tarefas presentes numa dada atividade*/
    sort_alphabetically(array_aux, j);
    inicial_sort(array_aux,j); /*este tipo de sorting tem de ser estável*/
    for( i = INDEX_0_TASK; i < j; i++){
        printf("%d %d %s\n", 
        array_aux[i].id_task,
        array_aux[i].inicial,
        array_aux[i].description);
    }
}

/*
*esta função executa o comando correspondente à letra "d"
*este comando é responsável pela listagem de todas as tarefas numa atividade
*/
void command_d(Task array_tasks[],Activity array_actv[]){
    
    /*string auxiliar para armazenar o input*/
    char c,act_temp[STR_ATIVIDADE];

    c = getchar();
    if(BLANK_CHARACTER(c)){
        scanf(READ_ACTIVITY,act_temp); /*leitura de uma possível descrição*/
        if(no_act_error(array_actv,act_temp) != ERROR)
            comando_d_auxi(array_tasks, act_temp);
    }
}

/*
*esta função executa o comando correspondente à letra "a"
*este comando adiciona uma atividade ou
*lista todas as atividades presentes por ordem de criação
*/
int command_a(Activity array_actv[]){
    char c,act_temp[STR_ATIVIDADE];
    int i;

    c = getchar();
    if(BLANK_CHARACTER(c)){ /*assume a adição de uma atividade*/
        scanf(READ_ACTIVITY, act_temp);
        if(errors_command_a(array_actv,act_temp) != ERROR){
            strcpy(array_actv[total_activities].desc_act,
            act_temp);
            ++total_activities;
        }
    }
    else if(NEWLINE(c)){ /*lista todas as atividade por ordem de criação*/
        for ( i = INDEX_0_ACTV; i < total_activities ; ++i){
            printf("%s\n", array_actv[i].desc_act);
        }
    }
    return total_activities;
}
/*esta função executa um comando se possível*/
int all_comands(Task array_tasks[], Activity array_actv[], User array_users[],char c){
    switch (c){
    case 'q': 
        return command_q();
    case 't': 
        total_tasks = command_t(array_actv,array_tasks); 
        return COMMAND;
    case 'l': 
        command_l(array_tasks);
        return COMMAND;
    case 'n': 
        command_n();
        return COMMAND;
    case 'u': 
        total_users = command_u(array_users);
        return COMMAND;
    case 'm': 
        command_m(array_actv,array_tasks,array_users);
        return COMMAND;
    case 'd': 
        command_d(array_tasks,array_actv);
        return COMMAND;
    case 'a': 
        total_activities = command_a(array_actv);
        return COMMAND;
    case '\n': 
        return COMMAND;
    default: 
        return IGNORE;
    }    
}
/*
*função principal do sistema, onde ocorre a análise do comando introduzido,
*a inicialização do algumas variáveis como a array de atividades,
*array de utilizadores, array de tarefas e uma máquina de estados
*/
int main(){
    /*esta array esta ordenada pela ordem de entrada no sistema*/
    Activity array_actv[MAX_ACTIVITIES]; 
    /*cada índice desta array representa o id-1 de uma dada tarefa*/
    Task array_tasks[MAX_ID]; 
    /*esta array esta ordenada pela ordem de entrada no sistema*/
    User array_users[MAX_USERS]; 
    
    int status = COMMAND;
    char c;
    /*adicção de atividades pre-definidas no sistema*/
    strcpy(array_actv[TO_DO].desc_act, TO_DO_STR);
    strcpy(array_actv[DONE].desc_act, DONE_STR);
    strcpy(array_actv[IN_PROGRESS].desc_act, IN_PROGRESS_STR);
    
    while (status != END){
        c = getchar();
        if (status  == COMMAND)
            status = all_comands(array_tasks,array_actv, array_users,c);
        else if(NEWLINE(c))/*assume a existência de um possível comando */
            status = COMMAND;
        else 
            status = IGNORE;
    }
    return EXIT_SUCCESS;
}