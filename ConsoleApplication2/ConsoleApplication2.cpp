#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>


int main()
{ 
   
   setlocale(LC_ALL, "Russian");
   cv::Mat image = cv::imread("D:/virandfpc/vir/ConsoleApplication2/wpnD7_nFsU.jpg");
   cv::Mat img_show = image.clone();
   if (image.empty()) {
      std::cout << "Ошибка загрузки изображения" << std::endl;
      return -1;
   }

   cv::Mat grayImage;
   cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

   cv::Mat gauss;
   cv::GaussianBlur(grayImage, gauss, cv::Size(5, 5), 0);

   std::vector<cv::Vec4i> lines;

   cv::Mat edges;
   cv::Canny(grayImage, edges, 50, 200);
   cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 5, 3);


   for (size_t i = 0; i < lines.size(); i++) {
      cv::Vec4i l = lines[i];
      cv::line(img_show, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 255, 0), 3, cv::LINE_AA);
   }

   std::vector<cv::Vec3f> circles;

   cv::HoughCircles(gauss, circles, cv::HOUGH_GRADIENT, 1, grayImage.rows / 4, 250, 100, 2, 150);

   for (size_t i = 0; i < circles.size(); i++) {
      cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      cv::circle(img_show, center, radius, cv::Scalar(0, 0, 255), 2, 8, 0);
   }

   cv::imshow("Image", image);
   cv::imshow("Image1", img_show);
   cv::waitKey(0);

}
