#include <iostream>
struct point { // список с данными точками
    int x;
    int y;
    point * next;
};
struct vector { // структура для удобного хранения векторов
    int x;
    int y;
};
point * head; // указатель на начало списка
point * first; // точка из списка; используется для обхода списка; всегда находится левее second и third
point * second; // точка из списка; используется для обхода списка; всегда находится левее third и правее first
point * third; // точка из списка; используется для обхода списка; всегда находится левее second и first
void test() { // проверяет можно ли построить плоскость на точках first, second и third; если можно: проверяет лежат ли точки, отличные от first, second и third по одну сторону от плоскости

}
/* struct point2 {
    point * first;
    point * second;
    point * third;
    point * point2;
}; */
int main() { // обход: first всегда левее second и third, между first и third идёт second, third всегда правее first и second
    bool end_third = false; // когда third - последняя точка в списке - меняет значение, чтобы сместить second или (second и third) вправо
    bool end_second = false; // когда second - предпоследняя точка в списке - меняет значение, чтобы сместить third вправо
    bool end_first = false; // когда first в списке вторая с конца - меняет значение, чтобы закончить проверки, так как программа обошла все комбинации точек
    FILE * input;
    input = fopen("         ","r");
    point * main = new point;
    fscanf(input,"%i %i",&main->x,&main->y); // сканирование координаты первой точки
    head = main; // указатель на начало списка
    main->next = NULL;
    while (feof(input) == false) { // сканирование координат всех точек
        main->next = new point;
        main = main->next;
        fscanf(input,"%i %i",&main->x,&main->y);
        main->next = NULL;
    }
    fclose(input);
    first = head; // first - первая точка в списке
    second = first->next; // second - вторая точка в списке
    third = second->next; // third - третья точка в списке
    while (end_first == false) {
        while (end_second == false) {
            while(end_third == false) {
                test();
                if (third->next == NULL) { // является ли точка third последней точкой списка?
                    end_third = true;  // да
                }
                else third = third->next; // нет
            }
            end_third = false;
            if (second->next->next == NULL) {  // является ли точка second предпоследней точкой списка?
                end_second = true; // да
            }
            else { // нет
                second = second->next;
                third = second->next;
            }
        }
        end_second = false;
        if (first->next->next->next == NULL) {  // является ли точка first второй с конца точкой списка?
            end_first = true; // да
        }
        else { // нет
            first = first->next;
            second = first->next;
            third = second->next;
        }
    }
    return 0;
}