#ifndef __H_JESTUREPIPE_BINDINGS__
#define __H_JESTUREPIPE_BINDINGS__

extern "C" {
typedef struct Status {
    int code;
    char* message;
} Status;

void status_free(Status* status);

Status* fails();

typedef struct JesturePipe JesturePipe;

JesturePipe* jesturepipe_new(const char* palm_model_path,
                             const int palm_model_len,
                             const char* hand_model_path,
                             const int hand_model_len);

void jesturepipe_free(JesturePipe* pipe);

Status* jesturepipe_initialize(JesturePipe* pipe);

Status* jesturepipe_start(JesturePipe* pipe, int camera_index, int num_hands);

Status* jesturepipe_stop(JesturePipe* pipe);

typedef struct OutputStreamPoller OutputStream;

OutputStreamPoller* jesturepipe_output_poller_new();

void jesturepipe_output_poller_free(OutputStreamPoller* poller);

Status* jesturepipe_add_output_poller(JesturePipe* pipe,
                                      const char* stream_name,
                                      int stream_name_len,
                                      OutputStreamPoller* output_poller);
}

#endif  // __H_JESTUREPIPE_BINDINGS__