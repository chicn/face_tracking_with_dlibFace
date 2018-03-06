#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/shape_predictor.h>
#include <dlib/opencv.h>

// #include "mtcnn/mtcnn.h"

#include "util/ElapsedTimer.hpp"


using namespace cv;
using namespace std;

//cv::Rect getMobileDispSize(cv::Mat &src);

int main(int argc, char **argv)
{


    dlib::shape_predictor shape;
    dlib::deserialize("/Users/chihiro/Programs/oss/dlib/shape_predictor_68_face_landmarks.dat") >> shape;

    // "BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN"
    Ptr<Tracker> tracker = Tracker::create("KCF");

    // Read video
    VideoCapture video(0);

    // Exit if video is not opened
    if(!video.isOpened()) return 1;

    // Read first frame
    Mat frame;
    bool ok = video.read(frame);

    //mtcnn faceDetector(frame.rows, frame.cols);

    auto faceDetector = dlib::get_frontal_face_detector();

    Rect2d bbox;
    bool hasBBox = false;

    // tracker->init(frame, bbox);

    //cv::Rect mobileWidowSize = getMobileDispSize(frame);

    auto redetect = [&] {
        dlib::cv_image<dlib::bgr_pixel> dlibImage(frame);
        auto dlibRects = faceDetector(dlibImage);
        if (dlibRects.size()) {
            bbox = Rect2d(dlibRects[0].left(), dlibRects[0].top(), dlibRects[0].width(), dlibRects[0].height());
            hasBBox = true;
        } else {
            hasBBox = false;
        }
    };

    int count = 0;
    for(;;) {

        video >> frame;
        resize(frame, frame, cv::Size(), 0.3, 0.3, CV_INTER_LINEAR);

        ElapsedTimer interval("Tracker");
        if (!hasBBox) {
            redetect();
            tracker->init(frame, bbox);
            rectangle(frame, bbox, Scalar(0,0,255), 2,8,0);
        } else if (count%10 == 0) {
            redetect();
            rectangle(frame, bbox, Scalar(0, 0, 255), 2, 8, 0);
        } else {
            bool ok = tracker->update(frame, bbox);
            rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
        }

        interval.end();

        //frame(mobileWidowSize);

        imshow("result", frame);
        int k = waitKey(1);
        if(k == 27)
        {
            break;
        }
        count++;
    }

    waitKey(0);
    frame.release();
    return 0;
}

//cv::Rect getMobileDispSize(cv::Mat &src) {
//    int h = 640;
//    int w = 360;
//    cv::Rect outRectSize;
//    outRectSize.height = h;
//    outRectSize.width = w;
//
//    outRectSize.x = int((w - src.cols) / 2);
//    outRectSize.y = int((h - src.rows) / 2);
//    return outRectSize;
//}