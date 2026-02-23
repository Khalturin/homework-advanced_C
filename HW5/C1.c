#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10000

int main() {
    // Буферы для строк: MAX_SIZE + 2 (10002) для хранения 10000 символов + '\0'
    char s1[MAX_SIZE + 2], s2[MAX_SIZE + 2];
    
    scanf("%10000s", s1);
    scanf("%10000s", s2);
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    // Первый результат: наибольший префикс s1 = суффиксу s2
    int result1 = 0;
    int max_len1 = (len1 < len2) ? len1 : len2; // Максимальная возможная длина совпадения (минимум из длин строк)
    for (int L = max_len1; L > 0; L--) {// Перебор возможных длин от максимальной вниз до 1 (ищем наибольшее совпадение)
        if (memcmp(s1, s2 + len2 - L, L) == 0) { // Сравнение префикса s1 и суффикса s2
            result1 = L;
            break;
        }
    }
    
    // Второй результат: наибольший суффикс s1 = префиксу s2
    int result2 = 0;
    int max_len2 = (len1 < len2) ? len1 : len2;
    for (int L = max_len2; L > 0; L--) {
        if (memcmp(s1 + len1 - L, s2, L) == 0) { // Сравнение суффикса s1 и префикса s2
            result2 = L;
            break;
        }
    }
    
    printf("%d %d\n", result1, result2);
    return 0;
}