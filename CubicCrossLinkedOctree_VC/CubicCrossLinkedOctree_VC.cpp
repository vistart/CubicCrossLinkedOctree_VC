// CubicCrossLinkedOctree_VC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
//
#include "PlyFile.h"
#include "CubicCrossLinkedOctree.h"
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid File Path!" << endl;
		return 0;
	}
	string file_path(argv[1]);

	// This statement (construct the PlyFile) will read the ply file.
	cout << "Reading the ply file: " << file_path << endl;
	const auto plyfile = make_shared<PlyFile>(file_path);
	cout << endl;
	
    const auto point_list = plyfile->GetPointList();
    cout << "The last point is: " << point_list->GetPoints()->back() << endl;

	cout << "Construct the Octree of Point Cloud: " << endl;
    CubicCrossLinkedOctree<PlyVertexList, PlyVertex, PlyFile> octree(point_list);
    //cout << "Hello World!\n";
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
