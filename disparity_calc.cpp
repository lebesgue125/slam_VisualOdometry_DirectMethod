#include <opencv2/opencv.hpp>
#include <string>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <chrono>
using namespace std;
using namespace cv;


string file_1 = "left.png";  // first image
string file_2 = "right.png";  // second image
string disparity_file = "disparity.png";

int main(int argc, char **argv) {

    // images, note they are CV_8UC1, not CV_8UC3
    Mat img1 = imread(file_1, 0);
    Mat img2 = imread(file_2, 0);
    Mat disparity_img = imread(disparity_file, 0);


    //cout<<disparity_img<<endl;
    //cout<<disparity_img.rows<<"@@@@@@@"<<disparity_img.cols<<endl;

    // key points, using GFTT here.
    vector<KeyPoint> kp1;
    Ptr<GFTTDetector> detector = GFTTDetector::create(500, 0.01, 20); // maximum 500 keypoints
    detector->detect(img1, kp1);



    // use opencv's flow
    vector<Point2f> pt1, pt2;
    for (auto &kp: kp1) pt1.push_back(kp.pt);
    vector<uchar> status;
    vector<float> error;
    cv::calcOpticalFlowPyrLK(img1, img2, pt1, pt2, status, error);
    //cv::calcOpticalFlowPyrLK(img1, img2, pt1, pt2, status, error, cv::Size(8, 8));
   cout<<"size1="<<pt1.size()<<endl;


/*    Mat img2_CV;
    cv::cvtColor(img2, img2_CV, CV_GRAY2BGR);
    for (int i = 0; i < pt2.size(); i++) {
        if (status[i]) {
            cv::circle(img2_CV, pt2[i], 2, cv::Scalar(0, 250, 0), 2);
            cv::line(img2_CV, pt1[i], pt2[i], cv::Scalar(0, 250, 0));
        }
    }

    cv::imshow("tracked by opencv", img2_CV);
    cv::waitKey(0);*/

   float dis_sum=0;
    for (size_t i = 0; i < pt1.size(); i++) {


        float dx=abs(pt1[i].x-pt2[i].x);
        float disparity = disparity_img.at<uchar>(pt1[i].y,pt1[i].x);
        cout<<i<<" dis_calc_byFlow="<<dx<<endl;
        cout<<i<<" dis_from_disparity="<<disparity<<endl;
        dis_sum=abs(dx-disparity);


    }
    cout<<"total_dis="<<dis_sum<<endl;



    return 0;
}


