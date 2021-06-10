#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utime.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h> 
#include <libgen.h> //pour basename et dirname

void recap(int rflag, int cflag, char* ref, char* end_file)
{
    printf("Récapitulatif des options choisies : \n");
    
    if(rflag) printf("rflag : true\n");
    else printf("rflag : false\n");
    
    if(cflag) printf("cflag : true\n");
    else printf("cflag : false\n");
                     
    printf("Fichier de référence : %s\n", ref);
    printf("Fichier à créer : %s\n", end_file);
}

int main(int argc, char* argv[])
{
    
    //printf("argc : %d\n", argc);
    /*   
    for(int i = 0; i < argc; i++)
        printf("argv : %s\n", argv[i]);
    */
    int rflag = 0;
    int cflag = 0;
    
    char *end_file = NULL;
	char *ref = NULL;
    
    int option;
    
    while((option = getopt(argc, argv, "cr:")) != -1) // ":" signale une entrée qui n'est pas une option, getopt met un pointeur dessus et s'obtient avec optarg
    {
        if(option == 'r')
        {
            rflag = 1;
            ref = optarg; //Permet d'obtenir le nom du fichier de référence
        }
        
        if(option == 'c')
        {
            cflag = 1;
        }
        
        if(option == '?')
        {
            perror("Option inconnue\n");
            exit(EXIT_FAILURE);
        }
    }
    
    if(argc == 1)
    {
        perror("Pas assez d'arguments\n");
        exit(EXIT_FAILURE);
    }
    
    if(argc > 5)
    {
        perror("Trop d'arguments\n");
        exit(EXIT_FAILURE);
    }
     
    end_file = argv[optind];
     
    if(ref != NULL && strcmp(end_file, ref) == 0) //0 : égales, taille(end_file) < taille(ref) : nbr négatif, taille(end_file) > taille(ref) : nbr positif
    {
        perror("Même fichier en entrée et en référence\n");
        exit(EXIT_FAILURE);
    }
    
     
    int fd;//, x, w;
    
    switch(rflag)
    {
        case 0:
            switch(argc)
            {
                case 2:
                case 3://Création de fichier et/ou modif des dates
            
                    if(access(end_file, F_OK) == -1) //si le fichier n'existe pas
                    {
                        switch(cflag) //si création possible
                        {
                        case 0:  //Si pas de flag anti création
                            
                            fd = open(end_file, O_CREAT, 777); //Création du fichier
                            
                            if(fd == -1)
                            {
                                perror("Le fichier n'a pas pu être créé\n");
                                exit(EXIT_FAILURE);
                            }
                            
                            close(fd);
                            exit(EXIT_SUCCESS);                            
                        
                        case 1:  //Si création interdite
                            
                            perror("Le fichier n'existe pas et ne sera pas être créé (-c)\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    
                    //Si le fichier existe
                    
                    struct utimbuf buf;//Date du fichier à changer
                    time_t t; //timestamp
                    buf.actime = time(&t); //time(t) : primitive pour avoir l'heure actuelle, quand le programme se lance
                    buf.modtime = time(&t);
                    
                    int change = utime(end_file, &buf); //Modification des dates via la primitive utime();
                        
                    if(change == 0) 
                    {
                        exit(EXIT_SUCCESS);
                    }
                    
                    else
                    {
                        perror("Echec dans la modification des dates.\n");
                        exit(EXIT_FAILURE);
                    }
            }
            
        case 1: //Si rflag est activé
            
            if((fd = access(ref, F_OK)) == -1) 
            {
                perror("Le fichier de référence n'existe pas\n"); 
                exit(0);
            }
                
                //end_file = argv[argc-1];
                
            if((fd = access(end_file, F_OK)) == -1) //Fichier de fin non ouvrable
            {
                if(cflag) //Arrêt, car pas de création de fichier dû au cflag
                {
                    perror("Le fichier à modifier n'existe pas\n");
                    exit(EXIT_FAILURE);
                }
            
                else //Création du fichier, car pas de -c
                {      
                    if((fd = open(end_file, O_CREAT, 0777)) == -1)
                    {
                        perror("Fichier non créé\n"); 
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        //printf("Fichier créé\n");
                        close(fd);
                    }
                }
            }
            
                //Modification des dates
            
            struct utimbuf buf;// = malloc(sizeof(struct utimbuf)); //Fichier à changer
            struct stat ref_buf;// = malloc(sizeof(struct stat)); //Fichier de réf
             
            stat(ref, &ref_buf); //On stocke les données de argv[2] dans le buffer associé au fichier de référence
            
            buf.actime = ref_buf.st_atime; //On assigne à buf les valeurs de ref_buf
            buf.modtime = ref_buf.st_mtime;
                
            int change = utime(end_file, &buf); //Changement des arguments de argv[3] via la struct buf;
                
            if(change == 0) //Valide avec un 0 comme valeur de retour
            {
                //printf("Changement de date réussi\n");
                //printf("Timestamp d'accès ref : %ld\n", ref_buf.st_atime); //Vérification de la correspondance des timestamps
                //printf("Timestamp d'accès end_file : %ld\n", buf.actime);
                
                exit(EXIT_SUCCESS);
            }
                
            else
            {
                perror("Echec du changement de date\n");
                exit(EXIT_FAILURE);
            }               
    }
}
                    
                
                    
   
