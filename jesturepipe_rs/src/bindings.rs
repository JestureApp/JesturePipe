use crate::error::{AbslError, AbslErrorType, Result};
use std::ffi::{c_char, c_int};

// Only ever used through a pointer.
enum _JesturePipe {}

enum _OutputStreamPoller {}

#[repr(C)]
struct Status {
    pub code: c_int,
    pub message: *const c_char,
}

mod raw {
    use std::ffi::{c_char, c_int};

    use super::{Status, _JesturePipe, _OutputStreamPoller};

    extern "C" {
        pub(super) fn fails() -> *const Status;

        pub(super) fn status_free(status: *const Status);

        pub(super) fn jesturepipe_new(
            palm_model_path: *const c_char,
            palm_model_len: c_int,
            hand_model_path: *const c_char,
            hand_model_len: c_int,
        ) -> *mut _JesturePipe;

        pub(super) fn jesturepipe_free(pipe: *mut _JesturePipe);

        pub(super) fn jesturepipe_initialize(pipe: *mut _JesturePipe) -> *const Status;

        pub(super) fn jesturepipe_start(
            pipe: *mut _JesturePipe,
            camera_index: c_int,
            num_hands: c_int,
        ) -> *const Status;

        pub(super) fn jesturepipe_stop(pipe: *mut _JesturePipe) -> *const Status;

        pub(super) fn jesturepipe_output_poller_new() -> *const _OutputStreamPoller;

        pub(super) fn jesturepipe_output_poller_free(poller: *const _OutputStreamPoller);

        pub(super) fn jesturepipe_add_output_poller(
            pipe: *mut _JesturePipe,
            stream_name: *const c_char,
            stream_name_len: c_int,
            poller: *const _OutputStreamPoller,
        ) -> *const Status;
    }
}

unsafe fn status_to_result(status: *const Status) -> Result<()> {
    let res: Result<()> = {
        if status.is_null() {
            panic!("status is null");
        }

        let code = (*status).code;

        if code == 0 {
            Ok(())
        } else {
            let error_type = AbslErrorType::from_code(code);
            let message = std::ffi::CStr::from_ptr((*status).message)
                .to_string_lossy()
                .to_string()
                .clone();

            Err(Box::new(AbslError {
                error_type,
                message,
            }))
        }
    };

    unsafe {
        raw::status_free(status);
    }

    res
}

#[allow(unused)]
pub fn fails() -> Result<()> {
    unsafe { status_to_result(raw::fails()) }
}

pub struct JesturePipe {
    ptr: *mut _JesturePipe,
    running: bool,
}

pub struct JesturePipeConfig {
    pub camera_index: i32,
    pub num_hands: i32,
}

impl JesturePipe {
    pub fn new<P>(palm_model_path: P, hand_model_path: P) -> Result<JesturePipe>
    where
        P: Into<Vec<u8>>,
    {
        let pipe = unsafe {
            let palm_model_path = std::ffi::CString::new(palm_model_path)?;
            let hand_model_path = std::ffi::CString::new(hand_model_path)?;

            raw::jesturepipe_new(
                palm_model_path.as_ptr(),
                palm_model_path.as_bytes().len() as i32,
                hand_model_path.as_ptr(),
                hand_model_path.as_bytes().len() as i32,
            )
        };

        if pipe.is_null() {
            panic!("Failed to create JesturePipe.");
        }

        unsafe { status_to_result(raw::jesturepipe_initialize(pipe)) }?;

        Ok(JesturePipe {
            ptr: pipe,
            running: false,
        })
    }

    pub fn start(&mut self, config: JesturePipeConfig) -> Result<()> {
        unsafe {
            status_to_result(raw::jesturepipe_start(
                self.ptr,
                config.camera_index,
                config.num_hands,
            ))
        }?;

        self.running = true;

        Ok(())
    }

    pub fn stop(&mut self) -> Result<()> {
        if !self.running {
            return Ok(());
        }

        self.running = false;
        unsafe { status_to_result(raw::jesturepipe_stop(self.ptr)) }
    }

    fn add_output_poller<S, T>(&self, stream_name: &str) -> Result<OutputStreamPoller<T>>
    where
        S: Into<Vec<u8>>,
    {
        let ptr = unsafe { raw::jesturepipe_output_poller_new() };

        if ptr.is_null() {
            panic!("Failed to create OutputStreamPoller.");
        }

        unsafe {
            let stream_name = std::ffi::CString::new(stream_name)?;

            status_to_result(raw::jesturepipe_add_output_poller(
                self.ptr,
                stream_name.as_ptr(),
                stream_name.as_bytes().len() as i32,
                ptr,
            ))?;
        }

        Ok(OutputStreamPoller {
            ptr,
            _phantom: std::marker::PhantomData,
        })
    }
}

impl Drop for JesturePipe {
    fn drop(&mut self) {
        self.stop().expect("Failed to stop JesturePipe.");

        unsafe {
            raw::jesturepipe_free(self.ptr);
        }
    }
}

pub struct OutputStreamPoller<T> {
    ptr: *const _OutputStreamPoller,
    _phantom: std::marker::PhantomData<T>,
}

impl<T> OutputStreamPoller<T> {}

impl<T> Drop for OutputStreamPoller<T> {
    fn drop(&mut self) {
        unsafe {
            raw::jesturepipe_output_poller_free(self.ptr);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    const PALM_MODEL_PATH: &str =
        "/home/storm/Workspace/Jesture/JesturePipe/jesturepipe_rs/data/palm_detection_lite.tflite";
    const HAND_MODEL_PATH: &str =
        "/home/storm/Workspace/Jesture/JesturePipe/jesturepipe_rs/data/hand_landmark_lite.tflite";

    #[test]
    fn test_fails() {
        let result = fails();
        assert!(result.is_err());
        let err = result.unwrap_err().downcast::<AbslError>().unwrap();

        assert_eq!(err.error_type, AbslErrorType::Internal);
        assert_eq!(err.message, "This is a test");
    }

    #[test]
    fn test_new() -> Result<()> {
        let mut pipe = JesturePipe::new(PALM_MODEL_PATH, HAND_MODEL_PATH)?;

        Ok(())
    }

    #[test]
    fn test_start_stop() -> Result<()> {
        let mut pipe = JesturePipe::new(PALM_MODEL_PATH, HAND_MODEL_PATH)?;

        pipe.start(JesturePipeConfig {
            camera_index: 0,
            num_hands: 1,
        })?;

        pipe.stop()?;

        Ok(())
    }
}
