//Given four color images, enhance the four color images in the RGB, HSI, and L*a*b* color spaces. 
//image name is  aloe.jpg chruch.jpg house.jpg kitchen.jpg
//By HKK 2015/12/22
#include <stdio.h>
#include <stdlib.h>
//#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
static int x = 0;
static int y = 200;
int print_image(char* name, Mat image, int row, int col);

//RGB
double R_box[752][768];
double G_box[752][768];
double B_box[752][768];
//HSI
double H_box[752][768];
double S_box[752][768];
double I_box[752][768];
//LAB
double L_box[752][768];
double A_box[752][768];
double B2_box[752][768];

double min_RGB(double R, double G, double B)
{
	double min = R;
	if (G < min)	min = G;
	else if (B < min) min = B;
	return min;
}

//RGB to HSI
void RGB_to_HSI(Mat image, Mat HSI_B, Mat HSI_G, Mat HSI_R)
{
	for (int j = 0; j < HSI_B.cols; j++)
	{
		for (int i = 0; i < HSI_B.rows; i++)
		{
			//double BGR
			double nor_B, nor_G, nor_R, theta = 0.0;
			double nor_H = 0.0, nor_S = 0.0, nor_I = 0.0;
			double min = 0.0;
			//double BGR value
			nor_B = (double)HSI_B.at<uchar>(i, j) / 255.0;
			nor_G = (double)HSI_G.at<uchar>(i, j) / 255.0;
			nor_R = (double)HSI_R.at<uchar>(i, j) / 255.0;


			theta = acos((0.5 * ((nor_R - nor_G) + (nor_R - nor_B))) / (sqrt(pow(nor_R - nor_G, 2) + ((nor_R - nor_B) * (nor_G - nor_B)))));
			//H
			if (nor_B <= nor_G)
				nor_H = (theta / 3.1415926) * 180;
			else if (nor_B > nor_G)
				nor_H = 360.0 - (theta / 3.1415926) * 180;
			//S
			min = min_RGB(nor_B, nor_G, nor_R);
			nor_S = 1.0 - (3.0 * min) / (nor_R + nor_B + nor_G);
			//I
			nor_I = (nor_R + nor_B + nor_G) / 3.0;
			if (nor_H < 0 || (nor_R == nor_G && nor_G == nor_B))
				nor_H = 0;

			//save into mat 
			HSI_B.at<uchar>(i, j) = (int)nor_H;
			HSI_G.at<uchar>(i, j) = (int)(nor_S * 255.0);
			HSI_R.at<uchar>(i, j) = (int)(nor_I * 255.0);
		}
	}
}

//HSI to RGB
void HSI_to_RGB(Mat image, Mat HSI_H, Mat HSI_S, Mat HSI_I)
{
	for (int i = 0; i < HSI_H.rows; i++)
	{
		for (int j = 0; j < HSI_H.cols; j++)
		{
			//double BGR
			double nor_B = 0.0, nor_G = 0.0, nor_R = 0.0, theta = 0.0;
			double nor_H = 0.0, nor_S = 0.0, nor_I = 0.0;

			//double HSI value
			nor_H = (double)HSI_H.at<uchar>(i, j);
			nor_S = (double)HSI_S.at<uchar>(i, j) / 255.0;
			nor_I = (double)HSI_I.at<uchar>(i, j) / 255.0;


			//theta = acos((0.5*((nor_R - nor_G) + (nor_R - nor_B))) / (sqrt(pow(nor_R - nor_G, 2) + ((nor_R - nor_B)*(nor_G - nor_B)))));

			//if 0 < H < 120
			if (nor_H >= 0.0 && nor_H < 120.0)
			{
				//R
				nor_R = nor_I * (1.0 + (nor_S * cos(nor_H / 180.0 * 3.1415926) / cos((60.0 - nor_H) / 180 * 3.1415926)));
				//G
				nor_G = 3.0 * nor_I - (nor_R + nor_B);
				//B
				nor_B = nor_I * (1.0 - nor_S);
			}
			//if 120 <= H < 240
			else if (nor_H >= 120.0 && nor_H < 240.0)
			{
				//H
				nor_H = nor_H - 120.0;
				//R
				nor_R = nor_I * (1.0 - nor_S);
				//G
				nor_G = nor_I * (1.0 + (nor_S * cos(nor_H / 180.0 * 3.1415926) / cos((60.0 - nor_H) / 180 * 3.1415926)));
				//B
				nor_B = 3.0 * nor_I - (nor_R + nor_G);
			}
			//if 240 <= H <= 360
			else if (nor_H >= 240.0 && nor_H <= 360.0)
			{
				//H
				nor_H = nor_H - 240.0;
				//R
				nor_R = 3.0 * nor_I - (nor_G + nor_B);
				//G
				nor_G = nor_I * (1.0 - nor_S);
				//B
				nor_B = nor_I * (1.0 + (nor_S * cos(nor_H / 180.0 * 3.1415926) / cos((60.0 - nor_H) / 180 * 3.1415926)));
			}

			nor_R = nor_R * 255.0;
			if (nor_R > 255.0)
				nor_R = 255.0;
			else if (nor_R < 0.0)
				nor_R = 0.0;

			nor_G = nor_G * 255.0;
			if (nor_G > 255.0)
				nor_G = 255.0;
			else if (nor_G < 0.0)
				nor_G = 0.0;

			nor_B = nor_B * 255.0;
			if (nor_B > 255.0)
				nor_B = 255.0;
			else if (nor_B < 0.0)
				nor_B = 0.0;

			//save in mat 
			HSI_H.at<uchar>(i, j) = (int)nor_B;
			HSI_S.at<uchar>(i, j) = (int)nor_G;
			HSI_I.at<uchar>(i, j) = (int)nor_R;

			//printf("%f\n", B_box[i][j]);
		}
	}
}

//RGB to L*a*b
void RGB_to_Lab(Mat image, Mat LAB_B, Mat LAB_G, Mat LAB_R)
{
	for (int j = 0; j < LAB_B.cols; j++)
	{
		for (int i = 0; i < LAB_B.rows; i++)
		{
			//double BGR
			double nor_B = 0.0, nor_G = 0.0, nor_R = 0.0;
			//double XYZ
			double X = 0.0, Y = 0.0, Z = 0.0;
			//double lab
			double nor_L = 0.0, nor_A = 0.0, nor_B1 = 0.0;
			//double BGR value
			nor_B = (double)LAB_B.at<uchar>(i, j) / 255.0;
			nor_G = (double)LAB_G.at<uchar>(i, j) / 255.0;
			nor_R = (double)LAB_R.at<uchar>(i, j) / 255.0;

			if (nor_R > 0.04045)
				nor_R = pow((nor_R + 0.055) / 1.055, 2.4);
			else
				nor_R = nor_R / 12.92;

			if (nor_G > 0.04045)
				nor_G = pow((nor_G + 0.055) / 1.055, 2.4);
			else
				nor_G = nor_G / 12.92;

			if (nor_B > 0.04045)
				nor_B = pow((nor_B + 0.055) / 1.055, 2.4);
			else
				nor_B = nor_B / 12.92;

			nor_R = nor_R * 100.0;
			nor_G = nor_G * 100.0;
			nor_B = nor_B * 100.0;

			X = nor_R * 0.4124 + nor_G * 0.3576 + nor_B * 0.1805;
			Y = nor_R * 0.2126 + nor_G * 0.7152 + nor_B * 0.0722;
			Z = nor_R * 0.0193 + nor_G * 0.1192 + nor_B * 0.9505;

			X = X / 95.047;
			Y = Y / 100.000;
			Z = Z / 108.883;

			if (X > 0.008856)
				X = pow(X, (double)(1.0 / 3.0));
			else
				X = (7.787 * X) + (double)(16.0 / 116.0);

			if (Y > 0.008856)
				Y = pow(Y, (double)(1.0 / 3.0));
			else
				Y = (7.787 * Y) + (double)(16.0 / 116.0);

			if (Z > 0.008856)
				Z = pow(Z, (double)(1.0 / 3.0));
			else
				Z = (7.787 * Z) + (double)(16.0 / 116.0);

			nor_L = (116.0 * Y) - 16.0;
			nor_A = 500.0 * (X - Y);
			nor_B1 = 200.0 * (Y - Z);

			//save into mat 
			LAB_B.at<uchar>(i, j) = (int)(nor_L * 255.0 / 100.0);
			LAB_G.at<uchar>(i, j) = (int)(nor_A);
			LAB_R.at<uchar>(i, j) = (int)(nor_B1);
		}
	}

}

//L*a*b to RGB
void Lab_to_RGB(Mat image, Mat LAB_L, Mat LAB_A, Mat LAB_B)
{
	for (int i = 0; i < LAB_L.rows; i++)
		for (int j = 0; j < LAB_L.cols; j++)
			LAB_L.at<uchar>(i, j) = LAB_L.at<uchar>(i, j) * 100.0 / 255.0;
	for (int i = 0; i < LAB_L.rows; i++)
	{
		for (int j = 0; j < LAB_L.cols; j++)
		{
			//double BGR
			double nor_B = 0.0, nor_G = 0.0, nor_R = 0.0;
			//double XYZ
			double X = 0.0, Y = 0.0, Z = 0.0;
			//double lab
			double nor_L = 0.0, nor_A = 0.0, nor_B1 = 0.0;

			nor_L = (double)LAB_L.at<uchar>(i, j);
			nor_A = (double)LAB_A.at<uchar>(i, j);
			nor_B1 = (double)LAB_B.at<uchar>(i, j);

			Y = (nor_L + 16.0) / 116.0;
			X = nor_A / 500.0 + Y;
			Z = Y - nor_B1 / 200.0;

			if (pow(Y, 3) > 0.008856)
				Y = pow(Y, 3);
			else
				Y = (Y - 16.0 / 116.0) / 7.787;

			if (pow(X, 3) > 0.008856)
				X = pow(X, 3);
			else
				X = (X - 16.0 / 116.0) / 7.787;

			if (pow(Z, 3) > 0.008856)
				Z = pow(Z, 3);
			else
				Z = (Z - 16.0 / 116.0) / 7.787;

			X = X * 95.047;
			Y = Y * 100.000;
			Z = Z * 108.883;

			X = X / 100.0;
			Y = Y / 100.0;
			Z = Z / 100.0;

			nor_R = X * 3.2406 + Y * -1.5372 + Z * -0.4986;
			nor_G = X * -0.9689 + Y * 1.8758 + Z * 0.0415;
			nor_B = X * 0.0557 + Y * -0.2040 + Z * 1.0570;

			if (nor_R > 0.0031308)
				nor_R = 1.055 * pow(nor_R, (double)(1.0 / 2.4)) - 0.055;
			else
				nor_R = 12.92 * nor_R;

			if (nor_G > 0.0031308)
				nor_G = 1.055 * pow(nor_G, (double)(1.0 / 2.4)) - 0.055;
			else
				nor_G = 12.92 * nor_G;

			if (nor_B > 0.0031308)
				nor_B = 1.055 * pow(nor_B, (double)(1.0 / 2.4)) - 0.055;
			else
				nor_B = 12.92 * nor_B;

			nor_B = nor_B * 255.0;
			if (nor_B > 255.0)
				nor_B = 255.0;
			else if (nor_B < 0.0)
				nor_B = 0.0;

			nor_G = nor_G * 255.0;
			if (nor_G > 255.0)
				nor_G = 255.0;
			else if (nor_G < 0.0)
				nor_G = 0.0;

			nor_R = nor_R * 255.0;
			if (nor_R > 255.0)
				nor_R = 255.0;
			else if (nor_R < 0.0)
				nor_R = 0.0;

			//save into mat 
			LAB_L.at<uchar>(i, j) = (int)nor_B;
			LAB_A.at<uchar>(i, j) = (int)nor_G;
			LAB_B.at<uchar>(i, j) = (int)nor_R;

		}
	}
}

//histogram
void histogram(Mat image)
{
	Mat meta;
	double LUT[256];
	int PDF[256];
	int CDF[256];
	double min = 0.0;
	double max = 0.0;
	meta = image.clone();
	for (int k = 0; k < 256; k++)
		PDF[k] = 0;
	for (int j = 0; j < meta.cols; j++)
		for (int i = 0; i < meta.rows; i++)
			PDF[meta.at<uchar>(i, j)]++;

	CDF[0] = PDF[0];
	for (int i = 1; i < 256; i++)
		CDF[i] = CDF[i - 1] + PDF[i];


	min = (double)CDF[0];
	max = (double)CDF[255];
	for (int i = 0; i < 256; i++)
		LUT[i] = 255.0 * (((double)CDF[i] - min) / (max - min));

	for (int j = 0; j < meta.cols; j++)
		for (int i = 0; i < meta.rows; i++)
			image.at<uchar>(i, j) = (int)(LUT[meta.at<uchar>(i, j)]);

}
//print image
int print_image(char* name, Mat image, int row, int col)
{
	int addr = 0;
	namedWindow(name, 0);
	moveWindow(name, x + addr, y);

	imshow(name, image);
	resizeWindow(name, row * 0.6, col * 0.6);
	waitKey(1);
	x = x + 400;
	return 0;
}

int color_image_enhancemoent(char* name)
{
	//define varible
	Mat source, rgb, hsi, lab;
	//Mat R, G, B;
	Mat RGB[3];
	Mat HSI[3];
	Mat LAB[3];
	int row = 0;
	int col = 0;
	char str_source[7] = "Source";
	char str_RGB[4] = "RGB";
	char str_HSI[4] = "HSI";
	char str_Lab[7] = "L*a*b*";

	//image read
	source = imread(name, 1);
	row = source.rows;
	col = source.cols;
	rgb = source.clone();
	hsi = source.clone();
	lab = source.clone();

	//RGB histogram
	split(rgb, RGB);
	histogram(RGB[0]);//B
	histogram(RGB[1]);//G
	histogram(RGB[2]);//R
	merge(RGB, 3, rgb);

	//HSI
	split(hsi, HSI);
	RGB_to_HSI(hsi, HSI[0], HSI[1], HSI[2]);
	histogram(HSI[1]);
	histogram(HSI[2]);
	HSI_to_RGB(hsi, HSI[0], HSI[1], HSI[2]);
	merge(HSI, 3, hsi);

	//LAB
	split(lab, LAB);
	RGB_to_Lab(lab, LAB[0], LAB[1], LAB[2]);
	histogram(LAB[0]);
	Lab_to_RGB(lab, LAB[0], LAB[1], LAB[2]);
	merge(LAB, 3, lab);

	//print
	print_image(str_source, source, row, col);
	print_image(str_RGB, rgb, row, col);
	print_image(str_HSI, hsi, row, col);
	print_image(str_Lab, lab, row, col);


	return 0;
}

int main()
{
	char str_aloe[9] = "aloe.jpg";
	char str_church[11] = "church.jpg";
	char str_house[11] = "house.jpg";
	char str_kitchen[12] = "kitchen.jpg";
	color_image_enhancemoent(str_aloe);
	printf("按Enter 到下一張\n");
	getchar();
	destroyAllWindows();
	system("cls");
	x = 0;
	color_image_enhancemoent(str_church);
	printf("按Enter 到下一張\n");
	getchar();
	destroyAllWindows();
	system("cls");
	x = 0;
	color_image_enhancemoent(str_house);
	printf("按Enter 到下一張\n");
	getchar();
	destroyAllWindows();
	system("cls");
	x = 0;
	color_image_enhancemoent(str_kitchen);
	printf("按Enter 結束\n");
	getchar();
	destroyAllWindows();

	return 0;
}