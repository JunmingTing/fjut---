#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ShoppingItem {
    char name[50];                   // 商品名称
    int quantity;                    // 商品数量
    struct ShoppingItem* next;       // 指向下一个节点的指针
};

struct ShoppingItem* addItem(void);
void removeItem(struct ShoppingItem** shoppingList);
void displayList(struct ShoppingItem* shoppingList);
void updateQuantity(struct ShoppingItem* shoppingList);
void clearList(struct ShoppingItem** shoppingList);
int totalQuantity(struct ShoppingItem* shoppingList);
void findItem(struct ShoppingItem* shoppingList);
void sortList(struct ShoppingItem* shoppingList);
void mergeLists(struct ShoppingItem** destList, struct ShoppingItem* srcList);
void deleteItem(struct ShoppingItem** shoppingList);

int main(void) {
    int n;
    struct ShoppingItem* shoppingList = NULL;

    while (1) {
        printf("输入：1,添加商品到购物清单\n输入：2,从购物清单中移除商品\n输入：3,查看购物清单\n输入：4,修改清单中商品数量\n输入：5,清空购物清单\n输入：6,计算购物清单中的商品\n输入：7,查找清单中的商品\n输入:8,排序购物清单\n输入：9,合并购物清单\n输入：10,删除购物清单中的商品\n输入:-1,结束程序\n");
        printf("———— ———— ———— ———— ———— ———— ———— ———— ———— ———— ———— \n");
        scanf("%d", &n);

        if (n == -1) {
            break;
        } else if (n == 1) {
            struct ShoppingItem* newItem = addItem();
            if (shoppingList == NULL) {
                shoppingList = newItem;
            } else {
                struct ShoppingItem* current = shoppingList;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newItem;
            }
        } else if (n == 2) {
            removeItem(&shoppingList);
        } else if (n == 3) {
            displayList(shoppingList);
        } else if (n == 4) {
            updateQuantity(shoppingList);
        } else if (n == 5) {
            clearList(&shoppingList);
        } else if (n == 6) {
            int total = totalQuantity(shoppingList);
            printf("商品总量为：%d\n", total);
        } else if (n == 7) {
            findItem(shoppingList);
        } else if (n == 8) {
            sortList(shoppingList);
        } else if (n == 9) {
            struct ShoppingItem* srcList = addItem();
            mergeLists(&shoppingList, srcList);
        } else if (n == 10) {
            deleteItem(&shoppingList);
        }
    }

    return 0;
}

struct ShoppingItem* addItem(void) {
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    char itemName[50];
    int itemQuantity;

    printf("输入商品数量：");
    scanf("%d", &itemQuantity);
    getchar();
    printf("输入商品名称：");
    fgets(itemName, 50, stdin);
    itemName[strcspn(itemName, "\n")] = '\0';

    while (itemQuantity != -1) {
        strcpy(newItem->name, itemName);
        newItem->quantity = itemQuantity;
        newItem->next = NULL;

        printf("输入商品数量：");
        scanf("%d", &itemQuantity);
        getchar();
        printf("输入商品名称：");
        fgets(itemName, 50, stdin);
        itemName[strcspn(itemName, "\n")] = '\0';
    }

    return newItem;
}

void removeItem(struct ShoppingItem** shoppingList) {
    char itemName[50];
    getchar();
    printf("输入要移除的商品名称：");
    fgets(itemName, 50, stdin);
    itemName[strcspn(itemName, "\n")] = '\0';

    if (*shoppingList != NULL) {
        struct ShoppingItem* current = *shoppingList;
        struct ShoppingItem* previous = NULL;

        while (current != NULL) {
            if (strcmp(current->name, itemName) == 0) {
                if (previous == NULL) {
                    *shoppingList = current->next;
                } else {
                    previous->next = current->next;
                }
                free(current);
                break;
            }
            previous = current;
            current = current->next;
        }
    }
}

void displayList(struct ShoppingItem* shoppingList) {
    struct ShoppingItem* current = shoppingList;
    printf("购物清单:\n");

    while (current != NULL) {
        printf("%s - 数量：%d\n", current->name, current->quantity);
        current = current->next;
    }
}

void updateQuantity(struct ShoppingItem* shoppingList) {
    char itemName[50];
    int newItemQuantity;

    getchar();
    printf("输入要修改的商品名称：");
    fgets(itemName, 50, stdin);
    itemName[strcspn(itemName, "\n")] = '\0';

    printf("输入新的商品数量：");
    scanf("%d", &newItemQuantity);

    if (shoppingList != NULL) {
        struct ShoppingItem* current = shoppingList;

        while (current != NULL) {
            if (strcmp(current->name, itemName) == 0) {
                current->quantity = newItemQuantity;
                break;
            }
            current = current->next;
        }
    }
}

void clearList(struct ShoppingItem** shoppingList) {
    struct ShoppingItem* current = *shoppingList;

    while (current != NULL) {
        struct ShoppingItem* temp = current;
        current = current->next;
        free(temp);
    }

    *shoppingList = NULL;
}

int totalQuantity(struct ShoppingItem* shoppingList) {
    struct ShoppingItem* current = shoppingList;
    int total = 0;

    while (current != NULL) {
        total += current->quantity;
        current = current->next;
    }

    return total;
}

void findItem(struct ShoppingItem* shoppingList) {
    char itemName[50];
    getchar();
    printf("输入要查找的商品名称：");
    fgets(itemName, 50, stdin);
    itemName[strcspn(itemName, "\n")] = '\0';

    if (shoppingList != NULL) {
        struct ShoppingItem* current = shoppingList;

        while (current != NULL) {
            if (strcmp(current->name, itemName) == 0) {
                printf("%s - 数量：%d\n", current->name, current->quantity);
                return;
            }
            current = current->next;
        }
    }

    printf("未找到商品 \"%s\"。\n", itemName);
}

void sortList(struct ShoppingItem* shoppingList) {
    if (shoppingList != NULL) {
        struct ShoppingItem* current = shoppingList;

        while (current != NULL) {
            struct ShoppingItem* nextItem = current->next;

            while (nextItem != NULL) {
                if (strcmp(current->name, nextItem->name) > 0) {
                    // 交换商品信息
                    char tempName[50];
                    int tempQuantity;

                    strcpy(tempName, current->name);
                    strcpy(current->name, nextItem->name);
                    strcpy(nextItem->name, tempName);

                    tempQuantity = current->quantity;
                    current->quantity = nextItem->quantity;
                    nextItem->quantity = tempQuantity;
                }
                nextItem = nextItem->next;
            }
            current = current->next;
        }
    }
}

void mergeLists(struct ShoppingItem** destList, struct ShoppingItem* srcList) {
    if (*destList == NULL) {
        *destList = srcList;
    } else {
        struct ShoppingItem* current = *destList;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = srcList;
    }
}

void deleteItem(struct ShoppingItem** shoppingList) {
    char itemName[50];
    int deleteAll;

    getchar();
    printf("输入要删除的商品名称：");
    fgets(itemName, 50, stdin);
    itemName[strcspn(itemName, "\n")] = '\0';

    printf("是否全部删除？（1：是，0：否）");
    scanf("%d", &deleteAll);

    if (*shoppingList != NULL) {
        struct ShoppingItem* current = *shoppingList;
        struct ShoppingItem* previous = NULL;

        while (current != NULL) {
            if (strcmp(current->name, itemName) == 0) {
                if (previous == NULL) {
                    // 删除第一个节点
                    struct ShoppingItem* temp = *shoppingList;
                    *shoppingList = (*shoppingList)->next;
                    free(temp);

                    if (!deleteAll) {
                        break;
                    }
                } else {
                    // 删除非第一个节点
                    previous->next = current->next;
                    free(current);

                    if (!deleteAll) {
                        break;
                    }
                }
            } else {
                previous = current;
            }
            current = current->next;
        }
    }
}