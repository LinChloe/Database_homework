#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 資料模型
typedef struct KeyValue {
    char* key;
    char* value;
    struct KeyValue* next;
} KeyValue;

// 創建一個新的鍵值對
KeyValue* createKeyValue(const char* key, const char* value) {
    KeyValue* kv = (KeyValue*)malloc(sizeof(KeyValue));
    kv->key = strdup(key);
    kv->value = strdup(value);
    kv->next = NULL;
    return kv;
}

// 新增鍵值對
void insertKeyValue(KeyValue** root, const char* key, const char* value) {
    KeyValue* newKV = createKeyValue(key, value);
    newKV->next = *root;
    *root = newKV;
}

// 根據鍵查詢值
const char* getKeyValue(const KeyValue* root, const char* key) {
    const KeyValue* current = root;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;  // 未找到對應的鍵
}

// 更新鍵對應的值
void updateKeyValue(KeyValue* root, const char* key, const char* newValue) {
    KeyValue* current = root;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(newValue);
            break;
        }
        current = current->next;
    }
}

// 刪除鍵值對
void deleteKeyValue(KeyValue** root, const char* key) {
    KeyValue* current = *root;
    KeyValue* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                // 要刪除的鍵值對是第一個
                *root = current->next;
            } else {
                // 要刪除的鍵值對不是第一個
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

// 釋放資源
void freeKeyValueList(KeyValue* root) {
    KeyValue* current = root;
    while (current != NULL) {
        KeyValue* next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}

int main() {
    KeyValue* database = NULL;

    // 創建鍵值對
    insertKeyValue(&database, "name", "John");
    insertKeyValue(&database, "age", "25");
    insertKeyValue(&database, "city", "New York");

    // 讀取鍵值對
    printf("Name: %s\n", getKeyValue(database, "name"));
    printf("Age: %s\n", getKeyValue(database, "age"));
    printf("City: %s\n", getKeyValue(database, "city"));

    // 更新鍵值對
    updateKeyValue(database, "age", "26");
    printf("Updated Age: %s\n", getKeyValue(database, "age"));

    // 刪除鍵值對
    deleteKeyValue(&database, "city");
    printf("City after deletion: %s\n", getKeyValue(database, "city"));

    // 釋放資源
    freeKeyValueList(database);

    return 0;
}
