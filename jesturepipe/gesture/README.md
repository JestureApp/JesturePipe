# JesturePipe Gesture API

# Principals
In JesturePipe hand gestures are represented as an ordered list of "frames."

Each frame in a gesture should describe a general shape of the hand with possibility that the hand is moving. A frame should be able to describe an arbitrary number of video frames, and as such is (partially)independent of the time taken by the frame.

The primary purpose of this representation is so that gestures are flexible enough to be independent of the time spent performing the gesture and to allow for a sort of "soft" matching in which similar frames are equated.

Allowing a frame to represent movement also reduces the number of frames required to represent moving gestures.

# Note to contributors
Fundamental changes to the logic of the Recognizer, Recorder and Library are discouraged. The logic that describes what constitutes a gesture and how they are constructed from hand landmarks is contained implemented in [Gesture Objects](#gesture-objects) and the [Frame Constructor](#the-frame-constructor)

# Gesture Objects
`Gesture` Objects are essentially just a vector of `GestureFrame`s. Though it should be noted that a copy of a `Gesture` shares the same reference to the list of frames. This allows `Gesture`s to be cheaply copied, but any mutation to any copy of a `Gesture` is replicated across all copies. This is less than ideal and if the need arises `Gesture` could be reimplemented as a [COW](https://en.wikipedia.org/wiki/Copy-on-write).

Each `GestureFrame` object simply contains a `HandShape` to represent that a shape of the hand and optional `movement_direction`.

## Comparison
A very important part of the API are the comparators `HandShape::Comparator` and `GestureFrame::Comparator`. They define the equality operation used to compare `HandShape`s and `GestureFrame`s respectively when matching gestures.

Any change to the representation of `HandShape` or `GestureFrame` requires changing the logic in their respective comparator.

# The Frame Constructor
The frame constructor is reasonable for creating `GestureFrame`s from `NormalizedHandLandmarkList`s that are produced by the hands subgraph.

Any changes to representation of `GestureFrame` will most likely require updates to the frame constructor.

```
TODO: Description of the algorithm used.
```

# The Gesture Library
The `GestureLibrary` is a thread safe collection of `Gesture`s that maps gesture ids to `Gesture`s. 

The API for `GestureLibrary` is still a WIP, but it contains some utilities for
thread safe reading and writing. 

# The Gesture Recognizer
```
TODO: Description of the algorithm used.
```

# The Gesture Recorder
```
TODO: Description of the algorithm used.
```