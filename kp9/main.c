#include "table.h"
#include "sort.h"


int main() {
    FILE* d = fopen("data.txt", "r");
    if(!d)
        exit(-1);
    Table* table = CreateTable();
    if(!table) {
        Destroy(table);
        return 0;
    }

    item nr;
    while (!feof(d)) {
        Key key;
        fscanf(d, "%28[^0-9]", key.str);
        fscanf(d, "%d", &key.num);
        fscanf(d, ":%s", nr.val);
        fscanf(d, "\n");
        nr.val[strcspn(nr.val, "\n")] = 0;
        nr.key = key;
        Add(table, nr);
        nr.key = (Key){"", 0};
    }


    fclose(d);
    if(!table) {
        exit(-1);
    }

    printf("\nTable\n");
    Print(table);
    char command;
    Key key;
    do {
        scanf("%c", &command);
        switch (command){
            case 'p':
            Print(table);
            break;
            case 'f':
            scanf(" %28[^0-9]", key.str);
            scanf("%d", &key.num);
            int res = Search(table, key);
            if (res == -1) {
                printf("Not found\n");
            } else {
                printf("[%s%d] -> (%s)\n", key.str, key.num, table->rows[res].val);
            }
            break;
            case 'h':
            printf("\n");
            printf("====================================================================\n");
            printf("# s - sorting table\n");
            printf("# q - stop programm\n");
            printf("# f KEY - search element for key in sorted table\n");
            printf("# p - print table\n");
            printf("====================================================================\n");

            break;
            case 's':
            printf("do:\n");
            Print(table);
            hSortR(table);
            printf("posle:\n");
            Print(table);
            break;
        }
    } while(command != 'q');
    Destroy(table);
    return 0;
}