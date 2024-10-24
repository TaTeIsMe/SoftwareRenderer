#include "TestCube.h"


TestCube::TestCube(int Length,SDL_Surface* texture) {
	Vertex3 test1;
	test1.x = Length;
	test1.y = -Length;
	test1.z = -Length;

	Vertex3 test2;
	test2.x = -Length;
	test2.y = -Length;
	test2.z = -Length;

	Vertex3 test3;
	test3.x = -Length;
	test3.y = Length;
	test3.z = -Length;

	Vertex3 test4;
	test4.x = Length;
	test4.y = Length;
	test4.z = -Length;

	Vertex3 test5;
	test5.x = Length;
	test5.y = -Length;
	test5.z = Length;

	Vertex3 test6;
	test6.x = -Length;
	test6.y = -Length;
	test6.z = Length;

	Vertex3 test7;
	test7.x = -Length;
	test7.y = Length;
	test7.z = Length;

	Vertex3 test8;
	test8.x = Length;
	test8.y = Length;
	test8.z = Length;

	Triangle3D CubeTri1, CubeTri2, CubeTri3, CubeTri4, CubeTri5, CubeTri6, CubeTri7, CubeTri8, CubeTri9, CubeTri10, CubeTri11, CubeTri12;
	CubeTri1[0] = test1; CubeTri1[1] = test2; CubeTri1[2] = test3;
	CubeTri2[0] = test1; CubeTri2[1] = test3; CubeTri2[2] = test4;
	CubeTri3[0] = test4; CubeTri3[1] = test1; CubeTri3[2] = test5;
	CubeTri4[0] = test8; CubeTri4[1] = test4; CubeTri4[2] = test5;
	CubeTri5[0] = test7; CubeTri5[1] = test8; CubeTri5[2] = test5;
	CubeTri6[0] = test7; CubeTri6[1] = test6; CubeTri6[2] = test5;
	CubeTri7[0] = test7; CubeTri7[1] = test6; CubeTri7[2] = test3;
	CubeTri8[0] = test2; CubeTri8[1] = test6; CubeTri8[2] = test3;
	CubeTri9[0] = test3; CubeTri9[1] = test4; CubeTri9[2] = test7;
	CubeTri10[0] = test8; CubeTri10[1] = test4; CubeTri10[2] = test7;
	CubeTri11[0] = test2; CubeTri11[1] = test1; CubeTri11[2] = test6;
	CubeTri12[0] = test5; CubeTri12[1] = test1; CubeTri12[2] = test6;
	CubeTri1.normal = Vector3(0, 0, -1);
	CubeTri2.normal = Vector3(0, 0, -1);
	CubeTri3.normal = Vector3(1, 0, 0);
	CubeTri4.normal = Vector3(1, 0, 0);
	CubeTri5.normal = Vector3(0, 0, 1);
	CubeTri6.normal = Vector3(0, 0, 1);
	CubeTri7.normal = Vector3(-1, 0, 0);
	CubeTri8.normal = Vector3(-1, 0, 0);
	CubeTri9.normal = Vector3(0, 1, 0);
	CubeTri10.normal = Vector3(0, 1, 0);
	CubeTri11.normal = Vector3(0, -1, 0);
	CubeTri12.normal = Vector3(0, -1, 0);

	CubeTri1.vertices[0].u = 1;
	CubeTri1.vertices[0].v = 0;
	CubeTri1.vertices[1].u = 0;
	CubeTri1.vertices[1].v = 0;
	CubeTri1.vertices[2].u = 0;
	CubeTri1.vertices[2].v = 1;
	CubeTri2.vertices[0].u = 1;
	CubeTri2.vertices[0].v = 0;
	CubeTri2.vertices[1].u = 0;
	CubeTri2.vertices[1].v = 1;
	CubeTri2.vertices[2].u = 1;
	CubeTri2.vertices[2].v = 1;

	CubeTri3.vertices[0].u = 0;
	CubeTri3.vertices[0].v = 1;
	CubeTri3.vertices[1].u = 0;
	CubeTri3.vertices[1].v = 0;
	CubeTri3.vertices[2].u = 1;
	CubeTri3.vertices[2].v = 0;
	CubeTri4.vertices[0].u = 1;
	CubeTri4.vertices[0].v = 1;
	CubeTri4.vertices[1].u = 0;
	CubeTri4.vertices[1].v = 1;
	CubeTri4.vertices[2].u = 1;
	CubeTri4.vertices[2].v = 0;

	CubeTri5.vertices[0].u = 1;
	CubeTri5.vertices[0].v = 1;
	CubeTri5.vertices[1].u = 0;
	CubeTri5.vertices[1].v = 1;
	CubeTri5.vertices[2].u = 0;
	CubeTri5.vertices[2].v = 0;
	CubeTri6.vertices[0].u = 1;
	CubeTri6.vertices[0].v = 1;
	CubeTri6.vertices[1].u = 1;
	CubeTri6.vertices[1].v = 0;
	CubeTri6.vertices[2].u = 0;
	CubeTri6.vertices[2].v = 0;

	CubeTri7.vertices[0].u = 0;
	CubeTri7.vertices[0].v = 1;
	CubeTri7.vertices[1].u = 0;
	CubeTri7.vertices[1].v = 0;
	CubeTri7.vertices[2].u = 1;
	CubeTri7.vertices[2].v = 1;
	CubeTri8.vertices[0].u = 0;
	CubeTri8.vertices[0].v = 1;
	CubeTri8.vertices[1].u = 0;
	CubeTri8.vertices[1].v = 0;
	CubeTri8.vertices[2].u = 1;
	CubeTri8.vertices[2].v = 1;

	CubeTri9.vertices[0].u = 0;
	CubeTri9.vertices[0].v = 0;
	CubeTri9.vertices[1].u = 1;
	CubeTri9.vertices[1].v = 0;
	CubeTri9.vertices[2].u = 0;
	CubeTri9.vertices[2].v = 1;
	CubeTri10.vertices[0].u = 1;
	CubeTri10.vertices[0].v = 1;
	CubeTri10.vertices[1].u = 1;
	CubeTri10.vertices[1].v = 0;
	CubeTri10.vertices[2].u = 0;
	CubeTri10.vertices[2].v = 1;

	CubeTri11.vertices[0].u = 0;
	CubeTri11.vertices[0].v = 0;
	CubeTri11.vertices[1].u = 1;
	CubeTri11.vertices[1].v = 0;
	CubeTri11.vertices[2].u = 0;
	CubeTri11.vertices[2].v = 1;
	CubeTri12.vertices[0].u = 1;
	CubeTri12.vertices[0].v = 1;
	CubeTri12.vertices[1].u = 1;
	CubeTri12.vertices[1].v = 0;
	CubeTri12.vertices[2].u = 0;
	CubeTri12.vertices[2].v = 1;

	CubeTri1.texture = texture;
	CubeTri2.texture = texture;
	CubeTri3.texture = texture;
	CubeTri4.texture = texture;
	CubeTri5.texture = texture;
	CubeTri6.texture = texture;
	CubeTri7.texture = texture;
	CubeTri8.texture = texture;
	CubeTri9.texture = texture;
	CubeTri10.texture = texture;
	CubeTri11.texture = texture;
	CubeTri12.texture = texture;
	shape = { CubeTri1, CubeTri2, CubeTri3, CubeTri4, CubeTri5, CubeTri6, CubeTri7, CubeTri8, CubeTri9, CubeTri10, CubeTri11, CubeTri12 };

	position.z = 1500;
	position.x = -100;
}