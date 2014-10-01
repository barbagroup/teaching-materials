/* B = A^t */

#define L (1<<11)

float a[L][L], b[L][L];

int main(void) {
	unsigned int i=0, j=0;
	for (i=0; i<L; ++i)
			for (j=0; j<L; ++j)
				b[j][i] = a[i][j];
	return (int)b[(int)b[0][2]][(int)b[2][0]];
}
