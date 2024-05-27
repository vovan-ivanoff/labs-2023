#ifndef __SHOP__
#define __SHOP__

typedef struct Shop {
    char prod_name[20]; // название продукта
    long artikul; // артикул
    float rating; // рейтинг
    long price; // цена в 18 квинтиллионов тугриков
    long remaining; // остаток больше чем частиц во вселенной(наверное)
} Shop;
#endif