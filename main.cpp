#include <iostream>
#include <unistd.h>
long int i = 1;
struct point { // список с данными точками
    long int x;
    long int y;
    long int z;
    point * next;
};
struct vector { // структура для удобного хранения векторов и точек
    long int x;
    long int y;
    long int z;
};
point * head; // указатель на начало списка
point * first; // точка из списка; используется для обхода списка; всегда находится левее second и third
point * second; // точка из списка; используется для обхода списка; всегда находится левее third и правее first
point * third; // точка из списка; используется для обхода списка; всегда находится левее second и first
long int Sign (long int number) { // знак
    if (number > 0) {
        return 1;
    }
    else {
        if (number < 0) {
            return -1;
        }
        else {
            return 0;
        }
    }
}
void test() { // проверяет можно ли построить плоскость на точках first, second и third; если можно: проверяет лежат ли точки, отличные от first, second и third по одну сторону от плоскости
    point * go = head;
    vector v1;
    vector v2;
    vector point;
    bool end = false;
    bool ok = true;
    long int sign = 2;
    long int A, B, C, D; // коэффиценты
    point.x = first->x;
    point.y = first->y;
    point.z = first->z;
    v1.x = third->x - first->x;
    v1.y = third->y - first->y;
    v1.z = third->z - first->z;
    v2.x = second->x - first->x;
    v2.y = second->y - first->y;
    v2.z = second->z - first->z;
    if ((v1.x * v2.y == v1.y * v2.x) && (v1.y * v2.z == v1.z * v2.y) && (v1.x * v2.z == v1.z * v2.x)) { // прямая

    }
    else { // плоскость
        A = v2.y * v1.z - v1.y * v2.z;
        B = v2.z * v1.x - v1.z * v2.x;
        C = v2.x * v1.y - v1.x * v2.y;
        D = point.x * v1.y * v2.z - point.x * v2.y * v1.z - point.y * v1.x * v2.z + point.y * v2.x * v1.z + point.z * v1.x * v2.y - point.z * v2.x * v1.y;
     //   printf("\nbefore 1 while\n");
        while (ok == true && sign == 2){ // знак первой возможной точки (точка не лежит в плоскости и не нашли точку)
            if (go == first || go == second || go == third){ // если точка =first second third
      //          printf("\ngo =f = s =t\n");
                go = go->next;
            }
            else {  // если точка !=first second third
        //        printf("\nelse go=f=s=t\n");
                if (A * go->x + B * go->y + C * go->z + D == 0) { // точка принадлежит плоскости
                    ok = false;
        //            printf("\nok=false\n");
                }
                else { // точка не принадлежит плоскости
         //           printf("\nelse ok=false\n");
                    sign = Sign(A * go->x + B * go->y + C * go->z + D);
                }
            }
        }
    //    printf("\nbefore 2 while\n");
        while (end == false && ok == true) { // не последняя точка и пока выполнены условия (точки по одну сторону от плоскости)
            if ((go != first) && (go != second) && (go != third)) { // рассматривая точка не равна first, second, third
                if (Sign(A * go->x + B * go->y + C * go->z + D) != sign) { // точка не лежит в том же полупространстве, что и остальные
                    ok = false; // можно перестать искать
                }
            }
            if (go->next == NULL) { // закончились точки на проверку?
                end = true;  // да
            }
            else go = go->next; // нет, берём следующую
        }
        if (ok == true){ // всё хорошо (все точки лежат по одну стороны от плоскости)
            printf("%li: (%li, %li, %li) (%li, %li, %li) (%li, %li, %li)\n",i,first->x,first->y,first->z,second->x,second->y,second->z,third->x,third->y,third->z);
            i++;
        }
    }
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
    input = fopen("C:\\Users\\199930\\CLionProjects\\point\\points.txt","r");
    point * main = new point;
    fscanf(input,"%li %li %li",&main->x,&main->y,&main->z); // сканирование координаты первой точки
    head = main; // указатель на начало списка
    main->next = NULL;
    while (feof(input) == false) { // сканирование координат всех точек
        main->next = new point;
        main = main->next;
        fscanf(input,"%li %li %li",&main->x,&main->y,&main->z);
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
    //            printf("\ntest\n");
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