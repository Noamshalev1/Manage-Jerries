/* In this part we manage all the jerries we got, and also could change things inside in order to the user wish. */
#include "Jerry.h"
/* function that clear all the memory*/
void memoryclear();
/* function that change a word from lower to upper case */
char* upperCase(char* name);
int numberOfPlanets, numberOfJerries;
Planet** planetsArray;
Jerry** jerriesArray;
char jerry_id[300], phc_name[300], planet_name[300]; // for inputs

int main(int argc, char *argv[] )
{

    numberOfPlanets = atoi(argv[1]);
    numberOfJerries = atoi(argv[2]);
    planetsArray = (Planet**)malloc(numberOfPlanets*sizeof(Planet*)); // array for pointers to planets
    jerriesArray = (Jerry **)malloc(numberOfJerries*sizeof(Jerry*)); // array for pointers to jerries
    /* Check if malloc do a good job */
    if(planetsArray == NULL || jerriesArray == NULL)
    {
        numberOfPlanets = 0;
        numberOfJerries = 0;
        memoryclear();
        printf("Memory Problem");
        exit(1);
    }
    /* function that collect the file */
    FILE* configuration_file = fopen(argv[3], "r");
    /* a buffer for all the inputs chars. */
    char buf[300];
    fscanf(configuration_file, "%*[^\n]\n"); // skip first line
    fgets(buf, sizeof(buf),configuration_file); // take the first line

    /* This part is to collect all planets */
    const char *p = ","; // char we need to split with
    char *input; // collect the first element from a line
    float x, y, z;
    for(int i=0; i<numberOfPlanets; i++) // a loop that takes all planets
    {
        input = strtok(buf, p); // planet's name
        /* this function change from string to float (used for the coordinates */
        x = atof(strtok(NULL, p));
        y = atof(strtok(NULL, p));
        z = atof(strtok(NULL, p));
        /* create a new planet */
        planetsArray[i] = createPlanet(input, x, y, z);
        /* Check if malloc do a good job */
        if(planetsArray[i] == NULL)
        {
            /* if something goes wrong */
            memoryclear();
            fclose(configuration_file);
            printf("Memory Problem");
            exit(1);
        }
        fgets(buf, sizeof(buf),configuration_file); // next line -- at the end contains "Jerries"
    }
    /* This part is to collect all jerries */
    fgets(buf, sizeof(buf),configuration_file); // ignore the line contains "Jerries"
    /* all these vales are for help */
    char *org, *planet;
    float val;
    int mood;
    Planet *ptr;
    status result = success;
    const char *d = ":"; // char for physical-characteristic split
    for(int i=0; i<numberOfJerries; i++)
    {
        input = strtok(buf, p); // Jerry's id
        org = strtok(NULL, p); // Jerry's name of origin
        planet = strtok(NULL, p); // jerry's planet
        mood = atoi(strtok(NULL, p)); // Jerry's mood
        for(int j=0; j<numberOfPlanets; j++) // find the planet
        {
            if(strcmp(planet,planetsArray[j]->name) == 0)
            {
                ptr = planetsArray[j];
                break;
            }
        }
        /* create a new jerry */
        jerriesArray[i] = createJerry(input, mood, ptr, org);
        /* Check if malloc do a good job */
        if(jerriesArray[i] == NULL)
        {
            /* if something goes wrong */
            memoryclear();
            printf("Memory Problem");
            exit(1);
        }
        fgets(buf, sizeof(buf),configuration_file); // next line
        while(buf[0] == '\t') // in case there are physical-characteristic
        {
            memmove(buf, buf+1, strlen(buf)); // this function ignore the '\t'
            input = strtok(buf, d); // name of physical-characteristic
            val = atof(strtok(NULL, d)); // value
            /* create and add a new physical-characteristic*/
            result = addPhc(jerriesArray[i], input, val);
            /* Check if malloc do a good job */
            if(result == failure)
            {
                /* if something goes wrong */
                memoryclear();
                fclose(configuration_file);
                printf("Memory Problem");
                exit(1);
            }
            fgets(buf, sizeof(buf),configuration_file); // next line
        }
    }


    /* MAIN program */
    char choice;
    int index = 0;
    float value;
    bool check;
    status returned_val;

    while (true) {
        check = false;
        returned_val = failure;
        printf("AW JEEZ RICK, what do you want to do now ? \n");
        printf("1 : Print all Jerries \n");
        printf("2 : Print all Planets \n");
        printf("3 : Add physical characteristic to Jerry \n");
        printf("4 : Remove physical characteristic from Jerry \n");
        printf("5 : Print Jerries by a planet \n");
        printf("6 : Print Jerries by a physical characteristic \n");
        printf("7 : Go home \n");
        scanf(" %s", &choice );
        switch( choice )
        {
            case '1': /* Print all Jerries */
                for(int i =0; i<numberOfJerries; i++)
                    printJerry(jerriesArray[i]);
                break;
            case '2': /* Print all Planets */
                for(int i =0; i<numberOfPlanets; i++)
                    printPlanet(planetsArray[i]);
                break;
            case '3': /* Add physical characteristic to Jerry */
                printf("What is your Jerry's ID ? \n");
                scanf("%s", jerry_id );
                for(int i =0; i<numberOfJerries; i++)
                {
                    if(strcmp(jerry_id, jerriesArray[i]->id) == 0)
                    {
                        index = i;
                        check = true;
                        break;
                    }
                }
                if(check == false)
                {
                    printf("OH NO! I CAN'T FIND HIM RICK ! \n");
                    continue;
                }
                printf("What physical characteristic can you add to Jerry - %s ? \n", jerry_id );
                scanf("%s", phc_name);
                if(isExistPhc(jerriesArray[index], phc_name))
                {
                    printf("RICK I ALREADY KNOW HIS %s ! \n", upperCase(phc_name));
                    continue;
                }
                printf("What is the value of his %s ? \n", phc_name );
                scanf("%f", &value);
                /* create and add a new physical-characteristic to jerry */
                returned_val = addPhc(jerriesArray[index], phc_name, value);
                /* Check if malloc do a good job */
                if(returned_val == failure)
                {
                    /* if something goes wrong */
                    memoryclear();
                    fclose(configuration_file);
                    printf("Memory Problem");
                    exit(1);
                }
                printJerry(jerriesArray[index]);
                break;
            case '4': /* Remove physical characteristic from Jerry */
                printf("What is your Jerry's ID ? \n");
                scanf("%s", jerry_id );
                for(int i =0; i<numberOfJerries; i++)
                {
                    if(strcmp(jerry_id, jerriesArray[i]->id) == 0)
                    {
                        index = i;
                        check = true;
                        break;
                    }
                }
                if(check == false)
                {
                    printf("OH NO! I CAN'T FIND HIM RICK ! \n");
                    continue;
                }
                printf("What physical characteristic do you want to remove from Jerry - %s ? \n", jerry_id );
                scanf("%s", phc_name);
                if(isExistPhc(jerriesArray[index], phc_name) == false)
                {
                    printf("RICK I DON'T KNOW HIS %s ! \n", upperCase(phc_name));
                    continue;
                }
                /* delete physical-characteristic from jerry */
                returned_val = deletePhc(jerriesArray[index], phc_name);
                /* Check if malloc do a good job */
                if(returned_val == failure)
                {
                    /* if something goes wrong */
                    memoryclear();
                    fclose(configuration_file);
                    printf("Memory Problem");
                    exit(1);
                }
                printJerry(jerriesArray[index]);
                break;
            case '5': /* Print Jerries a by planet */
                printf("What planet is your Jerry from ? \n");
                scanf("%s", planet_name);
                for(int i =0; i<numberOfPlanets; i++)
                {
                    if(strcmp(planet_name, planetsArray[i]->name) == 0)
                    {
                        check = true;
                        break;
                    }
                }
                if(check == false)
                {
                    printf("RICK I NEVER HEARD ABOUT %s ! \n", upperCase(planet_name));
                    continue;
                }
                check = false;
                for(int i =0; i<numberOfJerries; i++)
                {
                    if(strcmp(planet_name, jerriesArray[i]->org->planet->name) == 0)
                    {
                        check = true;
                        printJerry(jerriesArray[i]);
                    }
                }
                if(check == false)
                {
                    printf("OH NO! I DON'T KNOW ANY JERRIES FROM %s ! \n", upperCase(planet_name));
                    continue;
                }
                break;
            case '6': /* Print Jerries by a physical characteristic */
                printf("What do you know about your Jerry ? \n");
                scanf("%s", phc_name );
                for(int i =0; i<numberOfJerries; i++)
                {
                    if(isExistPhc(jerriesArray[i], phc_name) == true)
                    {
                        check = true;
                        printJerry(jerriesArray[i]);
                    }
                }
                if(check == false)
                {
                    printf("OH NO! I DON'T KNOW ANY JERRY'S %s ! \n", upperCase(phc_name));
                    continue;
                }
                break;
            case '7': /* Go home */
                memoryclear();
                fclose(configuration_file);
                printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE ! \n");
                exit(0);
            default:
                printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n");
                break;
        }
    }
    return 0;
}


/* This function clear the memory */
void memoryclear()
{
    for(int i=0; i<numberOfJerries; i++)
        freeJerry(jerriesArray[i]);
    for(int i=0; i<numberOfPlanets; i++)
        freePlanet(planetsArray[i]);
    free(planetsArray);
    free(jerriesArray);
}

/* This function change a string from lower to upper */
char* upperCase(char* name)
{
    for (int i = 0; name[i]!='\0'; i++)
    {
        if (name[i] >= 'a' && name[i] <= 'z')
            name[i] = name[i] - 32;
    }
    return name;
}









