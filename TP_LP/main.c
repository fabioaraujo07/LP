#include <stdio.h>
#include <stdlib.h>



#include "enterprise.h"
#include "input.h"
#include "branches.h"

#define LINE "-----------------------------------"

int main(int argc, char** argv) {
    int optionProfile = 1;

    Enterprises enterprises;
    Branches branches = {.contador = 0};
    Enterprise* temp;
    int id;
    int index;

    puts(LINE);

    initialiseEnterprises(&enterprises, FILE_ENTERPRISES);
    initialiseBranches(&branches, FILE_BRANCHES);

    while (optionProfile != 0) {
        printf("Choose your profile\n1-Admin\n2-User\n0-Exit\n");
        scanf("%d", &optionProfile);

        switch (optionProfile) {
            case 1:
                int optionBussines = 1;
                do {
                    printf("What do you want?\n1-Enterprise\n2-Branches\n3-Report\n0-Back\n");
                    scanf("%d", &optionBussines);

                    switch (optionBussines) {
                        case 1:
                            int optionAct = 1;
                            puts(LINE);
                            printf("Enterprise\n\n");

                            do {
                                printf("1-Create\n2-Edit\n3-Remove\n4-List\n5-Add Branche\n0-Back\n");
                                scanf("%d", &optionAct);

                                switch (optionAct) {
                                    case 1:
                                        puts(LINE);
                                        createEnterprises(&enterprises, FILE_ENTERPRISES);
                                        break;

                                    case 2:
                                        puts(LINE);
                                        printf("Edit\n\n");
                                        editEnterprise(&enterprises, FILE_ENTERPRISES);
                                        break;

                                    case 3:
                                        puts(LINE);
                                        printf("Remove\n\n");
                                        removeEnterprises(&enterprises);
                                        break;

                                    case 4:
                                        puts(LINE);
                                        printf("List\n\n");
                                        listEnterprises(enterprises);
                                        break;

                                    case 5:
                                        puts(LINE);
                                        printf("Add Branche\n\n");
                                        addBrancheToEnterprise(&enterprises, &branches);
                                        break;

                                    case 0:
                                        puts(LINE);
                                        break;

                                    default:
                                        puts(LINE);
                                        printf("Error!!\n");
                                        break;
                                }
                            } while (optionAct != 0);

                            break;

                        case 2:
                            int option4;
                            puts(LINE);
                            printf("Branches\n\n");

                            do {
                                printf("1-Create\n2-Edit\n3-Remove\n4-List\n0-Back\n");
                                scanf("%d", &option4);

                                switch (option4) {
                                    case 1:
                                        puts(LINE);
                                        printf("Create\n\n");
                                        createBranches(&branches, FILE_BRANCHES);
                                        break;

                                    case 2:
                                        puts(LINE);
                                        printf("Edit\n\n");
                                        editBranche(&branches, FILE_BRANCHES);
                                        break;

                                    case 3:
                                        puts(LINE);
                                        printf("Remove\n\n");
                                        removeBranches(&branches, &enterprises, FILE_BRANCHES);
                                        break;

                                    case 4:
                                        puts(LINE);
                                        printf("List\n\n");
                                        listBranches(branches);
                                        break;

                                    case 0:
                                        puts(LINE);
                                        break;

                                    default:
                                        puts(LINE);
                                        printf("Error!!\n");
                                        break;
                                }
                            } while (option4 != 0);

                            break;

                        case 3:
                            puts(LINE);
                            printf("Report\n0-Back\n");
                            int reportOption;
                            scanf("%d", &reportOption);

                            if (reportOption == 0) {
                                puts(LINE);
                                break;
                            }
                            // Implemente a lógica para relatórios aqui, se necessário
                            break;

                        case 0:
                            puts(LINE);
                            break;

                        default:
                            puts(LINE);
                            printf("Error!!\n");
                            break;
                    }
                } while (optionBussines != 0);
                break;

            case 2:
                int option2;
                do {
                    printf("What do you want?\n1-Search Enterprise\n2-Rank\n3-Comment\n0-Back\n");
                    scanf("%d", &option2);

                    switch (option2) {
                        case 1:
                            puts(LINE);
                            printf("Search Enterprise\n\n");

                            int search;

                            printf("1-Search by ID\n2-Search by name\n3-Search by Category\n");
                            scanf("%d", &search);

                            switch (search) {
                                case 1:
                                    puts(LINE);
                                    printf("Search by ID\n\n");
                                    searchEnterprises(enterprises);
                                    break;

                                case 2:
                                    puts(LINE);
                                    printf("Search by Name\n\n");
                                    searchEnterprisesByName(enterprises);
                                    break;

                                case 3:
                                    puts(LINE);
                                    printf("Search by Category\n\n");
                                    searchEnterprisesByCategory(enterprises);
                                    break;

                                default:
                                    puts(LINE);
                                    printf("Invalid Option");
                                    break;
                            }

                        case 2:
                            puts(LINE);
                            printf("Rank\n");
                            listEnterprises(enterprises);
                            printf("Insert the Enterprise's ID: \n");

                            scanf("%d", &id);

                            index = checkEnterprise(enterprises, id);
                            if (index != -1) {

                                createEditRating(&enterprises.enterprises[index]);
                            } else {
                                puts(ERROR_ENTERPRISE_NOT_EXIST);
                            }

                            break;

                        case 3:
                            puts(LINE);
                            printf("Comment\n");
                            listEnterprises(enterprises);
                            printf("Insert the Enterprise's ID: \n");

                            scanf("%d", &id);

                            index = checkEnterprise(enterprises, id);
                            if (index != -1) {
                                ;
                                createEditComment(&enterprises.enterprises[index]);
                            } else {
                                puts(ERROR_ENTERPRISE_NOT_EXIST);
                            }
                            break;

                        case 0:
                            puts(LINE);
                            break;

                        default:
                            puts(LINE);
                            printf("Error!!");
                            break;
                    }
                } while (option2 != 0);
                break;

            case 0:
                freeEnterprises(&enterprises);
                freeBranches(&branches);
                puts(LINE);
                printf("Saiu");
                
                break;

            default:
                puts(LINE);
                printf("Error!!\n");
                break;
        }
    }


    return (EXIT_SUCCESS);
}
