#include "jesturepipe/gesture/recorder.h"
namespace jesturepipe {

constexpr double ANGLE_THRESH = 40; // 0.055;

Gesture FrameFilter(Gesture gesture) {
    double init_sum_index = 0;
    double init_sum_middle = 0;
    double init_sum_ring = 0;
    double init_sum_pinky = 0;
    double init_sum_thumb = 0;
    double init_sum_movement = 0;
    int num_frames = 0;
    int movement_counter = 0;
    for (GestureFrame frame : *gesture.frames) {
        init_sum_index += frame.hand_shape.index_direction;
        init_sum_middle += frame.hand_shape.middle_direction;
        init_sum_ring += frame.hand_shape.ring_direction;
        init_sum_pinky += frame.hand_shape.pinky_direction;
        init_sum_thumb += frame.hand_shape.thumb_direction;

        if (frame.movement_direction.has_value())
            movement_counter++;
            init_sum_movement += frame.movement_direction.value();
        num_frames++;
    }

    double init_avg_index = init_sum_index/num_frames;
    double init_avg_middle = init_sum_middle/num_frames;
    double init_avg_ring = init_sum_ring/num_frames;
    double init_avg_pinky = init_sum_pinky/num_frames;
    double init_avg_thumb = init_sum_thumb/num_frames;
    double init_avg_movement = init_sum_movement/movement_counter;

    int new_num_frames;
    movement_counter = 0;
    double new_sum_index = 0;
    double new_sum_middle = 0;
    double new_sum_ring = 0;
    double new_sum_pinky = 0;
    double new_sum_thumb = 0;
    double new_sum_movement = 0;

    for (GestureFrame frame : *gesture.frames) {
        double movement_diff;
        double index_diff = std::abs(frame.hand_shape.index_direction - init_avg_index);
        double middle_diff = std::abs(frame.hand_shape.middle_direction - init_avg_middle);
        double ring_diff = std::abs(frame.hand_shape.ring_direction - init_avg_ring);
        double pinky_diff = std::abs(frame.hand_shape.pinky_direction - init_avg_pinky);
        double thumb_diff = std::abs(frame.hand_shape.thumb_direction - init_avg_thumb);
        if (frame.movement_direction.has_value()) 
            movement_diff = std::abs(frame.movement_direction.value() - init_avg_movement);
        
        if (index_diff > ANGLE_THRESH || middle_diff > ANGLE_THRESH || ring_diff > ANGLE_THRESH || pinky_diff > ANGLE_THRESH || thumb_diff > ANGLE_THRESH)
            continue;
        if (frame.movement_direction.has_value() && movement_diff > ANGLE_THRESH)
            continue;
        
        new_sum_index += frame.hand_shape.index_direction;
        new_sum_middle += frame.hand_shape.middle_direction;
        new_sum_ring += frame.hand_shape.ring_direction;
        new_sum_pinky += frame.hand_shape.pinky_direction;
        new_sum_thumb += frame.hand_shape.thumb_direction;

          if (frame.movement_direction.has_value())
            movement_counter++;
            new_sum_movement += frame.movement_direction.value();
            
        new_num_frames++;
    }

    double new_avg_index = new_sum_index/new_num_frames;
    double new_avg_middle = new_sum_middle/new_num_frames;
    double new_avg_ring = new_sum_ring/new_num_frames;
    double new_avg_pinky = new_sum_pinky/new_num_frames;
    double new_avg_thumb = new_sum_thumb/new_num_frames;
    double new_avg_movement = new_sum_movement/movement_counter;
    std::cout << new_avg_index << std::endl;
    return Gesture(
        std::vector<GestureFrame>{GestureFrame{.hand_shape =
                                                   HandShape{
                                                       .index_direction = new_avg_index,
                                                       .middle_direction = new_avg_middle,
                                                       .ring_direction = new_avg_ring,
                                                       .pinky_direction = new_avg_pinky,
                                                       .thumb_direction = new_avg_thumb,
                                                   },
                                               .movement_direction = new_avg_movement}});
}
void GestureRecorder::AddFrame(GestureFrame frame) {

    gesture.frames->push_back(frame);
}

Gesture GestureRecorder::Finish() { 
    gesture = FrameFilter(gesture);
    return gesture; 
}

}  // namespace jesturepipe