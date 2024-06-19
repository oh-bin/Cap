
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CEMA.h"
#include "CEMA_parameter.h"

static const BYTE SBox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

static const BYTE ISbox[256] = {
     0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
     0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
     0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
     0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
     0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
     0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
     0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
     0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
     0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
     0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
     0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
     0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
     0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
     0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
     0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
     0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

static const BYTE HM_SBox[256] = {
    4, 5, 6, 6, 5, 5, 6, 4, 2, 1, 5, 4, 7, 6, 5, 5,
    4, 2, 4, 6, 6, 4, 4, 4, 5, 4, 3, 6, 4, 3, 4, 2,
    6, 7, 4, 3, 4, 6, 7, 4, 3, 4, 5, 5, 4, 4, 3, 3,
    1, 5, 3, 4, 2, 4, 2, 4, 3, 2, 1, 4, 6, 4, 4, 5,
    2, 3, 3, 3, 4, 5, 4, 2, 3, 5, 5, 5, 3, 5, 5, 2,
    4, 4, 0, 6, 1, 6, 4, 5, 4, 5, 6, 4, 3, 3, 3, 6,
    3, 7, 4, 7, 3, 4, 4, 3, 3, 6, 1, 7, 2, 4, 6, 3,
    3, 4, 1, 5, 3, 5, 3, 6, 5, 5, 5, 2, 1, 8, 6, 4,
    5, 2, 3, 5, 6, 5, 2, 4, 3, 5, 6, 5, 3, 5, 3, 5,
    2, 2, 5, 5, 2, 3, 2, 2, 3, 6, 4, 2, 6, 5, 3, 6,
    3, 3, 4, 2, 3, 2, 2, 4, 3, 5, 4, 3, 3, 4, 4, 5,
    6, 3, 5, 5, 4, 5, 4, 4, 4, 4, 5, 5, 4, 5, 5, 1,
    5, 4, 3, 4, 3, 4, 4, 4, 4, 6, 4, 5, 4, 6, 4, 3,
    3, 5, 5, 4, 2, 2, 6, 3, 3, 4, 5, 5, 3, 3, 4, 5,
    4, 5, 3, 2, 4, 5, 4, 3, 5, 4, 4, 5, 5, 4, 2, 7,
    3, 3, 3, 3, 7, 5, 2, 3, 2, 4, 4, 4, 3, 3, 6, 3
};

static const BYTE HM_ISbox[256] = {
    3, 2, 4, 5, 2, 4, 4, 3, 7, 1, 4, 5, 2, 6, 6, 7,
    5, 5, 4, 2, 5, 5, 8, 4, 3, 4, 3, 2, 3, 6, 5, 5,
    3, 6, 3, 3, 4, 3, 3, 5, 6, 3, 4, 3, 2, 6, 4, 4,
    1, 4, 3, 4, 2, 5, 2, 4, 5, 5, 3, 3, 5, 4, 4, 3,
    4, 5, 6, 3, 3, 3, 3, 3, 4, 3, 4, 4, 5, 4, 5, 3,
    4, 3, 2, 2, 7, 6, 5, 5, 5, 3, 3, 5, 5, 4, 5, 2,
    2, 4, 5, 0, 3, 5, 5, 2, 7, 4, 3, 2, 4, 5, 3, 2,
    3, 3, 4, 5, 4, 6, 4, 1, 3, 6, 6, 2, 1, 3, 3, 5,
    4, 3, 2, 2, 5, 5, 5, 5, 5, 5, 6, 5, 4, 4, 5, 5,
    4, 4, 4, 2, 6, 5, 4, 3, 4, 6, 5, 4, 3, 5, 7, 5,
    4, 5, 3, 4, 4, 3, 4, 3, 6, 6, 3, 3, 4, 2, 6, 4,
    6, 4, 5, 4, 4, 4, 5, 1, 4, 6, 2, 7, 4, 5, 4, 5,
    5, 6, 3, 4, 2, 3, 5, 3, 4, 2, 1, 4, 4, 1, 5, 6,
    2, 3, 7, 4, 3, 5, 3, 3, 4, 5, 5, 6, 4, 4, 4, 7,
    2, 3, 5, 4, 5, 3, 6, 3, 3, 6, 6, 4, 3, 4, 4, 3,
    4, 4, 1, 6, 5, 6, 5, 3, 4, 4, 2, 4, 4, 2, 2, 6
};

//CEMA 최적화
void CEMA()
{
    // 암호문 버퍼
    // ciphertextbuf[파형 수(파형에 대응되는 평문)][평문바이트 수]
    BYTE** ciphertextbuf = (BYTE**)calloc(TRACENUMBER, sizeof(BYTE*));

    // 파형 버퍼
    float** tracebuf = (float**)calloc(POINTNUMBER, sizeof(float*));
    
    // 가상 소비전력 저장하는 부분
    // x: 가상 소비전력 저장
    // x_square: (가상 소비전력)^2을 저장
    long long x = 0; 
    long long x_square = 0;

    // 실제 전자파 방출량 저장하는 부분(최적화를 위해 포인트 별 (실제 전자파 방출량 합), (실제 전자파 방출량 합)^2을 미리 계산)
    // y[포인트 수]: 포인트 별 실제 전자파 방출량 합
    // y_square[포인트 수]: 포인트 별 (실제 전자파 방출량 합)^2
    // xy[포인트 수]: 포인트 별 (가상 소비전력) x (실제 전자파 방출량) 저장
    double* y = (double*)calloc(POINTNUMBER, sizeof(double));
    double* y_square = (double*)calloc(POINTNUMBER, sizeof(double));
    double* xy = (double*)calloc(POINTNUMBER, sizeof(double));

    // 상관계수 저장 버퍼
    double correlation_buf = 0.0; 

    // CEMA 결과 저장 부분
    // cema_result(구조체)
    // -> cema_result.key: key 저장
    // -> cema_result.pointnumber: 해당 key가 저장된 포인트 위치
    // -> cema_result.Largest_correlation: 가장 높은 상관계수
    // -> cema_result.Sec_largest_correlation: 두번째로 가장 높은 상관계수(key는 다를 때)
    Cema_result* cema_result = NULL;
    cema_result = (Cema_result*)calloc(CIPHERTEXTLENGTH, sizeof(Cema_result));

    // 파일 open
    FILE* ciphertextfile = fopen(CIPHERTEXTFILE, "rt");
    FILE* resultfile = fopen(RESULTFILE, "wt");
    FILE* tracefile = fopen(TRACEFILE, "rb");
    // 예외 처리
    if ((ciphertextfile == NULL) || (resultfile == NULL) || (tracefile == NULL))
    {
        fprintf(stderr, "file open error\n");
        return;
    }

    // 암호문 파일로 부터 암호문 읽어옴
    for (int tracenumber = 0; tracenumber < TRACENUMBER; tracenumber++)
    {
        ciphertextbuf[tracenumber] = (BYTE*)calloc(CIPHERTEXTLENGTH, sizeof(BYTE));
        for (int byteindex = 0; byteindex < CIPHERTEXTLENGTH; byteindex++)
        {
            fscanf(ciphertextfile, "%02x", &ciphertextbuf[tracenumber][byteindex]);
        }
    }
    fclose(ciphertextfile);

    // 파형 파일로 부터 파형 읽어옴
    for (int pointnumber = 0; pointnumber < POINTNUMBER; pointnumber++)
    {
        tracebuf[pointnumber] = (float*)calloc(TRACENUMBER, sizeof(float));
    }
    for (int pointnumber = 0; pointnumber < POINTNUMBER; pointnumber++)
    {
        fread(tracebuf[pointnumber], sizeof(float), TRACENUMBER, tracefile);
    }
    fclose(tracefile);

    // 실제 전자파 방출량 합
    for (int pointnumber = 0; pointnumber < POINTNUMBER; pointnumber++)
    {
        y[pointnumber] = 0;
        y_square[pointnumber] = 0;
        for (int tracenumber = 0; tracenumber < TRACENUMBER; tracenumber++)
        {
            y[pointnumber] += tracebuf[pointnumber][tracenumber]; //(실제 전자파 방출량) 합
            y_square[pointnumber] += (tracebuf[pointnumber][tracenumber] * tracebuf[pointnumber][tracenumber]);//(실제 전자파 방출량)^2 합

        }
    }

    // 16바이트에 대한 CEMA 진행
    for (int byteindex = 0; byteindex < 16; byteindex++)
    {
        for (int keycandidate = 0; keycandidate < 256; keycandidate++)
        {
            for (int tracenumber = 0; tracenumber < TRACENUMBER; tracenumber++)
            {
                // keycandidate에 대한 가상 소비전력 계산후 저장(포인트가 달라도 해당 값이 같다)
                x += HM_ISbox[ciphertextbuf[tracenumber][byteindex] ^ keycandidate];
                x_square += HM_ISbox[ciphertextbuf[tracenumber][byteindex] ^ keycandidate] * HM_ISbox[ciphertextbuf[tracenumber][byteindex] ^ keycandidate];
                // keycandidate에 대한 (가상 소비전력) x (실제 전자파 방출량) 계산/ 각 포인트 별로 (가상 소비전력) x (실제 전자파 방출량)을 계산해서 저장

                for (int pointnumber = 0; pointnumber < POINTNUMBER; pointnumber++)
                {
                    xy[pointnumber] += HM_ISbox[ciphertextbuf[tracenumber][byteindex] ^ keycandidate] * tracebuf[pointnumber][tracenumber];
                }
            }

            // 고정 key 후보에 대한 포인트별 상관계수 계산
            // 가상 소비전력은 포인트가 달라져도 해당 값이 같기 때문에 상관계수 계산할때 값 재활용
            // 실제 전자파 방출량은 미리 계산한 y, y_square 활용
            // (가상 소비전력) x (실제 전자파 방출량)은 미리 계산한 xy 활용
            for (int pointnumber = 0; pointnumber < POINTNUMBER; pointnumber++)
            {
                // 상관계수 분모가 0이하일 경우 예외 처리
                if (sqrt((TRACENUMBER * x_square - x * x) *
                    (TRACENUMBER * y_square[pointnumber] - y[pointnumber] * y[pointnumber])) <= 0)
                {
                    correlation_buf = 0.0;
                }
                else
                {
                    // 상관계수 계산
                    correlation_buf = ((TRACENUMBER * xy[pointnumber]) - (x * y[pointnumber])) /
                        sqrt((TRACENUMBER * x_square - x * x) * (TRACENUMBER * y_square[pointnumber] - y[pointnumber] * y[pointnumber]));
                }
                // 기존에 저장되어있는 상관계수 값 보다 계산한 상관계수가 클 경우
                if (fabs(correlation_buf) > fabs(cema_result[byteindex].Largest_correlation))
                {
                    // 저장되어있는 key와 keycandidate가 다르다면 원래 저장한 상관계수가 두번째로 큰 상관계수이다
                    if (cema_result[byteindex].key != keycandidate)
                    {
                        cema_result[byteindex].Sec_largest_correlation = cema_result[byteindex].Largest_correlation;
                    }
                    // 계산한 상관계수, key, point 저장
                    cema_result[byteindex].Largest_correlation = correlation_buf;
                    cema_result[byteindex].key = keycandidate;
                    cema_result[byteindex].pointnumber = pointnumber + 1;
                }
                // 저장된 키와 keycandiate가 다르고 Sec_largest_correlation < 계산한 상관계수 < Largest_correlation 이면 계산한 상관계수는 Sec_largest_correlation이다. 
                else if ((fabs(correlation_buf) > fabs(cema_result[byteindex].Sec_largest_correlation)) && cema_result[byteindex].key != keycandidate)
                {
                    cema_result[byteindex].Sec_largest_correlation = correlation_buf;
                }
                // xy을 0으로 저장(다음 계산에 활용하기 위해)
                xy[pointnumber] = 0.0;
            }
            // x, x_square 0으로 저장(다음 계산에 활용하기 위해)
            x = 0;
            x_square = 0;
            printf("\r%d번째 바이트 %.3f%% 진행 중", byteindex + 1, 100 * ((keycandidate + 1) / (float)256));
        }
    }

    for (int byteindex = 0; byteindex < 16; byteindex++)
    {
        printf("\n[%d번째 바이트]\n", byteindex + 1);
        printf("키: %02x, 해당 포인트: %d, 상관계수: %.10f, Ratio: %.10f\n", cema_result[byteindex].key, cema_result[byteindex].pointnumber,
            fabs(cema_result[byteindex].Largest_correlation), fabs(cema_result[byteindex].Largest_correlation / cema_result[byteindex].Sec_largest_correlation));

        fprintf(resultfile, "[%d번째 바이트]\n", byteindex + 1);
        fprintf(resultfile, "키: %02x, 해당 포인트: %d, 상관계수: %.10f, Ratio: %.10f\n", cema_result[byteindex].key, cema_result[byteindex].pointnumber,
            fabs(cema_result[byteindex].Largest_correlation), fabs(cema_result[byteindex].Largest_correlation / cema_result[byteindex].Sec_largest_correlation));
    }

    free(tracebuf);
    free(y);
    free(y_square);
    free(xy);
    free(cema_result);
    fclose(resultfile);
}