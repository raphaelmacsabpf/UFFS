#include <stdio.h>

struct S_Topology {
	int a;
	int b;
};

struct S_Traffic {
	int a;
	int b;
	int load;
};

struct S_Topology G_Topology[10];
struct S_Traffic G_Traffic[10];


int main() {
	G_Topology[0].a = 1;
	G_Topology[0].b = 2;

	G_Topology[0].a = 2;
	G_Topology[0].b = 3;

	G_Topology[0].a = 1;
	G_Topology[0].b = 2;

	G_Topology[0].a = 2;
	G_Topology[0].b = 4;

	G_Topology[0].a = 1;
	G_Topology[0].b = 2;
	G_Traffic[0].a = 1;
	G_Traffic[0].b = 2;
	G_Traffic[0].load = 5;
	G_Traffic[1].a = 1;
	G_Traffic[1].b = 3;
	G_Traffic[1].load = 10;
	return 1;
}