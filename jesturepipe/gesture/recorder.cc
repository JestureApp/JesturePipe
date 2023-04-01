#include "jesturepipe/gesture/recorder.h"
namespace jesturepipe {

constexpr double ANGLE_THRESH = 40; // 0.055;

void GestureRecorder::AddFrame(GestureFrame frame) {

    //   for (GestureFrame frame : *gesture.frames) {
    //     std::cout << "GestureFrame{" << std::endl;
    //     std::cout << "\tHandShape{" << std::endl;
    //     std::cout << "\t\tindex_direction: " << frame.hand_shape.index_direction
    //               << std::endl;
    //     std::cout << "\t\tmiddle_direction: "
    //               << frame.hand_shape.middle_direction << std::endl;
    //     std::cout << "\t\tring_direction: " << frame.hand_shape.ring_direction
    //               << std::endl;
    //     std::cout << "\t\tpinky_direction: " << frame.hand_shape.pinky_direction
    //               << std::endl;
    //     std::cout << "\t\tthumb_direction: " << frame.hand_shape.thumb_direction
    //               << std::endl;
    //     std::cout << "\t}" << std::endl;

    //     if (frame.movement_direction.has_value())
    //         std::cout << "movement_direction: "
    //                   << frame.movement_direction.value() << std::endl;

    //     std::cout << "}" << std::endl;
    // }

    gesture.frames->push_back(frame);
}

Gesture GestureRecorder::Finish() { 
    return gesture; 
}

}  // namespace jesturepipe