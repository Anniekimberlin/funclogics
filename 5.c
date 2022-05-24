#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct line //структура смежных вершин
{
    int node1; // вершина 1
    int node2; // вершина 2, смежная вершине 1
};

struct node //структура уникальных вершин
{
    int number;   // вершина
    bool visited; // была ли она посещена (нужно при обходе в глубину при проверки графа на связность)
};

int length = 0, uniq_count = 0;

FILE *openfile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Foner read error!\n");
        exit(1);
    }
    return file;
}

// считывание количества строк в прикреплённом файлике
size_t get_length(FILE *file)
{
    size_t size = 0;
    while (!feof(file))
    {
        if (fgetc(file) == '\n')
            size++;
    }
    size++;
    fseek(file, 0, 0);
    return size;
}

//заполнение массива структуры смежных вершин чиселками из прикреплённого файлика
void get_lines(struct line *lines, FILE *file)
{
    for (int l = 0; fscanf(file, "%d--%d", &(lines[l].node1), &(lines[l].node2)) != EOF; ++l)
        ;
}

int get_edges(int node1, int node2, struct line *list_lines)
{
    int a = -1;
    for (int i = 0; i < length; i++)
    {
        if (node1 == list_lines[i].node1 && node2 == list_lines[i].node2)
        {
            a = i;
        }
    }
    return a;
}

void del_edges(int a, struct line *list_lines)
{
    list_lines[a].node1 = list_lines[length - 1].node1;
    list_lines[a].node2 = list_lines[length - 1].node2;
    length--;
}

int main()
{
    const char filename[] = "graph";
    FILE *file = openfile(filename);
    length = get_length(file);
    printf("%d\n", length);

    struct line list_lines[length]; // создаем массив структур с длинной равной количеству строк в файле
    get_lines(list_lines, file);    // заполняем его
    fclose(file);
    //   вывод для проверки
    printf("Тhis graph was read from the file '%s' \n", filename);
    for (int i = 0; i < length; i++)
    {
        printf("%d--%d\n", list_lines[i].node1, list_lines[i].node2);
    }
    int node1, node2;
    printf("Input pls removable edge: ");
    scanf("%d-%d", &node1, &node2);

    printf("%d-%d\n", node1, node2);
    int x = get_edges(node1, node2, list_lines);
    if (x < 0)
    {
        printf("Вершина не найдена");
    }
    else
    {
        del_edges(x, list_lines);
        for (int i = 0; i < length; i++)
        {
            printf("%d--%d\n", list_lines[i].node1, list_lines[i].node2);
        }
    }
  system("dot -Tpng Dotfile.gv -o Dotfile.png");
    return 0;
}
