#include "search.h"
#include "stats.h"
#include <string.h>
#include <getopt.h>

void print_help_mesg() {
    printf("Usage: algocli [OPTION(s)] infile [outfile]\n");
    printf("A simple shortest-path algorithm command line interface\n");
    printf("The options are:\n");
    printf(" -h  --help\t\t\t\tYou know what this option is for...\n");
    printf(" -g  --graph <infile>\t\t\tAssume the graph is stored in this file path\n");
    printf(" -s  --stats\t\t\t\tCompute the specified statistics about this graph\n");
    printf(" -sp  --shortestpath\tSpecify the algorithm and compute the shortest path from given starting point to target point\n");
    printf(" -u  \t\t\t\t\t\tSpecify the starting point\n");
    printf(" -v  \t\t\t\t\t\tSpecify the target point\n");

}

void read_graph_info(char *filp)
{
    FILE *fp;
    fp = fopen(filp, "r");
    // insert code
    return;
}

int main(int argc, char *argv[]) {
    char *opt_string = "hd:b:", c;
    char *filp;
    FILE *fp;
    graph_l *graph;

    /* Test code */
    graph_l_init(fp);
    graph_m_init(fp);
    bfs(graph);
    dfs(graph);

    struct option long_options[] =
            {
                    {"help", no_argument, 0, 'h'},
                    {"dfs", required_argument, 0, 'd'},
                    {"bfs", required_argument, 0, 'b'}
            };

    if (argc < 2)
    {
        print_help_mesg();
        exit(1);
    }
    while((c = getopt_long(argc, argv, opt_string, &long_options[0], NULL)) != -1) {
        switch (c) {
            case '?':
                /* For unknown options or missing argument */
                print_help_mesg();
                exit(1);
            case 'h':
                print_help_mesg();
                exit(0);
            case 'd':
                filp = strdup(optarg);
                break;
            case 'b':
                filp = strdup(optarg);
                break;
        }
    }
    return 0;
}

