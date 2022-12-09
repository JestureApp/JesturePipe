# JesturePipe Graph

The JesturePipe graph implements the pipeline for Jesture. In summary, the pipeline transforms the video frames from the camera into actions. 

The structure of the graph is as follows:

```mermaid
flowchart TD
    cam[\Camera\]
    hands[Hands]
    rec[Gesture Recognizer]
    act[Actions]

    cam --Video Frame--> hands
    hands --Hand Landmarks--> rec
    rec --Gesture Label--> act
```