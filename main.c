#include "search.h"
#include "stats.h"

void print_help_mesg() {
    printf("Usage: algocli [OPTION(s)] infile [outfile]\n");
    printf("A simple graph analysis command line interface\n");
    printf("The options are:\n");
    printf(" -h  --help\t\t\t\tYou know what this option is for...\n");
    printf(" -g  --graph <infile>\t\t\tAssume the graph is stored in this file path\n");
    printf(" -s  --stats\t\t\t\tCompute the specified statistics about this graph\n");
    printf(" -sp  --shortestpath\t\t\tSpecify the shortest path algorithm\n");
    printf(" -u  \t\t\t\t\tSpecify the starting point\n");
    printf(" -v  \t\t\t\t\tSpecify the target point\n");
}

void draw_garlic(){
    for (float y = -1.5f; y < 1.5f; y += 0.1f){
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
            float a = x * x + y * y - 1;
            putchar(a * a * a - x * x * y * y * y <= 0.085f ? '*' : ' ');
        }
        putchar('\n');
    }
}

int main(int argc, char *argv[]) {
    char *filp;
    char *stats_params;
    char *algo_params;

    if (argc < 2)
    {
        print_help_mesg();
        exit(1);
    }

    if (!my_strcmp(argv[0], "./search-cli")){
        print_help_mesg();
        exit(1);
    }

    if (my_strcmp(argv[1], "-j") == 1){
        draw_garlic();
        return 0;
    }
    else if (my_strcmp(argv[1], "-g") || my_strcmp(argv[1], "--graph")){
        int filp_len = my_strlen(argv[2]);
        filp = (char *)malloc(sizeof(char) * (filp_len + 1));
        my_strcpy(filp, filp_len, argv[2]);
    }
    else {
        print_help_mesg();
        exit(1);
    }

    if (my_strcmp(argv[3], "-s") || my_strcmp(argv[3], "--stats")){
        int stats_len = my_strlen(argv[4]);
        stats_params = (char *)malloc(sizeof(char) * (stats_len + 1));
        my_strcpy(stats_params, stats_len, argv[4]);

        /* Compute the graph statistics */
        if (my_strcmp(stats_params, "edges")){
            int edges = numberOfEdges(filp);
            printf("The number of edges is %d\n", edges);
        }
        else if (my_strcmp(stats_params, "vertices")){
            int vertices = numberOfVertices(filp);
            printf("The number of vertices is %d\n", vertices);
        }
        else if (my_strcmp(stats_params, "freeman")){
            float freeman = freemanNetworkCentrality(filp);
            printf("The freeman centrality is %f\n", freeman);
        }
        else {
            printf("Invalid parameter(-h for help)\n");
            exit(1);
        }
    }
    else if (my_strcmp(argv[3], "-sp") || my_strcmp(argv[3], "--shortestpath")){
        int algo_len = my_strlen(argv[4]);
        algo_params = (char *)malloc(sizeof(char) * (algo_len + 1));
        my_strcpy(algo_params, algo_len, argv[4]);

        if (my_strcmp(argv[5], "-u") && my_strcmp(argv[7], "-v")){
            int start_p, target_p;
            char *sp;
            start_p = str_2_int(argv[6]);
            target_p = str_2_int(argv[8]);
            /* Compute the shortest path */
            sp = shortestpath(start_p, target_p, algo_params, filp);
            if (sp == NULL){
                printf("No connections between %d and %d\n", start_p, target_p);
            }
            else {
                printf("The shortest path is : %s\n", sp);
            }
        }
        else{
            printf("Missing starting point or target point(-h for help)\n");
            exit(1);
        }
    }
    else{
        print_help_mesg();
        exit(1);
    }
    return 0;
}

