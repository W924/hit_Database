#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "extmem.h"

void generateData(); // ����������ݣ�R��1~16 S��20~51
void BubbleSort(int A[56], int B[56]); // ������������ʱʹ�õ������㷨
void merge_sort(); // ��R.A��S.C��������������Ž�����ڣ�R��200~215 S��220~251

void linear_select(); // ����ѡ��A=40��C=60 �����300.blk��ʼ
void binary_select(); // ��Ԫ���� �����400.blk��ʼ
void index_select(); // �������� �����500.blk��ʼ������B+��������

void projection(); // ͶӰ���������ظ�ֵ�������600��ʼ
void projection_distinct(); // ͶӰ�������ظ�ֵ�������650��ʼ

void nest_loop_join(); // �����700.blk��ʼ
void sort_merge_join(); // �����900.blk��ʼ
void hash_join(); // �����1100.blk��ʼ


int main()
{
    //generateData();
    //merge_sort();
    // ��ϵѡ���㷨
    //linear_select();
    //binary_select();
    //index_select();
    // ��ϵͶӰ�㷨
    //projection();
    //projection_distinct();
    // ��ϵ�����㷨
    //nest_loop_join();
    //sort_merge_join();
    //hash_join();
    printf("sdad");
    return 0;
}

// �����������
void generateData() {

    Buffer buf;
    unsigned char *blk;
    int i, j, k;
    int tmp_data;
    char str[4];
    srand((int)time(0));

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }
    // ����R��16�� 16 * 7 = 112
    for(i=1; i<=16; i++) {
        blk = getNewBlockInBuffer(&buf);
		memset(blk, 0, 64);
        for(j=0; j<7; j++) {
            tmp_data = rand()%40 + 1;
            sprintf(str, "%d", tmp_data);
            for(k=0; k<strlen(str); k++) {
                *(blk + 8*j + k) = str[k];
            }
            tmp_data = rand()%1000+1;
            sprintf(str, "%d", tmp_data);
            for(k=0; k<strlen(str); k++) {
                *(blk + 8*j + k + 4) = str[k];
            }
        }
        if(i == 16) {
            tmp_data = 0;
        } else {
            tmp_data = i + 1;
        }
        sprintf(str, "%d", tmp_data);
        for(k=0; k<strlen(str); k++) {
            *(blk + 56 + k) = str[k];
        }
        if (writeBlockToDisk(blk, i, &buf) != 0) {
			perror("Writing Block Failed!\n");
		}
		freeBlockInBuffer(blk, &buf);
    }

    // ����S��32�� 32 * 7 = 224
    for(i=20; i<52; i++) {
        blk = getNewBlockInBuffer(&buf);
		memset(blk, 0, 64);
        for(j=0; j<7; j++) {
            tmp_data = rand()%40+20;
            sprintf(str, "%d", tmp_data);
            for(k=0; k<strlen(str); k++) {
                *(blk + 8*j + k) = str[k];
            }
            tmp_data = rand()%999+1;
            sprintf(str, "%d", tmp_data);
            for(k=0; k<strlen(str); k++) {
                *(blk + 8*j + k + 4) = str[k];
            }
        }
        if(i == 51) {
            tmp_data = 0;
        } else {
            tmp_data = i + 1;
        }
        sprintf(str, "%d", tmp_data);
        for(k=0; k<strlen(str); k++) {
            *(blk + 56 + k) = str[k];
        }
        if (writeBlockToDisk(blk, i, &buf) != 0) {
			perror("Writing Block Failed!\n");
		}
		freeBlockInBuffer(blk, &buf);
    }
}

// ����ѡ���㷨��A=40��C=60
void linear_select(){
    Buffer buf;
    unsigned char *blk;
    int i, j;
    int tmp_A, tmp_B;
    char str[4];
    int next_block = 1;

    int tmp_num = 0;
    unsigned char *result_blk;
    int result_length = 0;
    int result_blk_location = 300;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    printf("����ѡ��\n");

    while(next_block != 0) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_A = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j + 4);
            }
            tmp_B = atoi(str);
            if(tmp_A == 40) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + result_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + result_length + j + 4) = str[j];
                }
                result_length += 8;
                printf("%d, %d\n", tmp_A, tmp_B);
            }
            if(result_length == 56) {
                sprintf(str, "%d", result_blk_location + 1);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + 56 + j) = str[j];
                }
                if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                    perror("Writing Block Failed!\n");
                }
                freeBlockInBuffer(result_blk, &buf);

                result_blk = getNewBlockInBuffer(&buf);
                memset(result_blk, 0, 64);
                result_length = 0;
                result_blk_location++;
            }
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk + 56 + j);
		}
		next_block = atoi(str);
		freeBlockInBuffer(blk, &buf);
    }

    tmp_num = buf.numIO;
    // ��ѯC = 60��Ԫ��
/*
    int tmp_C, tmp_D;
    next_block = 20;
    while(next_block != 0) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_C = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j + 4);
            }
            tmp_D = atoi(str);
            if(tmp_C == 60) {
                sprintf(str, "%d", tmp_C);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + result_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_D);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + result_length + j + 4) = str[j];
                }
                result_length += 8;
                printf("%d, %d\n", tmp_C, tmp_D);
            }
            if(result_length == 56) {
                sprintf(str, "%d", result_blk_location + 1);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + 56 + j) = str[j];
                }
                if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                    perror("Writing Block Failed!\n");
                }
                freeBlockInBuffer(result_blk, &buf);

                result_blk = getNewBlockInBuffer(&buf);
                memset(result_blk, 0, 64);
                result_length = 0;
                result_blk_location++;
            }
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk + 56 + j);
		}
		next_block = atoi(str);
		freeBlockInBuffer(blk, &buf);
    }
*/
    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(result_blk + 56 + j) = str[j];
    }
    if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }
    freeBlockInBuffer(result_blk, &buf);
    printf("����A=40��IO: %d\n", tmp_num);
    // printf("����C=60��IO: %d\n", buf.numIO - tmp_num);
}

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

// �������ڵ������㷨������ð������
void BubbleSort(int A[56], int B[56]) {
	int i, j, k;
	for(i=0; i<56; i++) {
		k = i;
		for(j=i; j<56; j++) {
			if(A[j] < A[k])
				k = j;
		}
		swap(&A[k], &A[i]);
		swap(&B[k], &B[i]);
	}
}

// ���鲢����
void merge_sort() {
    Buffer buf;
    unsigned char *blk;
    int result_location, result_length;
    unsigned char *blk1, *blk2, *blk3, *blk4;
    int blk1_location, blk2_location, blk3_location, blk4_location;

    int i, j, k, m, n;
    int tmp_A, tmp_B, tmp_C, tmp_D;
    int tmp_A1, tmp_B1, tmp_C1, tmp_D1, tmp_C2, tmp_D2, tmp_C3, tmp_D3;
    int array_A[56], array_B[56], array_C[56], array_D[56];
    char str[4];

    int next_block, tmp_result_blk_location, count;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    // ��ϵR��ÿ����56��Ԫ�飬����������Ȼ������м���������
    next_block = 1;
    tmp_result_blk_location = 101;
    count = 0;
    while(next_block != 0) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_A = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j + 4);
            }
            tmp_B = atoi(str);
            array_A[count] = tmp_A;
            array_B[count] = tmp_B;
            count++;
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk + 56 + j);
		}
		next_block = atoi(str);
        freeBlockInBuffer(blk, &buf);
		// ��ʱԪ��װ�������еĻ�����
		if(count == 56) {
            count = 0;
            // ���ڴ��жԻ�������Ԫ���������
            BubbleSort(array_A, array_B);
            // �ڴ�������֮�󣬽�Ԫ��д�ش���
            blk = getNewBlockInBuffer(&buf);
            memset(blk, 0, 64);
            i=0;
            while(i<56) {
                // ÿ�����̿�д��7��Ԫ��
                for(j=0; j<7; j++) {
                    tmp_A = array_A[i];
                    tmp_B = array_B[i];
                    i++;
                    sprintf(str, "%d", tmp_A);
                    for(k=0; k<strlen(str); k++) {
                        *(blk + 8*j + k) = str[k];
                    }
                    sprintf(str, "%d", tmp_B);
                    for(k=0; k<strlen(str); k++) {
                        *(blk + 8*j + k + 4) = str[k];
                    }
                }
                if(i != 56) {
                    sprintf(str, "%d", tmp_result_blk_location + 1);
                } else {
                    sprintf(str, "%d", 0);
                }
                for(k=0; k<strlen(str); k++) {
                    *(blk + 56 + k) = str[k];
                }
                if(writeBlockToDisk(blk, tmp_result_blk_location, &buf) != 0) {
                    perror("Writing Block Failed!\n");
                }

                tmp_result_blk_location++;
                blk = getNewBlockInBuffer(&buf);
                memset(blk, 0, 64);
            }
            tmp_result_blk_location += 2;
        }
    }

    // ��ϵS��ÿ����56��Ԫ�飬����������Ȼ������м���������
    next_block = 20;
    tmp_result_blk_location = 121;
    count = 0;
    while(next_block != 0) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_C = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j + 4);
            }
            tmp_D = atoi(str);
            array_C[count] = tmp_C;
            array_D[count] = tmp_D;
            count++;
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk + 56 + j);
		}
		next_block = atoi(str);
        freeBlockInBuffer(blk, &buf);
		// ��ʱԪ��װ�������еĻ�����
		if(count == 56) {
            count = 0;
            // ���ڴ��жԻ�������Ԫ���������
            BubbleSort(array_C, array_D);
            // �ڴ�������֮�󣬽�Ԫ��д�ش���
            blk = getNewBlockInBuffer(&buf);
            memset(blk, 0, 64);
            i=0;
            while(i<56) {
                // ÿ�����̿�д��7��Ԫ��
                for(j=0; j<7; j++) {
                    tmp_C = array_C[i];
                    tmp_D = array_D[i];
                    i++;
                    sprintf(str, "%d", tmp_C);
                    for(k=0; k<strlen(str); k++) {
                        *(blk + 8*j + k) = str[k];
                    }
                    sprintf(str, "%d", tmp_D);
                    for(k=0; k<strlen(str); k++) {
                        *(blk + 8*j + k + 4) = str[k];
                    }
                }
                if(i != 56) {
                    sprintf(str, "%d", tmp_result_blk_location + 1);
                } else {
                    sprintf(str, "%d", 0);
                }
                for(k=0; k<strlen(str); k++) {
                    *(blk + 56 + k) = str[k];
                }
                if(writeBlockToDisk(blk, tmp_result_blk_location, &buf) != 0) {
                    perror("Writing Block Failed!\n");
                }
                freeBlockInBuffer(blk, &buf);
                tmp_result_blk_location++;
                blk = getNewBlockInBuffer(&buf);
                memset(blk, 0, 64);
            }
            tmp_result_blk_location += 2;
        }
    }

    // ���ڹ�ϵR��ʹ�ö�·�鲢�ϲ��м�������
    blk1_location = 101;
    blk2_location = 111;
    result_location = 200;
    result_length = 0;
    // ��ʼ�������������
    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }
    blk = getNewBlockInBuffer(&buf);
    memset(blk, 0, 64);

    i = 0;
    j = 0;
    blk1 = readBlockFromDisk(blk1_location, &buf);
    blk2 = readBlockFromDisk(blk2_location, &buf);
    while(blk1_location != 0 || blk2_location != 0) {
        // ÿ��ѭ����ȡ����ǰλ�õ�����Ԫ�أ��Ƚϴ�С
        for(k=0; k<4; k++) {
            str[k] = *(blk1 + 8*i + k);
        }
        tmp_A = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk1 + 8*i + k + 4);
        }
        tmp_B = atoi(str);

        for(k=0; k<4; k++) {
            str[k] = *(blk2 + 8*j + k);
        }
        tmp_A1 = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk2 + 8*j + k + 4);
        }
        tmp_B1 = atoi(str);

        if(blk1_location == 0) {
            j++;
            sprintf(str, "%d", tmp_A1);
            for(k=0; k<strlen(str); k++) {
                *(blk + result_length + k) = str[k];
            }
            sprintf(str, "%d", tmp_B1);
            for(k=0; k<strlen(str); k++) {
                *(blk + result_length + k + 4) = str[k];
            }
            result_length += 8;
        } else if(blk2_location == 0) {
            i++;
            sprintf(str, "%d", tmp_A);
            for(k=0; k<strlen(str); k++) {
                *(blk + result_length + k) = str[k];
            }
            sprintf(str, "%d", tmp_B);
            for(k=0; k<strlen(str); k++) {
                *(blk + result_length + k + 4) = str[k];
            }
            result_length += 8;
        } else {
            // ��Aֵ��С��д�����������
            if(tmp_A <= tmp_A1) {
                i++;
                sprintf(str, "%d", tmp_A);
                for(k=0; k<strlen(str); k++) {
                    *(blk + result_length + k) = str[k];
                }
                sprintf(str, "%d", tmp_B);
                for(k=0; k<strlen(str); k++) {
                    *(blk + result_length + k + 4) = str[k];
                }
                result_length += 8;
            } else {
                j++;
                sprintf(str, "%d", tmp_A1);
                for(k=0; k<strlen(str); k++) {
                    *(blk + result_length + k) = str[k];
                }
                sprintf(str, "%d", tmp_B1);
                for(k=0; k<strlen(str); k++) {
                    *(blk + result_length + k + 4) = str[k];
                }
                result_length += 8;
            }
        }

        if(i == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk1 + 56 + k);
            }
            blk1_location = atoi(str);
            i = 0;

            freeBlockInBuffer(blk1, &buf);
            if(blk1_location != 0) {
                if((blk1 = readBlockFromDisk(blk1_location, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(j == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            blk2_location = atoi(str);
            j = 0;

            freeBlockInBuffer(blk2, &buf);
            if(blk2_location != 0) {
                if((blk2 = readBlockFromDisk(blk2_location, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(result_length == 56) {
            if(blk1_location == 0 && blk2_location == 0) {
                sprintf(str, "%d", 0);
            } else {
                sprintf(str, "%d", result_location + 1);
            }
            for(k=0; k<strlen(str); k++) {
                *(blk + 56 + k) = str[k];
            }
            if(writeBlockToDisk(blk, result_location, &buf) != 0) {
                perror("Writing Block Failed!\n");
            }
            blk = getNewBlockInBuffer(&buf);
            memset(blk, 0, 64);
            result_length = 0;
            result_location++;
        }
    }

    // ���ڹ�ϵS��ʹ����·�鲢�ϲ��м�������
    blk1_location = 121;
    blk2_location = 131;
    blk3_location = 141;
    blk4_location = 151;
    result_location = 220;
    result_length = 0;
    // ��ʼ�������������
    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }
    blk = getNewBlockInBuffer(&buf);
    memset(blk, 0, 64);

    i = 0;
    j = 0;
    m = 0;
    n = 0;
    blk1 = readBlockFromDisk(blk1_location, &buf);
    blk2 = readBlockFromDisk(blk2_location, &buf);
    blk3 = readBlockFromDisk(blk3_location, &buf);
    blk4 = readBlockFromDisk(blk4_location, &buf);
    while(blk1_location != 0 || blk2_location != 0 || blk3_location != 0 || blk4_location != 0) {
        for(k=0; k<4; k++) {
            str[k] = *(blk1 + 8*i + k);
        }
        tmp_C = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk1 + 8*i + k + 4);
        }
        tmp_D = atoi(str);

        for(k=0; k<4; k++) {
            str[k] = *(blk2 + 8*j + k);
        }
        tmp_C1 = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk2 + 8*j + k + 4);
        }
        tmp_D1 = atoi(str);

        for(k=0; k<4; k++) {
            str[k] = *(blk3 + 8*m + k);
        }
        tmp_C2 = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk3 + 8*m + k + 4);
        }
        tmp_D2 = atoi(str);

        for(k=0; k<4; k++) {
            str[k] = *(blk4 + 8*n + k);
        }
        tmp_C3 = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk4 + 8*n + k + 4);
        }
        tmp_D3 = atoi(str);

        int final_C, final_D;
        if(blk1_location != 0 && blk2_location == 0 && blk3_location == 0 && blk4_location == 0) {
            i++;
            final_C = tmp_C;
            final_D = tmp_D;
        } else if(blk1_location == 0 && blk2_location != 0 && blk3_location == 0 && blk4_location == 0) {
            j++;
            final_C = tmp_C1;
            final_D = tmp_D1;
        } else if(blk1_location == 0 && blk2_location == 0 && blk3_location != 0 && blk4_location == 0) {
            m++;
            final_C = tmp_C2;
            final_D = tmp_D2;
        } else if(blk1_location == 0 && blk2_location == 0 && blk3_location == 0 && blk4_location != 0) {
            n++;
            final_C = tmp_C3;
            final_D = tmp_D3;
        } else if(blk1_location != 0 && blk2_location != 0 && blk3_location == 0 && blk4_location == 0) {
            if(tmp_C <= tmp_C1) {
                i++;
                final_C = tmp_C;
                final_D = tmp_D;
            } else {
                j++;
                final_C = tmp_C1;
                final_D = tmp_D1;
            }
        } else if(blk1_location != 0 && blk2_location == 0 && blk3_location != 0 && blk4_location == 0) {
            if(tmp_C <= tmp_C2) {
                i++;
                final_C = tmp_C;
                final_D = tmp_D;
            } else {
                m++;
                final_C = tmp_C2;
                final_D = tmp_D2;
            }
        } else if(blk1_location != 0 && blk2_location == 0 && blk3_location == 0 && blk4_location != 0) {
            if(tmp_C <= tmp_C3) {
                i++;
                final_C = tmp_C;
                final_D = tmp_D;
            } else {
                n++;
                final_C = tmp_C3;
                final_D = tmp_D3;
            }
        } else if(blk1_location == 0 && blk2_location != 0 && blk3_location != 0 && blk4_location == 0) {
            if(tmp_C1 <= tmp_C2) {
                j++;
                final_C = tmp_C1;
                final_D = tmp_D1;
            } else {
                m++;
                final_C = tmp_C2;
                final_D = tmp_D2;
            }
        } else if(blk1_location == 0 && blk2_location != 0 && blk3_location == 0 && blk4_location != 0) {
            if(tmp_C1 <= tmp_C3) {
                j++;
                final_C = tmp_C1;
                final_D = tmp_D1;
            } else {
                n++;
                final_C = tmp_C3;
                final_D = tmp_D3;
            }
        } else if(blk1_location == 0 && blk2_location == 0 && blk3_location != 0 && blk4_location != 0) {
            if(tmp_C2 <= tmp_C3) {
                m++;
                final_C = tmp_C2;
                final_D = tmp_D2;
            } else {
                n++;
                final_C = tmp_C3;
                final_D = tmp_D3;
            }
        } else if(blk1_location == 0 && blk2_location != 0 && blk3_location != 0 && blk4_location != 0) {
            if(tmp_C1 <= tmp_C2 && tmp_C1 <= tmp_C3) {
                j++;
                final_C = tmp_C1;
                final_D = tmp_D1;
            } else if(tmp_C2 <= tmp_C1 && tmp_C2 <= tmp_C3) {
                m++;
                final_C = tmp_C2;
                final_D = tmp_D2;
            } else if(tmp_C3 <= tmp_C1 && tmp_C3 <= tmp_C2) {
                n++;
                final_C = tmp_C3;
                final_D = tmp_D3;
            }
        } else if(blk1_location != 0 && blk2_location == 0 && blk3_location != 0 && blk4_location != 0) {
            if(tmp_C <= tmp_C2 && tmp_C <= tmp_C3) {
                i++;
                final_C = tmp_C;
                final_D = tmp_D;
            } else if(tmp_C2 <= tmp_C && tmp_C2 <= tmp_C3) {
                m++;
                final_C = tmp_C2;
                final_D = tmp_D2;
            } else if(tmp_C3 <= tmp_C && tmp_C3 <= tmp_C2) {
                n++;
                final_C = tmp_C3;
                final_D = tmp_D3;
            }
        } else if(blk1_location != 0 && blk2_location != 0 && blk3_location == 0 && blk4_location != 0) {
            if(tmp_C <= tmp_C1 && tmp_C <= tmp_C3) {
                i++;
                final_C = tmp_C;
                final_D = tmp_D;
            } else if(tmp_C1 <= tmp_C && tmp_C1 <= tmp_C3) {
                j++;
                final_C = tmp_C1;
                final_D = tmp_D1;
            } else if(tmp_C3 <= tmp_C && tmp_C3 <= tmp_C1) {
                n++;
                final_C = tmp_C3;
                final_D = tmp_D3;
            }
        } else if(blk1_location != 0 && blk2_location != 0 && blk3_location != 0 && blk4_location == 0) {
            if(tmp_C <= tmp_C1 && tmp_C <= tmp_C2) {
                i++;
                final_C = tmp_C;
                final_D = tmp_D;
            } else if(tmp_C1 <= tmp_C && tmp_C1 <= tmp_C2) {
                j++;
                final_C = tmp_C1;
                final_D = tmp_D1;
            } else if(tmp_C2 <= tmp_C && tmp_C2 <= tmp_C1) {
                n++;
                final_C = tmp_C2;
                final_D = tmp_D2;
            }
        } else {
            if(tmp_C <= tmp_C1 && tmp_C <= tmp_C2 && tmp_C <= tmp_C3) {
                i++;
                final_C = tmp_C;
                final_D = tmp_D;
            } else if(tmp_C1 <= tmp_C && tmp_C1 <= tmp_C2 && tmp_C1 <= tmp_C3) {
                j++;
                final_C = tmp_C1;
                final_D = tmp_D1;
            } else if(tmp_C2 <= tmp_C && tmp_C2 <= tmp_C1 && tmp_C2 <= tmp_C3) {
                m++;
                final_C = tmp_C2;
                final_D = tmp_D2;
            } else {
                n++;
                final_C = tmp_C3;
                final_D = tmp_D3;
            }
        }

        sprintf(str, "%d", final_C);
        for(k=0; k<strlen(str); k++) {
            *(blk + result_length + k) = str[k];
        }
        sprintf(str, "%d", final_D);
        for(k=0; k<strlen(str); k++) {
            *(blk + result_length + k + 4) = str[k];
        }
        result_length += 8;

        if(i == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk1 + 56 + k);
            }
            blk1_location = atoi(str);
            i = 0;
            freeBlockInBuffer(blk1, &buf);
            if(blk1_location != 0) {
                if((blk1 = readBlockFromDisk(blk1_location, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(j == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            blk2_location = atoi(str);
            j = 0;
            freeBlockInBuffer(blk2, &buf);
            if(blk2_location != 0) {
                if((blk2 = readBlockFromDisk(blk2_location, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(m == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk3 + 56 + k);
            }
            blk3_location = atoi(str);
            m = 0;
            freeBlockInBuffer(blk3, &buf);
            if(blk3_location != 0) {
                if((blk3 = readBlockFromDisk(blk3_location, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(n == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk4 + 56 + k);
            }
            blk4_location = atoi(str);
            n = 0;
            freeBlockInBuffer(blk4, &buf);
            if(blk4_location != 0) {
                if((blk4 = readBlockFromDisk(blk4_location, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(result_length == 56) {
            if(blk1_location == 0 && blk2_location == 0 && blk3_location == 0 && blk4_location == 0) {
                sprintf(str, "%d", 0);
            } else {
                sprintf(str, "%d", result_location + 1);
            }
            for(k=0; k<strlen(str); k++) {
                *(blk + 56 + k) = str[k];
            }
            if(writeBlockToDisk(blk, result_location, &buf) != 0) {
                perror("Writing Block Failed!\n");
            }
            freeBlockInBuffer(blk, &buf);
            blk = getNewBlockInBuffer(&buf);
            memset(blk, 0, 64);
            result_length = 0;
            result_location++;
        }


    }
}

// ��Ԫ�����㷨
void binary_select() {
    Buffer buf;
    unsigned char *blk;
    int i, j;
    int tmp_A, tmp_B;
    int min_inblock, max_inblock;
    char str[4];
    int start = 200, end=215;
    int next_block = 207;

    unsigned char *result_blk;
    int result_length = 0;
    int result_location = 400;

    int tmp_num;
    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    printf("\n\n��Ԫ������\n");

    while(next_block >= 200 && next_block <= 215) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}

        // ȡ����һ����֮�󣬻�ȡ�ÿ���������С��Ԫ��
        for(i=0; i<4; i++) {
            str[i] = *(blk + i);
        }
        min_inblock = atoi(str);
        for(i=0; i<4; i++) {
            str[i] = *(blk + 48 + i);
        }
        max_inblock = atoi(str);
        printf("block = %d, min = %d, max = %d\n", next_block, min_inblock, max_inblock);
        // �����������min��max������δ���
        if(min_inblock > 40) {
            end = next_block;
            next_block = (next_block + start) / 2;
            freeBlockInBuffer(blk, &buf);
            continue;
        }
        if(max_inblock < 40) {
            start = next_block;
            next_block = (next_block + end) / 2;
            freeBlockInBuffer(blk, &buf);
            continue;
        }
        // ���Ҫ��ѯ����ֻ�������������
        if(min_inblock < 40 && max_inblock > 40) {
            for(i=1; i<6; i++) {
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j);
                }
                tmp_A = atoi(str);
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j + 4);
                }
                tmp_B = atoi(str);

                if(tmp_A == 40) {
                    sprintf(str, "%d", tmp_A);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j) = str[j];
                    }
                    sprintf(str, "%d", tmp_B);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j + 4) = str[j];
                    }
                    result_length += 8;
                    printf("%d, %d\n", tmp_A, tmp_B);
                }
                if(result_length == 56) {
                    sprintf(str, "%d", result_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    freeBlockInBuffer(result_blk, &buf);

                    result_blk = getNewBlockInBuffer(&buf);
                    memset(result_blk, 0, 64);
                    result_length = 0;
                    result_location++;
                }
            }
            freeBlockInBuffer(blk, &buf);
            break;
        } else if(min_inblock == 40 && max_inblock != 40) {
            for(i=0; i<7; i++) {
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j);
                }
                tmp_A = atoi(str);
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j + 4);
                }
                tmp_B = atoi(str);

                if(tmp_A == 40) {
                    sprintf(str, "%d", tmp_A);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j) = str[j];
                    }
                    sprintf(str, "%d", tmp_B);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j + 4) = str[j];
                    }
                    result_length += 8;
                    printf("%d, %d\n", tmp_A, tmp_B);
                }
                if(result_length == 56) {
                    sprintf(str, "%d", result_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    freeBlockInBuffer(result_blk, &buf);

                    result_blk = getNewBlockInBuffer(&buf);
                    memset(result_blk, 0, 64);
                    result_length = 0;
                    result_location++;
                }
            }
            end = next_block;
            next_block--;
        } else {
            for(i=0; i<7; i++) {
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j);
                }
                tmp_A = atoi(str);
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j + 4);
                }
                tmp_B = atoi(str);

                if(tmp_A == 40) {
                    sprintf(str, "%d", tmp_A);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j) = str[j];
                    }
                    sprintf(str, "%d", tmp_B);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j + 4) = str[j];
                    }
                    result_length += 8;
                    printf("%d, %d\n", tmp_A, tmp_B);
                }
                if(result_length == 56) {
                    sprintf(str, "%d", result_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    freeBlockInBuffer(result_blk, &buf);

                    result_blk = getNewBlockInBuffer(&buf);
                    memset(result_blk, 0, 64);
                    result_length = 0;
                    result_location++;
                }
            }
            start = next_block;
            next_block++;
        }
        freeBlockInBuffer(blk, &buf);
    }

    tmp_num = buf.numIO;

    // ��ѯS.C=60
/*
    int tmp_C, tmp_D;
    start = 220, end=252;
    next_block = 235;
    while(next_block>=220 && next_block < 252) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
        // ȡ����һ����֮�󣬻�ȡ�ÿ���������С��Ԫ��
        for(i=0; i<4; i++) {
            str[i] = *(blk + i);
        }
        for(i=0; i<4; i++) {
            str[i] = *(blk + 48 + i);
        }
        max_inblock = atoi(str);
        printf("block = %d, min = %d, max = %d\n", next_block, min_inblock, max_inblock);
        // �����������min��max������δ���
        if(min_inblock > 60) {
            end = next_block;
            next_block = (next_block + start) / 2;
            freeBlockInBuffer(blk, &buf);
            continue;
        }
        if(max_inblock < 60) {
            start = next_block;
            next_block = (next_block + end) / 2;
            freeBlockInBuffer(blk, &buf);
            continue;
        }
        if(min_inblock < 60 && max_inblock > 60) {
            for(i=1; i<6; i++) {
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j);
                }
                tmp_C = atoi(str);
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j + 4);
                }
                tmp_D = atoi(str);

                if(tmp_C == 60) {
                    sprintf(str, "%d", tmp_C);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j) = str[j];
                    }
                    sprintf(str, "%d", tmp_D);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j + 4) = str[j];
                    }
                    result_length += 8;
                    printf("%d, %d\n", tmp_C, tmp_D);
                }
                if(result_length == 56) {
                    sprintf(str, "%d", result_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    freeBlockInBuffer(result_blk, &buf);

                    result_blk = getNewBlockInBuffer(&buf);
                    memset(result_blk, 0, 64);
                    result_length = 0;
                    result_location++;
                }
            }
            freeBlockInBuffer(blk, &buf);
            break;
        } else if(min_inblock == 60 && max_inblock != 60) {
            for(i=0; i<7; i++) {
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j);
                }
                tmp_C = atoi(str);
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j + 4);
                }
                tmp_D = atoi(str);

                if(tmp_C == 60) {
                    sprintf(str, "%d", tmp_C);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j) = str[j];
                    }
                    sprintf(str, "%d", tmp_D);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j + 4) = str[j];
                    }
                    result_length += 8;
                    printf("%d, %d\n", tmp_C, tmp_D);
                }
                if(result_length == 56) {
                    sprintf(str, "%d", result_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    freeBlockInBuffer(result_blk, &buf);

                    result_blk = getNewBlockInBuffer(&buf);
                    memset(result_blk, 0, 64);
                    result_length = 0;
                    result_location++;
                }
            }
            end = next_block;
            next_block--;
        } else {
            for(i=0; i<7; i++) {
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j);
                }
                tmp_C = atoi(str);
                for(j=0; j<4; j++) {
                    str[j] = *(blk + 8*i + j + 4);
                }
                tmp_D = atoi(str);

                if(tmp_C == 60) {
                    sprintf(str, "%d", tmp_C);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j) = str[j];
                    }
                    sprintf(str, "%d", tmp_D);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + result_length + j + 4) = str[j];
                    }
                    result_length += 8;
                    printf("%d, %d\n", tmp_C, tmp_D);
                }
                if(result_length == 56) {
                    sprintf(str, "%d", result_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    freeBlockInBuffer(result_blk, &buf);

                    result_blk = getNewBlockInBuffer(&buf);
                    memset(result_blk, 0, 64);
                    result_length = 0;
                    result_location++;
                }
            }
            start = next_block;
            next_block++;
        }
        freeBlockInBuffer(blk, &buf);
    }
*/
    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(result_blk + 56 + j) = str[j];
    }
    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }
    freeBlockInBuffer(result_blk, &buf);
    printf("����A=40��IO��%d\n", tmp_num);
    // printf("����C=60��IO: %d\n", buf.numIO - tmp_num);
}

// ͶӰ
void projection() {
    Buffer buf;
    unsigned char *blk;
    int i, j;
    int tmp_A;
    char str[4];
    int next_block = 1;

    unsigned char *result_blk;
    int result_length = 0;
    int result_blk_location = 600;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    printf("\n\nͶӰ����ȥ�أ���\n");

    while(next_block != 0) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_A = atoi(str);
            for(j=0; j<strlen(str); j++) {
                *(result_blk + result_length + j) = str[j];
            }
            result_length += 4;
            printf("A = %d\n", tmp_A);
            if(result_length == 56) {

                sprintf(str, "%d", result_blk_location + 1);

                for(j=0; j<strlen(str); j++) {
                    *(result_blk + 56 + j) = str[j];
                }
                if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                    perror("Writing Block Failed!\n");
                }
                freeBlockInBuffer(result_blk, &buf);

                result_blk = getNewBlockInBuffer(&buf);
                memset(result_blk, 0, 64);
                result_length = 0;
                result_blk_location++;
            }
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk + 56 + j);
		}
		next_block = atoi(str);
		freeBlockInBuffer(blk, &buf);
    }
    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(result_blk + 56 + j) = str[j];
    }
    if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }
    freeBlockInBuffer(result_blk, &buf);
}

// ͶӰ��ȥ��
void projection_distinct() {
    Buffer buf;
    unsigned char *blk;
    int i, j;
    int tmp_A;
    char str[4];
    int next_block = 200;

    unsigned char *result_blk;
    int result_length = 0;
    int result_blk_location = 650;
    int old_data = -1;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    printf("\n\nͶӰ��ȥ�أ���\n");

    while(next_block != 0) {
        if((blk = readBlockFromDisk(next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_A = atoi(str);
            if(tmp_A != old_data) {
                old_data = tmp_A;
            } else {
                continue;
            }
            for(j=0; j<strlen(str); j++) {
                *(result_blk + result_length + j) = str[j];
            }
            result_length += 4;
            printf("A = %d\n", tmp_A);
            if(result_length == 56) {

                sprintf(str, "%d", result_blk_location + 1);

                for(j=0; j<strlen(str); j++) {
                    *(result_blk + 56 + j) = str[j];
                }
                if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                    perror("Writing Block Failed!\n");
                }
                freeBlockInBuffer(result_blk, &buf);

                result_blk = getNewBlockInBuffer(&buf);
                memset(result_blk, 0, 64);
                result_length = 0;
                result_blk_location++;
            }
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk + 56 + j);
		}
		next_block = atoi(str);
		freeBlockInBuffer(blk, &buf);
    }
    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(result_blk + 56 + j) = str[j];
    }
    if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }
    freeBlockInBuffer(result_blk, &buf);
}

void nest_loop_join() {
    Buffer buf;
    unsigned char *blk1, *blk2;
    int i, j, k;
    int tmp_A, tmp_B, tmp_C, tmp_D;
    char str[4];
    int r_next_block = 200;
    int s_next_block;

    unsigned char *result_blk;
    int result_length = 0;
    int result_blk_location = 700;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    printf("\n\nnest-loop-join��\n");

    while(r_next_block != 0) {
        if((blk1 = readBlockFromDisk(r_next_block, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		s_next_block = 220;
		while(s_next_block != 0) {
            if((blk2 = readBlockFromDisk(s_next_block, &buf)) == NULL) {
                perror("Reading Block Failed!\n");
            }
            for(i=0; i<7; i++) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k);
                }
                tmp_A = atoi(str);
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k + 4);
                }
                tmp_B = atoi(str);
                for(j=0; j<7; j++) {
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k);
                    }
                    tmp_C = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k + 4);
                    }
                    tmp_D = atoi(str);
                    // ���д�ش���
                    if(tmp_A == tmp_C) {
                        sprintf(str, "%d", tmp_A);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        result_length += 16;
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C, tmp_D);
                    }
                    // ���д�ش��̿�����
                    if(result_length == 48) {
                        result_length = 0;
                        sprintf(str, "%d", result_blk_location + 1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + 56 + k) = str[k];
                        }
                        if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
                            perror("Writing Block Failed!\n");
                        }
                        result_blk_location++;
                        result_blk = getNewBlockInBuffer(&buf);
                        memset(result_blk, 0, 64);
                    }
                }
            }
            // ��Ҫ��ȡ��һ��s_next_block
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            s_next_block = atoi(str);
            freeBlockInBuffer(blk2, &buf);
		}
		// ��Ҫ��ȡ��һ��r_next_block
		for(k=0; k<4; k++) {
            str[k] = *(blk1 + 56 + k);
		}
		r_next_block = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }
    sprintf(str, "%d", 0);
    for(k=0; k<strlen(str); k++) {
        *(result_blk + 56 + k) = str[k];
    }
    if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
        perror("Writing Block Failed!\n");
    }
    printf("IO: %ld", buf.numIO);
}

// sort merge join
void sort_merge_join() {
    Buffer buf;
    unsigned char *blk1, *blk2;
    int r_next = 200;
    int s_next = 220;
    int result_blk_location = 900;
    int i, j, k;
    int tmp_i, tmp_j;
    int tmp_A, tmp_B, tmp_C, tmp_D;
    int tmp_A1, tmp_B1, tmp_C1, tmp_D1;
    char str[4];
    int r_next_tmp, s_next_tmp; //�����������
    unsigned char *tmp_blk; // �����������

    unsigned char *result_blk;
    int result_length = 0;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    printf("\n\nsort-merge-join��\n");

    i = 0;
    j = 0;
    blk1 = readBlockFromDisk(r_next, &buf);
    blk2 = readBlockFromDisk(s_next, &buf);
    while(r_next != 0 && s_next != 0) {
        // ÿ��ѭ����ȡ����ǰλ�õ�����Ԫ�أ��Ƚϴ�С
        for(k=0; k<4; k++) {
            str[k] = *(blk1 + 8*i + k);
        }
        tmp_A = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk1 + 8*i + k + 4);
        }
        tmp_B = atoi(str);

        for(k=0; k<4; k++) {
            str[k] = *(blk2 + 8*j + k);
        }
        tmp_C = atoi(str);
        for(k=0; k<4; k++) {
            str[k] = *(blk2 + 8*j + k + 4);
        }
        tmp_D = atoi(str);

        if(tmp_A < tmp_C) {
            i++;
        } else if(tmp_A > tmp_C) {
            j++;
        } else if(tmp_A == tmp_C) {
            // ���Ȱѵ�ǰλ�õ�ABCD�������ݻ�����
            sprintf(str, "%d", tmp_A);
            for(k=0; k<strlen(str); k++) {
                *(result_blk + result_length + k) = str[k];
            }
            sprintf(str, "%d", tmp_B);
            for(k=0; k<strlen(str); k++) {
                *(result_blk + result_length + k + 4) = str[k];
            }
            sprintf(str, "%d", tmp_C);
            for(k=0; k<strlen(str); k++) {
                *(result_blk + result_length + k + 8) = str[k];
            }
            sprintf(str, "%d", tmp_D);
            for(k=0; k<strlen(str); k++) {
                *(result_blk + result_length + k + 12) = str[k];
            }
            printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C, tmp_D);
            // ֻҪ��Ԫ����룬��Ҫ�жϸû�����Ƿ�����
            result_length += 16;
            if(result_length == 48) {
                sprintf(str, "%d", result_blk_location + 1);
                for(k=0; k<strlen(str); k++) {
                    *(result_blk + 56 + k) = str[k];
                }
                if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                    perror("Writing Block Failed!\n");
                }
                result_blk = getNewBlockInBuffer(&buf);
                memset(result_blk, 0, 64);
                result_length = 0;
                result_blk_location++;
            }
            // ���������ϵS���뵱ǰA��ȵ�C��Ԫ��
            // ������Ҫȷ����������ĵ�һ��S��Ԫ�����ڵ�λ��
            // �������������Ļ�����������
            tmp_j = j + 1;
            s_next_tmp = s_next;
            if(tmp_j == 7) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk2 + 56 + k);
                }
                s_next_tmp = atoi(str);
                tmp_j = 0;
            }
            while(s_next_tmp != 0) {
                if((tmp_blk = readBlockFromDisk(s_next_tmp, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
                int flag = 1;
                // ��ȡ��ǰλ�õ�C��D
                while(tmp_j < 7) {
                    for(k=0; k<4; k++) {
                        str[k] = *(tmp_blk + 8*tmp_j + k);
                    }
                    tmp_C1 = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(tmp_blk + 8*tmp_j + k + 4);
                    }
                    tmp_D1 = atoi(str);
                    // �ж����������C��A�Ƿ����
                    if(tmp_C1 == tmp_A) {
                        sprintf(str, "%d", tmp_A);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C1, tmp_D1);
                        // ֻҪ��Ԫ����룬��Ҫ�жϸû�����Ƿ�����
                        result_length += 16;
                        if(result_length == 48) {
                            sprintf(str, "%d", result_blk_location + 1);
                            for(k=0; k<strlen(str); k++) {
                                *(result_blk + 56 + k) = str[k];
                            }
                            if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                                perror("Writing Block Failed!\n");
                            }
                            result_blk = getNewBlockInBuffer(&buf);
                            memset(result_blk, 0, 64);
                            result_length = 0;
                            result_blk_location++;
                        }
                    } else {
                        flag = 0;
                    }
                    tmp_j++;
                }
                for(k=0; k<4; k++) {
                    str[k] = *(tmp_blk + 56 + k);
                }
                s_next_tmp = atoi(str);
                tmp_j = 0; // bug!!
                freeBlockInBuffer(tmp_blk, &buf);
                // ��������˲��ȵ�Ԫ�ؾ�ֹͣ�������
                if(flag == 0) {
                    break;
                }
            }
            // Ȼ�����������ϵR���뵱ǰS��ȵ�Ԫ��
            tmp_i = i + 1;
            r_next_tmp = r_next;
            if(tmp_i == 7) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 56 + k);
                }
                r_next_tmp = atoi(str);
                tmp_i = 0;
            }
            while(r_next_tmp != 0) {
                if((tmp_blk = readBlockFromDisk(r_next_tmp, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
                int flag = 1;
                // ��ȡ��ǰλ�õ�C��D
                while(tmp_i < 7) {
                    for(k=0; k<4; k++) {
                        str[k] = *(tmp_blk + 8*tmp_i + k);
                    }
                    tmp_A1 = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(tmp_blk + 8*tmp_i + k + 4);
                    }
                    tmp_B1 = atoi(str);
                    // �ж����������C��A�Ƿ����
                    if(tmp_A1 == tmp_C) {
                        sprintf(str, "%d", tmp_A1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A1, tmp_B1, tmp_C, tmp_D);
                        // ֻҪ��Ԫ����룬��Ҫ�жϸû�����Ƿ�����
                        result_length += 16;
                        if(result_length == 48) {
                            sprintf(str, "%d", result_blk_location + 1);
                            for(k=0; k<strlen(str); k++) {
                                *(result_blk + 56 + k) = str[k];
                            }
                            if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                                perror("Writing Block Failed!\n");
                            }
                            result_blk = getNewBlockInBuffer(&buf);
                            memset(result_blk, 0, 64);
                            result_length = 0;
                            result_blk_location++;
                        }
                    } else {
                        flag = 0;
                    }
                    tmp_i++;
                }
                for(k=0; k<4; k++) {
                    str[k] = *(tmp_blk + 56 + k);
                }
                r_next_tmp = atoi(str);
                tmp_i = 0;
                freeBlockInBuffer(tmp_blk, &buf);
                if(flag == 0) {
                    break;
                }
            }
            i++;
            j++;
        }

        if(i == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk1 + 56 + k);
            }
            r_next = atoi(str);
            i = 0;
            freeBlockInBuffer(blk1, &buf);
            if(r_next != 0) {
                if((blk1 = readBlockFromDisk(r_next, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(j == 7) {
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            s_next = atoi(str);
            j = 0;

            freeBlockInBuffer(blk2, &buf);
            if(s_next != 0) {
                if((blk2 = readBlockFromDisk(s_next, &buf)) == NULL) {
                    perror("Reading Block Failed!\n");
                }
            }
        }

        if(result_length == 56) {
            if(r_next == 0 && s_next == 0) {
                sprintf(str, "%d", 0);
            } else {
                sprintf(str, "%d", result_blk_location + 1);
            }
            for(k=0; k<strlen(str); k++) {
                *(result_blk + 56 + k) = str[k];
            }
            if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0) {
                perror("Writing Block Failed!\n");
            }
            result_blk = getNewBlockInBuffer(&buf);
            memset(result_blk, 0, 64);
            result_length = 0;
            result_blk_location++;
        }
    }
    sprintf(str, "%d", 0);
    for(k=0; k<strlen(str); k++) {
        *(result_blk + 56 + k) = str[k];
    }
    if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
        perror("Writing Block Failed!\n");
    }
    printf("IO: %ld\n", buf.numIO);
}

// hash-join, x mod 5
void hash_join() {
    Buffer buf;
    unsigned char *blk1, *blk2;
    unsigned char *h_blk0, *h_blk1, *h_blk2, *h_blk3, *h_blk4;
    int i, j, k;
    int tmp_A, tmp_B, tmp_C, tmp_D;
    char str[4];

    int r_next = 200;
    int s_next = 220;

    unsigned char *result_blk;
    int result_length = 0;
    int result_blk_location = 1100;

    int count = 0;
    int tmp_count;
    int r_hash0 = 2000, r_hash1 = 2050, r_hash2 = 2100, r_hash3 = 2150, r_hash4 = 2200;
    int s_hash0 = 2300, s_hash1 = 2350, s_hash2 = 2400, s_hash3 = 2450, s_hash4 = 2500;
    int hash0_length = 0, hash1_length = 0, hash2_length = 0, hash3_length = 0, hash4_length = 0;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    // ��ʼ����ϵR�Ĺ�ϣͰ
    h_blk1 = getNewBlockInBuffer(&buf);
    h_blk2 = getNewBlockInBuffer(&buf);
    h_blk3 = getNewBlockInBuffer(&buf);
    h_blk4 = getNewBlockInBuffer(&buf);
    h_blk0 = getNewBlockInBuffer(&buf);
    memset(h_blk1, 0, 64);
    memset(h_blk2, 0, 64);
    memset(h_blk3, 0, 64);
    memset(h_blk4, 0, 64);
    memset(h_blk0, 0, 64);

    // �Թ�ϵR��A���Խ��й�ϣ
    while(r_next != 0) {
        if((blk1 = readBlockFromDisk(r_next, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		count++;
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk1 + 8*i + j);
            }
            tmp_A = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk1 + 8*i + j + 4);
            }
            tmp_B = atoi(str);

            // ��A��ֵ���й�ϣ
            if(tmp_A % 5 == 0) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk0 + hash0_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk0 + hash0_length + j + 4) = str[j];
                }
                hash0_length += 8;
                if(hash0_length == 56) {
                    sprintf(str, "%d", r_hash0 + 1);
                    for(j=0; j<4; j++) {
                        *(h_blk0 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk0, r_hash0, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk0 = getNewBlockInBuffer(&buf);
                    memset(h_blk0, 0, 64);
                    hash0_length = 0;
                    r_hash0++;
                }
            } else if(tmp_A % 5 == 1) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk1 + hash1_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk1 + hash1_length + j + 4) = str[j];
                }
                hash1_length += 8;
                if(hash1_length == 56) {
                    sprintf(str, "%d", r_hash1 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk1 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk1, r_hash1, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk1 = getNewBlockInBuffer(&buf);
                    memset(h_blk1, 0, 64);
                    hash1_length = 0;
                    r_hash1++;
                }
            } else if(tmp_A % 5 == 2) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk2 + hash2_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk2 + hash2_length + j + 4) = str[j];
                }
                hash2_length += 8;
                if(hash2_length == 56) {
                    sprintf(str, "%d", r_hash2 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk2 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk2, r_hash2, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk2 = getNewBlockInBuffer(&buf);
                    memset(h_blk2, 0, 64);
                    hash2_length = 0;
                    r_hash2++;
                }
            } else if(tmp_A % 5 == 3) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk3 + hash3_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk3 + hash3_length + j + 4) = str[j];
                }
                hash3_length += 8;
                if(hash3_length == 56) {
                    sprintf(str, "%d", r_hash3 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk3 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk3, r_hash3, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk3 = getNewBlockInBuffer(&buf);
                    memset(h_blk3, 0, 64);
                    hash3_length = 0;
                    r_hash3++;
                }
            } else if(tmp_A % 5 == 4) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk4 + hash4_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk4 + hash4_length + j + 4) = str[j];
                }
                hash4_length += 8;
                if(hash4_length == 56) {
                    sprintf(str, "%d", r_hash4 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk4 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk4, r_hash4, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk4 = getNewBlockInBuffer(&buf);
                    memset(h_blk4, 0, 64);
                    hash4_length = 0;
                    r_hash4++;
                }
            }
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk1 + 56 + j);
		}
		r_next = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }

    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(h_blk0 + 56 + j) = str[j];
        *(h_blk1 + 56 + j) = str[j];
        *(h_blk2 + 56 + j) = str[j];
        *(h_blk3 + 56 + j) = str[j];
        *(h_blk4 + 56 + j) = str[j];
    }
    if(writeBlockToDisk(h_blk0, r_hash0, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk1, r_hash1, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk2, r_hash2, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk3, r_hash3, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk4, r_hash4, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }
    count += 5;
    printf("Ϊ��ϵ��R��������IO: %d\n", count);
    tmp_count = count;
    // �Թ�ϵS��C��������ϣ
    hash0_length = 0;
    hash1_length = 0;
    hash2_length = 0;
    hash3_length = 0;
    hash4_length = 0;
    h_blk1 = getNewBlockInBuffer(&buf);
    h_blk2 = getNewBlockInBuffer(&buf);
    h_blk3 = getNewBlockInBuffer(&buf);
    h_blk4 = getNewBlockInBuffer(&buf);
    h_blk0 = getNewBlockInBuffer(&buf);
    memset(h_blk1, 0, 64);
    memset(h_blk2, 0, 64);
    memset(h_blk3, 0, 64);
    memset(h_blk4, 0, 64);
    memset(h_blk0, 0, 64);
    while(s_next != 0) {
        if((blk1 = readBlockFromDisk(s_next, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		count++;
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk1 + 8*i + j);
            }
            tmp_A = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk1 + 8*i + j + 4);
            }
            tmp_B = atoi(str);

            // ��A��ֵ���й�ϣ
            if(tmp_A % 5 == 0) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk0 + hash0_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk0 + hash0_length + j + 4) = str[j];
                }
                hash0_length += 8;
                if(hash0_length == 56) {
                    sprintf(str, "%d", s_hash0 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk0 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk0, s_hash0, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk0 = getNewBlockInBuffer(&buf);
                    memset(h_blk0, 0, 64);
                    hash0_length = 0;
                    s_hash0++;
                }
            } else if(tmp_A % 5 == 1) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk1 + hash1_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk1 + hash1_length + j + 4) = str[j];
                }
                hash1_length += 8;
                if(hash1_length == 56) {
                    sprintf(str, "%d", s_hash1 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk1 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk1, s_hash1, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk1 = getNewBlockInBuffer(&buf);
                    memset(h_blk1, 0, 64);
                    hash1_length = 0;
                    s_hash1++;
                }
            } else if(tmp_A % 5 == 2) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk2 + hash2_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk2 + hash2_length + j + 4) = str[j];
                }
                hash2_length += 8;
                if(hash2_length == 56) {
                    sprintf(str, "%d", s_hash2 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk2 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk2, s_hash2, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk2 = getNewBlockInBuffer(&buf);
                    memset(h_blk2, 0, 64);
                    hash2_length = 0;
                    s_hash2++;
                }
            } else if(tmp_A % 5 == 3) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk3 + hash3_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk3 + hash3_length + j + 4) = str[j];
                }
                hash3_length += 8;
                if(hash3_length == 56) {
                    sprintf(str, "%d", s_hash3 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk3 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk3, s_hash3, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk3 = getNewBlockInBuffer(&buf);
                    memset(h_blk3, 0, 64);
                    hash3_length = 0;
                    s_hash3++;
                }
            } else if(tmp_A % 5 == 4) {
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk4 + hash4_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(h_blk4 + hash4_length + j + 4) = str[j];
                }
                hash4_length += 8;
                if(hash4_length == 56) {
                    sprintf(str, "%d", s_hash4 + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(h_blk4 + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(h_blk4, s_hash4, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    count++;
                    h_blk4 = getNewBlockInBuffer(&buf);
                    memset(h_blk4, 0, 64);
                    hash4_length = 0;
                    s_hash4++;
                }
            }
		}
		for(j=0; j<4; j++) {
            str[j] = *(blk1 + 56 + j);
		}
		s_next = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }

    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(h_blk0 + 56 + j) = str[j];
        *(h_blk1 + 56 + j) = str[j];
        *(h_blk2 + 56 + j) = str[j];
        *(h_blk3 + 56 + j) = str[j];
        *(h_blk4 + 56 + j) = str[j];
    }
    if(writeBlockToDisk(h_blk0, s_hash0, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk1, s_hash1, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk2, s_hash2, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk3, s_hash3, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(writeBlockToDisk(h_blk4, s_hash4, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    count += 5;
    printf("Ϊ��ϵ��S��������IO��%d\n", count - tmp_count);
    tmp_count = count;
    r_hash0 = 2000, r_hash1 = 2050, r_hash2 = 2100, r_hash3 = 2150, r_hash4 = 2200;
    s_hash0 = 2300, s_hash1 = 2350, s_hash2 = 2400, s_hash3 = 2450, s_hash4 = 2500;

    // ��ϣͰ��Ӧ���ӣ�������
    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    printf("\n\nhash-join��\n");

    while(r_hash0 != 0) {
        if((blk1 = readBlockFromDisk(r_hash0, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		count++;
		s_hash0 = 2300;
		while(s_hash0 != 0) {
            if((blk2 = readBlockFromDisk(s_hash0, &buf)) == NULL) {
                perror("Reading Block Failed!\n");
            }
            count++;
            for(i=0; i<7; i++) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k);
                }
                tmp_A = atoi(str);
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k + 4);
                }
                tmp_B = atoi(str);
                for(j=0; j<7; j++) {
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k);
                    }
                    tmp_C = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k + 4);
                    }
                    tmp_D = atoi(str);
                    // ���A��C�ÿ�λ��Ϊ�գ�ֱ������
                    if(tmp_C == 0) {
                        break;
                    }
                    // ���д�ش���
                    if(tmp_A == tmp_C) {
                        sprintf(str, "%d", tmp_A);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        result_length += 16;
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C, tmp_D);
                    }
                    // ���д�ش��̿�����
                    if(result_length == 48) {
                        result_length = 0;
                        sprintf(str, "%d", result_blk_location + 1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + 56 + k) = str[k];
                        }
                        if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
                            perror("Writing Block Failed!\n");
                        }
                        count++;
                        result_blk_location++;
                        result_blk = getNewBlockInBuffer(&buf);
                        memset(result_blk, 0, 64);
                    }
                }
                if(tmp_A == 0) {
                    break;
                }
            }
            // ��Ҫ��ȡ��һ��s_next_block
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            s_hash0 = atoi(str);
            freeBlockInBuffer(blk2, &buf);
		}
		// ��Ҫ��ȡ��һ��r_next_block
		for(k=0; k<4; k++) {
            str[k] = *(blk1 + 56 + k);
		}
		r_hash0 = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }

    while(r_hash1 != 0) {
        if((blk1 = readBlockFromDisk(r_hash1, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		count++;
		s_hash1 = 2350;
		while(s_hash1 != 0) {
            if((blk2 = readBlockFromDisk(s_hash1, &buf)) == NULL) {
                perror("Reading Block Failed!\n");
            }
            count++;
            for(i=0; i<7; i++) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k);
                }
                tmp_A = atoi(str);
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k + 4);
                }
                tmp_B = atoi(str);
                for(j=0; j<7; j++) {
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k);
                    }
                    tmp_C = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k + 4);
                    }
                    tmp_D = atoi(str);
                    // ���A��C�ÿ�λ��Ϊ�գ�ֱ������
                    if(tmp_C == 0) {
                        break;
                    }
                    // ���д�ش���
                    if(tmp_A == tmp_C) {
                        sprintf(str, "%d", tmp_A);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        result_length += 16;
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C, tmp_D);
                    }
                    // ���д�ش��̿�����
                    if(result_length == 48) {
                        result_length = 0;
                        sprintf(str, "%d", result_blk_location + 1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + 56 + k) = str[k];
                        }
                        if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
                            perror("Writing Block Failed!\n");
                        }
                        count++;
                        result_blk_location++;
                        freeBlockInBuffer(result_blk, &buf);
                        result_blk = getNewBlockInBuffer(&buf);
                        memset(result_blk, 0, 64);
                    }
                }
                if(tmp_A == 0) {
                    break;
                }
            }
            // ��Ҫ��ȡ��һ��s_next_block
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            s_hash1 = atoi(str);
            freeBlockInBuffer(blk2, &buf);
		}
		// ��Ҫ��ȡ��һ��r_next_block
		for(k=0; k<4; k++) {
            str[k] = *(blk1 + 56 + k);
		}
		r_hash1 = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }

    while(r_hash2 != 0) {
        if((blk1 = readBlockFromDisk(r_hash2, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		count++;
		s_hash2 = 2400;
		while(s_hash2 != 0) {
            if((blk2 = readBlockFromDisk(s_hash2, &buf)) == NULL) {
                perror("Reading Block Failed!\n");
            }
            count++;
            for(i=0; i<7; i++) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k);
                }
                tmp_A = atoi(str);
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k + 4);
                }
                tmp_B = atoi(str);
                for(j=0; j<7; j++) {
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k);
                    }
                    tmp_C = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k + 4);
                    }
                    tmp_D = atoi(str);
                    // ���A��C�ÿ�λ��Ϊ�գ�ֱ������
                    if(tmp_C == 0) {
                        break;
                    }
                    // ���д�ش���
                    if(tmp_A == tmp_C) {
                        sprintf(str, "%d", tmp_A);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        result_length += 16;
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C, tmp_D);
                    }
                    // ���д�ش��̿�����
                    if(result_length == 48) {
                        result_length = 0;
                        sprintf(str, "%d", result_blk_location + 1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + 56 + k) = str[k];
                        }
                        if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
                            perror("Writing Block Failed!\n");
                        }
                        count++;
                        result_blk_location++;
                        result_blk = getNewBlockInBuffer(&buf);
                        memset(result_blk, 0, 64);
                    }
                }
                if(tmp_A == 0) {
                    break;
                }
            }
            // ��Ҫ��ȡ��һ��s_next_block
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            s_hash2 = atoi(str);
            freeBlockInBuffer(blk2, &buf);
		}
		// ��Ҫ��ȡ��һ��r_next_block
		for(k=0; k<4; k++) {
            str[k] = *(blk1 + 56 + k);
		}
		r_hash2 = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }

    while(r_hash3 != 0) {
        if((blk1 = readBlockFromDisk(r_hash3, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		count++;
		s_hash3 = 2450;
		while(s_hash3 != 0) {
            if((blk2 = readBlockFromDisk(s_hash3, &buf)) == NULL) {
                perror("Reading Block Failed!\n");
            }
            count++;
            for(i=0; i<7; i++) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k);
                }
                tmp_A = atoi(str);
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k + 4);
                }
                tmp_B = atoi(str);
                for(j=0; j<7; j++) {
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k);
                    }
                    tmp_C = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k + 4);
                    }
                    tmp_D = atoi(str);
                    // ���A��C�ÿ�λ��Ϊ�գ�ֱ������
                    if(tmp_C == 0) {
                        break;
                    }
                    // ���д�ش���
                    if(tmp_A == tmp_C) {
                        sprintf(str, "%d", tmp_A);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        result_length += 16;
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C, tmp_D);
                    }
                    // ���д�ش��̿�����
                    if(result_length == 48) {
                        result_length = 0;
                        sprintf(str, "%d", result_blk_location + 1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + 56 + k) = str[k];
                        }
                        if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
                            perror("Writing Block Failed!\n");
                        }
                        count++;
                        result_blk_location++;
                        result_blk = getNewBlockInBuffer(&buf);
                        memset(result_blk, 0, 64);
                    }
                }
                if(tmp_A == 0) {
                    break;
                }
            }
            // ��Ҫ��ȡ��һ��s_next_block
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            s_hash3 = atoi(str);
            freeBlockInBuffer(blk2, &buf);
		}
		// ��Ҫ��ȡ��һ��r_next_block
		for(k=0; k<4; k++) {
            str[k] = *(blk1 + 56 + k);
		}
		r_hash3 = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }

    while(r_hash4 != 0) {
        if((blk1 = readBlockFromDisk(r_hash4, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		count++;
		s_hash4 = 2500;
		while(s_hash4 != 0) {
            if((blk2 = readBlockFromDisk(s_hash4, &buf)) == NULL) {
                perror("Reading Block Failed!\n");
            }
            count++;
            for(i=0; i<7; i++) {
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k);
                }
                tmp_A = atoi(str);
                for(k=0; k<4; k++) {
                    str[k] = *(blk1 + 8*i + k + 4);
                }
                tmp_B = atoi(str);
                for(j=0; j<7; j++) {
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k);
                    }
                    tmp_C = atoi(str);
                    for(k=0; k<4; k++) {
                        str[k] = *(blk2 + 8*j + k + 4);
                    }
                    tmp_D = atoi(str);
                    // ���A��C�ÿ�λ��Ϊ�գ�ֱ������
                    if(tmp_C == 0) {
                        break;
                    }
                    // ���д�ش���
                    if(tmp_A == tmp_C) {
                        sprintf(str, "%d", tmp_A);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k) = str[k];
                        }
                        sprintf(str, "%d", tmp_B);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 4) = str[k];
                        }
                        sprintf(str, "%d", tmp_C);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 8) = str[k];
                        }
                        sprintf(str, "%d", tmp_D);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + result_length + k + 12) = str[k];
                        }
                        result_length += 16;
                        printf("A = %d, B = %d, C = %d, D = %d\n", tmp_A, tmp_B, tmp_C, tmp_D);
                    }
                    // ���д�ش��̿�����
                    if(result_length == 48) {
                        result_length = 0;
                        sprintf(str, "%d", result_blk_location + 1);
                        for(k=0; k<strlen(str); k++) {
                            *(result_blk + 56 + k) = str[k];
                        }
                        if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
                            perror("Writing Block Failed!\n");
                        }
                        count++;
                        result_blk_location++;
                        result_blk = getNewBlockInBuffer(&buf);
                        memset(result_blk, 0, 64);
                    }
                }
                if(tmp_A == 0) {
                    break;
                }
            }
            // ��Ҫ��ȡ��һ��s_next_block
            for(k=0; k<4; k++) {
                str[k] = *(blk2 + 56 + k);
            }
            s_hash4 = atoi(str);
            freeBlockInBuffer(blk2, &buf);
		}
		// ��Ҫ��ȡ��һ��r_next_block
		for(k=0; k<4; k++) {
            str[k] = *(blk1 + 56 + k);
		}
		r_hash4 = atoi(str);
		freeBlockInBuffer(blk1, &buf);
    }
    sprintf(str, "%d", 0);
    for(k=0; k<strlen(str); k++) {
        *(result_blk + 56 + k) = str[k];
    }
    if(writeBlockToDisk(result_blk, result_blk_location, &buf) != 0){
        perror("Writing Block Failed!\n");
    }
    printf("hash-join IO: %d\n", count - tmp_count);
}

// B+ tree
// index-select
void index_select() {
    Buffer buf;
    unsigned char *blk;
    int i, j;
    int tmp_A, tmp_B;
    char str[4];
    int r_next = 200;

    unsigned char *leaf_blk; // ����B+������ʱҶ�ӽڵ����������
    unsigned char *blk1; // ����B+������ʱ�м�ڵ㣨�͸��ڵ㣩����������
    /*unsigned char *blk2;*/
    int leaf_length = 0, blk1_length = 0/*, blk2_length = 0*/;
    int leaf_location = 3000;
    int blk1_location = 4000;
    /*int blk2_location = 5000;*/ //������A��C�Ͻ�����ʱ��һ���ڵ��6��������ʱ�������㹻
    int max = 0; // ����B������ʱ������¼��ǰ���������ֵ

    unsigned char *result_blk;
    int result_length;
    int result_location = 500;

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    // ����b+������
    // ÿ����������������Ϊ4���������ı�ʾ��ʽΪ������+��һ�γ���ʱ���ڿ�ı��
    // ʲôʱ����ѣ�
    // ����Ԫ�ؽ���ʱ�������ǰҶ�ڵ����ˣ�����Ҫ���ѣ��÷��ѿ��ܻᵼ���м�ڵ����ڵ�ķ���
    leaf_blk = getNewBlockInBuffer(&buf);
    blk1 = getNewBlockInBuffer(&buf);
    /*blk2 = getNewBlockInBuffer(&buf);*/
    memset(leaf_blk, 0, 64);
    memset(blk1, 0, 64);
    /*memset(blk2, 0, 64);*/

    while(r_next != 0) {
        if((blk = readBlockFromDisk(r_next, &buf)) == NULL) {
			perror("Reading Block Failed!\n");
		}
		for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_A = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j + 4);
            }
            tmp_B = atoi(str);

            // �жϸ�Ԫ���Ƿ�Ӧ�÷�������
            if(tmp_A > max) {
                max = tmp_A;
                // ��Ԫ�ؽ��룬��Ҫ�жϵ�ǰҶ�ڵ��Ƿ������ģ�4�������
                // ���������ֱ��д�뵱ǰҶ�ڵ㼴��
                if(leaf_length < 48) {
                    sprintf(str, "%d", tmp_A);
                    for(j=0; j<strlen(str); j++) {
                        *(leaf_blk + leaf_length + j) = str[j];
                    }
                    sprintf(str, "%d", r_next);
                    for(j=0; j<strlen(str); j++) {
                        *(leaf_blk + leaf_length + j + 4) = str[j];
                    }
                    leaf_length += 8;
                } else {
                    // ������ˣ����Ƚ���ǰ����Ҷ�ڵ�д����̣�Ȼ�����µ�Ҷ�ڵ㣬����Ԫ�ط���
                    // ��Ҷ�ڵ�д�����
                    sprintf(str, "%d", leaf_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(leaf_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(leaf_blk, leaf_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    // �����µ�Ҷ�ڵ�
                    leaf_blk = getNewBlockInBuffer(&buf);
                    memset(leaf_blk, 0, 64);
                    leaf_length = 0;
                    leaf_location++;
                    // ����Ԫ�ط���
                    sprintf(str, "%d", tmp_A);
                    for(j=0; j<strlen(str); j++) {
                        *(leaf_blk + leaf_length + j) = str[j];
                    }
                    sprintf(str, "%d", r_next);
                    for(j=0; j<strlen(str); j++) {
                        *(leaf_blk + leaf_length + j + 4) = str[j];
                    }
                    leaf_length += 8;
                    // �����µ�Ҷ�ڵ����Ҫ�����м�ڵ�
                    if(blk1_length == 0) {
                        sprintf(str, "%d", leaf_location - 1);
                        for(j=0; j<strlen(str); j++) {
                            *(blk1 + j) = str[j];
                        }
                        sprintf(str, "%d", tmp_A);
                        for(j=0; j<strlen(str); j++) {
                            *(blk1 + 4 + j) = str[j];
                        }
                        sprintf(str, "%d", leaf_location);
                        for(j=0; j<strlen(str); j++) {
                            *(blk1 + 8 + j) = str[j];
                        }
                        blk1_length = 12;
                    } else {
                        sprintf(str, "%d", tmp_A);
                        for(j=0; j<strlen(str); j++) {
                            *(blk1 + blk1_length + j) = str[j];
                        }
                        sprintf(str, "%d", leaf_location);
                        for(j=0; j<strlen(str); j++) {
                            *(blk1 + blk1_length + j + 4) = str[j];
                        }
                        blk1_length += 8;
                    }
                }
            }
		}
		for(i=0; i<4; i++) {
            str[i] = *(blk + 56 + i);
		}
		r_next = atoi(str);
		freeBlockInBuffer(blk, &buf);
    }

    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(leaf_blk + 56 + j) = str[j];
    }
    if(writeBlockToDisk(leaf_blk, leaf_location, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    for(j=0; j<strlen(str); j++) {
        *(blk1 + 56 + j) = str[j];
    }
    if(writeBlockToDisk(blk1, blk1_location, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }

    if(!initBuffer(520, 64, &buf)) {
        perror("Buffer Initialization Failed!\n");
    }

    result_blk = getNewBlockInBuffer(&buf);
    memset(result_blk, 0, 64);
    result_length = 0;
    printf("\n\nB������������\n");

    int location = blk1_location;
    if((blk = readBlockFromDisk(location, &buf)) == NULL) {
        perror("Reading Block Failed!\n");
    }

    for(i=0; i<6; i++) {
        for(j=0; j<4; j++) {
            str[j] = *(blk + 4 + 8*i + j);
        }
        tmp_A = atoi(str);
        if(tmp_A < 40) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8 + 8*i + j);
            }
            location = atoi(str);
        }
        if(tmp_A >= 40) {
            break;
        }
    }

    freeBlockInBuffer(blk, &buf);
    if((blk = readBlockFromDisk(location, &buf)) == NULL) {
        perror("Reading Block Failed!\n");
    }

    for(i=0; i<7; i++) {
        for(j=0; j<4; j++) {
            str[j] = *(blk + 8*i + j);
        }
        tmp_A = atoi(str);
        if(tmp_A == 40) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j + 4);
            }
            location = atoi(str);
            break;
        }
    }
    freeBlockInBuffer(blk, &buf);

    int flag = 0;
    while(location != 0) {
        if((blk = readBlockFromDisk(location, &buf)) == NULL) {
            perror("Reading Block Failed!\n");
        }
        for(i=0; i<7; i++) {
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j);
            }
            tmp_A = atoi(str);
            for(j=0; j<4; j++) {
                str[j] = *(blk + 8*i + j + 4);
            }
            tmp_B = atoi(str);
            if(tmp_A == 40) {
                flag = 1;
                printf("A = %d, B = %d\n", tmp_A, tmp_B);
                sprintf(str, "%d", tmp_A);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + result_length + j) = str[j];
                }
                sprintf(str, "%d", tmp_B);
                for(j=0; j<strlen(str); j++) {
                    *(result_blk + result_length + j + 4) = str[j];
                }
                result_length += 8;
                if(result_length == 56) {
                    sprintf(str, "%d", result_location + 1);
                    for(j=0; j<strlen(str); j++) {
                        *(result_blk + 56 + j) = str[j];
                    }
                    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
                        perror("Writing Block Failed!\n");
                    }
                    result_blk = getNewBlockInBuffer(&buf);
                    memset(result_blk, 0, 64);
                    result_length = 0;
                    result_location++;
                }
            } else {
                if(flag == 1) {
                    flag = 0;
                }
            }
        }
        for(j=0; j<4; j++) {
            str[j] = *(blk + 56 + j);
        }
        location = atoi(str);
        freeBlockInBuffer(blk, &buf);
        if(flag == 0) {
            break;
        }
    }
    sprintf(str, "%d", 0);
    for(j=0; j<strlen(str); j++) {
        *(result_blk + 56 + j) = str[j];
    }
    if(writeBlockToDisk(result_blk, result_location, &buf) != 0) {
        perror("Writing Block Failed!\n");
    }
    printf("B-Tree index IO: %ld\n", buf.numIO);
}
