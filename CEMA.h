//CPA �Լ�

typedef unsigned char BYTE;
//cpa ���(����ü)
typedef struct Cema_result {
    BYTE key;
    int pointnumber;
    double Largest_correlation;
    double Sec_largest_correlation;
}Cema_result;

//CEMA ����ȭ
void CEMA();
