#include <stdio.h>

int main () {

	FILE *fface = fopen ("faces.txt", "r");
	FILE *fvert = fopen ("vertices.txt", "r");

	float v[1000][3];


	int a, b, c;
	int i;

	for (i=0; i<190; i++) {
		fscanf (fvert, "%f %f %f ", &v[i][0], &v[i][1], &v[i][2]);
	}

	for (i=0; i<375; i++) {
		fscanf (fface, "%i %i %i", &a, &b, &c);
		printf ("%e, %e, %e,\n", v[a][0], v[a][2], v[a][1]);
		printf ("%e, %e, %e,\n", v[b][0], v[b][2], v[b][1]);
		printf ("%e, %e, %e,\n", v[c][0], v[c][2], v[c][1]);
	}

	fscanf (fface, "%i %i %i", &a, &b, &c);
	printf ("%e, %e, %e,\n", v[a][0], v[a][2], v[a][1]);
	printf ("%e, %e, %e,\n", v[b][0], v[b][2], v[b][1]);
	printf ("%e, %e, %e", v[c][0], v[c][2], v[c][1]);
	
	fclose (fface);
	fclose (fvert);

	return 1;
}
