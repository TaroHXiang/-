#include <iostream>
#include <ctime>
using namespace std;

int main() {
    int n;
    cout << "Input n:";
    cin >> n;

    // �ڴ�������ʼ��
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    // ���ܲ��Ա���
    float seconds;
    clock_t start, finish;
    long counter = 0;
    start = clock();

    // չ���Ż�����
    int sum = 0;
    const int UNROLL_FACTOR = 8;  // 8·չ��
    int partial_sums[UNROLL_FACTOR] = { 0 };

    while (clock() - start < 5) {  // 5����Դ���
        counter++;
        sum = 0;
        // ���ò��ֺ�����
        for (int k = 0; k < UNROLL_FACTOR; k++) {
            partial_sums[k] = 0;
        }

        // ��ѭ����8·չ����
        int i = 0;
        for (; i <= n - UNROLL_FACTOR; i += UNROLL_FACTOR) {
            partial_sums[0] += a[i];
            partial_sums[1] += a[i + 1];
            partial_sums[2] += a[i + 2];
            partial_sums[3] += a[i + 3];
            partial_sums[4] += a[i + 4];
            partial_sums[5] += a[i + 5];
            partial_sums[6] += a[i + 6];
            partial_sums[7] += a[i + 7];
        }

        // ����ʣ��Ԫ�أ�n % UNROLL_FACTOR��
        for (; i < n; i++) {
            partial_sums[0] += a[i];
        }

        // �ϲ����ֺ�
        for (int k = 0; k < UNROLL_FACTOR; k++) {
            sum += partial_sums[k];
        }

        // �������
        finish = clock();
        seconds = (finish - start) / float(CLOCKS_PER_SEC);
        cout << "Size:" << n
            << " Executions:" << counter
            << " Runtime:" << seconds
            << " Per-run:" << seconds / counter << endl;
    }

    delete[] a;
    return 0;
}