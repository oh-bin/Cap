//CPA 함수

typedef unsigned char BYTE;
//cpa 결과(구조체)
typedef struct Cema_result {
    BYTE key;
    int pointnumber;
    double Largest_correlation;
    double Sec_largest_correlation;
}Cema_result;

//CEMA 최적화
void CEMA();
